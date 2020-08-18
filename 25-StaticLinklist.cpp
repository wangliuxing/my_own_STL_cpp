
#include <iostream>
#include "22-Linklist.cpp"

using namespace std;

namespace Wang
{
template<typename T ,int N>
class StaticLinklist : public Linklist<T>
{
protected:
    typedef typename Linklist<T>::Node Node;//���������һ���µ�����
//�ڶ���Linklist<T>::Node* p������������֪�����Ǹ�ָ�����ͣ����ǳ˷�����
//�����Ҫ����typename���߱��������Ǹ�����
    struct SNode : public Node
    {
        void* operator new(unsigned int size, void *loc)
        {//������أ�Ӧ����������ڲ���������
           (void)size;//Ϊ��ʹ��size
            return loc;
        }//C++��׼����Ϊ���ְ汾�����ز����׳��쳣
    };
    unsigned char m_space[sizeof(SNode)*N];//�����ڴ������
    int m_used[N];//�������
    Node* creat()
    {
        SNode* ret = NULL;
        for(int i=0;i<N;i++)
        {
            if(!m_used[i])
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;
                ret = new(ret)SNode();
                //��ָ���ڴ�ռ���ret���ù��캯��������SNode()���캯��
                //�ڵ�һ��ret���棬���TΪ�����ͣ���ôret��û�е��ù��캯��
                //���Ϊ��ֹ�ڹ��캯�����׳�
                m_used[i] = 1;
                break;
            }
        }
        return ret;
    }
    void destory(SNode *pn)
    {
        SNode *space = reinterpret_cast<SNode*>(m_space);
        //����ָ��ת��Ϊ����ָ�룬������virtual�£�ʹ��dynamic_cast
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