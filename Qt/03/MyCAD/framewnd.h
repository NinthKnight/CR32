#ifndef FRAMEWND_H
#define FRAMEWND_H

#include <QWidget>
#include <QPoint>
#include <QList>
#include "line.h"
#include "rect.h"
#include "eclipse.h"
#include <qsharedpointer.h>

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

private:
    QPoint m_ptBegin;
    QPoint m_ptEnd;

    Ui::MainWindow *ui;
    //添加容器
    QList<QSharedPointer<IShape>> m_ShapeLst;

signals:

public slots:
};

#endif // FRAMEWND_H
