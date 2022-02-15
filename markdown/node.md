# 数据结构｜单链表操作：增删改查、合并、逆置，与数组的转换

链表，通过节点中的指针链来建立节点之间的联系。

```c
struct node {
    int num;
    struct node *next;
};
```

或者进一步做类型定义：

```c
typedef struct node {
    int num;
    struct node *next;
} Node, *NodePtr;
```

![数据结构｜单链表操作：增删改查、合并、逆置，与数组的转换](https://p6.toutiaoimg.com/origin/tos-cn-i-qvj2lq49k0/905985e8f5064adeaa5d0f67921c8b4d?from=pc)

链表求长度：

```c
int length(NodePtr top) {
    int n = 0;
    NodePtr curr = top;
    while (curr != NULL) {
        n++;
        curr = curr -> next;
    }
    return n;
}
```

查找节点：

```c
NodePtr searchList(NodePtr top,int num)
{
    NodePtr prev = top->next;
    while(prev!=NULL && prev->num != num)
        prev = prev->next;
            return prev;
}
```

获得最后一个节点：

```c
NodePtr getLast(NodePtr top) {
    if (top == NULL) return NULL;
    while (top -> next != NULL)
        top = top -> next;
    return top;
}
```

在堆中新建一个节点：

```c
NodePtr makeNode(int n) {
    NodePtr np = (NodePtr) malloc(sizeof (Node));
    np -> num = n;
    np -> next = NULL;
    return np;
}
```

输出链表的每个节点：

```c
void printList(NodePtr np) {
    while (np != NULL) { // as long as there's a node
        printf("%d\n", np -> num);
        np = np -> next; // go on to the next node
    }
} 
```

插入节点：

![数据结构｜单链表操作：增删改查、合并、逆置，与数组的转换](https://p6.toutiaoimg.com/origin/tos-cn-i-qvj2lq49k0/3d87333d2a564314a1f1abe1052f52d1?from=pc)

```c
#include <stdio.h>
#include <malloc.h>

typedef struct node {
    int num;
    struct node *next;
} Node, *NodePtr;

NodePtr createList()                  // 使用头节点
{ 
    NodePtr top = (NodePtr)malloc(sizeof(Node));
    if(top==NULL)
    {
        printf("malloc failed!\n");
        return top;
    }
    top->num = 0;  // 也可以用来存储链表长度
    top->next = NULL;
    return top;
}

NodePtr makeNode(int n) {
    NodePtr np = (NodePtr) malloc(sizeof (Node));
    if(np==NULL)
    {
        printf("malloc failed!\n");
        return np;
    }
    np -> num = n;
    np -> next = NULL;
    return np;
}

int insertListFromHead(NodePtr top,int n) {

    NodePtr np = makeNode(n);
    if(np==NULL)
        return -1;
    np->next = top->next;
    top->next = np;
    return 0;
}

NodePtr searchList(NodePtr top,int num)
{
    NodePtr prev = top->next;
    while(prev!=NULL && prev->num != num)
        prev = prev->next;
            return prev;
}

void insertListFromPrev(NodePtr top,int PrevNum,int n) {
    NodePtr prev = searchList(top,PrevNum);
    if(prev!=NULL){
        NodePtr np = makeNode(n);
        np->next = prev->next;
        prev->next = np;
    }
}

void printList(NodePtr top) {
    NodePtr curr = top->next;
    while (curr != NULL) { // as long as there's a node
        printf("%d ", curr -> num);
        curr = curr -> next; // go on to the next node
    }
    printf("\n");
} 

void destroyList(NodePtr* top)
{
    NodePtr next = (*top)->next;
    while(next!=NULL)
    {
        free(*top);
        *top = next;
        next = next->next;
    }
    free(*top);
    *top = NULL;
}

int main()
{
    NodePtr top = createList();
    int arr[] = {15,23,36,52};
    int n = sizeof arr / sizeof *arr;
    for(int i=n-1;i>=0;i--)
        insertListFromHead(top,arr[i]);
    printList(top);
    insertListFromPrev(top,23,30);
    printList(top);
    destroyList(&top);
    getchar();
    return 0;
}
/*
15 23 36 52
15 23 30 36 52
*/
```

删除节点：

![数据结构｜单链表操作：增删改查、合并、逆置，与数组的转换](https://p6.toutiaoimg.com/origin/tos-cn-i-qvj2lq49k0/f2b33a12745e4ba5bf9a65be43bb450e?from=pc)

demo:

```c
#include <stdio.h>
#include <malloc.h>

typedef struct node {
    int num;
    struct node *next;
} Node, *NodePtr;

NodePtr createList()                  // 使用头节点
{ 
    NodePtr top = (NodePtr)malloc(sizeof(Node));
    if(top==NULL)
    {
        printf("malloc failed!\n");
        return top;
    }
    top->num = 0;  // 也可以用来存储链表长度
    top->next = NULL;
    return top;
}

NodePtr makeNode(int n) {
    NodePtr np = (NodePtr) malloc(sizeof (Node));
    if(np==NULL)
    {
        printf("malloc failed!\n");
        return np;
    }
    np -> num = n;
    np -> next = NULL;
    return np;
}

void insertListFromHead(NodePtr top,int n) 
{  
    NodePtr np = makeNode(n);
    np->next = top->next;
    top->next = np;
}

NodePtr searchListPrev(NodePtr top,int num)
{
    NodePtr prev = top->next;
    NodePtr curr = NULL;
    if(prev!=NULL)
        curr = prev->next;
    while(curr!=NULL && curr->num != num)
    {
        prev = curr;
        curr = prev->next;
    }
    return prev;
}

void deleteFromPrev(NodePtr top,int n) {
    NodePtr prev = searchListPrev(top,n);
    NodePtr curr = prev->next;
    if(prev!=NULL){
        prev->next = curr->next;
        if(curr!=NULL)
            free(curr);
    }
}

void printList(NodePtr top) {
    NodePtr curr = top->next;
    while (curr != NULL) { // as long as there's a node
        printf("%d ", curr -> num);
        curr = curr -> next; // go on to the next node
    }
    printf("\n");
} 

void destroyList(NodePtr* top)
{
    NodePtr next = (*top)->next;
    while(next!=NULL)
    {
        free(*top);
        *top = next;
        next = next->next;
    }
    free(*top);
    *top = NULL;
}

int main()
{
    NodePtr top = createList();
    int arr[] = {23,52,15,36};
    int n = sizeof arr / sizeof *arr;
    for(int i=n-1;i>=0;i--)
        insertListFromHead(top,arr[i]);
    printList(top);
    deleteFromPrev(top,15);
    printList(top);
    destroyList(&top);
    getchar();
    return 0;
}
/*
23 52 15 36
23 52 36
*/
```

链表有序插入结点：

```c
#include <stdio.h>
#include <malloc.h>

typedef struct node {
    int num;
    struct node *next;
} Node, *NodePtr;

NodePtr createList()                  // 使用头节点
{ 
    NodePtr top = (NodePtr)malloc(sizeof(Node));
    if(top==NULL)
    {
        printf("malloc failed!\n");
        return top;
    }
    top->num = 0;  // 也可以用来存储链表长度
    top->next = NULL;
    return top;
}

NodePtr makeNode(int n) {
    NodePtr np = (NodePtr) malloc(sizeof (Node));
    if(np==NULL)
    {
        printf("malloc failed!\n");
        return np;
    }
    np -> num = n;
    np -> next = NULL;
    return np;
}

NodePtr addInPlace(NodePtr top, int n) {
    // This functions inserts n in its ordered position in a (possibly empty)
    // list pointed to by top, and returns a pointer to the new list
    NodePtr np, curr, prev, makeNode(int);
    np = makeNode(n);
    prev = NULL;
    curr = top;
    while (curr != NULL && n > curr -> num) {
        prev = curr;
        curr = curr -> next;
    }
    if (prev == NULL) { //new number must be added at the top
        np -> next = top;
        return np; //the top of the list has changed to the new node
    }
    np -> next = curr;
    prev -> next = np;
    return top; //the top of the list has not changed
}

NodePtr searchList(NodePtr top,int num)
{
    NodePtr prev = top->next;
    while(prev!=NULL && prev->num != num)
        prev = prev->next;
            return prev;
}

void printList(NodePtr top) {
    NodePtr curr = top->next;
    while (curr != NULL) { // as long as there's a node
        printf("%d ", curr -> num);
        curr = curr -> next; // go on to the next node
    }
    printf("\n");
} 

void destroyList(NodePtr* top)
{
    NodePtr next = (*top)->next;
    while(next!=NULL)
    {
        free(*top);
        *top = next;
        next = next->next;
    }
    free(*top);
    *top = NULL;
}

int main()
{
    NodePtr top = createList();
    int arr[] = {36,15,52,23};
    int n = sizeof arr / sizeof *arr;
    for(int i=n-1;i>=0;i--)
        addInPlace(top,arr[i]);
    printList(top);
        addInPlace(top,30);
    printList(top);
    destroyList(&top);
    getchar();
    return 0;
}
/*
15 23 36 52
15 23 30 36 52
*/
```

链表节点更新：

```c
void update(NodePtr top,int oldVal,int newVal)
{
    NodePtr curr = top->next;
    while(curr!=NULL){
        if(curr->num == oldVal)
            curr->num = newVal;
        curr = curr->next;
    }
}
```

链表逆置：

```c
void reverse(NodePtr top)
{
    NodePtr p,q;
    p=top->next;
    top->next = NULL;

    while(p) //top(固定),q后p前，q前插，q、p不断前移
    {
        q=p;
        p=p->next;
        q->next = top->next; // 一开始top->next=NULL
        top->next = q;
    }
}
```

链表数据存储到数组：

```c
void list2arr(NodePtr top,int *saveLL,int size)
{
    int n = 0;
    while (top != NULL & n < size) {
        saveLL[n++] = top -> num;
        top = top -> next;
    }
}
```

链表和数组对比：

|                                                                                         |                                                                                                     |
| --------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------- |
| Array                                                                                   | Linked List                                                                                         |
| Direct access to any element                                                            | Must traverse list to get to element                                                                |
| If unsorted, sequential search                                                          | If unsorted, sequential search                                                                      |
| If sorted, binary search                                                                | If sorted, sequential search                                                                        |
| Easy-to-insert item at the tail of the list                                             | Easy to insert item anywhere in the list                                                            |
| Must move items to insert anywhere but the tail                                         | Easy to insert item anywhere in the list                                                            |
| Deletion (except the last one) requires items to be moved                               | Deletion of any item is easy                                                                        |
| Need to move items when adding a new item to a sorted list                              | Adding a new item to a sorted linked list is easy                                                   |
| Can use binary search on a sorted list to find the position at which to insert new item | Must use sequential search to find the position at which to insert new item in a sorted linked list |

合并有序链表：

![数据结构｜单链表操作：增删改查、合并、逆置，与数组的转换](https://p6.toutiaoimg.com/origin/tos-cn-i-qvj2lq49k0/8ea707fe782a4b6c94d4488490b5f474?from=pc)

demo:

```c
#include <stdio.h>
#include <malloc.h>

typedef struct node {
    int num;
    struct node *next;
} Node, *NodePtr;

NodePtr createList()                  // 使用头节点
{ 
    NodePtr top = (NodePtr)malloc(sizeof(Node));
    if(top==NULL)
    {
        printf("malloc failed!\n");
        return top;
    }
    top->num = 0;  // 也可以用来存储链表长度
    top->next = NULL;
    return top;
}

NodePtr makeNode(int n) {
    NodePtr np = (NodePtr) malloc(sizeof (Node));
    if(np==NULL)
    {
        printf("malloc failed!\n");
        return np;
    }
    np -> num = n;
    np -> next = NULL;
    return np;
}

NodePtr addInPlace(NodePtr top, int n) {
    // This functions inserts n in its ordered position in a (possibly empty)
    // list pointed to by top, and returns a pointer to the new list
    NodePtr np, curr, prev, makeNode(int);
    np = makeNode(n);
    prev = NULL;
    curr = top;
    while (curr != NULL && n > curr -> num) {
        prev = curr;
        curr = curr -> next;
    }
    if (prev == NULL) { //new number must be added at the top
        np -> next = top;
        return np; //the top of the list has changed to the new node
    }
    np -> next = curr;
    prev -> next = np;
    return top; //the top of the list has not changed
}

NodePtr searchList(NodePtr top,int num)
{
    NodePtr prev = top->next;
    while(prev!=NULL && prev->num != num)
        prev = prev->next;
    return prev;
}

void printList(NodePtr top) {
    NodePtr curr = top->next;
    while (curr != NULL) { // as long as there's a node
        printf("%d ", curr -> num);
        curr = curr -> next; // go on to the next node
    }
    printf("\n");
} 

void destroyList(NodePtr* top)
{
    NodePtr next = (*top)->next;
    while(next!=NULL)
    {
        free(*top);
        *top = next;
        next = next->next;
    }
    free(*top);
    *top = NULL;
}

NodePtr merge(NodePtr pa, NodePtr pb) {
    NodePtr C = NULL;
    NodePtr Clast = NULL;

    NodePtr A = pa->next;
    NodePtr B = pb->next;
    // check if either A or B is empty
    if (A == NULL) return B;
    if (B == NULL) return A;
    //both lists are non-empty
    while (A != NULL && B != NULL) {
        if (A -> num < B -> num) {
            if (C == NULL) 
                C = A; 
            else 
                Clast -> next = A;
            Clast = A;
            A = A -> next ;
        }
        else {
            if (C == NULL) 
                C = B; 
            else 
                Clast -> next = B;
            Clast = B; // 首先C==NULL，C、Clast指向A或B
            B = B -> next ;
        }
    }
    if (A == NULL) 
        Clast -> next = B;
    else 
        Clast -> next = A;
    return C;
}
int main()
{
    NodePtr A = createList();
    int arr[] = {21,35,28,75,61,40};
    int n = sizeof arr / sizeof *arr;
    for(int i=n-1;i>=0;i--)
        addInPlace(A,arr[i]);
    printList(A);
    NodePtr B = createList();
    int ar[] = {47,16,54,25};
    int m = sizeof ar / sizeof *ar;
    for(int j=m-1;j>=0;j--)
        addInPlace(B,ar[j]);
    printList(B);

    NodePtr C  =  createList();
    C->next = merge(A,B);
    printList(C);

    //destroyList(&A);
    //destroyList(&B);
    destroyList(&C);

    getchar();
    return 0;
}
/*
21 28 35 40 61 75
16 25 47 54
16 21 25 28 35 40 47 54 61 75
*/
```

链表建立回文判断：

```c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node {
    char ch;
    struct node * next;
} Node, *NodePtr;

NodePtr getPhrase();
NodePtr reverseLetters(NodePtr);
int compare(NodePtr, NodePtr);

int main() 
{
    NodePtr phrase, s1, s2;
    printf("Type a phrase. (To stop, press 'Enter' only): ");
    phrase = getPhrase();
    while (phrase != NULL) {
        s1 = reverseLetters(phrase);
        s2 = reverseLetters(s1);
        if (compare(s1, s2) == 0) 
            printf("is a palindrome\n");
        else 
            printf("is not a palindrome\n");
        printf("Type a word. (To stop, press 'Enter' only): ");
        phrase = getPhrase();
    }
    getchar();
}

NodePtr getPhrase() {
    NodePtr top = NULL, last, np;
    char c = getchar();
    while (c != '\n') {
        np = (NodePtr) malloc(sizeof(Node));
        np -> ch = c;
        np -> next = NULL;
        if (top == NULL) 
            top = np;
        else 
            last -> next = np;
        last = np;
        c = getchar();
    }
    return top;
}

NodePtr reverseLetters(NodePtr top) {
    NodePtr rev = NULL, np;
    char c;
    while (top != NULL) {
        c = top -> ch;
        if (isalpha(c)) { // add to new list
            np = (NodePtr) malloc(sizeof(Node));
            np -> ch = tolower(c);
            np -> next = rev;
            rev = np;
        }
        top = top -> next; //go to next character of phrase
    }
    return rev;
}

int compare(NodePtr s1, NodePtr s2) {
    while (s1 != NULL) {
        if (s1 -> ch < s2 -> ch) 
            return -1;
        else if (s1 -> ch > s2 -> ch) 
            return 1;
        s1 = s1 -> next;
        s2 = s2 -> next;
    }
    return 0;
}
```

ref:

Noel Kalicharan 《*Advanced* *topics* *in* *C*: core concepts *in* data structures》

－End－
