#ifndef INSERTCMD_H
#define INSERTCMD_H
#include "imycommand.h"

class InsertCmd : public IMyCommand
{
public:
    InsertCmd(QList<QSharedPointer<IShape>>& ShapeLst, QSharedPointer<IShape> Shape);

    //重做
    virtual void redo(){

        m_ShapeLst.push_back(m_Shape);

    }


    //撤销
    virtual void undo(){

        for (auto it = m_ShapeLst.begin(); it != m_ShapeLst.end(); it++){

            if (*it == m_Shape){
                m_ShapeLst.erase(it);
                break;
            }
        }
    }

private:
    QSharedPointer<IShape> m_Shape;

};

#endif // INSERTCMD_H
