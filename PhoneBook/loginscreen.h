#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>
#include <enroll.h>
#include<QPoint>
#include<QMouseEvent>
#include <QSystemTrayIcon>
#include <QMenu>
#include<QMovie>
#include <QGraphicsDropShadowEffect>
QT_BEGIN_NAMESPACE
namespace Ui { class LoginScreen; }
QT_END_NAMESPACE

class LoginScreen : public QWidget
{
    Q_OBJECT
    //任务栏 右键设置
    QMenu * menu;
    QAction *m_pShowAction;
    QAction *m_pCloseAction;

public:
    LoginScreen(QWidget *parent = nullptr);
    ~LoginScreen();
    QApplication* app;
    void Enroll_Widget();
    void Login();
    void Close();
    void timerEvent(QTimerEvent *);
    void timerEvent2(QTimerEvent *);
    QMovie * m_movie;
    bool isPressedWidget;
    bool isFindPassWord;
    QPoint last;
    void mousePressEvent(QMouseEvent *event);//鼠标点击
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放
     QSystemTrayIcon  * systemtrayicon;  //系统托盘
    static LoginScreen *mywidgt;
    int Timer_Login ;//定时器1
    int Timer_LoginComplete ;//定时器2
    Ui::LoginScreen *ui;

private slots:
    void on_btn_minisize_clicked();

    void on_checkBox_AutoLogin_clicked(bool checked);

    void on_progressBar_Login_valueChanged(int value);

    void on_btn_FindPassWord_clicked();

    void on_btn_Return_2_clicked();


    void on_btn_Next_clicked();

    void on_btn_Return_4_clicked();

    void on_btn_Next_3_clicked();

    void on_btn_Next_2_clicked();

    void on_btn_Return_3_clicked();

    void on_btn_Next_4_clicked();

    void on_btn_FindPassWord_2_clicked();

    void on_btn_QRCord_clicked();

    void on_btn_login_2_clicked();

private:

};
#endif // LOGINSCREEN_H
