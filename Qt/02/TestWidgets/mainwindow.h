#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void test(){

        //setupUi(nullptr);

    }

    bool EnumProcess();

signals:
    void test2(int n, char ch);

private slots:
    void on_pushButton_clicked();

    void on_pushButton2_clicked();

    void onTest2(int n, char ch);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
