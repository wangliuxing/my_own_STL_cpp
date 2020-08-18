
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "22-Linklist.cpp"
#include "12-Object.h"
using namespace std;
using namespace Wang;
struct Node
{
    int value;
    Node* next;
};
struct m_header :  public Object
{
    char reserved[sizeof(int)];
    Node *next;
};

Node* creat_list(int v,int len)//从v开始创建单链表，长度为len,无表头单链表
{
    Node* slider = NULL;
    Node* ret = NULL;
    for(int i=0;i<len;i++)
    {
        Node* n = new Node();
        n->value = v++;
        n->next = NULL;
        if(slider == NULL)
        {
            slider = n;
            ret = n;
        }
        else
        {
            slider->next = n;
            slider = slider->next;
        }
    }
    return ret;
}

void destroy(Node* list)
{
    while(list)
    {
        Node* toDel = list;
        list = list->next;
        delete toDel;
    }
}
void print(Node* list)
{
    while(list)
    {
        cout<<list->value<<"->";
        list = list->next;
    }
    cout<<"NULL"<<endl;
}
Node* reverse(Node* list)
{
    if((list==NULL)||(list->next == NULL))//边界条件
    {
        return list;
    }
    else
    {
        Node* guard = list->next;
        Node* ret = reverse(list->next);
        guard->next = list;
        list->next = NULL;
        return ret;
    }
}
Node* merge(Node* list1,Node* list2)
{
    if(list1==NULL)
    {
        return list2;
    }
    else if(list2==NULL)
    {
        return list1;
    }
    else if(list1->value < list2->value)
    {
        Node* list1_ = list1->next;
        Node *list = merge(list1_,list2);
        list1->next = list;
        return list1;
    }
    else
    {
        Node* list2_ = list2->next;
        Node *list = merge(list1,list2_);
        list2->next = list;
        return list2;
    }
}
void Hannoi(int n, char a, char b ,char c)
{
    if(n==1)
    {
        cout<<a<<"-->"<<c<<endl;//只需要打印首尾元素即可
    }
    else
    {
        Hannoi(n-1,a,c,b);
        Hannoi(1,a,b,c);
        Hannoi(n-1,b,a,c);
    }
}
void permu(char* s,char *e)//e用于指向首元素
{
    if(*s == '\0')
    {
        cout<<e<<endl;
    }
    else
    {
        int len = strlen(s);
        for(int i=0;i<len;i++)
        {
            if((i==0)||(s[0]!=s[i]))// 相等就不进行交换
            {
                swap(s[0],s[i]);
                permu(s+1,e);// 对子串进行全排列
                // 然后打印两条全排列
                // 改变s的过程只是在交换处
                swap(s[0],s[i]);
            }
        }
    }
}
void even_print(Node* list)
{
    if(list != NULL)
    {
        even_print(list->next);//不断的去调用这个函数，并判断是否为NULL
        // 如果此时为空，退栈，返回上一个函数，上一个函数进行判断
        if((list->value%2)==0)
        {
            cout<<list->value<<endl;
        }
    }
}
template<int SIZE>
class QueueSolution : public Object
{// 第i行不能放置皇后，那么第i-1放置皇后是错误的
protected:
    enum {N = SIZE + 2};//+2是为了显示边界
    struct Pos : public Object
    {
        Pos(int px = 0,int py = 0):x(px),y(py){}
        int x;
        int y;
    };
    int m_chessboard[N][N];
    Pos m_direction[3];// 3个结构体数组
    Wang::Linklist<Pos> m_solution;
    int m_count;
    void init()
    {
        m_count = 0;
        for(int i=0;i<N;i+=(N-1))
        {
            for(int j=0;j<N;j++)
            {
                m_chessboard[i][j] = 2;
                m_chessboard[j][i] = 2;
            }
        }// 2表示边界
        for(int i=1;i<=SIZE;i++)
        {
            for(int j=1;j<=SIZE;j++)
            {
                m_chessboard[i][j]=0;
            }
        }// 0表示空位
        // 1表示皇后
        m_direction[0].x=-1;m_direction[0].y=-1;//左下方
        m_direction[1].x=0;m_direction[1].y=-1;//正下方
        m_direction[2].x=1;m_direction[2].y=-1;//右下方
        //判断这三个方向上是否存在皇后
    }
    void print()
    {
        for(m_solution.move(0);!m_solution.end();m_solution.next())
        {
            cout<<"("<<m_solution.current().x<<","<<m_solution.current().y<<")"<<endl;
        }
        cout<<endl;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                switch(m_chessboard[i][j])
                {
                    case 0: cout<<" ";break;
                    case 1: cout<<"#";break;
                    case 2: cout<<"*";break;// 打印皇后的位置
                }
            }
            cout<<endl;
        }
        cout<<endl;
    }
    bool check(int x,int y,int d)// 检查的方向参数
    {
        bool flag = true;
        do
        {
            x+=m_direction[d].x;
            y+=m_direction[d].y;// 当前的方向上面加上方向参数
            flag = flag && (m_chessboard[x][y] == 0);
        }// 一直进行检查，直到碰到边界
        while(flag);
        return (m_chessboard[x][y] == 2);//到达了边界，返回1，没有到达返回0
    }
    void run(int j)//检测第j行有没有可以放置皇后的位置
    {
        if(j<=SIZE)
        {
            for(int i=1;i<=SIZE;i++)// 第j行各个位置
            {
                if(check(i,j,0)&&check(i,j,1)&&check(i,j,2))// 检查当前位置三个方向
                {// 三个方向都没有皇后全为1
                    m_chessboard[i][j] = 1;//放置皇后
                    m_solution.insert(Pos(i,j));// 当前的位置加入链表
                    run(j+1);// 判断下一行可不可以放皇后
                    // 如果返回，那么这个位置无法放皇后
                    m_chessboard[i][j] = 0;//产生回溯，无法放置皇后
                    m_solution.remove(m_solution.length()-1);// 删除产生回溯的值
                }
            }
        }
        else
        {
            m_count++;
            print();
        }
    }
public:
    QueueSolution()
    {
        init();
    }
    void run()
    {
        run(1);
        cout<<m_count<<endl;
    }
};
int main()
{
    Node* list = creat_list(0,5);
    print(list);
    return 0;
}
