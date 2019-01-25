#ifndef RECTFACTROY_H
#define RECTFACTROY_H
#include "factroy.h"
#include "rect.h"

class RectFactroy : public IFactroy
{
public:
    RectFactroy();

    virtual IShape* CreateInstance(QPoint& ptBegin, QPoint& ptEnd){

        return new Rect(ptBegin, ptEnd);
    }

};

#endif // RECTFACTROY_H
