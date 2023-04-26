/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *Hide;
    QGraphicsView *imageGraphicsView;
    QPushButton *openImageButton;
    QPushButton *EncodeButton;
    QPushButton *saveAsButton;
    QTextEdit *toHideTextEdit;
    QWidget *Decode;
    QTextEdit *toRevealTextEdit;
    QGraphicsView *imageGraphicsViewDecode;
    QPushButton *DecodeButton;
    QPushButton *openImageButtonDecode;
    QMenuBar *menubar;
    QMenu *menuSteaganographie;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(629, 429);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 631, 391));
        Hide = new QWidget();
        Hide->setObjectName("Hide");
        imageGraphicsView = new QGraphicsView(Hide);
        imageGraphicsView->setObjectName("imageGraphicsView");
        imageGraphicsView->setGeometry(QRect(10, 10, 411, 291));
        openImageButton = new QPushButton(Hide);
        openImageButton->setObjectName("openImageButton");
        openImageButton->setGeometry(QRect(10, 310, 411, 41));
        EncodeButton = new QPushButton(Hide);
        EncodeButton->setObjectName("EncodeButton");
        EncodeButton->setGeometry(QRect(440, 260, 171, 41));
        saveAsButton = new QPushButton(Hide);
        saveAsButton->setObjectName("saveAsButton");
        saveAsButton->setGeometry(QRect(440, 310, 171, 41));
        toHideTextEdit = new QTextEdit(Hide);
        toHideTextEdit->setObjectName("toHideTextEdit");
        toHideTextEdit->setGeometry(QRect(440, 10, 171, 241));
        tabWidget->addTab(Hide, QString());
        Decode = new QWidget();
        Decode->setObjectName("Decode");
        toRevealTextEdit = new QTextEdit(Decode);
        toRevealTextEdit->setObjectName("toRevealTextEdit");
        toRevealTextEdit->setGeometry(QRect(440, 10, 171, 291));
        imageGraphicsViewDecode = new QGraphicsView(Decode);
        imageGraphicsViewDecode->setObjectName("imageGraphicsViewDecode");
        imageGraphicsViewDecode->setGeometry(QRect(10, 10, 411, 291));
        DecodeButton = new QPushButton(Decode);
        DecodeButton->setObjectName("DecodeButton");
        DecodeButton->setGeometry(QRect(440, 310, 171, 41));
        openImageButtonDecode = new QPushButton(Decode);
        openImageButtonDecode->setObjectName("openImageButtonDecode");
        openImageButtonDecode->setGeometry(QRect(10, 310, 411, 41));
        tabWidget->addTab(Decode, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 629, 22));
        menuSteaganographie = new QMenu(menubar);
        menuSteaganographie->setObjectName("menuSteaganographie");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuSteaganographie->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        openImageButton->setText(QCoreApplication::translate("MainWindow", "Open Image", nullptr));
        EncodeButton->setText(QCoreApplication::translate("MainWindow", "Hide", nullptr));
        saveAsButton->setText(QCoreApplication::translate("MainWindow", "Save As", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Hide), QCoreApplication::translate("MainWindow", "Hide", nullptr));
        DecodeButton->setText(QCoreApplication::translate("MainWindow", "Decode", nullptr));
        openImageButtonDecode->setText(QCoreApplication::translate("MainWindow", "Open Image", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Decode), QCoreApplication::translate("MainWindow", "Decode", nullptr));
        menuSteaganographie->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
