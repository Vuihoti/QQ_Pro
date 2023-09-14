#ifndef MEMBERCENTER_H
#define MEMBERCENTER_H

#include <QWidget>

namespace Ui {
class MemberCenter;
}

class MemberCenter : public QWidget
{
    Q_OBJECT

public:
    explicit MemberCenter(QString id,QWidget *parent = nullptr);
    ~MemberCenter();

private:
    Ui::MemberCenter *ui;
};

#endif // MEMBERCENTER_H
