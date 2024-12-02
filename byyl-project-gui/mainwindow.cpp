// Copyright (c) 2024, 蒋昕玮
// 保留所有权利。
// 版本: 1.0
#include "mainwindow.h"
#include "ui_mainwindow.h"
// 函数实现
void printFirstMap(QTextEdit* textEdit, const std::unordered_map<std::string, std::unordered_set<std::string>>& firstMap) {
    std::ostringstream oss;
    for (const auto& pair : firstMap) {
        oss << "First(" << pair.first << ") = { ";
        for (const auto& item : pair.second) {
            oss << item << " ";
        }
        oss << "}\n";
    }
    textEdit->setPlainText(QString::fromStdString(oss.str()));
}

void printFollowMap(QTextEdit* textEdit, const std::unordered_map<std::string, std::unordered_set<std::string>>& followMap) {
    std::ostringstream oss;
    for (const auto& pair : followMap) {
        oss << "Follow(" << pair.first << ") = { ";
        for (const auto& item : pair.second) {
            oss << item << " ";
        }
        oss << "}\n";
    }
    textEdit->setPlainText(QString::fromStdString(oss.str()));
}
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

void MainWindow::on_pushButton_clicked()
{
    filePath = QFileDialog::getOpenFileName(this, "Open File", QString(), "Text Files (*.txt)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->graEdit->setText(in.readAll());
            file.close();
        }
    }
}


void MainWindow::on_saveButton_clicked()
{
    QString filePath2 = QFileDialog::getSaveFileName(this, "Save File", QString(), "Text Files (*.txt)");
    if (!filePath2.isEmpty()) {
        QFile file(filePath2);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->graEdit->toPlainText();
            file.close();
        }
    }
}


void MainWindow::on_generateButton_clicked()
{
    std::string temp = string(filePath.toLocal8Bit());
    LALR lalr(temp);
    printFirstMap(ui->firstEdit,lalr.G.firstMap);
    printFollowMap(ui->followEdit,lalr.G.followMap);
    printAutomaton(lalr,lalr.head,ui->LR1);
    printAutomaton(lalr,lalr.LALRhead,ui->LALR1);
    printParsingTable(lalr,ui->LALR1table);

}


void MainWindow::on_openreButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QString(), "Text Files (*.txt)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->re_text->setText(in.readAll());
            file.close();
        }
    }
}


void MainWindow::on_savere_Button_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", QString(), "Text Files (*.txt)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->re_text->toPlainText();
            file.close();
        }
    }
}



 void MainWindow::on_generate_reButton_clicked()
{
    // 清空 NFA 表格
    ui->NFA_tableWidget->clear();
    ui->NFA_tableWidget->setColumnCount(0);
    ui->NFA_tableWidget->setRowCount(0);

    // 获取正则表达式输入
    QString regexString = ui->re_text->toPlainText();

    // 定义正则表达式
    static QRegularExpression qregex("\\b([-a-zA-Z0-9]+)\\s*=\\s*([^\\n]+)");
    static QRegularExpression end("\\b_([-a-zA-Z0-9]+)\\s*=\\s*([^\\n]+)");

    // 全局匹配
    QRegularExpressionMatchIterator i = qregex.globalMatch(regexString);
    QMap<QString, QString> resultMap;

    // 遍历匹配项并插入 resultMap
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        QString key = match.captured(1).trimmed();
        QString value = match.captured(2).trimmed();
        resultMap.insert(key, value);
    }

    // 匹配包含“_”符号的表达式
    QRegularExpressionMatchIterator j = end.globalMatch(regexString);
    QMap<QString, QString> results;

    while (j.hasNext()) {
        QRegularExpressionMatch match2 = j.next();
        QString key2 = match2.captured(1).trimmed();
        QString result = match2.captured(2).trimmed();
        results[key2].append(result);
    }

    // 如果没有结果，显示警告
    if (results.isEmpty()) {
        QMessageBox::warning(nullptr, "Warning", "请输入合法的正则表达式，且至少有一个含“_”的最终表达式");
        return;
    }

    // 用 | 连接所有的结果
    QString combinedResult;
    for (auto i = results.begin(); i != results.end(); ++i)
    {
        combinedResult += "(" + i.value() + ")" + "|";
    }

    // 删除最后一个“|”符号
    combinedResult.chop(1);

    // 替换 resultMap 中的变量
    for (auto it = resultMap.begin(); it != resultMap.end(); ++it) {
        combinedResult.replace(it.key(), it.value());
    }

    qDebug() << "Combined Result: " << combinedResult << "\n";

    // 构建 NFA
    RE regex(combinedResult.toStdString());
    // cout<<regex.get_re()<<endl;
    // cout<<regex.get_post()<<endl;
    NFA_graph NFA;
    NFA.build_NFA(regex);

    // 分别保存小的NFA
    // qDebug() << "save NFAs";
    vector<NFA_graph> NFAs;
    for (auto i = results.begin(); i != results.end(); ++i)
    {
        QString replace_re = i.value();
        for (auto it = resultMap.begin(); it != resultMap.end(); ++it) {
            replace_re.replace(it.key(), it.value());
        }
        RE temp_regex(replace_re.toStdString());
        NFA_graph tempNFA;
        // qDebug() << "NFA: " <<i.key()<<" "<<replace_re;
        tempNFA.endtype = i.key().toStdString();
        tempNFA.build_NFA(temp_regex);
        NFAs.push_back(tempNFA);
    }
    //进入局部变量
    // qDebug()<<"Create NFA";
    {
    // 获取 NFA 图并设置表头
    auto graph = NFA.get_graph();
    QStringList header;
    header << "node";
    auto key = NFA.getkey();
    for (auto i : key)
    {
        header << QString(i);
    }

    ui->NFA_tableWidget->setColumnCount(header.size());
    ui->NFA_tableWidget->setHorizontalHeaderLabels(header);
    qDebug() << header;

    // 填充表格内容
    int row = 0;
    int column = 0;
    for (auto i : graph)
    {
        column = 0;
        ui->NFA_tableWidget->insertRow(row);
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(row));
        ui->NFA_tableWidget->setItem(row, column, item1);
        column++;
        for (auto j : key)
        {
            QTableWidgetItem *item = new QTableWidgetItem(vectorToQString(i[j]));
            ui->NFA_tableWidget->setItem(row, column, item);
            column++;
        }
        row++;
    }

    // 设置 NFA 的起始和结束节点
    ui->NFA_start->setText("start_node:" + QString::number(NFA.get_start()));
    ui->NFA_end->setText("end_node:" + QString::number(NFA.get_end()));

    // 自动调整表格列宽
    ui->NFA_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    qDebug()<<"generate DFA\n";
    //生成DFA

    DFA_graph DFA;
    qDebug()<<"Create DFA";
    DFA.build_from_NFA(NFAs);
    ui->DFA_tableWidget->clear();
    ui->DFA_tableWidget->setColumnCount(0);
    ui->DFA_tableWidget->setRowCount(0);
    //进入构建表格局部变量
    {
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
    ui->DFA_start->setText("start:"+QString::number(DFA.get_start()));
    string temp;
    for(auto i:DFA.endstring)
    {
        temp += (to_string(i.first) + "->" +i.second + " ");
    }
    qDebug()<<"endstring"<<temp;
    ui->DFA_end->setText("end:"+QString::fromStdString(temp));
    ui->DFA_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    //最小化DFA；
    qDebug()<<"Create minimize";
    DFA.minimize();
    ui->MIN_tableWidget->clear();
    ui->MIN_tableWidget->setColumnCount(0);
    ui->MIN_tableWidget->setRowCount(0);
    //进入构建表格局部变量
    {
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
    ui->MIN_start->setText("start:"+QString::number(DFA.get_start()));
    string temp;
    for(auto i:DFA.minendstring)
    {
        temp += (to_string(i.first) + "->" +i.second + " ");
    }
    ui->MIN_end->setText("end:"+QString::fromStdString(temp));
    ui->MIN_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }

    auto code = DFA.generateCode();
    ui->code_textEdit->setText(QString::fromStdString(code));
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

void MainWindow::on_savecode_Button_clicked()
{
    QString filePath2 = QFileDialog::getSaveFileName(this, "Save File", QString(), "CPP File (*.cpp)");
    if (!filePath2.isEmpty()) {
        QFile file(filePath2);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->code_textEdit->toPlainText();
            file.close();
        }
    }
}


void MainWindow::on_openlex_Button_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QString(), "Text Files (*.cpp)");
    this->sytanxCodePath=filePath;
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->ana_textEdit->setText(in.readAll());

            file.close();
        }
    }
}


void MainWindow::on_opencode_Button_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QString(), "Text Files (*)");
    this->codePath=filePath;
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->ana_textEdit->setText(in.readAll());
            file.close();
        }
    }
}


void MainWindow::on_startana_Button_clicked()
{
    if (codePath.isEmpty()) {
        QMessageBox::warning(this, "Warning", "请先打开一个词法分析代码文件。");
        return;
    }
    // 定义输出可执行文件路径和输出文本文件路径
    QString outputExecutable = "output_program";
    QString outputTextFile = "snyta_output.txt";
    // 使用 g++ 编译代码文件
    QProcess compileProcess;
    compileProcess.start("g++", QStringList() << this->sytanxCodePath << "-o" << outputExecutable);
    compileProcess.waitForFinished();
    if (compileProcess.exitCode() != 0) {
        QString errorMsg = compileProcess.readAllStandardError();
        QMessageBox::warning(this, "complie error", "complie fault:\n" + errorMsg);
        return;
    }

    // 运行已编译的可执行文件
    QProcess runProcess;
    runProcess.start(outputExecutable, QStringList() << this->codePath << outputTextFile);
    runProcess.waitForFinished();

    // 从文件中读取输出并在 `ana_textEdit` 文本编辑框中显示
    QFile outputFile(outputTextFile);
    if (outputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&outputFile);
        ui->ana_textEdit->setText(in.readAll());
        outputFile.close();
    } else {
        QMessageBox::warning(this, "error", "can not read outfile。");
    }
    // 清理可执行文件
    QFile::remove(outputExecutable+".exe");
}


void MainWindow::on_savelex_Button_clicked()
{
    QString filePath2 = QFileDialog::getSaveFileName(this, "Save File", QString(), "text File (*.lex)");
    if (!filePath2.isEmpty()) {
        QFile file(filePath2);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->ana_textEdit->toPlainText();
            file.close();
        }
    }
}


void MainWindow::on_gettoken_Button_clicked()
{
    lexPath = QFileDialog::getOpenFileName(this, "Save File", QString(), "text File (*.lex)");
    if (!lexPath.isEmpty()) {
        QFile file(lexPath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->a_code_Edit->setText(in.readAll());
            file.close();
        }
    }
}


void MainWindow::on_gentree_Button_clicked()
{
    std::string temp = string(filePath.toLocal8Bit());
    LALR lalr(temp);
    auto anaProcess = lalr.Analysis(string(lexPath.toLocal8Bit()),string(opPath.toLocal8Bit()));
    ui->a_code_Edit->setText(QString::fromStdString(anaProcess));
    lalr.printTreeView(ui->a_treeView);

}




void MainWindow::on_pushButton_2_clicked()
{
    opPath = QFileDialog::getOpenFileName(this, "Save File", QString(), "text File (*.txt)");
    if (!opPath.isEmpty()) {
        QFile file(opPath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->a_code_Edit->setText(in.readAll());
            file.close();
        }
    }

}

