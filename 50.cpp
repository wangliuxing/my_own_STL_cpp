
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "46-Sort.h"
using namespace std;
using namespace Wang;
struct Test : public Object
{
    int id;
    int data1[1000];
    double data2[500];
    bool operator <(const Test& obj)
    {
        return id<obj.id;
    }
    bool operator >=(const Test& obj)
    {
        return id>=obj.id;
    }
    bool operator >(const Test& obj)
    {
        return id>obj.id;
    }
    bool operator <=(const Test& obj)
    {
        return id<=obj.id;
    }
};
class TestProxy : public Object
{
protected:
    Test* m_pTest;//��Ϲ�ϵ
public:
 /**   TestProxy(Test* pTest)
    {
        m_pTest = pTest;
    }*/
    int id()
    {
        return m_pTest->id;
    }
    int* data1()
    {
        return
        m_pTest->data1;
    }
    double* data2()
    {
        return m_pTest->data2;
    }
    Test& test() const//���Է���ԭ���Ķ���
    {
        return *m_pTest;//������ָ�Ķ���
    }
    bool operator <(const TestProxy& obj)
    {
        return test() < obj.test();//����֮��ıȽϾ���id֮��ıȽ�
    }
    bool operator >=(const TestProxy& obj)
    {
        return test()>=obj.test();
    }
    bool operator >(const TestProxy& obj)
    {
        return test()>obj.test();
    }
    bool operator <=(const TestProxy& obj)
    {
        return test()<=obj.test();
    }
    Test& operator =(Test& test)
    {
        m_pTest = &test;
        return *m_pTest;
    }
};
Test t[1000];
TestProxy pt[1000];
int main()
{
    clock_t begin = 0;
    clock_t end = 0;
    for(int i=0;i<1000;i++)
    {
        t[i].id = i;
        pt[i] = t[i];//ÿһ�����ʹ�ô���
    }
    begin = clock();
    Sort::Bubble(pt,1000,false);
    end = clock();
    cout<<"t="<<(end-begin)<<endl;
    return 0;
}