#ifndef FRAMEWND_H
#define FRAMEWND_H

#include <QWidget>
#include <QPoint>
#include <QList>
#include "line.h"
#include "rect.h"
#include "eclipse.h"
#include <qsharedpointer.h>
#include "factroy.h"

namespace Ui {
class MainWindow;
}


class FrameWnd : public QWidget
{
    Q_OBJECT
public:
    explicit FrameWnd(QWidget *parent = nullptr, Ui::MainWindow *ui = nullptr);

public:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void setCurFactroy(IFactroy* f){
        m_Factory = QSharedPointer<IFactroy>(f);
    }

private:
    QPoint m_ptBegin;
    QPoint m_ptEnd;

    QSharedPointer<IFactroy> m_Factory;

    Ui::MainWindow *ui;

    //添加容器
    QList<QSharedPointer<IShape>> m_ShapeLst;

    QSharedPointer<IShape> m_selShape;

signals:

public slots:
    void OnTriggered(QAction *action);
};

#endif // FRAMEWND_H
