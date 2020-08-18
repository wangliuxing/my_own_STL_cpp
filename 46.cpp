
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "12-Object.h"
using namespace std;
using namespace Wang;
class Test : public Object
{
    int key1;//high
    int key2;//low
public:
    Test(int k1,int k2)
    {
        key1 = k1;
        key2 = k2;
    }
    bool operator ==(const Test& t)
    {
        return ((key1 == t.key1)&&(key2 == t.key2));
    }
    bool operator !=(const Test& t)
    {
        return !(*this == t);
    }
    bool operator <(const Test& t)
    {
        return ((key1 < t.key1)||(key1 == t.key1)&&(key2 < t.key2));
    }
    bool operator >=(const Test& t)
    {
        return !(*this < t );
    }
    bool operator >(const Test& t)
    {
        return ((key1 > t.key1)||(key1 == t.key1)&&(key2 > t.key2));
    }
    bool operator <=(const Test& t)
    {
        return !(*this > t );
    }
};
int main()
{


    return 0;
}
