#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "12-Object.h"
#include "27-Sharedpoint.h"
#include "19-Array.cpp"
#include "35-Static_Link_Queue.h"
#include "34-Static_Link_Stack.h"
#include "46-Sort.h"
using namespace std;
namespace Wang
{
    template <typename E>
    struct Edge : public Object
    {
        int b;//�׶���ı��
        int e;//β����ı��
        E data;//����
        Edge(int i=-1, int j=-1)
        {
            b = i;
            e = j;
        }
        Edge(int i, int j, const E& value)
        {
            b = i;
            e = j;
            data = value;
        }
        bool operator ==(const Edge<E>& obj)
        {
            return (b == obj.b)&&(e==obj.e);
        }
        bool operator !=(const Edge<E>& obj)
        {
            return !(*this == obj);
        }
        bool operator < (const Edge<E>&obj)
        {
            return (data < obj.data);
        }
        bool operator > (const Edge<E>&obj)
        {
            return (data > obj.data);
        }
    };
template <typename V, typename E>
class Graph : public Object
{
protected:
    template<typename T>
    DynamicArray<T>* toArray(LinkQueue<T>& queue)
    {
         DynamicArray<T>* ret = new DynamicArray<T>(queue.length());
         if(ret != NULL)
         {
            for(int i=0;i<ret->length();i++)
            {
                ret->set(i,queue.front());
                queue.remove();
            }
         }
         else
         {
             //�׳��쳣
         }
         return ret;
    }
    Sharedpoint<Array<Edge<E> > >getUndirectedEdges()
    {
        DynamicArray<Edge<E> >*ret = NULL;
        if(asUndirectrd())
        {
            LinkQueue<Edge<E> > queue;
            for(int i=0;i<vCount();i++)
            {
                for(int j=i;j<vCount();j++)
                {
                    if(isAdjacent(i,j))
                    {
                        queue.add(Edge<E>(i,j,getEdge(i,j)));
                    }
                }
            }
            ret = toArray(queue);
        }
        else
        {
            //�׳��쳣
        }
        return ret;
    }
    int find(Array<int>& p, int v)
    {
        while(p[v]!=-1)
        {
            v = p[v];
        }
        return v;
    }
public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V& value) = 0;
    virtual bool setVertex(int i, const V& value) = 0;
    virtual Sharedpoint< Array<int> > getAdjacent(int i) = 0;
    virtual E getEdge(int i, int j) = 0;
    virtual bool getEdge(int i, int j, E& value) = 0;
    virtual bool setEdge(int i, int j, const E& value) = 0;
    virtual bool removeEdge(int i, int j) = 0;
    virtual int vCount() = 0;
    virtual int eCount() = 0;
    virtual int OD(int i) = 0;
    virtual int ID(int i) = 0;
    virtual bool isAdjacent(int i,int j) = 0;//�ж�i��j�Ƿ�����
    virtual int TD(int i)
    {
        return (OD(i) + ID(i));
    }
    bool asUndirectrd()//�ж��Ƿ�Ϊ����ͼ
    {
        bool ret = true;
        for(int i =0;i<vCount();i++)
        {
            for(int j =0;j<vCount();j++)
            {
                if(isAdjacent(i,j))
                {
                    ret = ret&&isAdjacent(j,i)&&(getEdge(i,j)==getEdge(j,i));
                }
            }
        }
        return ret;
    }
    Sharedpoint< Array< Edge<E> > >prim(const E& LIMIT, const bool MINMAX = true)//�����ϵ����Ȩֵ
    {//Ĭ��ֵtrue����С������
        LinkQueue< Edge<E> > ret;
        if(asUndirectrd())
        {
            DynamicArray<int> adjVex(vCount());// ���ڱ��������
            DynamicArray<bool> mark(vCount());
            DynamicArray<E> cost(vCount());
            Sharedpoint< Array<int> > aj = NULL;//���ڻ�ȡ�ߵ���Ϣ
            bool end = false;
            int v = 0;//��0Ѱ����С������
            for(int i=0;i<vCount();i++)
            {
                adjVex[i] = -1;
                mark[i] = false;
                cost[i] = LIMIT;
            }
            mark[v] = true;
            aj = getAdjacent(v);// ��ȡ��v���ڵĵ�
            for(int j=0;j<aj->length();j++)
            {
                cost[(*aj)[j]] = getEdge(v,(*aj)[j]);//������v���ڵĸ����ߵ�Ȩֵ�������ڸ�������ֵ��
                adjVex[(*aj)[j]] = v;//���涥�㣬��������v�����ĵ㱣��Ϊv
            }
            for(int i=0;(i<vCount())&&!end;i++)
            {
                E m = LIMIT;//m���ڼ�¼��СȨֵ
                int k = -1;//���ڼ�¼��ǰ����
                for(int j=0;j<vCount();j++)
                {
                    if(!mark[j]&&(MINMAX? (cost[j]<m):(cost[j]>m)))
                    {
                        m = cost[j];//��m�ҵ���Сֵ����
                        k = j;
                    }//����СȨֵ���Լ���Ӧ����ı��
                }
                end = (k == -1);//�Ҳ�����СȨֵ���˳���������
                if(!end)
                {
                    ret.add(Edge<E>(adjVex[k],k,getEdge(adjVex[k],k)));//����һ����
                    //�ҵ��˵�k���Լ�adjVex[k]�����������СȨֵ����ѹ�����
                    mark[k] = true;
                    aj = getAdjacent(k);
                    for(int j=0;j<aj->length();j++)
                    {
                        if(!mark[(*aj)[j]] && (MINMAX?(getEdge(k,(*aj)[j]) < cost[(*aj)[j]]):(getEdge(k,(*aj)[j]) > cost[(*aj)[j]])))
                        {
                            cost[(*aj)[j]] = getEdge(k,(*aj)[j]);
                            adjVex[(*aj)[j]] = k;
                        }
                    }
                }
            }
        }
        else
        {
            //�׳��쳣
        }
        if(ret.length()==(vCount()-1))//�жϱߵ���Ŀ�Ƿ�Ϊn-1
        return toArray(ret);
    }
    Sharedpoint< Array<Edge<E> > >kruskal(const bool MINMUM = true)
    {
        LinkQueue<Edge<E> > ret;
        Sharedpoint< Array<Edge<E> > > edges = getUndirectedEdges();
        DynamicArray<int> p(vCount());
        for(int i=0;i<vCount();i++)
        {
            p[i] = -1;
        }
        Sort::Shell(*edges,MINMUM);
        for(int i=0;(i<edges->length())&&(ret.length()<vCount()-1);i++)
        {
            int b = find(p,(*edges)[i].b);
            int e = find(p,(*edges)[i].e);
            if(b != e)//�����ɻ�·
            {
                p[e] = b;//����ǰ�������ֵ��
                ret.add((*edges)[i]);
            }
        }
        if(ret.length() != (vCount()-1))
        {
            //�׳��쳣
        }
        return toArray(ret);
    }
    Sharedpoint< Array<int> >DFS1(int i)
    {
        DynamicArray<int>* ret = NULL;//���ص���һ�����飬���ڷ�ӳ�����ʵ��Ⱥ����
        if((0<=i)&&(i<vCount()))
        {
            LinkStack<int> s;
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());
            for(int j=0;j<visited.length();j++)
            {
                visited[j] = false;
            }
            s.push(i);
            while(s.size() > 0)
            {
                int v = s.top();
                s.pop();
                if(!visited[v])
                {
                    Sharedpoint< Array<int> > aj = getAdjacent(v);
                    for(int j=0;j<aj->length();j++)
                    {
                        s.push((*aj)[j]);
                    }// ���е���v�������ڽӶ���ȫ��ѹ��ջ��
                    r.add(v);// ͷ���ѹ���������
                    visited[v] = true;// �ѱ�־λ����Ϊfalse
                }
            }
            ret = toArray(r);
        }
        else
        {
            //�׳��쳣
        }
        return ret;
    }
    Sharedpoint< Array<int> > BFS(int i)
    {
        DynamicArray<int>* ret = NULL;//���ص���һ�����飬���ڷ�ӳ�����ʵ��Ⱥ����
        if((0<=i)&&(i<vCount()))
        {
            LinkQueue<int> q;
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());
            for(int j=0;j<visited.length();j++)
            {
                visited[j] = false;
            }
            q.add(i);
            while(q.length() > 0)
            {
                int v = q.front();
                q.remove();
                if(!visited[v])
                {
                    Sharedpoint<Array<int> > aj = getAdjacent(v);
                    for(int j=0;j<aj->length();j++)
                    {
                        q.add((*aj)[j]);
                    }
                    r.add(v);
                    visited[v] = true;
                }
            }
            ret = toArray(r);
        }
        else
        {
            //�׳��쳣
        }
        return ret;
    }

    void DFS2(Graph<V,E>& g, int v, Array<bool>& visited)
    {
        if((0<=v)&&(v<vCount()))
        {
            cout<<v<<endl;//���ʽ��
            visited[v] = true;
            Sharedpoint<Array<int> > aj = g.getAdjacent(v);
            for(int j=0;j<aj->length();j++)
            {
                if(!visited[(*aj)[j]])
                {
                    DFS2(g,(*aj)[j],visited);
                }
            }
        }
        else
        {
            //�׳��쳣
        }
    }
    void DFS2(Graph<V,E>& g,int v)
    {
        DynamicArray<bool> visit(g.vCount());
        for(int j=0;j<visit.length();j++)
        {
            visit[j] = false;
        }
        DFS2(g,v,visit);
    }
    Sharedpoint<Array<int> > dijkstra(int i,int j,const E& MAX)
    {
        LinkQueue<int> ret;
        if((0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount()))
        {
            DynamicArray<E> dist(vCount());
            DynamicArray<int> path(vCount());
            DynamicArray<bool> mark(vCount());
            for(int k=0;k<vCount();k++)
            {
                dist[k] = false;
                path[k] = -1;
                dist[k] = isAdjacent(i,k)?(path[k]=i,getEdge(i,k)):MAX;
            }
            mark[i] = true;
            for(int k=0;k<vCount();k++)
            {
                E m = MAX;
                int u = -1;
                for(int w=0;w<vCount();w++)
                {
                    if(!mark[w] && (dist[w] < m))
                    {
                        m = dist[w];
                        u = w;
                    }
                }
                if(u == -1)
                {
                    break;//û����С·��
                }
                mark[u] = true;
                for(int w=0;w<vCount();w++)//ͨ����֪����С·���ܲ����ҵ�������С·��
                {
                    if(!mark[w] && isAdjacent(u,w) &&(dist[u]+getEdge(u,w) < dist[w]))
                    {
                       dist[w] = dist[u]+getEdge(u,w);
                       path[w] = u;
                    }
                }
            }
            LinkStack<int> s;
            s.push(j);
            for(int k=path[j];k!=-1;k=path[k])//path����Ķ����˳��������ģ���Ҫͨ��ջ������ת
            {
                s.push(k);
            }
            while(s.size()>0)
            {
                ret.add(s.top());
                s.pop();
            }
        }
        else
        {
            //�׳��쳣
        }
        if(ret.length()<2)
        {
            //�׳��쳣����ʾ���ɴ��
        }
        return toArray(ret);
    }
    Sharedpoint< Array<int> > floyd(int x,int y,const E& LIMIT)
    {
         LinkQueue<int> ret;
         if((0<=x)&&(x<vCount())&&(0<=y)&&(y<vCount()))
         {
             DynamicArray< DynamicArray<E> > dist(vCount());
             DynamicArray< DynamicArray<int> > path(vCount());
             for(int k=0;k<vCount();k++)
             {
                 dist[k].resize(vCount());
                 path[k].resize(vCount());
             }
             for(int i=0;i<vCount();i++)
             {
                for(int j=0;j<vCount();j++)
                {
                    path[i][j] = -1;//û������
                    dist[i][j] = (isAdjacent(i,j)?(path[i][j]=j,getEdge(i,j)):LIMIT);//��������
                }
             }
             for(int k=0;k<vCount();k++)
             {
                 for(int i=0;i<vCount();i++)
                {
                    for(int j=0;j<vCount();j++)
                    {
                        if((dist[i][k]+dist[k][j])<dist[i][j])
                        {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            path[i][j] = path[i][k];
                        }
                    }
                }
             }
             while((x!=-1)&&(x!=y))//�������е����Ӷ��㣬x��ֵ���ܴ������һ������
             {
                 ret.add(x);
                 x = path[x][y];
             }
             if(x!=-1)
             {
                 ret.add(x);
             }//�����һ��������뷵��ֵ��
         }
         else
         {
             //�׳��쳣
         }
         return toArray(ret);
    }
};
template <int N, typename V, typename E>
class MatrixGraph : public Graph<V, E>
{
protected:
    V* m_vertexes[N];//ÿ��Ԫ�ض���ָ��
    E* m_edges[N][N];
    int m_ecount;//��¼�ߵ���Ŀ
public:
    MatrixGraph()
    {
        for(int i=0;i<vCount();i++)
        {
            m_vertexes[i] = NULL;
            for(int j=0;j<vCount();j++)
            {
                m_edges[i][j] = NULL;
            }
        }
        m_ecount = 0;
    }
    virtual V getVertex(int i)
    {
        V ret;
        if(!getVertex(i, ret))
        {
            //�׳��쳣
        }
        return ret;
    }
    virtual bool getVertex(int i, V& value)
    {
        int ret = ((0<=i)&&(i<vCount()));
        if(ret)
        {
            if(m_vertexes[i] != NULL)//��������Ԫ��
            {
                value = *(m_vertexes[i]);//��ȡ����Ԫ��
            }
            else
            {
                //�׳��쳣
            }
        }
        return ret;
    }
    virtual bool setVertex(int i, const V& value)//O(1)
    {
        int ret = ((0<=i)&&(i<vCount()));
        if(ret)
        {
            V* data = m_vertexes[i];//��ʼ��data
            if(data == NULL)//��������Ԫ��
            {
                data = new V();
            }
            if(data != NULL)
            {
                *data = value;
                m_vertexes[i] = data;//�쳣��ȫ
            }
            else
            {
                //�׳��쳣
            }
        }
        return ret;
    }
    virtual Sharedpoint< Array<int> > getAdjacent(int i)//��ȡ�ڵ�i���ڽӶ���
    {//O(n)
        DynamicArray<int>* ret = NULL;
        if((0 <= i)&&(i < vCount()))
        {
            int n = 0;
            for(int j=0;j<vCount();j++)
            {
                if(m_edges[i][j]!=NULL) n++;//������i��
            }
            ret = new DynamicArray<int>(n);//����һ������Ϊn�Ķ�̬����
            if(ret != NULL)
            {
                for(int j=0,k=0;j<vCount();j++)
                {
                    if(m_edges[i][j]!=NULL) ret->set(k++,j);//���ñ��
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
    virtual E getEdge(int i, int j)
    {
        E ret;
        if(!getEdge(i, j, ret))
        {
            //�׳��쳣
        }
        return ret;
    }
    virtual bool getEdge(int i, int j, E& value)//o(1)
    {
        int ret = ((0 <= i)&&(i < vCount())&&(0 <= j)&&(j < vCount()));
        if(ret)
        {
            if(m_edges[i][j] != NULL)//��������Ԫ��
            {
                value = *(m_edges[i][j]);//��ȡ����Ԫ��
            }
            else
            {
                //�׳��쳣
            }
        }
        return ret;
    }
    virtual bool setEdge(int i, int j, const E& value)//o(1)
    {
        int ret = ((0 <= i)&&(i < vCount())&&(0 <= j)&&(j < vCount()));
        if(ret)
        {
            E* ne = m_edges[i][j];
            if(ne == NULL)
            {
                ne = new E();//ָ��ѿռ��һƬ�ڴ�
                if(ne != NULL)
                {
                    *ne = value;
                    m_edges[i][j] = ne;
                    m_ecount++;
                }
                else
                {
                    //�׳��쳣
                }
            }
            else
            {
                *ne = value;
            }
        }
        return ret;
    }
    virtual bool removeEdge(int i, int j)//o(1)
    {
        int ret = ((0 <= i)&&(i < vCount())&&(0 <= j)&&(j < vCount()));
        if(ret)
        {
            E* toDel = m_edges[i][j];//ָ����Ҫɾ���Ķ���
            m_edges[i][j] = NULL;//�쳣��ȫ
            if(toDel != NULL)
            {
                m_ecount--;
                delete toDel;
            }
        }
        return ret;
    }
    virtual bool isAdjacent(int i,int j)
    {
        return (0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount())&&(m_edges[i][j]!=NULL);
    }
    virtual int vCount()
    {
        return N;
    }
    virtual int eCount()
    {
        return m_ecount;
    }
    virtual int OD(int i)//������i��
    {
        int ret = 0;
        if((0 <= i)&&(i < vCount()))
        {
            for(int j=0;j<vCount();j++)
            {
                if(m_edges[i][j] != NULL) ret++;
            }
        }
        else
        {
            //�׳��쳣
        }
        return ret;
    }
    virtual int ID(int i)//������i��
    {//o(n)
        int ret = 0;
        if((0 <= i)&&(i < vCount()))
        {
            for(int j=0;j<vCount();j++)
            {
                if(m_edges[j][i] != NULL) ret++;
            }
        }
        else
        {
            //�׳��쳣
        }
        return ret;
    }
    ~MatrixGraph()//ɾ���ߵ�ͬʱ��ɾ���ڵ�
    {
        for(int i=0;i<vCount();i++)
        {
            for(int j=0;j<vCount();j++)
            {
                delete m_edges[i][j];
            }
            delete m_vertexes[i];
        }
    }
};
}
#endif