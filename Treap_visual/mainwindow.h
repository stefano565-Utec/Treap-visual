#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPen>

#include "treap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onInsertClicked();
    void onDeleteClicked();
    void onSearchClicked();

private:
    Ui::MainWindow *ui;
    Treap treap;
    int calculateSubtreeWidth(TreapNode* node);
    int subtreeWidth(TreapNode* node);
    void drawTreap(TreapNode* node, QGraphicsScene* scene, int x, int y, int subtreeSpace);
    void displayTreap();
};

#endif // MAINWINDOW_H
