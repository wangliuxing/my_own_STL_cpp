#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include "12-Object.h"
using namespace std;
namespace Wang
{
template<typename T>
class Queue : public Object
{
public:
    virtual void add(const T& e) = 0 ;//入队列
    virtual void remove() = 0 ;//出队列
    virtual T front() const = 0 ;
    virtual void clear() = 0 ;
    virtual int length() const = 0 ;
};
}
#endif // _QUEUE_H
