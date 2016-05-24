#ifndef ITEM_H
#define ITEM_H
#include"object.h"

class Item:public Object{
public:
    virtual void pickedUp() = 0;
    virtual ~Item() = 0;
};

#endif
