#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);trem1 = new Trem(1,10,160, 200);

    trem1 = new Trem(1,10,160, 200);
    trem2 = new Trem(2,190,10, 200);
    trem3 = new Trem(3,330,10, 200);
    trem4 = new Trem(4,510,160,200);
    trem5 = new Trem(5,330,310,200);
    trem6 = new Trem(6,190,310,200);
    trem7 = new Trem(7,330,160,200);

    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem6,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem7,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
    trem6->start();
    trem7->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInterface(int id, int x, int y)
{
    switch(id){
        case 1:
            ui->labelTrem1->setGeometry(x,y,20,20);
            break;
        case 2:
            ui->labelTrem2->setGeometry(x, y, 20, 20);
            break;
        case 3:
            ui->labelTrem3->setGeometry(x, y, 20, 20);
            break;
        case 4:
            ui->labelTrem4->setGeometry(x, y, 20, 20);
            break;
        case 5:
            ui->labelTrem5->setGeometry(x, y, 20, 20);
            break;
        case 6:
            ui->labelTrem6->setGeometry(x, y, 20, 20);
            break;
        case 7:
            ui->labelTrem7->setGeometry(x, y, 20, 20);
            break;
        default:
            break;
    }
}

