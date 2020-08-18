
#include <iostream>
#include "22-Linklist.cpp"

using namespace std;

namespace Wang
{
template<typename T ,int N>
class StaticLinklist : public Linklist<T>
{
protected:
    typedef typename Linklist<T>::Node Node;//给这个类型一个新的名字
//在定义Linklist<T>::Node* p；编译器并不知道这是个指针类型，还是乘法运算
//因此需要添加typename告诉编译器这是个类型
    struct SNode : public Node
    {
        void* operator new(unsigned int size, void *loc)
        {//这个重载，应该是在类的内部进行重载
           (void)size;//为了使用size
            return loc;
        }//C++标准库认为这种版本的重载不会抛出异常
    };
    unsigned char m_space[sizeof(SNode)*N];//分配内存的数组
    int m_used[N];//标记数组
    Node* creat()
    {
        SNode* ret = NULL;
        for(int i=0;i<N;i++)
        {
            if(!m_used[i])
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;
                ret = new(ret)SNode();
                //在指定内存空间上ret调用构造函数，调用SNode()构造函数
                //在第一个ret里面，如果T为类类型，那么ret并没有调用构造函数
                //因此为防止在构造函数中抛出
                m_used[i] = 1;
                break;
            }
        }
        return ret;
    }
    void destory(SNode *pn)
    {
        SNode *space = reinterpret_cast<SNode*>(m_space);
        //父类指针转化为子类指针，并且有virtual下，使用dynamic_cast
        for(int i=0;i<N;i++)
        {
            if( pn == (space + i))
            {
                m_used[i] = 0;
                pn->~SNode();
                break;
            }
        }
    }
public:
    StaticLinklist()
    {
        for(int i=0;i<N;i++)
        {
            m_used[i] = 0;
        }
    }
    int capacity()
    {
        return N;
    }
    ~StaticLinklist()
    {
        this->clear();
    }
};
}
