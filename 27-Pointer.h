#ifndef POINTER_H
#define POINTER_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "12-Object.h"

using namespace std;
namespace Wang
{
    template<typename T>
    class Pointer : public Object
    {
    protected:
        T* m_pointer;
    public:
        Pointer(T *p = NULL)
        {
            m_pointer = p;
        }
        T* operator->()
        {
            return m_pointer;
        }
        T& operator*()
        {
            return *m_pointer;
        }
         const T* operator->() const
        {
            return m_pointer;
        }
        const T& operator*() const
        {
            return *m_pointer;
        }
        bool isNull() const
        {
            return (m_pointer == NULL);
        }
        T *get() const
        {
            return m_pointer;
        }
        //����Ҫʵ��������������Ϊ���㸸���д���һ�����麯��
    };
}
#endif // POINTER_H