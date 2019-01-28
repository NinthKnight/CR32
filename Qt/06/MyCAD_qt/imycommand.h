#ifndef IMYCOMMAND_H
#define IMYCOMMAND_H

#include <QList>
#include <QSharedPointer>
#include "ishape.h"

class IMyCommand
{
public:
    IMyCommand(QList<QSharedPointer<IShape>>& ShapeLst);

    virtual void redo() = 0; //重做
    virtual void undo() = 0; //撤销

    QList<QSharedPointer<IShape>>& m_ShapeLst;
};

#endif // IMYCOMMAND_H
