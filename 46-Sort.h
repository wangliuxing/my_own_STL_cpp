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
        while(i<=mid)//��ʣ�������Ԫ�ؽ��п���
        {
            helper[k++] = src[i++];
        }
        while(j<=end)
        {
            helper[k++] = src[j++];
        }
        for(int i=0;i<=end;i++)
        {
            src[i] = helper[i];//�Ӷѿռ���ȡ�����ݶ�ԭ�������ݽ��и�ֵ
        }
    }
    template <typename T>
    static void Merge(T src[], T helper[], int begin, int end, bool mintomax = true)
    {
        if(begin == end)
        {
            return;//�߽�����
        }
        else
        {
            int mid = (begin + end)/2;
            Merge(src,helper,begin,mid,mintomax);//��߽��й鲢
            Merge(src,helper,mid+1,end,mintomax);//�ұ߽��й鲢
            Merge(src,helper,begin,mid,end,mintomax);//�������߽��й鲢���й鲢
        }
    }
    template<typename T>
    static int Partition(T array[],int begin,int end,bool mintomax=true)
    {
        int pv = array[begin];//����ѡ���һ��Ԫ��Ϊ��׼
        int i = begin;    int j = end;
        while(true)
        {
            while((i<=j)&&(array[i] <= pv)) i++;
            while((i<=j)&&(array[j] >= pv)) j--;
            if(i>=j) break;
            swap(array[i],array[j]);
        }
        array[j] = pv;
        return j;//�����±�
    }
    template <typename T>
    static void Quick(T array[], int begin, int end)
    {
        if(begin<end)
        {
            int pi = Partition(array,begin,end);//�ҵ���׼ֵ���±�
            //ʹ�û�׼ֵ��ߵ�Ԫ�ض�С�ڻ�׼ֵ���ұ߶����ڻ�׼ֵ
            Quick(array,begin,pi-1);
            Quick(array,pi+1,end);
        }
    }
public:
    //////////////////////////////////////////////////////////////
    //ѡ������
    template<typename T>
    static void Select(T array[], int len, bool mintomax = true)
    //Ĭ������½��д�С��������
    {
        for(int i=0;i<len;i++)
        {
            int m = i;//��һ��m��¼��Сֵ���±�
            for(int j=i+1;j<len;j++)
            {
                if( mintomax? (array[j] < array[m]): (array[j] > array[m]))
                {
                    m = j;//
                }
            }
            if(m!=i) Swap(array[i], array[m]);
            //�ñȽϲ����ܿ���������
        }
    }
    //////////////////////////////////////////////////////////////
    //��������
    template<typename T>
    static void Insert(T array[], int len, bool mintomax = true)//Ĭ������½��д�С��������
    {
        for(int i=1;i<len;i++)
        {
            int k = i;
            T e = array[i];//�ó��������Ԫ��
            for(int j=i-1;(j>=0)&&(mintomax?(array[j]>e):(array[j]<e));j--)//�Ӻ���ǰ�Ƚ�
            {
                array[j+1] = array[j];//����ƶ�һ��λ��
                k = j;//��¼λ��
            }
            if(k != i) array[k] = e;//������ͬԪ�ؽ��н���
        }
    }
    //////////////////////////////////////////////////////////////
    //ð������
    template<typename T>
    static void Bubble(T array[], int len, bool mintomax = true)
    {
        bool exchange = true;//�����������
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
            }//i�Ժ������Ԫ�ض��ź��ˣ��Ͳ��������ˣ���exchange��Ϊ1
        }
    }
    //////////////////////////////////////////////////////////////
    //ϣ������
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
                T e = array[i];//�ó��������Ԫ��
                for(int j=i-d;(j>=0)&&(mintomax?(array[j]>e):(array[j]<e));j-=d)//�Ӻ���ǰ�Ƚ�
                {
                    array[j+d] = array[j];//����ƶ�һ��λ��
                    k = j;//��¼λ��
                }
                if(k != i) array[k] = e;//����Ԫ��
            }
        }while (d>1);
    }
    template <typename T>
    static void Merge(T array[], int len, bool mintomax = true)
    {
        T* helper = new T[len];//����һ���ѿռ����ڴ������

        if(helper != NULL)
        {
            Merge(array,helper,0,len-1,true);//len-1��Ҫָ�����±�
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
/**    �������������෢����ϵ��ʹ�õ��������������   */
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