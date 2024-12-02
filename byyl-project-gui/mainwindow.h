// Copyright (c) 2024, 蒋昕玮
// 保留所有权利。
// 版本: 1.0
// 功能摘要:
// 该类定义了一个Qt应用程序的主窗口，用于提供图形用户界面（GUI）与用户交互。 
// 它包括文件打开、保存、生成、分析等多种功能，支持正则表达式处理、词法分析、语法分析等操作。
// 此类通过QTextEdit等控件与用户交互，调用LALR分析器、DFA生成器等进行各种操作。
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// 引入Qt的库和自定义的头文件
#include <QFileDialog>
#include <QHash>
#include <QRegularExpressionMatch>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>
#include <QMainWindow>
#include <QTextEdit>
#include <QStandardItem>
#include <LALR.h>
#include <DFA.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // 构造函数，初始化界面和其他组件
    MainWindow(QWidget *parent = nullptr);

    // 析构函数，清理资源
    ~MainWindow();

private slots:
    // 各种按钮点击事件的槽函数
    void on_pushButton_clicked();  // 点击按钮事件
    void on_saveButton_clicked();  // 保存文件按钮事件
    void on_generateButton_clicked(); // 生成按钮事件
    void on_openreButton_clicked();  // 打开正则表达式按钮事件
    void on_savere_Button_clicked(); // 保存正则表达式按钮事件
    void on_generate_reButton_clicked(); // 生成正则表达式按钮事件
    void on_savecode_Button_clicked();  // 保存代码按钮事件
    void on_openlex_Button_clicked();   // 打开词法分析文件按钮事件
    void on_opencode_Button_clicked();  // 打开代码文件按钮事件
    void on_startana_Button_clicked();  // 启动分析按钮事件
    void on_savelex_Button_clicked();   // 保存词法分析结果按钮事件
    void on_gettoken_Button_clicked();  // 获取token按钮事件
    void on_gentree_Button_clicked();   // 生成语法树按钮事件

    void on_pushButton_2_clicked();

private:
    // UI组件
    Ui::MainWindow *ui;

    // 文件路径相关
    QString filePath;  // 当前文件路径
    QString sytanxCodePath;  // 语法代码文件路径
    QString codePath;  // 代码文件路径
    QString lexPath;   // 词法分析文件路径
    QString opPath; //语法分析运算符文件路径
    // 辅助函数，将vector<int>转换为QString
    QString vectorToQString(const std::vector<int> &vec);
};

// 用于打印first集映射表到文本编辑控件
void printFirstMap(QTextEdit* textEdit, const std::unordered_map<std::string, std::unordered_set<std::string>>& firstMap);

// 用于打印follow集映射表到文本编辑控件
void printFollowMap(QTextEdit* textEdit, const std::unordered_map<std::string, std::unordered_set<std::string>>& followMap);

#endif // MAINWINDOW_H
