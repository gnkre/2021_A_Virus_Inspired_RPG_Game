#include "Object.h"

Object::Object(string name_in, string tag_in) :name(name_in), tag(tag_in) {};
Object::Object()
{
    name = "NULL";
    tag = "NULL";
}
void Object::setName(string name_in)
{
    name = name_in;
    return;
}

void Object::setTag(string tag_in)
{
    tag = tag_in;
    return;
}

string Object::getName()
{
    return name;
}

string Object::getTag()
{
    return tag;
}