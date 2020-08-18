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
        int b;//首顶点的编号
        int e;//尾顶点的编号
        E data;//数据
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
             //抛出异常
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
            //抛出异常
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
    virtual bool isAdjacent(int i,int j) = 0;//判断i与j是否连接
    virtual int TD(int i)
    {
        return (OD(i) + ID(i));
    }
    bool asUndirectrd()//判断是否为无向图
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
    Sharedpoint< Array< Edge<E> > >prim(const E& LIMIT, const bool MINMAX = true)//理论上的最大权值
    {//默认值true找最小生成树
        LinkQueue< Edge<E> > ret;
        if(asUndirectrd())
        {
            DynamicArray<int> adjVex(vCount());// 用于保存各个点
            DynamicArray<bool> mark(vCount());
            DynamicArray<E> cost(vCount());
            Sharedpoint< Array<int> > aj = NULL;//用于获取边的信息
            bool end = false;
            int v = 0;//从0寻找最小生成树
            for(int i=0;i<vCount();i++)
            {
                adjVex[i] = -1;
                mark[i] = false;
                cost[i] = LIMIT;
            }
            mark[v] = true;
            aj = getAdjacent(v);// 获取与v相邻的点
            for(int j=0;j<aj->length();j++)
            {
                cost[(*aj)[j]] = getEdge(v,(*aj)[j]);//保存与v相邻的各个边的权值，保存在各个顶点值下
                adjVex[(*aj)[j]] = v;//保存顶点，把所有与v相连的点保存为v
            }
            for(int i=0;(i<vCount())&&!end;i++)
            {
                E m = LIMIT;//m用于记录最小权值
                int k = -1;//用于记录当前顶点
                for(int j=0;j<vCount();j++)
                {
                    if(!mark[j]&&(MINMAX? (cost[j]<m):(cost[j]>m)))
                    {
                        m = cost[j];//用m找到最小值坐标
                        k = j;
                    }//找最小权值，以及对应顶点的编号
                }
                end = (k == -1);//找不到最小权值，退出整个程序
                if(!end)
                {
                    ret.add(Edge<E>(adjVex[k],k,getEdge(adjVex[k],k)));//加入一条边
                    //找到了点k，以及adjVex[k]相连的这个最小权值，并压入队列
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
            //抛出异常
        }
        if(ret.length()==(vCount()-1))//判断边的数目是否为n-1
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
            if(b != e)//不构成环路
            {
                p[e] = b;//设置前驱矩阵的值，
                ret.add((*edges)[i]);
            }
        }
        if(ret.length() != (vCount()-1))
        {
            //抛出异常
        }
        return toArray(ret);
    }
    Sharedpoint< Array<int> >DFS1(int i)
    {
        DynamicArray<int>* ret = NULL;//返回的是一个数组，用于反映结点访问的先后次序
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
                    }// 所有的与v相连的邻接顶点全部压入栈中
                    r.add(v);// 头结点压入输出队列
                    visited[v] = true;// 把标志位设置为false
                }
            }
            ret = toArray(r);
        }
        else
        {
            //抛出异常
        }
        return ret;
    }
    Sharedpoint< Array<int> > BFS(int i)
    {
        DynamicArray<int>* ret = NULL;//返回的是一个数组，用于反映结点访问的先后次序
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
            //抛出异常
        }
        return ret;
    }

    void DFS2(Graph<V,E>& g, int v, Array<bool>& visited)
    {
        if((0<=v)&&(v<vCount()))
        {
            cout<<v<<endl;//访问结点
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
            //抛出异常
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
                    break;//没有最小路径
                }
                mark[u] = true;
                for(int w=0;w<vCount();w++)//通过已知的最小路径能不能找到其他最小路径
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
            for(int k=path[j];k!=-1;k=path[k])//path保存的顶点的顺序是逆序的，需要通过栈进行中转
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
            //抛出异常
        }
        if(ret.length()<2)
        {
            //抛出异常，表示不可达的
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
                    path[i][j] = -1;//没有连接
                    dist[i][j] = (isAdjacent(i,j)?(path[i][j]=j,getEdge(i,j)):LIMIT);//存在连接
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
             while((x!=-1)&&(x!=y))//遍历所有的连接顶点，x的值不能大于最后一个顶点
             {
                 ret.add(x);
                 x = path[x][y];
             }
             if(x!=-1)
             {
                 ret.add(x);
             }//把最后一个顶点放入返回值中
         }
         else
         {
             //抛出异常
         }
         return toArray(ret);
    }
};
template <int N, typename V, typename E>
class MatrixGraph : public Graph<V, E>
{
protected:
    V* m_vertexes[N];//每个元素都是指针
    E* m_edges[N][N];
    int m_ecount;//记录边的数目
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
            //抛出异常
        }
        return ret;
    }
    virtual bool getVertex(int i, V& value)
    {
        int ret = ((0<=i)&&(i<vCount()));
        if(ret)
        {
            if(m_vertexes[i] != NULL)//存在数据元素
            {
                value = *(m_vertexes[i]);//获取数据元素
            }
            else
            {
                //抛出异常
            }
        }
        return ret;
    }
    virtual bool setVertex(int i, const V& value)//O(1)
    {
        int ret = ((0<=i)&&(i<vCount()));
        if(ret)
        {
            V* data = m_vertexes[i];//初始化data
            if(data == NULL)//存在数据元素
            {
                data = new V();
            }
            if(data != NULL)
            {
                *data = value;
                m_vertexes[i] = data;//异常安全
            }
            else
            {
                //抛出异常
            }
        }
        return ret;
    }
    virtual Sharedpoint< Array<int> > getAdjacent(int i)//获取节点i的邻接顶点
    {//O(n)
        DynamicArray<int>* ret = NULL;
        if((0 <= i)&&(i < vCount()))
        {
            int n = 0;
            for(int j=0;j<vCount();j++)
            {
                if(m_edges[i][j]!=NULL) n++;//遍历第i行
            }
            ret = new DynamicArray<int>(n);//创建一个长度为n的动态数组
            if(ret != NULL)
            {
                for(int j=0,k=0;j<vCount();j++)
                {
                    if(m_edges[i][j]!=NULL) ret->set(k++,j);//放置编号
                }
            }
            else
            {
                //抛出异常
            }
        }
        else
        {
            //抛出异常
        }
        return ret;
    }
    virtual E getEdge(int i, int j)
    {
        E ret;
        if(!getEdge(i, j, ret))
        {
            //抛出异常
        }
        return ret;
    }
    virtual bool getEdge(int i, int j, E& value)//o(1)
    {
        int ret = ((0 <= i)&&(i < vCount())&&(0 <= j)&&(j < vCount()));
        if(ret)
        {
            if(m_edges[i][j] != NULL)//存在数据元素
            {
                value = *(m_edges[i][j]);//获取数据元素
            }
            else
            {
                //抛出异常
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
                ne = new E();//指向堆空间的一片内存
                if(ne != NULL)
                {
                    *ne = value;
                    m_edges[i][j] = ne;
                    m_ecount++;
                }
                else
                {
                    //抛出异常
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
            E* toDel = m_edges[i][j];//指向需要删除的对象
            m_edges[i][j] = NULL;//异常安全
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
    virtual int OD(int i)//遍历第i行
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
            //抛出异常
        }
        return ret;
    }
    virtual int ID(int i)//遍历第i列
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
            //抛出异常
        }
        return ret;
    }
    ~MatrixGraph()//删除边的同时，删除节点
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
