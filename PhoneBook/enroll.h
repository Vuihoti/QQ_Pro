#ifndef ENROLL_H
#define ENROLL_H

#include <QWidget>

namespace Ui {
class Enroll;
}

class Enroll : public QWidget
{
    Q_OBJECT

public:
    explicit Enroll(QWidget *parent = nullptr);
    ~Enroll();
    bool isPressedWidget;
    void Determine();
    void Cancel();
    QPoint last;
    bool ConditionAccount=false,ConditionPasswordSame=false;bool ConditionPassword = false;
    bool PASS1=false;bool PASS2=false;bool PASS3=false;bool PASS4=false;
private slots:
    void mousePressEvent(QMouseEvent *event);//鼠标点击
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放

    void on_lineEdit_account_textChanged(const QString &arg1);

    void on_lineEdit_confirmpassword_textChanged(const QString &arg1);

    void on_lineEdit_password_textChanged(const QString &arg1);


    void on_lineEdit_Issues1_textChanged(const QString &arg1);

    void on_lineEdit_Answer1_textChanged(const QString &arg1);

    void on_lineEdit_Issues1_2_textChanged(const QString &arg1);

    void on_lineEdit_Answer2_textChanged(const QString &arg1);

    void on_btn_Return_2_clicked();

    void on_btn_Finishi_clicked();

    void on_btn_Next_4_clicked();

private:
    Ui::Enroll *ui;
};

#endif // ENROLL_H
