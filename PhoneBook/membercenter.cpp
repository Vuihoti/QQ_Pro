#include "membercenter.h"
#include "ui_membercenter.h"
#include <QFile>
#include <QDir>

MemberCenter::MemberCenter(QString id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemberCenter)
{
    ui->setupUi(this);
    this->setFixedSize(571,481);
    this->setWindowTitle("会员中心");
    //读头像
    QFile file_Avatar(QDir::currentPath()+"/User/"+id+"/Avatar.txt");
    file_Avatar.open(QIODevice::ReadOnly);
    ui->avatar->setWhatsThis(id);
    ui->avatar->setPixmap(QPixmap(file_Avatar.readAll()));
    file_Avatar.close();
    //读ID
    QFile file_UserName(QDir::currentPath()+"/User/"+id+"/UserName.txt");
    file_UserName.open(QIODevice::ReadOnly);
    ui->id->setText(file_UserName.readAll());
    file_UserName.close();
    //读点券数目
    QFile file_Bonds(QDir::currentPath()+"/User/"+id+"/Bonds.txt");
    file_Bonds.open(QIODevice::ReadOnly);
    ui->bonds->setText(file_Bonds.readAll());
    file_Bonds.close();
    //读会员
    QFile file_Member(QDir::currentPath()+"/User/"+id+"/Member.txt");
    file_Member.open(QIODevice::ReadOnly);
    ui->member->setPixmap(QPixmap(QDir::currentPath()+"/Img/VIP/"+file_Member.readAll()));
    file_Member.close();
}

MemberCenter::~MemberCenter()
{
    delete ui;
}
