#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QFileDialog"
#include <QString>
#include <string>
#include<iostream>
#include <iostream>
#include <string>
#include<unordered_set>
#include<vector>
#include<regex>
namespace token {
using namespace std;

/* 单词编码 */

enum TokenCode
{
    UNDEF = 0,
    KEYWORD,
    OPERATOR,
    IDENTIFIER,
    COMMENT,
    DELIMITER,
    INT,
    FLOAT,
    CHAR,
    STRING,
    SPECIAL
};
struct TOKEN
{
    string word;
    TokenCode code;
    TOKEN(string a, TokenCode b) :word(a), code(b) {};
};
const std::unordered_set<std::string> keywords = {
    "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto",
    "bitand", "bitor", "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t", "class",
    "compl", "concept", "const", "consteval", "constexpr", "constinit", "const_cast", "continue", "co_await",
    "co_return", "co_yield", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum",
    "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int", "long",
    "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private",
    "protected", "public", "register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof",
    "static", "static_assert", "static_cast", "struct", "switch", "synchronized", "template", "this",
    "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
    "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq","include","main"
};
const std::unordered_set<char> operators = { '+', '-', '*', '/', '=', '!', '<', '>', '&', '|', '^', '%' };
const std::unordered_set<char> delimiters = { '(', ')', '{', '}', '[', ']', ',', ';', '.', ':','#','\"','\'','\\' };

bool isKeyword(const std::string& word) {
    return keywords.find(word) != keywords.end();
}
bool isOperator(const char word) {
    return operators.find(word) != operators.end();
}
bool isDelimiter(const char word) {
    return delimiters.find(word) != delimiters.end();
}
string to_chinese(TokenCode key)
{
    switch (key)
    {
    case UNDEF:
        return "未定义字符";
        break;
    case KEYWORD:
        return "关键字";
        break;
    case OPERATOR:
        return "运算符";
        break;
    case IDENTIFIER:
        return "标识符";
        break;
    case COMMENT:
        return "注释";
        break;
    case DELIMITER:
        return "分界符";
        break;
    case INT:
        return "整数";
        break;
    case FLOAT:
        return "浮点数";
        break;
    case CHAR:
        return "字符";
        break;
    case STRING:
        return "字符串";
        break;
    case SPECIAL:
        return"特殊字符";
        break;
    default:
        return "未知类型";
        break;
    }
}
bool isLetter(char letter)
{
    if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') || letter == '_')
        return true;
    return false;

}
bool isDigit(char digit)
{
    if (digit >= '0' && digit <= '9')
        return true;
    return false;
}

vector<TOKEN> scan(string code)
{
    string tokenstring;
    vector<TOKEN> result;
    string::const_iterator it = code.begin();
    while (it != code.end())
    {
        char ch = *it;
        if (ch == ' ' || ch == '\n' || ch == '\t')
        {
            it++;
            continue;
        }
        else if (isLetter(ch))
        {
            tokenstring = "";
            while (isLetter(ch))
            {
                tokenstring.push_back(ch);
                it++;
                ch = *it;
            }
            if (isKeyword(tokenstring))
            {
                TOKEN token(tokenstring, KEYWORD);
                result.push_back(token);

            }
            else
            {
                TOKEN token(tokenstring, IDENTIFIER);
                result.push_back(token);
            }
        }
        else if (isDigit(ch))
        {
            bool isfloat = false;
            tokenstring = "";
            while (isDigit(ch))
            {
                tokenstring.push_back(ch);
                it++;
                ch = *it;
                if (ch == '.' && !isfloat)
                {
                    isfloat = true;
                    tokenstring.push_back(ch);
                    it++;
                    ch = *it;
                }
            }
            if (isfloat)
            {
                TOKEN token(tokenstring, FLOAT);
                result.push_back(token);
            }
            else
            {
                TOKEN token(tokenstring, INT);
                result.push_back(token);
            }

        }
        else if (isDelimiter(ch))
        {
            tokenstring = "";
            if (ch == '\"')
            {
                tokenstring.push_back(ch);
                it++;
                ch = *(it);
                while (ch != '\"')
                {
                    ch = *it;
                    tokenstring.push_back(ch);
                    it++;
                }
                TOKEN token(tokenstring, STRING);
                result.push_back(token);

            }
            else
            {
                tokenstring = ch;
                TOKEN token(tokenstring, DELIMITER);
                result.push_back(token);
                it++;
            }
        }
        else if (isOperator(ch))
        {
            tokenstring = "";
            if (ch == '/')
            {
                regex regexComment("^//.*$|/\\*.*?\\*/", regex::ECMAScript); // 修改正则表达式以匹配单行和多行注释
                smatch re_result;
                string::const_iterator iterStart = it;
                string::const_iterator iterEnd = code.end();
                if (regex_search(iterStart, iterEnd, re_result, regexComment))
                {
                    TOKEN token(re_result[0], COMMENT);
                    result.push_back(token);
                    it = re_result[0].second;
                }
                else
                {
                    tokenstring = ch;
                    TOKEN token(tokenstring, OPERATOR);
                    result.push_back(token);
                    ++it;
                }
            }
            else if (ch == '<')
            {
                regex regexComment("^<.*>$", regex::ECMAScript);
                smatch re_result;
                string::const_iterator iterStart = it;
                string::const_iterator iterEnd = code.end();
                if (regex_search(iterStart, iterEnd, re_result, regexComment))
                {
                    TOKEN token(re_result[0], SPECIAL);
                    result.push_back(token);
                    it = re_result[0].second;
                }
                else
                {
                    while (isOperator(ch))
                    {
                        tokenstring.push_back(ch);
                        it++;
                        ch = *it;
                    }
                    TOKEN token(tokenstring, OPERATOR);
                    result.push_back(token);
                }
            }
            else
            {
                while (isOperator(ch))
                {
                    tokenstring.push_back(ch);
                    it++;
                    ch = *it;
                }
                TOKEN token(tokenstring, OPERATOR);
                result.push_back(token);
            }
        }
        else
        {
            tokenstring = ch;
            TOKEN token(tokenstring, UNDEF);
            result.push_back(token);
            ++it;
        }

    }
    return result;
}
}
std::string readFileContent(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 文件打开失败
        return "";
    }

    QTextStream in(&file);
    QString content = in.readAll();

    file.close();
    return content.toStdString();
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    this->setWindowTitle("20222131051蒋昕玮编译原理实验1");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("选择文件"), QDir::currentPath(), tr("文本文件 (*.txt);;C++文件 (*.cpp)"));
    if (!fileNames.isEmpty()) {
        for (const auto& fileName : fileNames) {
            std::string fileContent = readFileContent(fileName);
            ui->plainTextEdit->appendPlainText(QString::fromStdString(fileContent));
            std::vector<token::TOKEN> tokens=token::scan(fileContent);
            for (const auto& token : tokens) {
                QString text = QString::fromStdString( "标记: " +token.word+ ", 类型: "+token::to_chinese(token.code));
                ui->plainTextEdit->appendPlainText(text);
            }
        }
    }
}
