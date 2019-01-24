#ifndef ECLIPSE_H
#define ECLIPSE_H
#include "ishape.h"

class Eclipse : public IShape
{
public:
    Eclipse();

    bool Draw(QPainter& painter);
};

#endif // ECLIPSE_H
