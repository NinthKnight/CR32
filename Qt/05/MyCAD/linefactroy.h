#ifndef LINEFACTROY_H
#define LINEFACTROY_H
#include "factroy.h"
#include "line.h"

class LineFactroy : public IFactroy
{
public:
    LineFactroy();

    virtual IShape* CreateInstance(QPoint& ptBegin, QPoint& ptEnd){

        return new line(ptBegin, ptEnd);
    }

};

#endif // LINEFACTROY_H
