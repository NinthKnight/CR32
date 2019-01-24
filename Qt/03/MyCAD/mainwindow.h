#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "framewnd.h"
#include <QSharedPointer>
#include <QActionGroup>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_act_line_triggered();

private:
    Ui::MainWindow *ui;

    QActionGroup* m_pActGroup;

    QSharedPointer<FrameWnd> m_FrameWnd;



};

#endif // MAINWINDOW_H
