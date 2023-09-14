#include "mouseevent.h"
#include "ui_mainmenu.h"

#include "personalinformation.h"
#include "change.h"
#include "addfriends.h"
#include "showfriends.h"
#include "shop.h"
#include "showcommodity.h"
#include "knapsack.h"
#include "membercenter.h"

#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QDebug>
MouseEvent::MouseEvent(QWidget *parent) : QLabel(parent)
{

}

//鼠标事件 主要是完成一些非PushButton类的控件实现按钮功能

//当鼠标进入到控件
void MouseEvent::enterEvent(QEvent *event){
    //this->setFrameShape(QLabel::WinPanel);
    this->setCursor(Qt::PointingHandCursor);
}
//当鼠标离开控件
void MouseEvent::leaveEvent(QEvent *){
   //this->setFrameShape(QLabel::NoFrame);
}
//鼠标释放事件
void MouseEvent::mouseReleaseEvent(QMouseEvent *ev){
    //控件"个人信息" 所在的窗口为"MainMenu"
    if(this->accessibleName()=="个人信息"){
        //进入到个人信息窗口
        PersonalInformation *ToPersonalInformation = new PersonalInformation(this->whatsThis());
        ToPersonalInformation->show();
    }
    //控件"更换头像" 所在的窗口为"PersonalInformation"
    else if(this->accessibleName()=="更换头像"){
        //选择一张图片来当头像
        QString fileName = QFileDialog::getOpenFileName(this,"选择一个文件",QCoreApplication::applicationFilePath(),"*.jpg");
        //如果选择的不是空的
        if(fileName.isEmpty()==false){
            //写入头像信息
            QFile file_ChangeAvatar(QDir::currentPath()+"/User/"+this->whatsThis()+"/Avatar.txt");
            file_ChangeAvatar.open(QIODevice::ReadWrite|QFile::Truncate);
            file_ChangeAvatar.write(fileName.toUtf8());
            file_ChangeAvatar.close();
            //更新个人页面中的头像
            QFile file_Update(QDir::currentPath()+"/User/"+this->whatsThis()+"/Avatar.txt");
            file_Update.open(QIODevice::ReadOnly);
            this->setPixmap(QPixmap(file_Update.readAll()));
            file_Update.close();
        }
        //如果是空的就不了了之
        else{;}

    }
    //控件"更新说明" 所在的窗口为"MainMenu"
    else if(this->accessibleName()=="更新日记"){
        //前往更新说明的网站
        QDesktopServices::openUrl(QUrl(QLatin1String("https://lol.qq.com/main.shtml")));;
    }
    //控件"显示密码" 所在的窗口为"LoginScreen"
    else if(this->accessibleName()=="显示密码"){
        //更新控件为"隐藏密码"
        this->setPixmap(QPixmap(QDir::currentPath()+"/Img/FunctionalIcons/browse.png"));
        this->setAccessibleName("隐藏密码");
        this->setToolTip("隐藏密码");
        //前往跨类调用UI
        class change Change;
        int b = Change.ChangeSomeThingInLoginScreen();
        b =0;
    }
    //控件"隐藏密码" 所在的窗口为"LoginScreen"
    else if(this->accessibleName()=="隐藏密码"){
        //更新控件为"显示密码"
        this->setPixmap(QPixmap(QDir::currentPath()+"/Img/FunctionalIcons/hide.png"));
        this->setAccessibleName("显示密码");
        this->setToolTip("显示密码");
        //前往跨类调用UI
        class change Change;
        int a = Change.ChangeSomeThingInLoginScreen();
        a =0;
    }
    //控件"添加好友" 所在的窗口为"MainMenu"
    else if(this->accessibleName()=="添加好友"){
        //进入"添加好友"窗口
        AddFriends *ToAddFriends = new AddFriends(this->whatsThis());
        ToAddFriends->show();
    }
    else if(this->accessibleName()=="更改联系人头像"){
        QString fileName = QFileDialog::getOpenFileName(this,"选择一个文件",QCoreApplication::applicationFilePath(),"*.jpg");
        if(fileName.isEmpty()==false){
            //写入头像信息
            this->setWhatsThis(fileName);
            this->setPixmap(QPixmap(fileName));
        }
        //如果是空的就不了了之
        else{
            ;
        }
    }
    else if(this->accessibleName()=="搜索联系人"){
//        QMessageBox::information(this,"s",this->whatsThis());
       QDir path;
       if(!path.exists(QDir::currentPath()+"/User/"+this->accessibleDescription()+"/Friends/"+this->whatsThis())){
           QMessageBox::warning(this,"搜索联系人","无此联系人\n["+this->whatsThis()+"]");
       }
        else{
           ShowFriends *ToShowFriends = new ShowFriends(this->whatsThis(),this->accessibleDescription());
           ToShowFriends->show();;
       }
    }
    else if(this->accessibleName()=="商城"){
        Shop *Toshop = new Shop(this->whatsThis());
        Toshop->show();
    }
    else if(this->accessibleName()=="改名卡"){
        ShowCommodity *ToShowCommodity = new ShowCommodity(this->whatsThis(),this->statusTip());
        ToShowCommodity->show();
    }
    else if(this->accessibleName()=="背包"){
        Knapsack *ToKnapsack = new Knapsack(this->whatsThis());
        ToKnapsack -> show();
    }
    else if(this->accessibleName()=="会员中心"){
        MemberCenter *ToMemberCenter = new MemberCenter(this->whatsThis());
        ToMemberCenter -> show();
    }
    else if(this->text()=="找回密码"){

    }
}
