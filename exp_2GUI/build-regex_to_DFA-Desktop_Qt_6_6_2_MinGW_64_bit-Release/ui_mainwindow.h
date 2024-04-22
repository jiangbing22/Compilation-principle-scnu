/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *regex_edit;
    QPushButton *save_button;
    QPushButton *load_button;
    QPushButton *to_nfa_button;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *NFA_tableWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *NFA_start;
    QLineEdit *NFA_end;
    QPushButton *to_DFA_button;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *DFA_tableWidget;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *DFA_start;
    QLineEdit *DFA_end;
    QPushButton *minimize_button;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *MIN_tableWidget;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *MIN_end;
    QLineEdit *MIN_start;
    QPushButton *exit_button;
    QMenuBar *menubar;
    QMenu *menu2022;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1149, 775);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 20, 551, 341));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        regex_edit = new QTextEdit(verticalLayoutWidget);
        regex_edit->setObjectName("regex_edit");

        verticalLayout->addWidget(regex_edit);

        save_button = new QPushButton(verticalLayoutWidget);
        save_button->setObjectName("save_button");

        verticalLayout->addWidget(save_button);

        load_button = new QPushButton(verticalLayoutWidget);
        load_button->setObjectName("load_button");

        verticalLayout->addWidget(load_button);

        to_nfa_button = new QPushButton(verticalLayoutWidget);
        to_nfa_button->setObjectName("to_nfa_button");

        verticalLayout->addWidget(to_nfa_button);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(570, 20, 541, 341));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        NFA_tableWidget = new QTableWidget(verticalLayoutWidget_2);
        NFA_tableWidget->setObjectName("NFA_tableWidget");

        verticalLayout_3->addWidget(NFA_tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        NFA_start = new QLineEdit(verticalLayoutWidget_2);
        NFA_start->setObjectName("NFA_start");
        NFA_start->setReadOnly(true);
        NFA_start->setClearButtonEnabled(false);

        horizontalLayout->addWidget(NFA_start);

        NFA_end = new QLineEdit(verticalLayoutWidget_2);
        NFA_end->setObjectName("NFA_end");
        NFA_end->setReadOnly(true);

        horizontalLayout->addWidget(NFA_end);


        verticalLayout_3->addLayout(horizontalLayout);

        to_DFA_button = new QPushButton(verticalLayoutWidget_2);
        to_DFA_button->setObjectName("to_DFA_button");

        verticalLayout_3->addWidget(to_DFA_button);

        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(0, 370, 551, 351));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        DFA_tableWidget = new QTableWidget(verticalLayoutWidget_3);
        DFA_tableWidget->setObjectName("DFA_tableWidget");

        verticalLayout_4->addWidget(DFA_tableWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        DFA_start = new QLineEdit(verticalLayoutWidget_3);
        DFA_start->setObjectName("DFA_start");
        DFA_start->setReadOnly(true);

        horizontalLayout_2->addWidget(DFA_start);

        DFA_end = new QLineEdit(verticalLayoutWidget_3);
        DFA_end->setObjectName("DFA_end");

        horizontalLayout_2->addWidget(DFA_end);


        verticalLayout_4->addLayout(horizontalLayout_2);

        minimize_button = new QPushButton(verticalLayoutWidget_3);
        minimize_button->setObjectName("minimize_button");

        verticalLayout_4->addWidget(minimize_button);

        verticalLayoutWidget_4 = new QWidget(centralwidget);
        verticalLayoutWidget_4->setObjectName("verticalLayoutWidget_4");
        verticalLayoutWidget_4->setGeometry(QRect(570, 370, 541, 351));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        MIN_tableWidget = new QTableWidget(verticalLayoutWidget_4);
        MIN_tableWidget->setObjectName("MIN_tableWidget");

        verticalLayout_5->addWidget(MIN_tableWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        MIN_end = new QLineEdit(verticalLayoutWidget_4);
        MIN_end->setObjectName("MIN_end");
        MIN_end->setReadOnly(true);

        horizontalLayout_3->addWidget(MIN_end);

        MIN_start = new QLineEdit(verticalLayoutWidget_4);
        MIN_start->setObjectName("MIN_start");
        MIN_start->setReadOnly(true);

        horizontalLayout_3->addWidget(MIN_start);


        verticalLayout_5->addLayout(horizontalLayout_3);

        exit_button = new QPushButton(verticalLayoutWidget_4);
        exit_button->setObjectName("exit_button");

        verticalLayout_5->addWidget(exit_button);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1149, 21));
        menu2022 = new QMenu(menubar);
        menu2022->setObjectName("menu2022");
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName("menu_3");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu2022->menuAction());
        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        regex_edit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\257\267\350\276\223\345\205\245\346\255\243\345\210\231\350\241\250\350\276\276\345\274\217</p></body></html>", nullptr));
        save_button->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        load_button->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275", nullptr));
        to_nfa_button->setText(QCoreApplication::translate("MainWindow", "\350\275\254\346\215\242\344\270\272NFA", nullptr));
        NFA_start->setText(QCoreApplication::translate("MainWindow", "\350\265\267\345\247\213\350\212\202\347\202\271", nullptr));
        NFA_end->setText(QCoreApplication::translate("MainWindow", "\347\273\210\346\255\242\350\212\202\347\202\271", nullptr));
        to_DFA_button->setText(QCoreApplication::translate("MainWindow", "\350\275\254\346\215\242\344\270\272DFA", nullptr));
        DFA_start->setText(QCoreApplication::translate("MainWindow", "\350\265\267\345\247\213\350\212\202\347\202\271", nullptr));
        DFA_end->setText(QCoreApplication::translate("MainWindow", "\347\273\210\346\255\242\350\212\202\347\202\271", nullptr));
        minimize_button->setText(QCoreApplication::translate("MainWindow", "DFA\346\234\200\345\260\217\345\214\226", nullptr));
        MIN_end->setText(QCoreApplication::translate("MainWindow", "\350\265\267\345\247\213\350\212\202\347\202\271", nullptr));
        MIN_start->setText(QCoreApplication::translate("MainWindow", "\347\273\210\346\255\242\350\212\202\347\202\271", nullptr));
        exit_button->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        menu2022->setTitle(QCoreApplication::translate("MainWindow", "20222131051", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\350\222\213\346\230\225\347\216\256", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227\346\234\272\347\247\221\345\255\246\344\270\216\346\212\200\346\234\257", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\344\270\211\347\217\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
