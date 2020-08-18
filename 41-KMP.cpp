
#include <iostream>
#include <cstring>
#include "39-String.h"
using namespace std;
using namespace Wang;
////////////kmp算法
int* make_pmt(const char* p)//  O(n)
{
    /**
    int len = strlen(p);
    int *ret = static_cast<int*>(malloc(sizeof(int)*len));
    if(ret != NULL)
    {
        int ll = 0;
        ret[0] = 0;
        for(int i=1;i<len;i++)
        {
            while((p[ll] != p[i])&&(ll>0))
            {
                ll = ret[ll-1];
            }
            if(p[ll]==p[i])//进行扩展比对,比对成功，理想算法
            {
                ll++;
            }
            ret[i] = ll;
        }
    }
    return ret;
    */
    int len = strlen(p);
    int *ll = static_cast<int*>(malloc(sizeof(int)*len));
    if(ll != NULL)
    {
        ll[0] = 0;
        ll[1] = 0;//开始修正ll[1]
        for(int i=1;i<len;i++)
        {
            while((p[ll[i]] != p[i])&&(ll[i]>0))
            {
                ll[i] = ll[ll[i]-1]-1;
            }
            if(p[ll[i]]==p[i])
            {
                ll[i]++;
            }
        }
    }
    return ll;
}
int kmp(const char*s, const char* p)//O(n)
{
    int ret = -1;
    int sl = strlen(s);// 长的
    int pl = strlen(p);// 短的
    int *pmt = make_pmt(p);//目标子串为p
    if((pmt != NULL)&&( pl > 0)&&(pl <= sl))
    {
        for(int i=0,j=0;i<sl;i++)
        {
            while((j>0)&&(s[i] != p[j]))//匹配不成功
            {
                j = pmt[j-1];//进行右移，右移动的位置由pmt决定
            }
            if(s[i]==p[j])//匹配成功
            {
                j++;
            }// 长的与短的匹配成功了
            if(j == pl)
            {
                ret = i + 1 - pl;//取得比对成功的位置
                break;
            }
        }
    }
    free(pmt);
    return ret;
}
int main()
{
cout<<kmp("baabax","a")<<endl;
return 0;
}
