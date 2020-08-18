
#include <iostream>
#include <cstring>
#include "39-String.h"
using namespace std;
using namespace Wang;
////////////kmp�㷨
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
            if(p[ll]==p[i])//������չ�ȶ�,�ȶԳɹ��������㷨
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
        ll[1] = 0;//��ʼ����ll[1]
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
    int sl = strlen(s);// ����
    int pl = strlen(p);// �̵�
    int *pmt = make_pmt(p);//Ŀ���Ӵ�Ϊp
    if((pmt != NULL)&&( pl > 0)&&(pl <= sl))
    {
        for(int i=0,j=0;i<sl;i++)
        {
            while((j>0)&&(s[i] != p[j]))//ƥ�䲻�ɹ�
            {
                j = pmt[j-1];//�������ƣ����ƶ���λ����pmt����
            }
            if(s[i]==p[j])//ƥ��ɹ�
            {
                j++;
            }// ������̵�ƥ��ɹ���
            if(j == pl)
            {
                ret = i + 1 - pl;//ȡ�ñȶԳɹ���λ��
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