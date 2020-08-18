#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "12-Object.h"
#include "27-Sharedpoint.h"
#include "19-Array.cpp"
#include "71-Graph.h"
#include "22-Linklist.cpp"
using namespace std;
namespace Wang
{
template <typename V, typename E>
class ListGraph : public Wang::Graph<V, E>
{
protected:
    struct Vertex : public Object
    {
        V* data;//ָ��data��ָ��
        Linklist< Edge<E> > edge;//�洢�����͵�����
        Vertex()
        {
            data = NULL;
        }
    };
    Linklist<Vertex*> m_list;//�洢����һ��ָ�򶥵��ָ��
public:
    ListGraph(unsigned int n = 0)//��n������
    {
        for(int i=0;i<n;i++)
        {
            addVertex();
        }
    }
    int addVertex()//o(n)
    {
        int ret = -1;
        Vertex* v = new Vertex();
        if(v != NULL)
        {
            m_list.insert(v);
            ret = m_list.length() - 1;//���ر�ţ����ӵ�ĩβ
        }
        else
        {
            //�׳��쳣
        }
        return ret;
    }
    int addVertex(const V& value)//o(n)
    {
        int ret = addVertex();
        if(ret >= 0)
        {
            setVertex(ret,value);//����ڵ��ʱ������ֵ
        }
        else
        {
            //�׳��쳣
        }
        return ret;
    }
    bool setVertex(int i, const V& value)//��i��λ������value
    {//�Ѿ���i�������˽ڵ�//o(n)
        int ret = ((0 <= i)&&(i < vCount()));
        if(ret)
        {
            Vertex* vertex = m_list.get(i);
            V* data = vertex->data;
            if(data == NULL)
            {
                data = new V();
            }
            if(data != NULL)
            {
                *data = value;
                vertex->data = data;
            }
            else
            {
                //�׳��쳣
            }
        }
        return ret;
    }
    V getVertex(int i)//o(n)
    {
        V ret;
        if(!getVertex(i,ret))
        {
            //�׳��쳣
        }
        return ret;
    }
    bool getVertex(int i, V& value)//o(n)
    {
        int ret = ((0 <= i)&&(i < vCount()));
        if(ret)
        {
            Vertex* v = m_list.get(i);

            if(v->data != NULL)
            {
                value = *(v->data);
            }
            else
            {
                //�׳��쳣
            }
        }
        return ret;
    }
    void removeVertex()//o(n*n)ɾ�����һ���ڵ�
    {
        if(m_list.length() > 0)
        {
            int index = m_list.length() - 1;//����ɾ���Ķ�����
            Vertex* v = m_list.get(index);//o(n)
            if(m_list.remove(index))
            {
                int i = 0;
                for(m_list.move(0);!m_list.end();m_list.next())//o(n)
                //ɾ������Ķ�����˶��������ı�
                {
                    int pos = m_list.current()->edge.find(Edge<E>(i,index));//o(n)
                    if(pos >= 0)
                    {
                        m_list.current()->edge.remove(pos);
                    }
                    i++;
                }
                delete v->data;
                delete v;//�ͷſռ�ֵ
            }
        }
        else
        {
            //�׳��쳣
        }
    }
    Sharedpoint< Wang::Array<int> > getAdjacent(int i)//o(n)
    {
        DynamicArray<int>* ret = NULL;
        if((0<=i)&&(i<vCount()))
        {
            Vertex* vertex = m_list.get(i);
            ret = new DynamicArray<int>(vertex->edge.length());
            if(ret != NULL)
            {
                int k = 0;
                for(vertex->edge.move(0);!vertex->edge.end();vertex->edge.next())
                {
                    ret->set(k++,vertex->edge.current().e);
                }
            }
            else
            {
                //�׳��쳣
            }
        }
        else
        {
            //�׳��쳣
        }
        return ret;
    }
    E getEdge(int i, int j)
    {
        E ret;
        if(getEdge(i,j,ret)) return ret;
    }
    bool getEdge(int i, int j, E& value)//o(n)
    {
        int ret = ((0 <= i)&&(i < vCount())&&(0 <= j)&&(j < vCount()));
        if(ret)
        {
            Vertex* vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i,j));//��i��j֮��ı��Ƿ����
            if(pos >= 0)
            {
                value = vertex->edge.get(pos).data;//ȡ��Ȩֵ
            }
            else
            {
                //�׳��쳣
            }
        }
        return ret;
    }
    bool setEdge(int i, int j, const E& value)//o(n)
    {
        int ret = ((0 <= i)&&(i < vCount())&&(0 <= j)&&(j < vCount()));
        if(ret)
        {
            Vertex* vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i,j));
            if(pos >= 0)
            {
                ret = vertex->edge.set(pos,Edge<E>(i,j,value));
            }
            else
            {
                ret = vertex->edge.insert(0,Edge<E>(i,j,value));
            }
        }
        return ret;
    }
    bool removeEdge(int i, int j)//o(n)
    {
        int ret = ((0 <= i)&&(i < vCount())&&(0 <= j)&&(j < vCount()));
        if(ret)
        {
            Vertex* vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i,j));
            if(pos >= 0)
            {
                ret = vertex->edge.remove(pos);
            }
        }
        return ret;
    }
    virtual bool isAdjacent(int i,int j)
    {
        return (0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount())&&(m_list.get(i)->edge.find(Edge<E>(i,j)));
    }
    int vCount()//o(1)
    {
        return m_list.length();
    }
    int eCount()//o(n)
    {
        int ret = 0;
        for(m_list.move(0);!m_list.end();m_list.next())
        {
            ret += m_list.current()->edge.length();
        }
        return ret;
    }
    int ID(int i)//o(n*n)
    {
        int ret = 0;
        if((0 <= i)&&(i < vCount()))
        {
            for(m_list.move(0);!m_list.end();m_list.next())
            {
                Linklist< Edge<E> >& egde = m_list.current()->edge;
                for(egde.move(0);!egde.end();egde.next())
                {
                    if(egde.current().e == i)
                    {
                        ret++;
                        break;
                    }
                }
            }
        }
        else
        {
            //�׳��쳣
        }
        return ret;
    }
    int OD(int i)//o(n)
    {
        int ret = 0;
        if((0 <= i)&&(i < vCount()))
        {
            ret = m_list.get(i)->edge.length();
        }
        else
        {
            //�׳��쳣
        }
        return ret;
    }
    ~ListGraph()
    {
        while(m_list.length() > 0)
        {
            Vertex* toDel = m_list.get(0);
            m_list.remove(0);
            delete toDel->data;
            delete toDel;
        }
    }

};
}
#endif
/**
MatrixGraph<3, int,int> g;

    g.setEdge(0,1,1);
    g.setEdge(1,0,2);
    g.setEdge(1,2,3);
    cout<<g.vCount()<<endl;
    cout<<g.eCount()<<endl;
    cout<<g.OD(1)<<endl;
    cout<<g.ID(1)<<endl;
    Sharedpoint< Array<int> > aj = g.getAdjacent(1);//��ȡ��1���ڵĶ���
    for(int i=0;i<aj->length();i++)
    {
        cout<<(*aj)[i]<<" ";
    }
    cout<<endl;

    ListGraph<char, int> q(4);
    q.setVertex(0,'A');
    q.setVertex(1,'B');
    q.setVertex(2,'C');
    q.setVertex(3,'D');

    for(int i=0;i<q.vCount();i++)
    {
        cout<< i << ":"<<q.getVertex(i)<<endl;
    }
    q.setEdge(0,1,5);
    q.setEdge(0,3,6);
    q.setEdge(1,2,8);
    q.setEdge(2,3,2);
    q.setEdge(3,1,9);
    cout<<"W(0,1):"<<q.getEdge(0,1)<<endl;
    cout<<"W(0,3):"<<q.getEdge(0,3)<<endl;
    cout<<"W(1,2):"<<q.getEdge(1,2)<<endl;
    cout<<"W(2,3):"<<q.getEdge(2,3)<<endl;
    cout<<"W(3,1):"<<q.getEdge(3,1)<<endl;

    g.removeEdge(3,1);

    Sharedpoint<Array<int> > aj1 = q.getAdjacent(0);
    for(int i=0;i<aj1->length();i++)
    {
        cout<<(*aj1)[i]<<endl;
    }
*/