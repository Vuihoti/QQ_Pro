#include "personalinformation.h"
#include "ui_personalinformation.h"
#include "loginscreen.h"
#include "mainmenu.h"
#include <QFile>
#include <QDir>
#include <QMessageBox>
PersonalInformation::PersonalInformation(QString id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalInformation)
{
    this->setWindowIcon(QIcon(":/Img/asppa-0b5li-001.ico"));
    ui->setupUi(this);
     //为窗口打上"个人信息"的标题 设置大小为 431*600
    this->setFixedSize(431,600);
    //重置页面为显示信息
    ui->stackedWidget->setCurrentWidget(ui->page_show);
    this->setWindowTitle("个人信息");
    //先传个ID先
    ui->avatar->setWhatsThis(id);
    //读头像
    QFile file_Avatar(QDir::currentPath()+"/User/"+id+"/Avatar.txt");
    file_Avatar.open(QIODevice::ReadOnly);
    ui->avatar->setPixmap(QPixmap(file_Avatar.readAll()));
    file_Avatar.close();
    //读名称
    ui->avatar->setWhatsThis(id);
    QFile file_UserName(QDir::currentPath()+"/User/"+id+"/UserName.txt");
    file_UserName.open(QIODevice::ReadOnly);
    ui->lineEdit_username->setText(file_UserName.readAll());
    file_UserName.close();
    //读个人说明
    QFile file_PersonalInstructions(QDir::currentPath()+"/User/"+id+"/PersonalInstructions.txt");
    file_PersonalInstructions.open(QIODevice::ReadOnly);
    ui->textEdit_personalinstructions->setText(file_PersonalInstructions.readAll());
    file_PersonalInstructions.close();
    //实现按钮"编辑"的功能
    connect(ui->btn_edit,&QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentWidget(ui->page_edit);
        ui->lineEdit_changeusername->setText(ui->lineEdit_username->text());
        ui->textEdit_changepersonalinstructions->setText(ui->textEdit_personalinstructions->toMarkdown());
    });
    //实现按钮关闭的功能
    connect(ui->btn_close,&QPushButton::clicked,this,[=](){
        this->close();
    });
    //实现按钮确定的功能
    connect(ui->btn_determine,&QPushButton::clicked,this,[=](){

        if(ui->lineEdit_changeusername->text()!=ui->lineEdit_username->text()){
            if(QMessageBox::Yes == QMessageBox::question(this,"编辑信息","更改名字需要一张改名卡\n确定要更改姓名吗")){
                QFile file_RenameCardNumber(QDir::currentPath()+"/User/"+id+"/Knapsack/RenameCard.txt");
                file_RenameCardNumber.open(QIODevice::ReadOnly);
                int RenameCardNumber = file_RenameCardNumber.readAll().toInt();
                if(RenameCardNumber>0){
                    file_RenameCardNumber.close();
                    RenameCardNumber--;
                    file_RenameCardNumber.open(QIODevice::WriteOnly|QIODevice::Truncate);
                    file_RenameCardNumber.write(QString::number(RenameCardNumber).toUtf8());
                    file_RenameCardNumber.close();
                    QFile file_UserName(QDir::currentPath()+"/User/"+id+"/UserName.txt");
                    QFile file_PersonalInstructions(QDir::currentPath()+"/User/"+id+"/PersonalInstructions.txt");
                    //删除重新更新数据
                    file_UserName.open(QIODevice::WriteOnly|QFile::Truncate);
                    file_PersonalInstructions.open(QIODevice::WriteOnly|QFile::Truncate);
                    file_UserName.write(ui->lineEdit_changeusername->text().toUtf8());
                    file_PersonalInstructions.write(ui->textEdit_changepersonalinstructions->toMarkdown().toUtf8());
                    file_UserName.close();
                    file_PersonalInstructions.close();
                    QMessageBox::information(this,"编辑资料","修改成功!");
                    ui->lineEdit_username->setText(ui->lineEdit_changeusername->text());
                    ui->textEdit_personalinstructions->setText(ui->textEdit_changepersonalinstructions->toMarkdown());
                    //将页面转回展示
                    ui->stackedWidget->setCurrentWidget(ui->page_show);
                }
                else {
                    QMessageBox::critical(this,"编辑信息","改名卡不足!");
                }
            }
        }
        else {
            QFile file_UserName(QDir::currentPath()+"/User/"+id+"/UserName.txt");
            QFile file_PersonalInstructions(QDir::currentPath()+"/User/"+id+"/PersonalInstructions.txt");
            //删除重新更新数据
            file_UserName.open(QIODevice::WriteOnly|QFile::Truncate);
            file_PersonalInstructions.open(QIODevice::WriteOnly|QFile::Truncate);
            file_UserName.write(ui->lineEdit_changeusername->text().toUtf8());
            file_PersonalInstructions.write(ui->textEdit_changepersonalinstructions->toMarkdown().toUtf8());
            file_UserName.close();
            file_PersonalInstructions.close();
            QMessageBox::information(this,"编辑资料","修改成功!");
            ui->lineEdit_username->setText(ui->lineEdit_changeusername->text());
            ui->textEdit_personalinstructions->setText(ui->textEdit_changepersonalinstructions->toMarkdown());
            //将页面转回展示
            ui->stackedWidget->setCurrentWidget(ui->page_show);
        }
    });
    //实现按钮取消的功能
    connect(ui->btn_cancel,&QPushButton::clicked,this,[=](){
        //判断个人信息是否遭到修改
        if(ui->lineEdit_changeusername->text()!=ui->lineEdit_username->text()||ui->textEdit_changepersonalinstructions->toMarkdown()!=ui->textEdit_personalinstructions->toMarkdown()){
            //如果遭到修改就询问客户是否保存
            if(QMessageBox::Yes == QMessageBox::question(this,"保存资料","你已经对设置作了修改，是否保存?",QMessageBox::Yes|QMessageBox::No,QMessageBox::No)){
                //选择保存就写入数据并弹窗提醒
                QFile file_UserName(QDir::currentPath()+"/User/"+id+"/UserName.txt");
                QFile file_PersonalInstructions(QDir::currentPath()+"/User/"+id+"/PersonalInstructions.txt");
                file_UserName.open(QIODevice::WriteOnly|QFile::Truncate);
                file_PersonalInstructions.open(QIODevice::WriteOnly|QFile::Truncate);
                file_UserName.write(ui->lineEdit_changeusername->text().toUtf8());
                file_PersonalInstructions.write(ui->textEdit_changepersonalinstructions->toMarkdown().toUtf8());
                file_UserName.close();
                file_PersonalInstructions.close();
                QMessageBox::information(this,"编辑资料","修改成功!");
                ui->lineEdit_username->setText(ui->lineEdit_changeusername->text());
                ui->textEdit_personalinstructions->setText(ui->textEdit_changepersonalinstructions->toMarkdown());
                ui->stackedWidget->setCurrentWidget(ui->page_show);
            }
            //如果选择不保存就转到展示界面
            else
                ui->stackedWidget->setCurrentWidget(ui->page_show);
        }
        //如果没被修改就转到展示界面
        else
            ui->stackedWidget->setCurrentWidget(ui->page_show);
    });
}
PersonalInformation::~PersonalInformation()
{
    delete ui;
}
