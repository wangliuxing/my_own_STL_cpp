#ifndef _OBJECT
#define _OBJECT

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
namespace Wang
{
class Object
{
public:
    void*operator new(unsigned int size) throw();//�������쳣����mallocʧ��ʱ�����ص��ǿ�ֵ�������׳��쳣
    void operator delete(void *p);
    void*operator new[](unsigned int size) throw();
    void operator delete[](void *p);
    bool operator ==(const Object& object);
    bool operator !=(const Object& object);
    virtual ~Object()=0;
};
    void* Object::operator new(unsigned int size)throw()
    {

        return malloc(size);
    }
    void Object::operator delete(void *p)
    {
        free(p);
    }
    void* Object::operator new[](unsigned int size)throw()
    {
        return malloc(size);
    }
    void Object::operator delete[](void *p)
    {
        free(p);
    }
    Object::~Object()
    {

    }
    bool Object::operator ==(const Object& object)
    {
        return (this == &object);
    }
    bool Object::operator !=(const Object& object)
    {
        return (this != &object);
    }
}
/*
class test: public Wang::Object
{
public:
        int i;
        int j;//����һ�����ص�ָ���麯����ָ��
};
class child: public test
{
public:
        int k;
};
int main()
{
    Wang::Object* p1=new test();
    Wang::Object* p2=new child();
    delete p1;
    delete p2;
    return 0;
} �����������11.cpp������д
*/
#endif // _OBJECT