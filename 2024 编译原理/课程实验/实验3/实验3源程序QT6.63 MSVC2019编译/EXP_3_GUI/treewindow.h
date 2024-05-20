#ifndef TREEWINDOW_H
#define TREEWINDOW_H
#include<QTreeWidgetItem>
#include <QWidget>
#include"parser.h"
namespace Ui {
class treewindow;
}

class treewindow : public QWidget
{
    Q_OBJECT
private:
    Ui::treewindow *ui;
    void buildTree(QTreeWidgetItem *root,TreeNode* node,int depth);
public:
    explicit treewindow(QWidget *parent = nullptr);
    void build(TreeNode* node,int depth);
    ~treewindow();



};

#endif // TREEWINDOW_H
