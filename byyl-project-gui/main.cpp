// Copyright (c) 2024, 蒋昕玮
// 保留所有权利。
// 版本: 1.0
// 功能摘要：
// 窗口运行入口
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
