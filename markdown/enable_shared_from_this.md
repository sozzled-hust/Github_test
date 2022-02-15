# std::enable_shared_from_this的原理及意义

enable_shared_from_this是一个模板类，定义于头文件\<memory\>，其原型为：

```c++
template< class T > class enable_shared_from_this;
```

 std::enable_shared_from_this 能让一个对象（假设其名为 t ，且已被一个 std::shared_ptr 对象 pt 管理）**安全地生成其他额外的 std::shared_ptr 实例**（假设名为 pt1, pt2, ... ） ，它们与 pt 共享对象 t 的所有权。

若一个类 T 继承 std::enable_shared_from_this\<T> ，则会为**该类 T 提供成员函数**： shared_from_this 。 当 T 类型对象 t 被一个为名为 pt 的 std::shared_ptr\<T> 类对象管理时，调用 T::shared_from_this 成员函数，将会返回一个新的 std::shared_ptr\<T> 对象，它与 pt 共享 t 的所有权。

## 一.使用场合

 当类A被share_ptr管理，且在类A的成员函数里需要把当前类对象作为参数传给其他函数时，就需要传递一个指向自身的share_ptr。

### 1.为何不直接传递this指针

使用智能指针的初衷就是为了方便资源管理，如果在某些地方使用智能指针，某些地方使用原始指针，很容易破坏智能指针的语义，从而产生各种错误。

### 2.可以直接传递share_ptr\<this>么？

答案是不能，因为这样会造成2个非共享的share_ptr指向同一个对象，未增加引用计数导对象被析构两次，例如：

```c++
#include <memory>
#include <iostream>
 
class Bad
{
public:
    std::shared_ptr<Bad> getptr() {
        return std::shared_ptr<Bad>(this);
    }
~Bad() { 
    std::cout << "Bad::~Bad() called" << std::endl; 
}
};
 
int main()
{
    // 错误的示例，每个shared_ptr都认为自己是对象仅有的所有者
    std::shared_ptr<Bad> bp1(new Bad());
    std::shared_ptr<Bad> bp2 = bp1->getptr();
    // 打印bp1和bp2的引用计数
    std::cout << "bp1.use_count() = " << bp1.use_count() << std::endl;
    std::cout << "bp2.use_count() = " << bp2.use_count() << std::endl;
} // Bad 对象将会被删除两次
```

输出结果如下

```shell
bp1.use_count() = 1
bp2.use_count() = 1
Bad::~Bad() called
Bad::~Bad() called
free(): double free detected in tcache 2
已放弃 (核心已转储)
```

正确的实现如下：

```C++
#include <memory>
#include <iostream>
 
struct Good : std::enable_shared_from_this<Good> // 注意：继承
{
public:
    std::shared_ptr<Good> getptr() {
    return shared_from_this();
}
~Good() { 
    std::cout << "Good::~Good() called" << std::endl;
}
};
 
int main()
{
// 大括号用于限制作用域，这样智能指针就能在system("pause")之前析构
    {
        std::shared_ptr<Good> gp1(new Good());
        std::cout << "befor: gp1.use_count() = " << gp1.use_count() << std::endl;
        std::shared_ptr<Good> gp2 = gp1->getptr();
        // 打印gp1和gp2的引用计数
        std::cout << "after: gp1.use_count() = " << gp1.use_count() << std::endl;
        std::cout << "gp2.use_count() = " << gp2.use_count() << std::endl;
    }
    // system("pause");
    return 0;
}
#endif
```

输出如下：

```
befor: gp1.use_count() = 1
after: gp1.use_count() = 2
gp2.use_count() = 2
Good::~Good() called
```

## 二.为何会出现这种使用场合

因为在异步调用中，存在一个保活机制，异步函数执行的时间点我们是无法确定的，然而异步函数可能会使用到异步调用之前就存在的变量。为了保证该变量在异步函数执期间一直有效，我们可以传递一个指向自身的share_ptr给异步函数，这样在异步函数执行期间share_ptr所管理的对象就不会析构，所使用的变量也会一直有效了（保活）。

**另一篇文章：**
首先看cppreference的解释：

```markdown
std::enable_shared_from_this allows an object t that is currently managed by a std::shared_ptr named pt to safely generate additional std::shared_ptr instances pt1, pt2, ... that all share ownership of t with pt.Publicly inheriting from std::enable_shared_from_this provides the type T with a member function shared_from_this. If an object t of type T is managed by a std::shared_ptr named pt, then calling T::shared_from_this will return a new std::shared_ptr that shares ownership of t with pt
```

意思就是说，如果一个T类型的对象t，是被std::shared_ptr管理的，且类型T继承自std::enable_shared_from_this，那么T就有个shared_from_this的成员函数，这个函数返回一个新的std::shared_ptr的对象，也指向对象t。

那么这个特性的应用场景是什么呢？一个主要的场景是保证异步回调函数中操作的对象仍然有效。比如有这样一个类：

```c++
class Foo
{
public:
	void Bar(std::function<void(Foo*)> p_fnCallback)
	{
		//async call p_fnCallback with this
	}
};
```

Foo::Bar接受一个函数对象，这个对象需要一个Foo*指针，其实要的就是Foo::Bar的this指针，但是这个回调是异步的，也就是说可能在调用这个回调函数时，this指向的Foo对象已经提前析构了。这时候，std::enable_shared_from_this就派上用场了。修改后如下：

```c++
class Foo : public std::enable_shared_from_this<Foo>
{
public:
	void Bar(std::function<void(std::shared_ptr<Foo>)> p_fnCallback)
	{
		std::shared_ptr<Foo> pFoo = shared_from_this();
		//async call p_fnCallback with pFoo
	}
};
```

这样就可以保证异步回调时，Foo对象仍然有效。

注意到cppreference中说道，必须要是std::shared_ptr管理的对象，调用shared_from_this才是有效的，为什么呢？这个就需要看看std::enable_shared_from_this的实现原理了：

std::enable_shared_from_this\<T> 有一个std::weak_ptr\<T>的成员，实际上在构造std::enable_shared_from_this\<T>时，并没有初始化std::weak_ptr<T>成员，而是在用这个std::enable_shared_from_this\<T>去构造std::shared_ptr的时候，去构造并初始化这个std::weak_ptr\<T>成员。所以这也就是为什么cppreference中说的这个对象必须是std::shared_ptr管理的，因为这个对象不是通过std::shared_ptr来管理，那么std::weak_ptr是未初始化的，无法通过其提升为std::shared_ptr对象



