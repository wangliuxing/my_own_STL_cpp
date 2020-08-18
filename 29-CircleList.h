#ifndef _CIRCLELIST.H
#define _CIRCLELIST.H

#include <iostream>
#include "22-Linklist.cpp"

using namespace std;

namespace Wang
{
template<typename T>
class CircleList : public Linklist<T>
{
protected:
    typedef typename Linklist<T>::Node Node;
    Node* last()const //O(n)
    {
        return this->position(this->m_length-1)->next;
    }
    void last_to_first()const //O(n)
    {
        last()->next = this->m_header.next ;
    }
    int mode(int i)const //O(1)
    {
        return (this->m_length == 0)? 0:(i%(this->m_length));
    }
public:
    bool insert(const T& e)
    {
        return insert(this->m_length,e);
    }
    bool insert(int i, const T& e) //O(n)
    {
        bool ret = true;
        i = i%(this->m_length + 1 );
        ret = Linklist<T>::insert(i,e);// ��λ��i��ǰһ��
        // ��i�������
        if(ret&&(i==0))
        {
            last_to_first();
        }
        return ret;
    }
    bool remove(int i) //O(n)
    {
        bool ret = true;
        i = mode(i);
        if(i == 0)
        {
            Node *toDel = this->m_header.next;
            if(toDel != NULL)
            {
                this->m_header.next = toDel->next;
                this->m_length--;
                if(this->m_length > 0)
                {
                    last_to_first();
                    if(this->m_current = toDel)//����ƶ�����currentָ��
                    {
                        this->m_current = toDel->next;
                    }
                }
                else
                {
                    this->m_header.next = NULL;
                    this->m_current = NULL;
                }
                this->destory(toDel);//�����׽ڵ�
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = Linklist<T>::remove(i);//O(n)
        }
        return ret;
    }
    bool set(int i, const T& e)
    {
        return Linklist<T>::set(mode(i),e);
    }
    virtual T get(int i)const
    {
        return Linklist<T>::get(mode(i));
    }
    bool get(int i,T &e)const
    {
        return Linklist<T>::get(mode(i),e);
    }
    int find(const T& e) const //O(n)
    {
        int ret = -1;

        Node *slider = this->m_header.next;
        for(int i=0;i<this->m_length;i++)
        {
            if(slider->value == e)
            {
                ret = i;
                break;
            }
            slider = slider->next;
        }
        return ret;
    }
    void clear()
    {
        while(this->m_length > 1)//O(n)
        {
            remove(1);//O(1)
            //ÿ�ζ�ɾ��λ�á�1���Ľڵ�
            //remove(0)�ᵼ��ѭ�������Ĳ����ƶ��ع�
        }
        if(this->m_length == 1)
        {
            Node *toDel = this->m_header.next;
            this->m_header.next = NULL;
            this->m_length = 0;
            this->m_current = NULL;
            this->destory(toDel);
        }
    }
    bool move(int i, int step)//�ƶ���Ŀ��λ��
    {
        return Linklist<T>::move(mode(i),step);
    }
    bool end()
    {
        return(this->m_length == 0) ||(this->m_current == NULL);
    }
    ~CircleList()
    {
        clear();
    }
};
}

#endif // _CIRCLELIST
/*

#include <iostream>
#include "29-CircleList.h"
using namespace std;
using namespace Wang;
void josephus(int n , int s , int m)
{
    CircleList<int> c1;
    for(int i=0;i<=n;i++)
    {
        c1.insert(i);//��ʼ��
    }
    c1.move(s-1,m-1);//���㿪ʼ���s-1������3�����ƶ�������
    while(c1.length()>0)
    {
        c1.next();
        cout<<c1.current()<<endl;
        c1.remove(c1.find(c1.current()));
    }
}
int main()
{
    josephus(41,1,3);
    //41���˿�ʼ�����Ϸ����1��ʼ��������3��ʼ��ɱ
    Wang::CircleList<int> p;
    int m =0 ;
    for(int i=0;i<5;i++)
    {
        p.insert(0,i);
    }
    p.set(8,10000);

    return 0;
}

*/