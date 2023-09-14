#ifndef SHOP_H
#define SHOP_H

#include <QWidget>

namespace Ui {
class Shop;
}

class Shop : public QWidget
{
    Q_OBJECT

public:
    explicit Shop(QString id,QWidget *parent = nullptr);
    ~Shop();
    void deleteOnelineInFile(QString fileurl,QString needtochangetext,QString changetext);
private:
    Ui::Shop *ui;
};

#endif // SHOP_H
