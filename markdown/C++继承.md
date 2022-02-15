# C++继承

## 一.实例

```c++
// tabtenn1.h -- a table-tennis base class
#ifndef TABTENN1_H_
#define TABTENN1_H_
#include <string>
using std::string;
// simple base class
class TableTennisPlayer
{
private:
    string firstname;
    string lastname;
    bool hasTable;
public:
    TableTennisPlayer (const string & fn = "none",
                       const string & ln = "none", bool ht = false);
    void Name() const;
    bool HasTable() const { return hasTable; };
    void ResetTable(bool v) { hasTable = v; };
};

// simple derived class
class RatedPlayer : public TableTennisPlayer
{
private:
    unsigned int rating;
public:
    RatedPlayer (unsigned int r = 0, const string & fn = "none",
                 const string & ln = "none", bool ht = false);
    RatedPlayer(unsigned int r, const TableTennisPlayer & tp);
    unsigned int Rating() const { return rating; }
    void ResetRating (unsigned int r) {rating = r;}
};

#endif

```



```c++
//tabtenn1.cpp -- simple base-class methods
#include "tabtenn1.h"
#include <iostream>

TableTennisPlayer::TableTennisPlayer (const string & fn, 
    const string & ln, bool ht) : firstname(fn),
	    lastname(ln), hasTable(ht) {}
    
void TableTennisPlayer::Name() const
{
    std::cout << lastname << ", " << firstname;
}

// RatedPlayer methods
RatedPlayer::RatedPlayer(unsigned int r, const string & fn,
     const string & ln, bool ht) : TableTennisPlayer(fn, ln, ht)
{
    rating = r;
}

RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer & tp)
    : TableTennisPlayer(tp), rating(r)
{
}

```

### 1.公有派生

```c++
class RatedPlayer : public TableTennisPlayer
{
    ...
}
```

冒号指出RatedPlayer类的基类是TableTennisPlayer类。上述public表明tableTennisPlayer是一个共有基类，这被称为共有派生

**特点：基类的共有成员将成为派生类的共有成员；基类的私有部分将成为派生类的一部分，但只能通过基类的共有方法和保护方法访问**

* **派生类对象存储了基类的数据成员（派生类继承了基类的实现）**
* **派生类对象可以使用基类的方法（派生类继承了基类的借口）**

RatedPlayer对象科技存储运动员的姓名以及是否有桌球。另外，RatedPlayer对象还可以使用TableTennisPlayer类的Name()、hasTable()、TesetTable()方法

派生类需要添加的东西：

* **派生类需要添加自己的构造函数**
* **派生类可以根据需要添加额外的数据成员和成员函数**

### 2.构造函数：访问权限的考虑

派生类不能直接访问基类的私有成员，而必须通过基类的方法进行访问。例如上面代码中，RatedPlayer构造函数不能直接设置继承的成员（firstname、lastname、hasTable），必须使用基类的共有方法（派生类的构造函数必须使用基类的构造函数）来访问基类的私有成员。

```c++
RatedPlayer::RatedPlaer(unsigned int r, const string & fn,
	const string &ln, bool ht) : TableTennisPlayer(fn,ln,ht)//TableTennisPlayer(fn,ln,ht)是初始化成员列表
{
	rating = r;
}
//实例化
RatedPlayer rplayer1(1140,"Mallory","Duck",true);
```

上述代码是，使用RatedPlayer构造函数把实参"Mallory","Duck",true赋给形参fn、ln、ht，然后将这些形参作为实参传递给TableTennisPlayer构造函数，后者将创建一个嵌套TableTennisPlayer对象，并将"Mallory","Duck",true存储在该对象中。然后程序将进入RatedPlayer构造函数，完成RatedPlayer对象的创建。

### 3.默认的基类构造函数

```c++
RatedPlayer::RatedPlaer(unsigned int r, const string & fn,
	const string &ln, bool ht)
{
    rating = r;
}
```

程序没有调用基类的构造函数，但是又必须先创建基类对象，所以程序将使用默认的基类构造函数，上述代码与下面的等效

```c++
RatedPlayer::RatedPlaer(unsigned int r, const string & fn,
	const string &ln, bool ht)// : TableTennisPlayer()
{
    rating = r;
}
```

### 4.复制构造函数

```c++
RatedPlayer::RatedPlaer(unsigned int r, const TableTennisPlayer &tp)
    :TableTennisPlayer(tp)
{
	rating = r;        
}
```

这里将TableTennisPlayer的信息传递给了TableTennisPlayer构造函数

````c++
TableTennisPlayer(tp)
````

由于tp的类型是TableTennisPlayer &，因此将调用基类的复制构造函数。基类没有定义复制构造函数，编译器将自动生成一个。在这种情况下将执行成员复制的隐式复制构造函数式合适的（这个类没有使用动态内存分配）。

上述代码也可以换成一下形式

```C++
RatedPlayer::RatedPlaer(unsigned int r, const TableTennisPlayer &tp)
    :TableTennisPlayer(tp),rating(r)
{
}
```

* **首先创建基类对象**
* **派生类构造函数应通过成员初始化列表将基类信息传递给基类构造函数**
* **派生类构造函数应初始化派生类新增成员**
* **释放派生类对象过程与创建过程相反，首先是执行派生类的析构函数然后自动调用基类的析构函数**

### 5.派生类和基类的关系

* **派生类对象可以使用基类的方法，条件是该方法不能是私有的**
* **基类指针可以在不进行显示类型转换的情况下指向派生类**
* **基类引用可以在不进行显示类型转换的情况下引用派生类**
* **上述特性反过来是不允许的，因为没有意义**

```c++
RatedPlayer rplayer(1140,"Mollory","Duck",true);
TableTennisPlayer & rt = rplayer;
TableTennisPlayer * pt = rplayer;
rt.Name();
pt->Name();
```



## 二.多态共有继承

如果希望一个方法在派生类和基类中的行为是不同的，该怎么处理

* **在派生类中创建新的方法**
* **使用虚方法**

```c++
// brass.h  -- bank account classes
#ifndef BRASS_H_
#define BRASS_H_
#include <string>
// Brass Account Class
class Brass
{
private:
    std::string fullName;
    long acctNum;
    double balance;
public:
    Brass(const std::string & s = "Nullbody", long an = -1,
                double bal = 0.0);
    void Deposit(double amt);
    virtual void Withdraw(double amt);
    double Balance() const;
    virtual void ViewAcct() const;
    virtual ~Brass() {}
};

//Brass Plus Account Class
class BrassPlus : public Brass
{
private:
    double maxLoan;
    double rate;
    double owesBank;
public:
    BrassPlus(const std::string & s = "Nullbody", long an = -1,
            double bal = 0.0, double ml = 500,
            double r = 0.11125);
    BrassPlus(const Brass & ba, double ml = 500, 
		                        double r = 0.11125);
    virtual void ViewAcct()const;
    virtual void Withdraw(double amt);
    void ResetMax(double m) { maxLoan = m; }
    void ResetRate(double r) { rate = r; };
    void ResetOwes() { owesBank = 0; }
};

#endif

```

```c++
// brass.cpp -- bank account class methods
#include <iostream>
#include "brass.h"
using std::cout;
using std::endl;
using std::string;

// formatting stuff
typedef std::ios_base::fmtflags format;
typedef std::streamsize precis;
format setFormat();
void restore(format f, precis p);

// Brass methods

Brass::Brass(const string & s, long an, double bal)
{
    fullName = s;
    acctNum = an;
    balance = bal;
}

void Brass::Deposit(double amt)
{
    if (amt < 0)
        cout << "Negative deposit not allowed; "
             << "deposit is cancelled.\n";
    else
        balance += amt;
}

void Brass::Withdraw(double amt)
{
    // set up ###.## format
    format initialState = setFormat();
    precis prec = cout.precision(2);

    if (amt < 0)
        cout << "Withdrawal amount must be positive; "

             << "withdrawal canceled.\n";
    else if (amt <= balance)
        balance -= amt;
    else
        cout << "Withdrawal amount of $" << amt
             << " exceeds your balance.\n"
             << "Withdrawal canceled.\n";
    restore(initialState, prec);
}
double Brass::Balance() const
{
    return balance;
}

void Brass::ViewAcct() const
{
     // set up ###.## format
    format initialState = setFormat();
    precis prec = cout.precision(2);
    cout << "Client: " << fullName << endl;
    cout << "Account Number: " << acctNum << endl;
    cout << "Balance: $" << balance << endl;
    restore(initialState, prec); // Restore original format
}

// BrassPlus Methods
BrassPlus::BrassPlus(const string & s, long an, double bal,
           double ml, double r) : Brass(s, an, bal)
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

BrassPlus::BrassPlus(const Brass & ba, double ml, double r)
           : Brass(ba)   // uses implicit copy constructor
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

// redefine how ViewAcct() works
void BrassPlus::ViewAcct() const
{
    // set up ###.## format
    format initialState = setFormat();
    precis prec = cout.precision(2);

    Brass::ViewAcct();   // display base portion
    cout << "Maximum loan: $" << maxLoan << endl;
    cout << "Owed to bank: $" << owesBank << endl;
    cout.precision(3);  // ###.### format
    cout << "Loan Rate: " << 100 * rate << "%\n";
    restore(initialState, prec); 
}

// redefine how Withdraw() works
void BrassPlus::Withdraw(double amt)
{
    // set up ###.## format
    format initialState = setFormat();
    precis prec = cout.precision(2);

    double bal = Balance();
    if (amt <= bal)
        Brass::Withdraw(amt);
    else if ( amt <= bal + maxLoan - owesBank)
    {
        double advance = amt - bal;
        owesBank += advance * (1.0 + rate);
        cout << "Bank advance: $" << advance << endl;
        cout << "Finance charge: $" << advance * rate << endl;
        Deposit(advance);
        Brass::Withdraw(amt);
    }
    else
        cout << "Credit limit exceeded. Transaction cancelled.\n";
    restore(initialState, prec); 
}

format setFormat()
{
    // set up ###.## format
    return cout.setf(std::ios_base::fixed, 
                std::ios_base::floatfield);
} 

void restore(format f, precis p)
{
    cout.setf(f, std::ios_base::floatfield);
    cout.precision(p);
}

```

* **BrassPlus类在Brass类的基础上添加了3个私有数据成员和3个共有成员函数**
* **BrassPlus类和Brass类都申明了ViewAcct()和Withdraw()方法，但是BrassPlus对象和Brass对象的这些方法的行为是不同的**
* **Brass类在声明ViewAcct()和Withdraw()时使用了关键字virtual(虚方法)**
* **Brass还声明了虚析构函数**

### 1.多态的使用

#### 1.1实例1

```c++
Brass dom("Dominic Banker", 111224,4183.45);
BrassPlus dot("Dorothy Banker", 12118,2592.00);
dom.ViewAcct();//use Brass::ViewAcct()
dot.ViewAcct();//use BrassPlus::ViewAcct()
```

#### 1.2实例2

* 如果ViewAcct()方法**没有声明**为virtual

```c++
Brass dom("Dominic Banker", 111224,4183.45);
BrassPlus dot("Dorothy Banker", 12118,2592.00);
Brass & b1_ref = dom;
Brass & b2_ref = dot;
b1_ref.ViewAcct();//use Brass::ViewAcct()
b2_ref.ViewAcct();//use Brass::ViewAcct()
```

引用变量的类型都是Brass，所以选择Brass::ViewAcct()，使用指针也是一样的情况；

#### 1.3实例3

* 如果ViewAcct()方法**声明**为virtual

```c++
Brass dom("Dominic Banker", 111224,4183.45);
BrassPlus dot("Dorothy Banker", 12118,2592.00);
Brass & b1_ref = dom;
Brass & b2_ref = dot;
b1_ref.ViewAcct();//use Brass::ViewAcct()
b2_ref.ViewAcct();//use BrassPlus::ViewAcct()
```

使用virtual，程序将根据引用类型或指针指向的对象类型来选择方法。上例中，b1_ref引用dom是Brass类型，所以调用的是Brass::ViewAcct()，b2_ref引用dot是BrassPlus类型，所以调用的是BrassPlus::ViewAcct()



* **基类声明了一个虚的析构函数。这样做是为了确保释放派生类对象时，按正确的顺序调用析构函数**

#### 1.4在派生类中使用派生类共有方法

```c++
void BrassPlus::ViewAcct() const
{
    Brass::ViewAcct(); // display base portion
    cout << "Maximum loan: $" << maxLoan << endl;
    ...
}
```

BrassPlus::ViewAcct()显示新增的BrassPlus成员，并调用基类方法Brass::ViewAcct()来显示基类数据成员。**在派生类方法中，标准技术是使用作用域解析运算符来调用积累方法**。

### 2.静态联编和动态联编

* **函数名联编**：将源代码中的函数调用解释为执行特定的函数代码块
* **静态联编**：在编译过程中进行联编
* **动态联编**：编译器必须生成能够在程序运行时选择正确的虚方法
* **向上强制转换**：将派生类引用或指针转换为基类引用或指针
* **向下强制转换**：将基类引用或指针转换为派生类引用或指针

### 3.虚函数注意事项

* **在基类方法的声明中使用关键字virtual可使该方法在基类以及所有的派生类（包括从派生类派生出来的类）中是虚的**
* **如果使用指向对象的引用或指针来调用虚方法，程序将使用为对象类型定义的方法，而不适用引用或指针类型定义的方法**
* **如果定义的类将被作为基类，则应将那些要在派生类中重新定义的类方法声明为虚的**

#### 3.1构造函数不能使虚函数

派生类有自己的构造函数，并不会继承基类的构造函数，所以没必要将构造函数声明为虚

#### 3.2析构函数

* **析构函数应该为虚函数，除非类不用做基类**
* **给类定义一个虚的析构函数并非错误，即使这个类**



