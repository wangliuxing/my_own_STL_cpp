#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "12-Object.h"
#include "19-Array.cpp"
using namespace std;
namespace Wang
{
class Sort : public Object
{
private:
    Sort();
    Sort(const Sort&);
    Sort& operator = (const Sort&);
    template<typename T>
    static void Swap(T& a, T& b)
    {
        T c = a;
        a = b;
        b = c;
    }
    template <typename T>
    static void Merge(T src[], T helper[], int begin, int mid, int end, bool mintomax = true)
    {
        int i = begin; int j = mid + 1; int k = begin;
        while((i<=mid)&&(j<=end))
        {
            if(mintomax?(src[i] < src[j]):(src[i] > src[j])){helper[k++] = src[i++];}
            else{helper[k++] = src[j++];}
        }
        while(i<=mid)//把剩余的数据元素进行拷贝
        {
            helper[k++] = src[i++];
        }
        while(j<=end)
        {
            helper[k++] = src[j++];
        }
        for(int i=0;i<=end;i++)
        {
            src[i] = helper[i];//从堆空间中取出数据对原来的数据进行赋值
        }
    }
    template <typename T>
    static void Merge(T src[], T helper[], int begin, int end, bool mintomax = true)
    {
        if(begin == end)
        {
            return;//边界条件
        }
        else
        {
            int mid = (begin + end)/2;
            Merge(src,helper,begin,mid,mintomax);//左边进行归并
            Merge(src,helper,mid+1,end,mintomax);//右边进行归并
            Merge(src,helper,begin,mid,end,mintomax);//左右两边进行归并进行归并
        }
    }
    template<typename T>
    static int Partition(T array[],int begin,int end,bool mintomax=true)
    {
        int pv = array[begin];//首先选择第一个元素为基准
        int i = begin;    int j = end;
        while(true)
        {
            while((i<=j)&&(array[i] <= pv)) i++;
            while((i<=j)&&(array[j] >= pv)) j--;
            if(i>=j) break;
            swap(array[i],array[j]);
        }
        array[j] = pv;
        return j;//返回下标
    }
    template <typename T>
    static void Quick(T array[], int begin, int end)
    {
        if(begin<end)
        {
            int pi = Partition(array,begin,end);//找到基准值的下标
            //使得基准值左边的元素都小于基准值，右边都大于基准值
            Quick(array,begin,pi-1);
            Quick(array,pi+1,end);
        }
    }
public:
    //////////////////////////////////////////////////////////////
    //选择排序
    template<typename T>
    static void Select(T array[], int len, bool mintomax = true)
    //默认情况下进行从小到大排序
    {
        for(int i=0;i<len;i++)
        {
            int m = i;//用一个m记录最小值的下标
            for(int j=i+1;j<len;j++)
            {
                if( mintomax? (array[j] < array[m]): (array[j] > array[m]))
                {
                    m = j;//
                }
            }
            if(m!=i) Swap(array[i], array[m]);
            //用比较操作避开交换操作
        }
    }
    //////////////////////////////////////////////////////////////
    //插入排序
    template<typename T>
    static void Insert(T array[], int len, bool mintomax = true)//默认情况下进行从小到大排序
    {
        for(int i=1;i<len;i++)
        {
            int k = i;
            T e = array[i];//拿出待插入的元素
            for(int j=i-1;(j>=0)&&(mintomax?(array[j]>e):(array[j]<e));j--)//从后向前比较
            {
                array[j+1] = array[j];//向后移动一个位置
                k = j;//记录位置
            }
            if(k != i) array[k] = e;//避免相同元素进行交换
        }
    }
    //////////////////////////////////////////////////////////////
    //冒泡排序
    template<typename T>
    static void Bubble(T array[], int len, bool mintomax = true)
    {
        bool exchange = true;//如果不用排序
        for(int i=0;(i<len)&&exchange;i++)
        {
            exchange = false;

            for(int j=len-1;j>i;j--)
            {
                if(mintomax?(array[j]<array[j-1]):(array[j]>array[j-1]))
                {
                    swap(array[j],array[j-1]);
                    exchange = true;
                }
            }//i以后的所有元素都排好了，就不用排列了，把exchange置为1
        }
    }
    //////////////////////////////////////////////////////////////
    //希尔排序
    template<typename T>
    static void Shell(T array[], int len, bool mintomax = true)
    {
        int d = len;
        do
        {
            d = d/3 + 1;
            for(int i = d;i<len;i+=d)
            {
                int k =i;
                T e = array[i];//拿出待插入的元素
                for(int j=i-d;(j>=0)&&(mintomax?(array[j]>e):(array[j]<e));j-=d)//从后向前比较
                {
                    array[j+d] = array[j];//向后移动一个位置
                    k = j;//记录位置
                }
                if(k != i) array[k] = e;//插入元素
            }
        }while (d>1);
    }
    template <typename T>
    static void Merge(T array[], int len, bool mintomax = true)
    {
        T* helper = new T[len];//申请一个堆空间用于存放数据

        if(helper != NULL)
        {
            Merge(array,helper,0,len-1,true);//len-1主要指的是下标
        }

        delete helper;
    }
    template <typename T>
    static void Quick(T array[], int len, bool mintomax = true)
    {
        Quick(array,0,len-1,mintomax);
    }
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
/**    排序类与数组类发生关系，使用的是所定义的数组   */
    template <typename T>
    static void Select(Array<T>& array,bool mintomax = true)
    {
        Select(array.array(),array.length(),mintomax);
    }
    template <typename T>
    static void Insert(Array<T>& array,bool mintomax = true)
    {
        Insert(array.array(),array.length(),mintomax);
    }
    template <typename T>
    static void Bubble(Array<T>& array,bool mintomax = true)
    {
        Bubble(array.array(),array.length(),mintomax);
    }
    template <typename T>
    static void Shell(Array<T>& array,bool mintomax = true)
    {
        Shell(array.array(),array.length(),mintomax);
    }
    template <typename T>
    static void Merge(Array<T>& array,bool mintomax = true)
    {
        Merge(array.array(),array.length(),mintomax);
    }
    template <typename T>
    static void Quick(Array<T>& array,bool mintomax = true)
    {
        Quick(array.array(),array.length(),mintomax);
    }
};
}


#endif // SORT_H
