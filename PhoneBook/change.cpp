#include "change.h"

change::change(QWidget *parent) : QWidget(parent)
{

}

int change::ChangeSomeThingInLoginScreen(){
    //判断这个时候是什么状态
    if(ui->label_HideBrowse->accessibleName()=="隐藏密码"){
        //设置为显示密码
        ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
    }
    else {
        //设置为隐藏密码
        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}
    return 0;
}


