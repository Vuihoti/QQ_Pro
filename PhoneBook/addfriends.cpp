#include "addfriends.h"
#include "ui_addfriends.h"
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
AddFriends::AddFriends(QString id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFriends)
{
    this->setWindowIcon(QIcon(":/Img/asppa-0b5li-001.ico"));
    ui->setupUi(this);
    //为窗口打上"添加联系人"的标题 设置大小为 340*460
    setWindowTitle("添加联系人");
    setFixedSize(340,460);
    //实现取消按钮功能
    connect(ui->btn_cancel,&QPushButton::clicked,this,[=](){
        //判断用户有没有输入信息
        if(ui->lineEdit_name->text().isEmpty()&&ui->lineEdit_email->text().isEmpty()&&ui->lineEdit_birthday->text().isEmpty()&&ui->lineEdit_workpalce->text().isEmpty()&&
                ui->lineEdit_phonenumber->text().isEmpty()&&ui->textEdit_remark->toMarkdown().isEmpty()){
           this->close();
        }
        else{
            if(QMessageBox::Yes == QMessageBox::question(this,"添加联系人","你已经做出了编辑,是否放弃添加？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No)){
                this->close();
            }
        }
    });
    connect(ui->btn_changeavatar,&QPushButton::clicked,this,[=](){
        QString fileName = QFileDialog::getOpenFileName(this,"选择一个文件",QCoreApplication::applicationFilePath(),"*.jpg");
        ui->label_FriendAvatar->setPixmap(QPixmap(fileName));
        ui->label_FriendAvatar->setWhatsThis(fileName);
    });
    //实现完成按钮的功能
    connect(ui->btn_complete,&QPushButton::clicked,this,[=](){
        //布尔三个变量 分别为[号码是否纯数字]  [朋友是否未重复] [头像文件是否重复]
        bool ConditionPhoneNumber=false,FriendsNooneSame=false,FriendAvatarNoonesame=true;
        //判断号码纯数字
        if(QString(ui->lineEdit_phonenumber->text()).contains(QRegExp("^\\d+$"))){
            //如果是的话就返回一个true
            ConditionPhoneNumber=true;
        }
        else{
            //如果不是的话就弹窗警告 并结束按钮功能
            QMessageBox::critical(this,"ERROR","号码仅限数字");
         }
        QDir path;
        if(!path.exists(QDir::currentPath()+"/User/"+id+"/Friends/"+ui->lineEdit_name->text())){
            FriendsNooneSame = true;
        }
        else{
            //如果不是的话就弹窗警告 并结束按钮功能
            QMessageBox::critical(this,"ERROR","已有["+ui->lineEdit_name->text()+"] 联系人");
        }
        QFile file_FriendsAvatarList(QDir::currentPath()+"/User/"+id+"/FriendsAvatarList.txt");
        QFile file_FriendsNumber(QDir::currentPath()+"/User/"+id+"/FriendsNumber.txt");
        file_FriendsAvatarList.open(QIODevice::ReadOnly|QIODevice::Text);
         file_FriendsNumber.open(QIODevice::ReadOnly|QIODevice::Text);
         int FriendsNumberOUT=file_FriendsNumber.readAll().toInt();
         file_FriendsNumber.close();
        for(int Times=0;Times<FriendsNumberOUT;Times++){
            if(ui->label_FriendAvatar->whatsThis()+"\n"==file_FriendsAvatarList.readLine()){
                QMessageBox::critical(this,"ERROR","头像文件重名");
                FriendAvatarNoonesame=false;
                break;
            }
            else{;}
        }
        file_FriendsAvatarList.close();
        if(FriendsNooneSame&&ConditionPhoneNumber&&FriendAvatarNoonesame){
            //打开FriendsNumberMax与FriendsNumber 并创建两个整形数分别储存
            QFile file_FriendsNumberMax(QDir::currentPath()+"/User/"+id+"/FriendsNumberMax.txt");
             file_FriendsNumberMax.open(QIODevice::ReadOnly);
             file_FriendsNumber.open(QIODevice::ReadWrite);
             int FriendsNumberMax =file_FriendsNumberMax.readAll().toInt();
             int FriendsNumber= file_FriendsNumber.readAll().toInt();
             file_FriendsNumberMax.close();
             file_FriendsNumber.close();
             //检查联系人数量是否到上限
             if(FriendsNumberMax<=FriendsNumber){
                 //是的话就弹窗警告
                  QMessageBox::critical(this,"ERROR","可创建的联系人已达上限\n提升会员等级可创建更多联系人!");
             }
             //不是的话就创建
             else{
             path.mkdir(QDir::currentPath()+"/User/"+id+"/Friends/"+ui->lineEdit_name->text());
             ui->label_FriendAvatar->setAccessibleName(ui->lineEdit_name->text());
            //创建头像
            QFile file_Avatar(QDir::currentPath()+"/User/"+id+"/Friends/"+ui->lineEdit_name->text()+"/Avatar.txt");
            file_Avatar.open(QIODevice::WriteOnly);
            if(ui->label_FriendAvatar->whatsThis().isEmpty()){
                file_Avatar.write(QString::number(FriendsNumber).toUtf8());
            }
            else
                file_Avatar.write(ui->label_FriendAvatar->whatsThis().toUtf8());
            file_Avatar.close();
            //创建用户名
            QFile file_Name(QDir::currentPath()+"/User/"+id+"/Friends/"+ui->lineEdit_name->text()+"/Name.txt");
            file_Name.open(QIODevice::WriteOnly);
            file_Name.write(ui->lineEdit_name->text().toUtf8());
            file_Name.close();
            //创建工作单位
            QFile file_WorkPlace(QDir::currentPath()+"/User/"+id+"/Friends/"+ui->lineEdit_name->text()+"/WorkPlace.txt");
            file_WorkPlace.open(QIODevice::WriteOnly);
            file_WorkPlace.write(ui->lineEdit_workpalce->text().toUtf8());
            file_WorkPlace.close();
            //创建电话号码
            QFile file_PhoneNumber(QDir::currentPath()+"/User/"+id+"/Friends/"+ui->lineEdit_name->text()+"/PhoneNumber.txt");
            file_PhoneNumber.open(QIODevice::WriteOnly);
            file_PhoneNumber.write(ui->lineEdit_phonenumber->text().toUtf8());
            file_PhoneNumber.close();
            //创建电子邮箱
            QFile file_EMail(QDir::currentPath()+"/User/"+id+"/Friends/"+ui->lineEdit_name->text()+"/EMail.txt");
            file_EMail.open(QIODevice::WriteOnly);
            file_EMail.write(ui->lineEdit_email->text().toUtf8());
            file_EMail.close();
            //创建生日
            QFile file_Birthday(QDir::currentPath()+"/User/"+id+"/Friends/"+ui->lineEdit_name->text()+"/Birthday.txt");
            file_Birthday.open(QIODevice::WriteOnly);
            file_Birthday.write(ui->lineEdit_birthday->text().toUtf8());
            file_Birthday.close();
            //创建备注
            QFile file_Remark(QDir::currentPath()+"/User/"+id+"/Friends/"+ui->lineEdit_name->text()+"/Remark.txt");
            file_Remark.open(QIODevice::WriteOnly);
            file_Remark.write(ui->textEdit_remark->toMarkdown().toUtf8());
            file_Remark.close();
            //向FriendsList里面传输联系人ID
            QFile file_FriendsList(QDir::currentPath()+"/User/"+id+"/FriendsList.txt");
            file_FriendsList.open(QIODevice::WriteOnly|QIODevice::Append);
            file_FriendsList.write(ui->lineEdit_name->text().toUtf8()+"\n");
            file_FriendsList.close();
            //向FriendsAvatarList里面传输联系人头像
            file_FriendsAvatarList.open(QIODevice::WriteOnly|QIODevice::Append);
            if(ui->label_FriendAvatar->whatsThis().isEmpty()){
                file_FriendsAvatarList.write(QString::number(FriendsNumber).toUtf8()+"\n");
            }
            else
                file_FriendsAvatarList.write(ui->label_FriendAvatar->whatsThis().toUtf8()+"\n");
            file_FriendsAvatarList.close();
            QMessageBox::information(this,"添加联系人","添加成功");
            //成功创建联系人之后就使FriendsNumber+1 并代回文件中
            FriendsNumber++;
            file_FriendsNumber.open(QIODevice::ReadWrite|QFile::Truncate);
            file_FriendsNumber.write(QString::number(FriendsNumber).toUtf8());
            file_FriendsNumber.close();
            this->close();
            }
        }
    });
}

AddFriends::~AddFriends()
{
    delete ui;
}
