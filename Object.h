#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Object
{
private:
    string name;
    string tag;
public:
    Object();
    Object(string name_in, string tag_in);

    /* pure virtual function */
    virtual bool triggerEvent(Object*) = 0;

    /* Set & Get function*/
    void setName(string name_in);
    void setTag(string tag_in);
    string getName();
    string getTag();
};

#endif // OBJECT_H_INCLUDED
