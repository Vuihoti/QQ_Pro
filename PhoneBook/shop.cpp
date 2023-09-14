#include "shop.h"
#include "ui_shop.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
Shop::Shop(QString id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Shop)
{
    ui->setupUi(this);
    this->setWindowTitle("商城");
    ui->dockWidget_recharge->setFixedSize(441,311);
    ui->dockWidget_recharge->close();
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
    ui->label_renamecard->setStatusTip(id);
    //充值中心的实现
    {
        connect(ui->btn_recharge,&QPushButton::clicked,this,[=](){
            ui->dockWidget_recharge->show();
            ui->lineEdit_key->clear();
        });
        connect(ui->btn_true,&QPushButton::clicked,this,[=](){
            bool Restore = false;
            QFile file_FaceValue10(QDir::currentPath()+"/BondsFaceValue/Face_Value10.txt");
            QFile file_FaceValue50(QDir::currentPath()+"/BondsFaceValue/Face_Value50.txt");
            QFile file_FaceValue100(QDir::currentPath()+"/BondsFaceValue/Face_Value100.txt");
            QFile file_Bonds(QDir::currentPath()+"/User/"+id+"/Bonds.txt");
            file_FaceValue10.open(QIODevice::ReadOnly|QIODevice::Text);
            file_FaceValue50.open(QIODevice::ReadOnly|QIODevice::Text);
            file_FaceValue100.open(QIODevice::ReadOnly|QIODevice::Text);
            for(int list=0;list<20;list++){//寻找秘钥
                if(ui->lineEdit_key->text()==file_FaceValue10.readLine().trimmed()){
                    file_Bonds.open(QIODevice::ReadOnly);
                    int Bonds = file_Bonds.readAll().toInt();
                    file_Bonds.close();
                    file_Bonds.open(QIODevice::WriteOnly|QIODevice::Truncate);
                    Bonds+=1000;//加1000点券
                    file_Bonds.write(QString::number(Bonds).toUtf8());
                    file_Bonds.close();
                    deleteOnelineInFile(QDir::currentPath()+"/User/"+id+"/Face_Value10.txt",ui->lineEdit_key->text(),"");
                    Restore=true;//找到返回True
                    //读点券数目
                    QFile file_Bonds(QDir::currentPath()+"/User/"+id+"/Bonds.txt");
                    file_Bonds.open(QIODevice::ReadOnly);
                    ui->bonds->setText(file_Bonds.readAll());
                    file_Bonds.close();
                    break;
                }
                if(ui->lineEdit_key->text()==file_FaceValue50.readLine().trimmed()){
                    file_Bonds.open(QIODevice::ReadOnly);
                    int Bonds = file_Bonds.readAll().toInt();
                    file_Bonds.close();
                    file_Bonds.open(QIODevice::WriteOnly|QIODevice::Truncate);
                    Bonds+=5000;//加5000点券
                    file_Bonds.write(QString::number(Bonds).toUtf8());
                    file_Bonds.close();
                    deleteOnelineInFile(QDir::currentPath()+"/User/"+id+"/Face_Value50.txt",ui->lineEdit_key->text(),"");
                    Restore=true;//找到返回True
                    //读点券数目
                    QFile file_Bonds(QDir::currentPath()+"/User/"+id+"/Bonds.txt");
                    file_Bonds.open(QIODevice::ReadOnly);
                    ui->bonds->setText(file_Bonds.readAll());
                    file_Bonds.close();
                    break;
                }
                if(ui->lineEdit_key->text()==file_FaceValue100.readLine().trimmed()){
                    file_Bonds.open(QIODevice::ReadOnly);
                    int Bonds = file_Bonds.readAll().toInt();
                    file_Bonds.close();
                    file_Bonds.open(QIODevice::WriteOnly|QIODevice::Truncate);
                    Bonds+=10000;//加10000点券
                    file_Bonds.write(QString::number(Bonds).toUtf8());
                    file_Bonds.close();
                    deleteOnelineInFile(QDir::currentPath()+"/User/"+id+"/Face_Value100.txt",ui->lineEdit_key->text(),"");
                    Restore=true;//找到返回True
                    //读点券数目
                    QFile file_Bonds(QDir::currentPath()+"/User/"+id+"/Bonds.txt");
                    file_Bonds.open(QIODevice::ReadOnly);
                    ui->bonds->setText(file_Bonds.readAll());
                    file_Bonds.close();
                    break;
                }
            }
            file_FaceValue10.close();
            file_FaceValue50.close();
            file_FaceValue100.close();
            if(Restore){
                file_Bonds.open(QIODevice::ReadOnly);
                QMessageBox::information(this,"充值中心","充值成功 √\n当前点券余额为:"+file_Bonds.readAll());
                file_Bonds.close();
            }
            else{
                QMessageBox::critical(this,"充值中心","充值失败 ×\n秘钥错误");
            }
        });
    }
    //实现刷新按钮的功能
    connect(ui->btn_updata,&QPushButton::clicked,this,[=](){
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
    });
}
void Shop::deleteOnelineInFile(QString fileurl,QString needtochangetext,QString changetext){
    QString strAll;
    QStringList strList;
    QFile readFile(fileurl);		//fileurl是自定义读取文件的地址
    if(readFile.open((QIODevice::ReadOnly|QIODevice::Text)))
    {
        //把文件所有信息读出来
        QTextStream stream(&readFile);
        strAll=stream.readAll();
    }
    readFile.close();

    QFile writeFile(fileurl);	//fileurl是自定义写文件的地址
    if(writeFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
            QTextStream stream(&writeFile);
            strList=strAll.split("\n");           //以换行符为基准分割文本
            for(int i=0;i<strList.count();i++)    //遍历每一行
            {
                if(strList.at(i).contains(needtochangetext))    //needtochangetext是要修改的内容
                {
                    QString tempStr=strList.at(i);
                    tempStr.replace(0,tempStr.length(),changetext);   //changetext是要替换的内容
                }
                //如果没有找到要替换的内容，照常写入
                else
                {
                    if(i==strList.count()-1)
                    {
                       stream<<strList.at(i);
                    }
                    else
                    {
                       stream<<strList.at(i)<<'\n';
                    }
                }
            }
    }
    writeFile.close();
}
Shop::~Shop()
{
    delete ui;
}
