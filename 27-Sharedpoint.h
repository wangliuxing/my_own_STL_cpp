#ifndef _SHAREDPOINT
#define _SHAREDPOINT

#include "27-Pointer.h"
#include <cstdlib>
using namespace std;
namespace Wang
{
    template<typename T>
    class Sharedpoint : public Pointer<T>
    {
protected:
    int *m_ref;
    void assign(const Sharedpoint<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;
        if(this->m_ref)//��������ַ��Ϊ�գ�����ɹ���
        {
            (*this->m_ref)++;//��һ�ν��б�ʶ
            *(const_cast<Sharedpoint<T>&>(obj).m_ref) = *this->m_ref;
        }
    }
public:
    Sharedpoint(T *p = NULL) : m_ref(NULL)
    {
        if(p)
        {
            this->m_ref = static_cast<int*>(std::malloc(sizeof(int)));
            //�Ӷѿռ�����һƬ�ڴ棬���ڴ洢m_ref
            if(this->m_ref)//�������ɹ�
            {
                *(this->m_ref) = 1;
                this->m_pointer = p;//��p��m_pointer���г�ʼ��
            }
            else
            {
                //�׳��쳣
            }
        }
    }
    Sharedpoint(const Sharedpoint<T> &obj)
    {
        assign(obj);
        // 1����this���г�ʼ�� 2����������ָ���m_ref++
    }
    Sharedpoint<T>& operator =(const Sharedpoint<T> &obj)
    {
        if(this != &obj)
        {
            clear();//��ǰ������ָ���ÿ�
            assign(obj);
        }
        return *this;
    }
    void clear()
    {
        T *toDel = this->m_pointer;
        int *ref = this->m_ref;//��ֹ�쳣�׳�
        this->m_pointer = NULL;
        this->m_ref = NULL;
        if(ref)//ref��Ϊ�գ��е�ַ
        {
            (*ref)--;
            if(*ref == 0)
            {
                free(ref);
                delete toDel;
            }
        }
    }
    ~Sharedpoint()
    {
        clear();
    }
    };
    template <typename T>
    bool operator == (const Sharedpoint<T>& Q,const Sharedpoint<T>& W)
    {
        return (Q.get()== W.get());
    }
    template <typename T>
    bool operator != (const Sharedpoint<T>& Q,const Sharedpoint<T>& W)
    {
        return !( Q == W );//ʹ��==������
    }
}
#endif // _SHAREDPOINT