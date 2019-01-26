#ifndef FACTROY_H
#define FACTROY_H
#include "ishape.h"

class IFactroy
{
public:
    IFactroy();

    virtual IShape* CreateInstance(QPoint& ptBegin, QPoint& ptEnd) = 0;
};

#endif // FACTROY_H
