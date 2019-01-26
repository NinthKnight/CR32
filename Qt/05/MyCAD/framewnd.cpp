#include "framewnd.h"
#include <qpainter.h>
#include <qdebug.h>
#include <QMouseEvent>
#include "ui_mainwindow.h"
#include "linefactroy.h"

FrameWnd::FrameWnd(QWidget *parent, Ui::MainWindow *u) : QWidget(parent),
    m_ctxMenu(this), m_SetDlg(this)
{
    m_IsCurPaint = false;
    ui = u;
    m_Factory = QSharedPointer<IFactroy>(new LineFactroy());

    setContextMenuPolicy(Qt::CustomContextMenu);

    //QWidget::customContextMenuRequested(const QPoint &pos)

    QObject::connect(this,
                     SIGNAL(customContextMenuRequested(const QPoint &)),
                     this,
                     SLOT(OnContextMenu(const QPoint &)));


    QAction* pAct1 = m_ctxMenu.addAction("设置");

    QObject::connect(pAct1,
                     SIGNAL(triggered()),
                     this,
                     SLOT(OnSetting()));


    QObject::connect(ui->act_undo,
                     SIGNAL(triggered()),
                     this,
                     SLOT(OnUndo()));

    QObject::connect(ui->act_redo,
                     SIGNAL(triggered()),
                     this,
                     SLOT(OnRedo()));

}

void FrameWnd::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

//    QPen pen(QColor(255, 0, 0));

//    painter.setPen(pen);

    //绘制链表中的图形
    for(auto shape : m_ShapeLst){

        shape->Draw(painter);
    }

    //绘制当前正在画的图形
    //painter.drawLine(m_ptBegin, m_ptEnd);

    if (m_IsCurPaint){
        if (ui->act_line->isChecked()){

            painter.drawLine(m_ptBegin, m_ptEnd);
        }
        else if(ui->act_rect->isChecked()){

            QSharedPointer<Rect>(new Rect(m_ptBegin, m_ptEnd))->Draw(painter);
        }
    }


}

void FrameWnd::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton){
        return;
    }

    m_IsCurPaint = true;
    m_ptBegin = event->pos();

    qDebug() << "mousePressEvent:" << m_ptBegin << endl;

    if (m_selShape.data() != nullptr){
        m_selShape->SetSelect(false);
    }

    //表示是选中的状态
    if (ui->act_sel->isChecked()){
        //遍历list判断图形是否被选中
        for(auto shape : m_ShapeLst){

            if (shape->IsSelect(m_ptBegin)){
                m_selShape = shape;

                shape->SetSelect(true);
                break;
            }
        }
    }

}

void FrameWnd::OnTriggered(QAction *action)
{
    qDebug() << "void FrameWnd::OnTriggered(QAction *action)" << endl;

    //根据用户的选择来判断创建合适的工厂
}

void FrameWnd::OnContextMenu(const QPoint &pos)
{
    qDebug() << "OnContextMenu" << endl;



    m_ctxMenu.exec(QCursor::pos());

}

void FrameWnd::OnSetting()
{
    qDebug() << "OnSetting" << endl;

    m_SetDlg.exec();

    //m_color =

}

//撤销
void FrameWnd::OnUndo()
{
    qDebug() << "FrameWnd::OnUndo" << endl;

    if (m_doStk.empty()){

        return ;
    }

    QSharedPointer<IMyCommand> curCmd = m_doStk.top();
    m_doStk.pop();

    curCmd->undo();

    m_undoStk.push(curCmd);

    repaint();
}

void FrameWnd::OnRedo()
{
    qDebug() << "FrameWnd::OnRedo" << endl;

    if (m_undoStk.empty()){

        return ;
    }

    QSharedPointer<IMyCommand> curCmd = m_undoStk.top();
    m_undoStk.pop();

    curCmd->redo();

    m_doStk.push(curCmd);

    repaint();
}

void FrameWnd::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "mouseMoveEvent: " << event->buttons() << endl;
    if (event->buttons() != Qt::LeftButton){
        return;
    }

    m_ptEnd = event->pos();

    //qDebug() << "mouseReleaseEvent:" << m_ptEnd << endl;

    if (m_selShape.data() != nullptr){
        m_selShape->Move(m_ptBegin, m_ptEnd);
        m_ptBegin = m_ptEnd;
    }

    repaint();
}

void FrameWnd::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug() << "mouseReleaseEvent" << endl;
    if (event->button() != Qt::LeftButton){
        return;
    }


    m_ptEnd = event->pos();

    if (m_Factory != nullptr){
        //m_ShapeLst.push_front(QSharedPointer<IShape>(m_Factory->CreateInstance(m_ptBegin, m_ptEnd)));

         //产生一个插入动作
        QSharedPointer<IMyCommand> insertCmd =
                QSharedPointer<IMyCommand>(new InsertCmd(m_ShapeLst,
                                                         QSharedPointer<IShape>(m_Factory->CreateInstance(m_ptBegin, m_ptEnd))));

        m_doStk.push_back(insertCmd);

        insertCmd->redo();

        //m_ptBegin = m_ptEnd;
        m_IsCurPaint = false;

    }


    qDebug() << "mouseReleaseEvent:" << m_ptEnd << endl;

    repaint();
}

