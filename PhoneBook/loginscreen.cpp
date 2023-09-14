#include "loginscreen.h"
#include "ui_loginscreen.h"
#include <enroll.h>
#include <mainmenu.h>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QHBoxLayout>
#include "change.h"

LoginScreen *LoginScreen::mywidgt=nullptr;

QString UserList[100];
LoginScreen::LoginScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginScreen)
{
    this->setWindowIcon(QIcon(":/Img/asppa-0b5li-001.ico"));
    ui->setupUi(this);
    //创建QDir成员函数
    QDir Arous;
    ui->label_HideBrowse->setPixmap(QPixmap(QDir::currentPath()+"/Img/FunctionalIcons/hide.png"));
    if (!Arous.exists(QDir::currentPath()+"/User")) {  // 使用QDir成员函数exists()来判断文件夹是否存在
        Arous.mkdir(QDir::currentPath()+"/User");}  //不存在的话先创建一个
    //下拉框设计
    QFile file_AccountNumber(QDir::currentPath()+"/AccountList/AccountNumber.txt");
    file_AccountNumber.open(QIODevice::ReadWrite);
    int AccountNumber = file_AccountNumber.readAll().toInt();
    file_AccountNumber.close();
    QIcon icon1;
    for (int i=1;i<=AccountNumber;i++) {
        QFile file_Accountlist(QDir::currentPath()+"/AccountList/"+QString::number(i)+".txt");
        file_Accountlist.open(QIODevice::ReadOnly);
        QString Accountlist=file_Accountlist.readAll();
        QFile file_Avatar(QDir::currentPath()+"/User/"+Accountlist+"/Avatar.txt");
        file_Avatar.open(QIODevice::ReadOnly);
        QFile file_UserName(QDir::currentPath()+"/User/"+Accountlist+"/UserName.txt");
        file_UserName.open(QIODevice::ReadOnly);
        icon1.addPixmap(QPixmap(file_Avatar.readAll()));
        ui->comboBox->addItem(icon1,file_UserName.readAll()+"\n"+Accountlist);
        UserList[i-1]=Accountlist;
        file_Accountlist.close();
        file_Avatar.close();
    }
    //登录保存
    QFile file_LastLogin(QDir::currentPath()+"/AccountList/LastLogin.txt");
    file_LastLogin.open(QIODevice::ReadOnly);
    QString LastLogin = file_LastLogin.readAll();
    file_LastLogin.close();
    if(LastLogin==""){
        ;
    }
    else{
        ui->lineEdit_account->setText(LastLogin);
        QFile file_Avatar(QDir::currentPath()+"/User/"+LastLogin+"/Avatar.txt");
        file_Avatar.open(QIODevice::ReadOnly);
        ui->label_Ava->setStyleSheet("border-image: url("+file_Avatar.readAll()+");background-color: rgb(126, 255, 71);border-width:0px;border-radius:30px;border-style:solid;border-color: rgb(255, 255, 255);");
        file_Avatar.close();
        //判断有无记住密码
        QFile file_RememberPassWord(QDir::currentPath()+"/User/"+LastLogin+"/RememberPassWord.txt");
        file_RememberPassWord.open(QIODevice::ReadOnly);
        QString RememberPassWord=file_RememberPassWord.readAll();
        file_RememberPassWord.close();
        if(RememberPassWord=="True"){
            QFile file_PassWord(QDir::currentPath()+"/User/"+LastLogin+"/PassWord.txt");
            file_PassWord.open(QIODevice::ReadOnly);
            ui->lineEdit_password->setText(file_PassWord.readAll());
            file_PassWord.close();
            ui->checkBox_RemamberPassWord->setChecked(true);
        }
        else{
            ui->lineEdit_password->clear();
            ui->checkBox_RemamberPassWord->setChecked(false);
        }
        ui->btn_login->setEnabled(true);
    }
    //自动登录
    QFile file_AutoLogin(QDir::currentPath()+"/AccountList/AutoLogin.txt");
    //下拉选取账号
    connect(ui->comboBox,&QComboBox::currentTextChanged,this,[=](){
        QString Text = ui->comboBox->currentText();
        ui->lineEdit_account->setText(Text.mid(Text.indexOf("\n")+1));
        //换头像
        QFile file_Avatar(QDir::currentPath()+"/User/"+Text.mid(Text.indexOf("\n")+1)+"/Avatar.txt");
        file_Avatar.open(QIODevice::ReadOnly);
        ui->label_Ava->setStyleSheet("border-image: url("+file_Avatar.readAll()+");background-color: rgb(126, 255, 71);border-width:0px;border-radius:30px;border-style:solid;border-color: rgb(255, 255, 255);");
        file_Avatar.close();

        //判断有无记住密码
        QFile file_RememberPassWord(QDir::currentPath()+"/User/"+Text.mid(Text.indexOf("\n")+1)+"/RememberPassWord.txt");
        file_RememberPassWord.open(QIODevice::ReadOnly);
        QString RememberPassWord=file_RememberPassWord.readAll();
        file_RememberPassWord.close();
        if(RememberPassWord=="True"){
            QFile file_PassWord(QDir::currentPath()+"/User/"+Text.mid(Text.indexOf("\n")+1)+"/PassWord.txt");
            file_PassWord.open(QIODevice::ReadOnly);
            ui->lineEdit_password->setText(file_PassWord.readAll());
            file_PassWord.close();
            ui->checkBox_RemamberPassWord->setChecked(true);
        }
        else{
            ui->lineEdit_password->clear();
            ui->checkBox_RemamberPassWord->setChecked(false);
        }
    });
    //设置窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //实例阴影shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    //设置阴影距离
    shadow->setOffset(0, 0);
    //设置阴影颜色
    shadow->setColor(QColor("#444444"));
    //设置阴影圆角
    shadow->setBlurRadius(10);
    //给嵌套QWidget设置阴影
    ui->widget->setGraphicsEffect(shadow);
    //给垂直布局器设置边距(此步很重要, 设置宽度为阴影的宽度)
    ui->widget->setContentsMargins(1,1,1,1);

    //大地球
    m_movie = new QMovie(":/Img/backround.gif");
    ui->label->setMovie(m_movie);
    QMovie *m_movie2 = new QMovie(":/Img/backround.gif");
    ui->label_backround->setMovie(m_movie2);
    m_movie2->setScaledSize(QSize(429,328));
    m_movie2->setSpeed(500);//速度快不卡
    m_movie2->start();
    ui->label_backround_2->setMovie(m_movie2);
    QSize si(ui->label->width(),ui->label->height());
    m_movie->setScaledSize(si);
    m_movie->setSpeed(500);//速度快不卡
    m_movie->start();

    //lineedit的图标
    QAction * searchAction = new QAction(ui->lineEdit_account);
    searchAction->setIcon(QIcon(":/Img/QQSING.png"));
    ui->lineEdit_account->addAction(searchAction,QLineEdit::LeadingPosition);//表示action所在方位（左侧）。
    ui->lineEdit_FindAccount->addAction(searchAction,QLineEdit::LeadingPosition);
    QAction * searchAction_2 = new QAction(ui->lineEdit_password);
    searchAction_2->setIcon(QIcon(":/Img/lock_gray.png"));
    ui->lineEdit_password->addAction(searchAction_2,QLineEdit::LeadingPosition);//表示action所在方位（左侧）。
    this->setWindowFlags(Qt::SplashScreen|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
    mywidgt = this;
    change Change;
    Change.ChangeSomeThingInLoginScreen();
    //初始化系统托盘
        systemtrayicon = new QSystemTrayIcon(this);
        QIcon icon = QIcon(":/Img/QQ_NoLogin.ico");
        //添加图标
        systemtrayicon->setIcon(icon);
        //当鼠标悬浮，显示文字
        systemtrayicon->setToolTip(QObject::trUtf8("QQ"));
        //显示图标
        systemtrayicon->show();

        //任务栏设  置
        menu = new QMenu(this);
        m_pShowAction = new QAction("打开主面板");
        m_pCloseAction = new QAction("退出");

        menu->addAction(m_pShowAction);
        menu->addSeparator();
        menu->addAction(m_pCloseAction);
        systemtrayicon->setContextMenu(menu);
        connect(m_pShowAction,&QAction::triggered,this,[=](){
            this->show();
        });
        connect(m_pCloseAction,&QAction::triggered,this,[=](){
            this->close();
           app->quit();
        });
        //按钮可用
        connect(ui->lineEdit_FindAccount,&QLineEdit::textChanged,this,[=](){
            QString account = ui->lineEdit_FindAccount->text();
            ui->label_ERRORTIP->clear();
            if(account==""){
                ui->btn_Next->setEnabled(false);
                ui->btn_Next->setStyleSheet("QPushButton{background-color: rgb(159, 200, 254);color: rgb(255, 255, 255);border-radius: 10px;font-size:14px; }QPushButton:hover{background-color: rgb(63, 225, 253);color: rgb(255, 255, 255);border-radius: 10px;}");
            }
            else{
                ui->btn_Next->setEnabled(true);
                ui->btn_Next->setStyleSheet("QPushButton{background-color: rgb(63, 147, 253);color: rgb(255, 255, 255);border-radius: 10px;font-size:14px; }QPushButton:hover{background-color: rgb(63, 225, 253);color: rgb(255, 255, 255);border-radius: 10px;}");
            }
        });
        connect(ui->lineEdit_ChangePassWord1,&QLineEdit::textChanged,this,[=](){
            QString account = ui->lineEdit_ChangePassWord1->text();
            ui->label_ERRORTIP->clear();
            if(account==""){
                ui->btn_Next_3->setEnabled(false);
                ui->btn_Next_3->setStyleSheet("QPushButton{background-color: rgb(159, 200, 254);color: rgb(255, 255, 255);border-radius: 10px;font-size:14px; }QPushButton:hover{background-color: rgb(63, 225, 253);color: rgb(255, 255, 255);border-radius: 10px;}");
            }
            else{
                ui->btn_Next_3->setEnabled(true);
                ui->btn_Next_3->setStyleSheet("QPushButton{background-color: rgb(63, 147, 253);color: rgb(255, 255, 255);border-radius: 10px;font-size:14px; }QPushButton:hover{background-color: rgb(63, 225, 253);color: rgb(255, 255, 255);border-radius: 10px;}");
            }
        });
        //清除ERROR
        connect(ui->lineEdit_ConfidentialityIssues1,&QLineEdit::textChanged,this,[=](){
            ui->label_ERRORTip2->clear();
        });
        connect(ui->lineEdit_ConfidentialityIssues2,&QLineEdit::textChanged,this,[=](){
            ui->label_ERRORTip2->clear();
        });
        //清除ERROR
        connect(ui->lineEdit_ChangePassWord1,&QLineEdit::textChanged,this,[=](){
            ui->label_ERRORTip3->clear();
            ui->label_ERRORTip4->clear();
        });
        connect(ui->lineEdit_ChangePassWord2,&QLineEdit::textChanged,this,[=](){
            ui->label_ERRORTip3->clear();
            ui->label_ERRORTip4->clear();
        });
        //按钮可用不可用？+换头像
        connect(ui->lineEdit_account,&QLineEdit::textChanged,this,[=](){
            QDir path;
            QString account = ui->lineEdit_account->text();
            if (!path.exists(QDir::currentPath()+"/User/"+account)||account==""){
                ui->label_Ava->setStyleSheet("border-image: url(:/Img/moren.png);background-color: rgb(126, 255, 71);border-width:0px;border-radius:30px;border-style:solid;border-color: rgb(255, 255, 255);");
                ui->lineEdit_password->clear();
                ui->checkBox_RemamberPassWord->setChecked(false);
            }
            else{
                //换头像
                QFile file_Avatar(QDir::currentPath()+"/User/"+account+"/Avatar.txt");
                file_Avatar.open(QIODevice::ReadOnly);
                ui->label_Ava->setStyleSheet("border-image: url("+file_Avatar.readAll()+");background-color: rgb(126, 255, 71);border-width:0px;border-radius:30px;border-style:solid;border-color: rgb(255, 255, 255);");
                file_Avatar.close();
                //判断有无记住密码
                QFile file_RememberPassWord(QDir::currentPath()+"/User/"+account+"/RememberPassWord.txt");
                file_RememberPassWord.open(QIODevice::ReadOnly);
                QString RememberPassWord=file_RememberPassWord.readAll();
                file_RememberPassWord.close();
                if(RememberPassWord=="True"){
                    QFile file_PassWord(QDir::currentPath()+"/User/"+account+"/PassWord.txt");
                    file_PassWord.open(QIODevice::ReadOnly);
                    ui->lineEdit_password->setText(file_PassWord.readAll());
                    file_PassWord.close();
                    ui->checkBox_RemamberPassWord->setChecked(true);
                }
                else{
                    ui->lineEdit_password->clear();
                    ui->checkBox_RemamberPassWord->setChecked(false);
                }
            }
            if(account==""){
                ui->btn_login->setEnabled(false);
            }
            else{
                ui->btn_login->setEnabled(true);
            }
        });
    //为窗口打上"登录"的标题 设置大小为 296*233
    setFixedSize(429,328);
    setWindowTitle("登录");
    //实现按钮注册的功能
    connect(ui->btn_enroll,&QPushButton::clicked,this,&LoginScreen::Enroll_Widget);
    //实现按钮登录的功能
    connect(ui->btn_login,&QPushButton::clicked,this,&LoginScreen::Login);
    connect(ui->btn_minisize_2,&QPushButton::clicked,this,&LoginScreen::on_btn_minisize_clicked);
    connect(ui->btn_minisize_3,&QPushButton::clicked,this,&LoginScreen::on_btn_minisize_clicked);
    connect(ui->btn_minisize_4,&QPushButton::clicked,this,&LoginScreen::on_btn_minisize_clicked);
    connect(ui->btn_minisize_5,&QPushButton::clicked,this,&LoginScreen::on_btn_minisize_clicked);
    connect(ui->btn_minisize_6,&QPushButton::clicked,this,&LoginScreen::on_btn_minisize_clicked);
    connect(ui->btn_minisize_7,&QPushButton::clicked,this,&LoginScreen::on_btn_minisize_clicked);
    connect(ui->btn_minisize_8,&QPushButton::clicked,this,&LoginScreen::on_btn_minisize_clicked);
    //实现按钮退出的功能
    connect(ui->btn_close,&QPushButton::clicked,this,&LoginScreen::Close);
    connect(ui->btn_close_2,&QPushButton::clicked,this,&LoginScreen::Close);
    connect(ui->btn_close_3,&QPushButton::clicked,this,&LoginScreen::Close);
    connect(ui->btn_close_4,&QPushButton::clicked,this,&LoginScreen::Close);
    connect(ui->btn_close_5,&QPushButton::clicked,this,&LoginScreen::Close);
    connect(ui->btn_close_6,&QPushButton::clicked,this,&LoginScreen::Close);
    connect(ui->btn_close_7,&QPushButton::clicked,this,&LoginScreen::Close);
    connect(ui->btn_close_8,&QPushButton::clicked,this,&LoginScreen::Close);
    //换层圆角
    connect(ui->stackedWidget,&QStackedWidget::currentChanged,this,[=](){

            if(ui->stackedWidget->currentIndex()==3){
                ui->stackedWidget->setFrameShape(QFrame::NoFrame);
            }
            else if(ui->stackedWidget->currentIndex()==0){
                ui->stackedWidget->setFrameShape(QFrame::Panel);
            }

    });

    //自动登录
    file_AutoLogin.open(QIODevice::ReadOnly);
    QString AutoLogin = file_AutoLogin.readAll();
    if(AutoLogin=="NOONEWANTAUTOLOGIN~"){
        ui->checkBox_AutoLogin->setChecked(false);;
    }
    else{
        ui->checkBox_AutoLogin->setChecked(true);
        ui->btn_login->clicked();
    }
    //返回
    connect(ui->btn_Return,&QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(0);
        ui->lineEdit_password->clear();
    });
}
//去往注册窗口
void LoginScreen::Enroll_Widget(){
    Enroll *ToEnroll = new Enroll;
    this->close();
    systemtrayicon->hide();
    ToEnroll->show();
}
//登录
void LoginScreen::Login(){
    ui->stackedWidget->setCurrentIndex(1);
    ui->progressBar_Login->setValue(0);
    Timer_Login = startTimer(40);
    ui->label_AvaW->setStyleSheet(ui->label_Ava->styleSheet());
}
//实现了关闭按钮
void LoginScreen::Close(){
    app->quit();
}
void Enroll::mousePressEvent(QMouseEvent *event)
{
    isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
    last = event->globalPos();



}

void Enroll::mouseMoveEvent(QMouseEvent *event)
{
    if (isPressedWidget)
        {
            int dx = event->globalX() - last.x();
            int dy = event->globalY() - last.y();
            last = event->globalPos();
            move(x()+dx, y()+dy);
        }
}

void Enroll::mouseReleaseEvent(QMouseEvent *event)
{
    int dx = event->globalX() - last.x();
    int dy = event->globalY() - last.y();
    move(x()+dx, y()+dy);
    isPressedWidget = false; // 鼠标松开时，置为false
}
LoginScreen::~LoginScreen()
{
    delete ui;
}


void LoginScreen::on_btn_minisize_clicked()
{
    this->hide();
}


void LoginScreen::on_checkBox_AutoLogin_clicked(bool checked)
{
    if(checked==true){
        ui->checkBox_RemamberPassWord->setChecked(true);
    }
}

void LoginScreen::timerEvent(QTimerEvent *ev){
    if(ev->timerId()==Timer_Login){//进度条 每0.04秒使得进度条+1%
        int i = ui->progressBar_Login->value();
        ui->progressBar_Login->setValue(i+1);
    }
    if(ev->timerId()==Timer_LoginComplete){//登录成功后等待两秒进入主页面
        MainMenu *ToMainMenu = new MainMenu(ui->lineEdit_account->text());
        ToMainMenu->show();
       systemtrayicon->hide();
       killTimer(Timer_LoginComplete);
       this->close();
    }
}

void LoginScreen::on_progressBar_Login_valueChanged(int value)
{
    if(value==25) ui->label_4->setText("登录中.");
    if(value==50) ui->label_4->setText("登录中..");
    if(value==75) ui->label_4->setText("登录中...");
    if(value==100){
        ui->label_4->setText("登录中....");
        killTimer(Timer_Login);
        //QDir一个对象
        QDir path;
        QString str;
        bool LoginError;
        //判断账号是否存在
        if (!path.exists(QDir::currentPath()+"/User/"+ui->lineEdit_account->text())) {
            //如果不存在就弹出警告窗口
            LoginError = false;
        }
        else{
            //如果存在就准备登录
            QFile file(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/PassWord.txt");
            file.open(QIODevice::ReadOnly);
            //判断用户名密码是否匹配
            if(str.prepend(file.readAll())==ui->lineEdit_password->text()){

                //记录本次登录的用户
                QFile file_LastLogin(QDir::currentPath()+"/AccountList/LastLogin.txt");
                 file_LastLogin.open(QIODevice::WriteOnly);
                 file_LastLogin.write(ui->lineEdit_account->text().toLatin1());
                 file_LastLogin.close();
                //记住密码
                QFile file_RememberPassWord(QDir::currentPath()+"/User/"+ui->lineEdit_account->text()+"/RememberPassWord.txt");
                file_RememberPassWord.open(QIODevice::WriteOnly);
                if(ui->checkBox_RemamberPassWord->isChecked()==true){
                    file_RememberPassWord.write("True");
                }
                else{
                    file_RememberPassWord.write("False");
                }
                file_RememberPassWord.close();
                //自动登录
                QFile file_AutoLogin(QDir::currentPath()+"/AccountList/AutoLogin.txt");
                file_AutoLogin.open(QIODevice::WriteOnly);
                if(ui->checkBox_AutoLogin->isChecked()==true){
                    file_AutoLogin.write(ui->lineEdit_account->text().toLatin1());
                }
                else{
                   file_AutoLogin.write("NOONEWANTAUTOLOGIN~");
                }
                file_AutoLogin.close();
                //更改序号
                int UserOrdinal;
                //找在第几个
                for(int ii=0;;ii++){
                    if(UserList[ii]==ui->lineEdit_account->text()){
                        UserOrdinal=ii+1;
                        break;
                    }
                }
                QFile file_Accountlist(QDir::currentPath()+"/AccountList/1.txt");
                file_Accountlist.open(QIODevice::WriteOnly);
                file_Accountlist.write(ui->lineEdit_account->text().toUtf8());
                file_Accountlist.close();
                for(int ii=2;ii<=UserOrdinal;ii++){
                    QFile file_Accountlist(QDir::currentPath()+"/AccountList/"+QString::number(ii)+".txt");
                    file_Accountlist.open(QIODevice::WriteOnly);
                    file_Accountlist.write(UserList[ii-2].toUtf8());
                    file_Accountlist.close();
                }
                //传入id （很重要）
                QString id = ui->lineEdit_account->text();
                LoginError = true;
                file.close();

           }
            else
                //如果密码不匹配就警告弹窗
                LoginError=false;
            file.close();
        }
        if(LoginError){
           ui->label_4->setText("登录成功") ;
           Timer_LoginComplete = startTimer(4000);
        }
        else {
            ui->stackedWidget->setCurrentIndex(2);
        }
    }
}

void LoginScreen::on_btn_FindPassWord_2_clicked(){
    ui->stackedWidget->setCurrentIndex(3);
}

void LoginScreen::on_btn_FindPassWord_clicked()
{

    ui->stackedWidget->setCurrentIndex(3);
}

void LoginScreen::on_btn_Return_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void LoginScreen::on_btn_Next_clicked()
{
    QDir path;
    //判断用户名密码是否匹配
    if(!path.exists(QDir::currentPath()+"/User/"+ui->lineEdit_FindAccount->text())){
        ui->label_ERRORTIP->setText("账号错误，请重新输入");
    }
    else{
        ui->stackedWidget->setCurrentIndex(4);
        //加载问题1
        QFile file_ConfidentialityIssues1(QDir::currentPath()+"/User/"+ui->lineEdit_FindAccount->text()+"/ConfidentialityIssues/Issue1.txt");
        file_ConfidentialityIssues1.open(QIODevice::ReadOnly);
        ui->label_ConfidentialityIssues1->setText("问题1："+file_ConfidentialityIssues1.readAll());
        file_ConfidentialityIssues1.close();
        //加载问题2
        QFile file_ConfidentialityIssues2(QDir::currentPath()+"/User/"+ui->lineEdit_FindAccount->text()+"/ConfidentialityIssues/Issue2.txt");
        file_ConfidentialityIssues2.open(QIODevice::ReadOnly);
        ui->label_ConfidentialityIssues2->setText("问题2："+file_ConfidentialityIssues2.readAll());
        file_ConfidentialityIssues2.close();
    }
}

void LoginScreen::on_btn_Return_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void LoginScreen::on_btn_Next_3_clicked()
{
    bool ConditionPassword =false;
    bool ConditionPasswordSame = false;
     //判断密码是否有汉字
    if(!ui->lineEdit_ChangePassWord1->text().contains(QRegExp("[\\x4e00-\\x9fa5]+"))){
        //如果是的话就返回一个true
        ConditionPassword=true;
    }
    //判断密码是否相同
    if(ui->lineEdit_ChangePassWord1->text()==ui->lineEdit_ChangePassWord2->text()){
        //是的话就返回一个true
        ConditionPasswordSame=true;
    }
    if(ConditionPassword&&ConditionPasswordSame){
        QFile file_PassWord (QDir::currentPath()+"/User/"+ui->lineEdit_FindAccount->text()+"/PassWord.txt");
        file_PassWord.open(QIODevice::WriteOnly);
        file_PassWord.write(ui->lineEdit_ChangePassWord1->text().toUtf8());
        ui->stackedWidget->setCurrentIndex(6);
        ui->label_ChangeCompleteAccount->setText(ui->lineEdit_FindAccount->text());
    }
    else{
        if(!ConditionPasswordSame){
            ui->label_ERRORTip3->setText("密码不相同，请重新输入");
        }
        if(!ConditionPassword){
            ui->label_ERRORTip4->setText("密码中不能含有中文字符");
        }
    }
}

void LoginScreen::on_btn_Next_2_clicked()
{
    //加载答案1
    QFile Answer1(QDir::currentPath()+"/User/"+ui->lineEdit_FindAccount->text()+"/ConfidentialityIssues/Answer1.txt");
    Answer1.open(QIODevice::ReadOnly);
    QString IssuesAnswer1 = Answer1.readAll();
    Answer1.close();
    QFile Answer2(QDir::currentPath()+"/User/"+ui->lineEdit_FindAccount->text()+"/ConfidentialityIssues/Answer2.txt");
    Answer2.open(QIODevice::ReadOnly);
    QString IssuesAnswer2 = Answer2.readAll();
    Answer2.close();
    if(ui->lineEdit_ConfidentialityIssues1->text()==IssuesAnswer1&&ui->lineEdit_ConfidentialityIssues2->text()==IssuesAnswer2){
        ui->stackedWidget->setCurrentIndex(5);
    }
    else{
        ui->label_ERRORTip2->setText("答案错误，请重新输入");
    }
}

void LoginScreen::on_btn_Return_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}



void LoginScreen::on_btn_Next_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void LoginScreen::on_btn_QRCord_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void LoginScreen::on_btn_login_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
