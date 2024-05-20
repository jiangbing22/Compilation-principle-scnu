#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QHash>
#include<QRegularExpressionMatch>
#include<QDebug>
#include<QMessageBox>
#include<iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_open_file_button_clicked()
{
    filePath = QFileDialog::getOpenFileName(this, "Open File", QString(), "Text Files (*.txt)");
    // file = copyString(filePath.toUtf8().data(),s);
    // s.setsource(file);
    // qDebug()<<file;
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->codeEdit->setText(in.readAll());
            file.close();
        }
    }
}


void MainWindow::on_parse_button_clicked()
{
    if(filePath.isEmpty())
    {
        QMessageBox::warning(nullptr, "Warning", "请先打开文件");
        return;
    }
    scaner temp_scan;
    parser temp_p;
    auto file = copyString(filePath.toUtf8().data(),temp_scan);
    temp_scan.setsource(file);
    TreeNode * root = temp_p.parse(temp_scan);
    tree.build(root,0);
    tree.show();
}


void MainWindow::on_gettoken_button_clicked()
{

    if(filePath.isEmpty())
    {
         QMessageBox::warning(nullptr, "Warning", "请先打开文件");
        return;
    }
    scaner s;
    auto file = copyString(filePath.toUtf8().data(),s);
    s.setsource(file);
    auto token = s.getToken();
    printtoken(token, s.gettokenstring());
    while (token != ENDFILE)
    {
        token = s.getToken();
        printtoken(token, s.gettokenstring());
    }
}

void MainWindow:: printtoken(TokenType token,const char* tokenString)
{
    QString text;
    switch (token) {
    // 保留字
    case IF:      text = "Reserved word: if"; break;
    case ELSE:    text = "Reserved word: else"; break;
    case END:     text = "Reserved word: end"; break;
    case READ:    text = "Reserved word: read"; break;
    case WRITE:   text = "Reserved word: write"; break;
    case FOR:    text = "Reserved word: for"; break;
    case ENDWHILE:    text = "Reserved word: endwhile"; break;
    case UNTIL:    text = "Reserved word: until"; break;
    // 赋值符号
    case ASSIGN:  text = "ASSIGN :="; break;
    // 比较运算符
    case EQ:      text = "EQ ="; break;
    case LT:      text = "LT <"; break;
    case LT_EQ:   text = "LT_EQ <="; break;
    case GT:      text = "GT >"; break;
    case GT_EQ:   text = "GT_EQ >="; break;
    case NOT_EQ:  text = "NOT_EQ <>"; break;
    // 算术运算符
    case PLUS:    text = "PLUS +"; break;
    case MINUS:   text = "MINUS -"; break;
    case TIMES:   text = "TIMES *"; break;
    case OVER:    text = "OVER /"; break;
    case MOD:     text = "MOD %"; break; // 注意：%在Qt中是特殊字符，表示模运算符
    case POWER:   text = "POWER ^"; break;
    // 逻辑运算符
    case OR:      text = "or (|)"; break;
    case AND:     text = "and (&)"; break;
    // 正则表达式相关
    case RANGE:   text = "char range (-)"; break;
    case RE_EQ:   text = "regex equal (==)"; break;
    case RECHAR:  text = QString("regex character: %1").arg(tokenString); break;
    case CLOSURE: text = "closure (#)"; break;
    case OPTIONAL: text = "optional (?)"; break;
    case DOLLAR:  text = "end of line ($)"; break;
    // 括号
    case LBRACKET: text = "left bracket ([)"; break;
    case RBRACKET: text = "right bracket (])"; break;
    case ANYCHAR:  text = "any character (.)"; break;
    // 其他符号
    case LPAREN:   text = "Left Parenthesis ("; break;
    case RPAREN:   text = "Right Parenthesis )"; break;
    case SEMI:     text = "Semicolon (;)"; break;
    // 操作符
    case INCREMENT: text = "Increment (++)"; break;
    case DECREMENT: text = "Decrement (--)"; break;
    // 文件结束
    case ENDFILE:  text = "End of File"; break;
    // 错误处理
    case ERROR:    text = QString("Error: %1").arg(tokenString); break;
    // 标识符和数字
    case ID:       text = QString("Identifier: %1").arg(tokenString); break;
    case NUM:      text = QString("Number: %1").arg(tokenString); break;
    // 默认的未知token
    default:       text = "Unknown token"; break;
    }

    // 添加换行符，因为通常每个token打印后都希望换行
    text += "\n";

    QTextCursor cursor = ui->codeEdit->textCursor();
    cursor.movePosition(QTextCursor::End); // 移动光标到文档末尾
    cursor.insertText(text); // 插入文本
    ui->codeEdit->setTextCursor(cursor); // 设置文本编辑器的当前光标
    ui->codeEdit->ensureCursorVisible(); // 确保新插入的文本可见
}
