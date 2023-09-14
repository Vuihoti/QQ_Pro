#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "loginscreen.h"
#include "showfriends.h"
#include "mouseevent.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QPixmap>
#include <QMessageBox>
#include <QDesktopServices>
#include <QListWidget>
#include <QIcon>
#include <loginscreen.h>

MainMenu::MainMenu(QString id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    this->setWindowIcon(QIcon(":/Img/asppa-0b5li-001.ico"));
    ui->setupUi(this);
    ui->label_shop->setWhatsThis(id);
    ui->label_search->setAccessibleDescription(id);
    ui->label_membercenter->setWhatsThis(id);

    //为窗口打上"通讯录"的标题 设置大小为 370*550
    this->setFixedSize(370,550);
    this->setWindowTitle("PhoneBook");
    //加载"添加好友"和"点券"模块的图标
    ui->label_addfriends->setPixmap(QPixmap(QDir::currentPath()+"/Img/FunctionalIcons/AddFriends.png"));
    ui->label_addfriends->setWhatsThis(id);
    ui->label_knapsack->setWhatsThis(id);
    ui->label_bonds->setPixmap(QPixmap(QDir::currentPath()+"/Img/FunctionalIcons/Bonds.png"));
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
    //读取联系人信息
    QFile file_FriendsList(QDir::currentPath()+"/User/"+id+"/FriendsList.txt");
    QFile file_FriendsAvatarList(QDir::currentPath()+"/User/"+id+"/FriendsAvatarList.txt");
    QFile file_FriendsNumber(QDir::currentPath()+"/User/"+id+"/FriendsNumber.txt");
    file_FriendsNumber.open(QIODevice::ReadOnly);
    file_FriendsList.open(QIODevice::ReadOnly|QIODevice::Text);
    file_FriendsAvatarList.open(QIODevice::ReadOnly|QIODevice::Text);
    int FriendsNumber=file_FriendsNumber.readAll().toInt();
    file_FriendsNumber.close();
    ui->listWidget_friends->clear();
    //加载头像中
    for(int Times=0; Times<FriendsNumber;Times++){
        ui->listWidget_friends->addItem(file_FriendsList.readLine().trimmed());
        QString FriendsAvatar =file_FriendsAvatarList.readLine();
        if(*FriendsAvatar.data()<=FriendsNumber+ '0')
           ui->listWidget_friends->item(Times)->setIcon(QIcon(":/Img/Arous.png")) ;
        else
            ui->listWidget_friends->item(Times)->setIcon(QIcon(FriendsAvatar.trimmed()));
    }
    file_FriendsList.close();
    file_FriendsAvatarList.close();
    //实现刷新按钮的功能
    connect(ui->btn_updata,&QPushButton::clicked,this,[=](){
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
        //读联系人信息
        QFile file_FriendsList(QDir::currentPath()+"/User/"+id+"/FriendsList.txt");
        QFile file_FriendsAvatarList(QDir::currentPath()+"/User/"+id+"/FriendsAvatarList.txt");
        QFile file_FriendsNumber(QDir::currentPath()+"/User/"+id+"/FriendsNumber.txt");
        file_FriendsNumber.open(QIODevice::ReadOnly);
        file_FriendsList.open(QIODevice::ReadOnly|QIODevice::Text);
        file_FriendsAvatarList.open(QIODevice::ReadOnly|QIODevice::Text);
        int FriendsNumber=file_FriendsNumber.readAll().toInt();
        file_FriendsNumber.close();
        ui->listWidget_friends->clear();
        //加载头像中
        for(int Times=0; Times<FriendsNumber;Times++){
            ui->listWidget_friends->addItem(file_FriendsList.readLine().trimmed());
            QString FriendsAvatar =file_FriendsAvatarList.readLine();
            if(*FriendsAvatar.data()<=FriendsNumber+ '0')
               ui->listWidget_friends->item(Times)->setIcon(QIcon(":/Img/Arous.png")) ;
            else
                ui->listWidget_friends->item(Times)->setIcon(QIcon(FriendsAvatar.trimmed()));
        }
        file_FriendsList.close();
        file_FriendsAvatarList.close();
    });
    //双击弹出 用户详细资料
    connect(ui->listWidget_friends,&QListWidget::itemDoubleClicked,this,[=](QListWidgetItem *item){
       ShowFriends *ToShowFriends = new ShowFriends(item->text(),id);
       ToShowFriends->show();
    });
    //实现清空搜索功能
    connect(ui->lineEdit_searchline,&QLineEdit::textChanged,this,[=](){
        ui->label_search->setWhatsThis(ui->lineEdit_searchline->text());
    });
    connect(ui->btn_delete,&QPushButton::clicked,this,[=](){
        ui->lineEdit_searchline->clear();
    });
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_btn_retrun_clicked()
{
    QFile file_AutoLogin(QDir::currentPath()+"/AccountList/AutoLogin.txt");
    file_AutoLogin.open(QIODevice::WriteOnly);
    file_AutoLogin.write("NOONEWANTAUTOLOGIN~");
    file_AutoLogin.close();
    LoginScreen *ToLoginScreen = new LoginScreen;
    ToLoginScreen->show();
    this->hide();

}

