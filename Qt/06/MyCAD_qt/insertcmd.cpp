#include "insertcmd.h"

InsertCmd::InsertCmd(QList<QSharedPointer<IShape>>& ShapeLst, QSharedPointer<IShape> shape)
          :IMyCommand(ShapeLst), m_Shape(shape)
{

}
