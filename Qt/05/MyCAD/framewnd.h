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
#include <qmenu.h>
#include "settingdlg.h"
#include "imycommand.h"
#include "insertcmd.h"
#include <QStack>

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

    QMenu m_ctxMenu;//表示右键菜单

    SettingDlg m_SetDlg;

    QStack<QSharedPointer<IMyCommand>> m_doStk;
    QStack<QSharedPointer<IMyCommand>> m_undoStk;

    bool m_IsCurPaint;


signals:

public slots:
    void OnTriggered(QAction *action);
    void OnContextMenu(const QPoint &pos);

    void OnSetting();

    void OnUndo();

    void OnRedo();
};

#endif // FRAMEWND_H
