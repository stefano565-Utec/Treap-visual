#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->insertButton, &QPushButton::clicked, this, &MainWindow::onInsertClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


int MainWindow::subtreeWidth(TreapNode* node) {
    if (!node) return 0;
    return 1 + subtreeWidth(node->left) + subtreeWidth(node->right);
}

void MainWindow::drawTreap(TreapNode* node, QGraphicsScene* scene, int x, int y, int subtreeWidth) {
    if (!node) return;

    const int nodeRadius = 20;
    const int verticalSpacing = 80;
    const float horizontalScale = 1.25;

    QGraphicsEllipseItem* ellipse = scene->addEllipse(x - nodeRadius, y - nodeRadius, nodeRadius * 2, nodeRadius * 2);
    ellipse->setBrush(Qt::yellow);
    ellipse->setPen(QPen(Qt::black));

    QGraphicsTextItem* keyText = scene->addText(QString::number(node->key));
    keyText->setPos(x - 10, y - 10);

    QGraphicsTextItem* priorityText = scene->addText(QString::number(node->priority));
    priorityText->setPos(x - 10, y + nodeRadius + 5);

    if (node->left) {
        int leftX = x - static_cast<int>(subtreeWidth * horizontalScale);
        scene->addLine(x, y + nodeRadius, leftX, y + verticalSpacing - nodeRadius, QPen(Qt::black));
        drawTreap(node->left, scene, leftX, y + verticalSpacing, subtreeWidth / 2);
    }

    if (node->right) {
        int rightX = x + static_cast<int>(subtreeWidth * horizontalScale);
        scene->addLine(x, y + nodeRadius, rightX, y + verticalSpacing - nodeRadius, QPen(Qt::black));
        drawTreap(node->right, scene, rightX, y + verticalSpacing, subtreeWidth / 2);
    }
}



void MainWindow::displayTreap() {
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->clear();
    if (treap.root) {
        const int initialSpace = 400;
        drawTreap(treap.root, scene, initialSpace, 50, initialSpace);
    }
}


void MainWindow::onInsertClicked() {
    int key = ui->lineEdit->text().toInt();
    if (treap.search(key)) {
        ui->statusLabel->setText("El valor " + QString::number(key) + " ya existe en el Treap.");
    } else {
        treap.insert(key);
        ui->statusLabel->setText("Nodo insertado: " + QString::number(key));
        displayTreap();
    }
}

void MainWindow::onDeleteClicked() {
    int key = ui->lineEdit->text().toInt();

    bool success = treap.deleteNode(key);

    if (success) {
        ui->statusLabel->setText("Nodo eliminado: " + QString::number(key));
    } else {
        ui->statusLabel->setText("El nodo con la clave " + QString::number(key) + " no existe en el Treap.");
    }

    displayTreap();
}

void MainWindow::onSearchClicked() {
    int key = ui->lineEdit->text().toInt();
    if (treap.search(key)) {
        ui->statusLabel->setText("Nodo encontrado: " + QString::number(key));
    } else {
        ui->statusLabel->setText("Nodo no encontrado");
    }
    displayTreap();
}
