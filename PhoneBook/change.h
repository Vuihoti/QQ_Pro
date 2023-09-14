#ifndef CHANGE_H
#define CHANGE_H

#include <QWidget>

#include "loginscreen.h"
#include "ui_loginscreen.h"


class change : public QWidget
{
    Q_OBJECT
public:
    explicit change(QWidget *parent = nullptr);
    Ui::LoginScreen *ui = LoginScreen::mywidgt->ui;   // 5、将主类中的ui传过来
    int ChangeSomeThingInLoginScreen();  // test类初始化函数

signals:

private slots:

};

#endif // CHANGE_H
