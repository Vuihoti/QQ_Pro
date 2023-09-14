#include "enroll.h"
#include "ui_enroll.h"
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <loginscreen.h>
Enroll::Enroll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Enroll)
{
    this->setWindowIcon(QIcon(":/Img/asppa-0b5li-001.ico"));
    ui->setupUi(this);
    //为窗口打上"注册"的标题 设置大小
    this->setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(580,513);
    setWindowTitle("注册");
    //实现"确定"按钮的功能
    connect(ui->btn_determine,&QPushButton::clicked,this,&Enroll::Determine);
    //实现"取消"按钮的功能
    connect(ui->btn_cancel,&QPushButton::clicked,this,&Enroll::Cancel);
    connect(ui->btn_close,&QPushButton::clicked,this,&Enroll::Cancel);

}
//确定
void Enroll::Determine(){
    //布尔两个变量 分别为[账号是否纯数字] [密码是否纯数字] [密码是否相同] 
    //判断"密码"和"确定密码"是否相同
    if(ui->lineEdit_password->text()==ui->lineEdit_confirmpassword->text())
    {ConditionPasswordSame=true;}
    else{
        ui->label_ErrorTip_3->setText("密码不相同");
    }
    //判断[账号是否纯数字]  [密码是否相同]是否同时成立
    if(ConditionAccount&&ConditionPasswordSame&&ConditionPassword){
        QDir path; // 创建一个QDir变量
        if (!path.exists(QDir::currentPath()+"/User/"+ui->lineEdit_account->text())) {  // 使用QDir成员函数exists()来判断文件夹是否存在
           ui->stackedWidget->setCurrentIndex(1);
        }
        else{
            //如果存在的话就警告弹窗
            ui->label_ErrorTip->setText("账户["+ui->lineEdit_account->text()+"]已存在");
        }
    }
}
void Enroll::Cancel(){
    LoginScreen *ToLoginScreen = new LoginScreen;
    ToLoginScreen->show();
    this->hide();
}
Enroll::~Enroll()
{
    delete ui;
}
//判断是否纯数字和是否空
void Enroll::on_lineEdit_account_textChanged(const QString &arg1)
{
    if(QString(arg1).contains(QRegExp("^\\d+$"))){
        ConditionAccount=true;
        ui->label_ErrorTip->clear();
    }
    else
    {
        ConditionAccount=false;
        ui->label_ErrorTip->setText("账号只允许数字");
    }
    if(arg1==""){
        ConditionAccount=false;
        ui->label_ErrorTip->setText("账号不能为空");
    }
}
//判断是否有中文和是否空
void Enroll::on_lineEdit_confirmpassword_textChanged(const QString &)
{
    ui->label_ErrorTip_3->clear();
}

void Enroll::on_lineEdit_password_textChanged(const QString &arg1)
{
    if(!arg1.contains(QRegExp("[\\x4e00-\\x9fa5]+"))){
        //如果是的话就返回一个true
        ConditionPassword=true;
        ui->label_ErrorTip_2->clear();
    }
    else{
        ConditionPassword=false;
        ui->label_ErrorTip_2->setText("密码中不能含有中文字符");
    }
    if(arg1==""){
        ConditionPassword=false;
        ui->label_ErrorTip_2->setText("密码不能为空");
    }
}

void LoginScreen::mousePressEvent(QMouseEvent *event)
{
    isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
    last = event->globalPos();



}

void LoginScreen::mouseMoveEvent(QMouseEvent *event)
{
    if (isPressedWidget)
        {
            int dx = event->globalX() - last.x();
            int dy = event->globalY() - last.y();
            last = event->globalPos();
            move(x()+dx, y()+dy);
        }
}

void LoginScreen::mouseReleaseEvent(QMouseEvent *event)
{
    int dx = event->globalX() - last.x();
    int dy = event->globalY() - last.y();
    move(x()+dx, y()+dy);
    isPressedWidget = false; // 鼠标松开时，置为false
}

void Enroll::on_lineEdit_Issues1_textChanged(const QString &arg1)
{
    if(arg1==""){
        PASS1=false;
        ui->label_ErrorTip_4->setText("密保问题不能为空");
    }
    else{
        PASS1=true;
        ui->label_ErrorTip_4->clear();
    }
}

void Enroll::on_lineEdit_Answer1_textChanged(const QString &arg1)
{
    if(arg1==""){
        PASS2=false;
        ui->label_ErrorTip_5->setText("密保答案不能为空");
    }
    else{
        PASS2=true;
        ui->label_ErrorTip_5->clear();
    }
}

void Enroll::on_lineEdit_Issues1_2_textChanged(const QString &arg1)
{
    if(arg1==""){
        PASS3=false;
        ui->label_ErrorTip_6->setText("密保问题不能为空");
    }
    else{
        PASS3=true;
        ui->label_ErrorTip_6->clear();
    }
}

void Enroll::on_lineEdit_Answer2_textChanged(const QString &arg1)
{
    if(arg1==""){
        PASS4=false;
        ui->label_ErrorTip_7->setText("密保答案不能为空");
    }
    else{
        PASS4=true;
        ui->label_ErrorTip_7->clear();
    }
}

void Enroll::on_btn_Return_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Enroll::on_btn_Finishi_clicked()
{
    if(PASS1&&PASS2&&PASS3&PASS4){
        QDir path; // 创建一个QDir变量
        path.mkdir(QDir::currentPath()+"/User/"+ui->lineEdit_account->text());  // 使用mkdir来创建文件夹
                   //创建账户
                   QFile file_Account(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/Account.txt");
                   file_Account.open(QIODevice::WriteOnly);
                   file_Account.write(ui->lineEdit_account->text().toUtf8());
                   file_Account.close();
                   //创建密码
                   QFile file_PassWord(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/PassWord.txt");
                   file_PassWord.open(QIODevice::WriteOnly);
                   file_PassWord.write(ui->lineEdit_password->text().toUtf8());
                   file_PassWord.close();
                   //创建头像
                   QFile file_Avatar(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/Avatar.txt");
                   file_Avatar.open(QIODevice::WriteOnly);
                   file_Avatar.write(":/Img/Arous.png");
                   file_Avatar.close();
                   //创建点券
                   QFile file_Bonds(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/Bonds.txt");
                   file_Bonds.open(QIODevice::WriteOnly);
                   file_Bonds.write("0");
                   file_Bonds.close();
                   //创建用户名
                   QFile file_UserName(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/UserName.txt");
                   file_UserName.open(QIODevice::WriteOnly);
                   file_UserName.write(ui->lineEdit_account->text().toUtf8());
                   file_UserName.close();
                   //创建个人说明
                   QFile file_PersonalInstructions(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/PersonalInstructions.txt");
                   file_PersonalInstructions.open(QIODevice::WriteOnly);
                   file_PersonalInstructions.write("这个人很懒,什么都没有留下....");
                   file_PersonalInstructions.close();
                   //创建会员
                   QFile file_Member(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/Member.txt");
                   file_Member.open(QIODevice::WriteOnly);
                   file_Member.write("VIP1.png");
                   file_Member.close();
                   //创建朋友数量
                   QFile file_FriendsNumber(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/FriendsNumber.txt");
                   file_FriendsNumber.open(QIODevice::WriteOnly);
                   file_FriendsNumber.write("0");
                   file_FriendsNumber.close();
                   //创建朋友上限
                   QFile file_FriendsNumberMax(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/FriendsNumberMax.txt");
                   file_FriendsNumberMax.open(QIODevice::WriteOnly);
                   file_FriendsNumberMax.write("5");
                   file_FriendsNumberMax.close();
                   //创建朋友列表
                   QFile file_FriendsList(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/FriendsList.txt");
                   file_FriendsList.open(QIODevice::WriteOnly);
                   file_FriendsList.close();
                   //创建朋友头像列表
                   QFile file_FriendsAvatarList(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/FriendsAvatarList.txt");
                   file_FriendsAvatarList.open(QIODevice::WriteOnly);
                   file_FriendsAvatarList.close();
                    //创建朋友文件夹
                   path.mkdir(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/Friends");
                   //创建密保文件夹
                   path.mkdir(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/ConfidentialityIssues");
                   QFile file_Issus1(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/ConfidentialityIssues/Issue1.txt");
                   QFile file_Issus2(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/ConfidentialityIssues/Issue2.txt");
                   QFile file_Answer1(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/ConfidentialityIssues/Answer1.txt");
                   QFile file_Answer2(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/ConfidentialityIssues/Answer2.txt");
                    //写入密保问题
                   file_Issus1.open(QIODevice::WriteOnly);
                   file_Issus2.open(QIODevice::WriteOnly);
                   file_Answer1.open(QIODevice::WriteOnly);
                   file_Answer2.open(QIODevice::WriteOnly);
                   file_Issus1.write(ui->lineEdit_Issues1->text().toUtf8());
                   file_Issus2.write(ui->lineEdit_Issues1_2->text().toUtf8());
                   file_Answer1.write(ui->lineEdit_Answer1->text().toUtf8());
                   file_Answer2.write(ui->lineEdit_Answer2->text().toUtf8());
                   file_Issus1.close();
                   file_Issus2.close();
                   file_Answer1.close();
                   file_Answer2.close();
                   //创建背包文件夹
                   path.mkdir(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/Knapsack");
                   //创建背包物品-改名卡
                   QFile file_KnapsackList(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/Knapsack/RenameCard.txt");
                   file_KnapsackList.open(QIODevice::WriteOnly);
                   file_KnapsackList.write("1");
                   file_KnapsackList.close();
                   //更新玩家数
                   QFile file_AccountNumber(QDir::currentPath()+"/AccountList/AccountNumber.txt");
                   file_AccountNumber.open(QIODevice::ReadOnly);
                   int AccountNumber=file_AccountNumber.readAll().toInt()+1;
                   file_AccountNumber.close();
                   file_AccountNumber.open(QIODevice::WriteOnly);
                   file_AccountNumber.write(QString::number(AccountNumber).toUtf8());
                   file_AccountNumber.close();
                   QFile file_AccountList(QDir::currentPath()+"/AccountList/"+QString::number(AccountNumber)+".txt");
                   file_AccountList.open(QIODevice::WriteOnly);
                   file_AccountList.write(ui->lineEdit_account->text().toUtf8());
                   file_AccountList.close();
                   ui->label_CompleteAccount->setText(ui->lineEdit_account->text());
                   ui->stackedWidget->setCurrentIndex(2);
    }
}

void Enroll::on_btn_Next_4_clicked()
{
    LoginScreen *ToLoginScreen = new LoginScreen;
    ToLoginScreen->show();
    this->hide();
}
