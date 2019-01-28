#include "imycommand.h"

IMyCommand::IMyCommand(QList<QSharedPointer<IShape>>& ShapeLst)
           : m_ShapeLst(ShapeLst)
{

}
