#include "framewnd.h"
#include <qpainter.h>
#include <qdebug.h>
#include <QMouseEvent>
#include "ui_mainwindow.h"
#include "linefactroy.h"

FrameWnd::FrameWnd(QWidget *parent, Ui::MainWindow *u) : QWidget(parent)
{
    ui = u;
    m_Factory = QSharedPointer<IFactroy>(new LineFactroy());
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

    if (ui->act_line->isChecked()){

        painter.drawLine(m_ptBegin, m_ptEnd);
    }
    else if(ui->act_rect->isChecked()){

        QSharedPointer<Rect>(new Rect(m_ptBegin, m_ptEnd))->Draw(painter);
    }

}

void FrameWnd::mousePressEvent(QMouseEvent *event)
{
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

void FrameWnd::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "mouseMoveEvent" << endl;

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

    m_ptEnd = event->pos();

    if (m_Factory != nullptr){
         m_ShapeLst.push_front(QSharedPointer<IShape>(m_Factory->CreateInstance(m_ptBegin, m_ptEnd)));
    }


    qDebug() << "mouseReleaseEvent:" << m_ptEnd << endl;

    repaint();
}

