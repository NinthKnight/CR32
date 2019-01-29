/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *act_line;
    QAction *act_ecl;
    QAction *act_rect;
    QAction *act_sel;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        act_line = new QAction(MainWindow);
        act_line->setObjectName(QStringLiteral("act_line"));
        act_line->setCheckable(true);
        act_line->setChecked(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/img/res/line.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        act_line->setIcon(icon);
        act_ecl = new QAction(MainWindow);
        act_ecl->setObjectName(QStringLiteral("act_ecl"));
        act_ecl->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/img/res/ellc.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        act_ecl->setIcon(icon1);
        act_rect = new QAction(MainWindow);
        act_rect->setObjectName(QStringLiteral("act_rect"));
        act_rect->setCheckable(true);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/img/res/rect.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        act_rect->setIcon(icon2);
        act_sel = new QAction(MainWindow);
        act_sel->setObjectName(QStringLiteral("act_sel"));
        act_sel->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(act_line);
        menu->addAction(act_ecl);
        menu->addAction(act_rect);
        menu_2->addAction(act_sel);
        mainToolBar->addAction(act_line);
        mainToolBar->addAction(act_rect);
        mainToolBar->addAction(act_ecl);
        mainToolBar->addSeparator();
        mainToolBar->addAction(act_sel);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        act_line->setText(QApplication::translate("MainWindow", "\347\233\264\347\272\277", nullptr));
        act_ecl->setText(QApplication::translate("MainWindow", "\346\244\255\345\234\206", nullptr));
        act_rect->setText(QApplication::translate("MainWindow", "\347\237\251\345\275\242", nullptr));
        act_sel->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\345\233\276\345\275\242", nullptr));
        menu_2->setTitle(QApplication::translate("MainWindow", "\345\267\245\345\205\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
