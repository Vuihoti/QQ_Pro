#include "knapsack.h"
#include "ui_knapsack.h"
#include <QFile>
#include <QDir>

Knapsack::Knapsack(QString id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Knapsack)
{
    ui->setupUi(this);
    this->setWindowTitle("背包");
    this->setFixedSize(830,504);
    ui->label_shop->setWhatsThis(id);
    QFile file_RenameCardNumber(QDir::currentPath()+"/User/"+id+"/Knapsack/RenameCard.txt");
    file_RenameCardNumber.open(QIODevice::ReadOnly);
    ui->label_renamecard->setPixmap(QPixmap(QDir::currentPath()+"/Img/Commodity/RenameCard.png"));
    ui->label_renamecardnumber->setText("拥有:"+file_RenameCardNumber.readAll());

    //读点券
    QFile file_Bonds(QDir::currentPath()+"/User/"+id+"/Bonds.txt");
    file_Bonds.open(QIODevice::ReadOnly);
    ui->bonds->setText(file_Bonds.readAll());
}

Knapsack::~Knapsack()
{
    delete ui;
}
