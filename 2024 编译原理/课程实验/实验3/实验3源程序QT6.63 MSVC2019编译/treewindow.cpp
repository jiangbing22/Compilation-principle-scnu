#include "treewindow.h"
#include "ui_treewindow.h"

treewindow::treewindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::treewindow)
{
    ui->setupUi(this);
}

void treewindow::build(TreeNode* node,int depth=0)
{
    ui->treeWidget->clear();
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0, "start"); // ���ø��ڵ��ı�
    buildTree(item,node,depth);
}
void treewindow::buildTree(QTreeWidgetItem *root,TreeNode* node,int depth)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(root);
    item->setText(0, node->getvalue()); // ���ø��ڵ��ı�
    item->setExpanded(true);
    for (int i = 0; i < MAXCHILDREN; i++)
    {
        if (node->child[i] != nullptr)
        {
            buildTree(item,node->child[i],depth+1); //�Լ��� ���Ӹ� �Լ���Ϊroot
        }
    }
    TreeNode *sibling = node->sibling;
    if (sibling != nullptr)
    {
        buildTree(root,sibling,depth); // ͬ���Ľ�������
    }
}
treewindow::~treewindow()
{
    delete ui;
}
