#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QHash>
#include<QRegularExpressionMatch>
#include<QDebug>
#include<QMessageBox>
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

void MainWindow::on_save_button_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", QString(), "Text Files (*.txt)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->regex_edit->toPlainText();
            file.close();
        }
    }
}


void MainWindow::on_load_button_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QString(), "Text Files (*.txt)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->regex_edit->setText(in.readAll());
            file.close();
        }
    }
}
void MainWindow::on_to_nfa_button_clicked()
{
    ui->NFA_tableWidget->clear();
    ui->NFA_tableWidget->setColumnCount(0);
    ui->NFA_tableWidget->setRowCount(0);
    QString regexString = ui->regex_edit->toPlainText();
    static QRegularExpression qregex("\\b([a-zA-Z0-9]+)\\s*=\\s*([^,\n]+)");
    static QRegularExpression end("\\b_([a-zA-Z0-9]+)\\s*=\\s*([^,\n]+)");
    QRegularExpressionMatchIterator i = qregex.globalMatch(regexString);
    QMap<QString, QString> resultMap;
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        QString key = match.captured(1).trimmed();
        QString value = match.captured(2).trimmed();
        qDebug()<<key<<":"<<value;
        resultMap.insert(key, value);
    }


    QRegularExpressionMatchIterator j = end.globalMatch(regexString);
    if(!j.hasNext())
    {
        QMessageBox::warning(nullptr, "Warning", "请输入合法的正则表达式，且有一个含“_”的最终表达式");
        return;
    }
    QRegularExpressionMatch match2 = j.next();
    QString key2 = match2.captured(1).trimmed();
    QString result = match2.captured(2).trimmed();
    for (auto it = resultMap.begin(); it != resultMap.end(); ++it)
    {
        result.replace(it.key(), it.value());
    }

    QRegularExpression r(result);
    QRegularExpressionValidator validator(r);
    qDebug()<<"result"<<result;
    if (!validator.regularExpression().isValid()) {
        // 正则表达式不合法，弹出警告框
        QMessageBox::warning(nullptr, "Warning", "请输入合法的正则表达式");
        return;
    }


    regex.create(result.toStdString());
    NFA.build_NFA(regex);
    auto graph=NFA.get_graph();
    QStringList header;
    header<<"node";
    auto key=NFA.getkey();
    for(auto i:key)
    {
        header<<QString(i);
    }
    ui->NFA_tableWidget->setColumnCount(header.size());
    ui->NFA_tableWidget->setHorizontalHeaderLabels(header);
    qDebug()<<header;


    int row=0;
    int column=0;
    for(auto i:graph)
    {
        column=0;
        ui->NFA_tableWidget->insertRow(row);
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(row));
        ui->NFA_tableWidget->setItem(row,column,item1);
        column++;
        for(auto j:key)
        {
            QTableWidgetItem *item = new QTableWidgetItem(vectorToQString(i[j]));

            ui->NFA_tableWidget->setItem(row,column,item);
            column++;
        }
        row++;
    }
    ui->NFA_start->setText("起始节点:"+QString::number(NFA.get_start()));
    ui->NFA_end->setText("终止节点:"+QString::number(NFA.get_end()));
     ui->NFA_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}



void MainWindow::on_exit_button_clicked()
{
    QWidget::close();
}

QString MainWindow::vectorToQString(const std::vector<int> &vec) {
    QString result;

    // 遍历 vector<int> 中的每个元素
    for (size_t i = 0; i < vec.size(); ++i) {
        result += QString::number(vec[i]);

        // 如果不是最后一个元素，则添加一个分隔符，例如逗号
        if (i < vec.size() - 1) {
            result += ",";
        }
    }
    return result;
}


void MainWindow::on_to_DFA_button_clicked()
{
    DFA.build_from_NFA(NFA);
    ui->DFA_tableWidget->clear();
    ui->DFA_tableWidget->setColumnCount(0);
    ui->DFA_tableWidget->setRowCount(0);
    auto graph=DFA.get_Graph();
    QStringList header;
    header<<"node"<<"node_set";
    auto key=DFA.get_key();
    for(auto i:key)
    {
        header<<QString(i);
    }
    ui->DFA_tableWidget->setColumnCount(header.size());
    ui->DFA_tableWidget->setHorizontalHeaderLabels(header);
    qDebug()<<header;


    int row=0;
    int column=0;
    for(auto i:graph)
    {
        column=0;
        ui->DFA_tableWidget->insertRow(row);
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(row));
        ui->DFA_tableWidget->setItem(row,column,item1);
        column++;
        QTableWidgetItem *item2 = new QTableWidgetItem(vectorToQString(i.first));
        ui->DFA_tableWidget->setItem(row,column,item2);
        column++;
        for(auto j:key)
        {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(DFA.state_map[DFA.vectorToString(i.second[j])]));
            ui->DFA_tableWidget->setItem(row,column,item);
            column++;
        }
        row++;
    }
    ui->DFA_start->setText("起始节点:"+QString::number(DFA.get_start()));
    auto temp=DFA.get_end();
    ui->DFA_end->setText("终止节点:"+QString::fromStdString(DFA.setToString(temp)));
     ui->DFA_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}


void MainWindow::on_minimize_button_clicked()
{
    DFA.minimize();
    ui->MIN_tableWidget->clear();
    ui->MIN_tableWidget->setColumnCount(0);
    ui->MIN_tableWidget->setRowCount(0);
    auto graph=DFA.get_minimizeGraph();
    QStringList header;
    header<<"node";
    auto key=DFA.get_key();
    for(auto i:key)
    {
        header<<QString(i);
    }
    ui->MIN_tableWidget->setColumnCount(header.size());
    ui->MIN_tableWidget->setHorizontalHeaderLabels(header);
    qDebug()<<header;


    int row=0;
    int column=0;
    for(auto i:graph)
    {
        column=0;
        ui->MIN_tableWidget->insertRow(row);
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(i.first));
        ui->MIN_tableWidget->setItem(row,column,item1);
        column++;
        for(auto j:key)
        {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(i.second[j]));
            ui->MIN_tableWidget->setItem(row,column,item);
            column++;
        }
        row++;
    }
    ui->MIN_start->setText("起始节点:"+QString::number(DFA.get_start()));
    auto temp=DFA.get_minimize_end();
    ui->MIN_end->setText("终止节点:"+QString::fromStdString(DFA.setToString(temp)));
    ui->MIN_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

