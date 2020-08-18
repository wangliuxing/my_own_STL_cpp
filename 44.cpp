
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

Node* creat_list(int v,int len)//��v��ʼ����������������Ϊlen,�ޱ�ͷ������
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
    if((list==NULL)||(list->next == NULL))//�߽�����
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
        cout<<a<<"-->"<<c<<endl;//ֻ��Ҫ��ӡ��βԪ�ؼ���
    }
    else
    {
        Hannoi(n-1,a,c,b);
        Hannoi(1,a,b,c);
        Hannoi(n-1,b,a,c);
    }
}
void permu(char* s,char *e)//e����ָ����Ԫ��
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
            if((i==0)||(s[0]!=s[i]))// ��ȾͲ����н���
            {
                swap(s[0],s[i]);
                permu(s+1,e);// ���Ӵ�����ȫ����
                // Ȼ���ӡ����ȫ����
                // �ı�s�Ĺ���ֻ���ڽ�����
                swap(s[0],s[i]);
            }
        }
    }
}
void even_print(Node* list)
{
    if(list != NULL)
    {
        even_print(list->next);//���ϵ�ȥ����������������ж��Ƿ�ΪNULL
        // �����ʱΪ�գ���ջ��������һ����������һ�����������ж�
        if((list->value%2)==0)
        {
            cout<<list->value<<endl;
        }
    }
}
template<int SIZE>
class QueueSolution : public Object
{// ��i�в��ܷ��ûʺ���ô��i-1���ûʺ��Ǵ����
protected:
    enum {N = SIZE + 2};//+2��Ϊ����ʾ�߽�
    struct Pos : public Object
    {
        Pos(int px = 0,int py = 0):x(px),y(py){}
        int x;
        int y;
    };
    int m_chessboard[N][N];
    Pos m_direction[3];// 3���ṹ������
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
        }// 2��ʾ�߽�
        for(int i=1;i<=SIZE;i++)
        {
            for(int j=1;j<=SIZE;j++)
            {
                m_chessboard[i][j]=0;
            }
        }// 0��ʾ��λ
        // 1��ʾ�ʺ�
        m_direction[0].x=-1;m_direction[0].y=-1;//���·�
        m_direction[1].x=0;m_direction[1].y=-1;//���·�
        m_direction[2].x=1;m_direction[2].y=-1;//���·�
        //�ж��������������Ƿ���ڻʺ�
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
                    case 2: cout<<"*";break;// ��ӡ�ʺ��λ��
                }
            }
            cout<<endl;
        }
        cout<<endl;
    }
    bool check(int x,int y,int d)// ���ķ������
    {
        bool flag = true;
        do
        {
            x+=m_direction[d].x;
            y+=m_direction[d].y;// ��ǰ�ķ���������Ϸ������
            flag = flag && (m_chessboard[x][y] == 0);
        }// һֱ���м�飬ֱ�������߽�
        while(flag);
        return (m_chessboard[x][y] == 2);//�����˱߽磬����1��û�е��ﷵ��0
    }
    void run(int j)//����j����û�п��Է��ûʺ��λ��
    {
        if(j<=SIZE)
        {
            for(int i=1;i<=SIZE;i++)// ��j�и���λ��
            {
                if(check(i,j,0)&&check(i,j,1)&&check(i,j,2))// ��鵱ǰλ����������
                {// ��������û�лʺ�ȫΪ1
                    m_chessboard[i][j] = 1;//���ûʺ�
                    m_solution.insert(Pos(i,j));// ��ǰ��λ�ü�������
                    run(j+1);// �ж���һ�пɲ����ԷŻʺ�
                    // ������أ���ô���λ���޷��Żʺ�
                    m_chessboard[i][j] = 0;//�������ݣ��޷����ûʺ�
                    m_solution.remove(m_solution.length()-1);// ɾ���������ݵ�ֵ
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