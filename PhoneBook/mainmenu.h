#ifndef MAINMENU_H
#define MAINMENU_H
#include "ui_mainmenu.h"
#include <QLabel>
#include <QWidget>
namespace Ui {
class MainMenu;
}

class MainMenu :  public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QString id,QWidget *parent = nullptr);
    ~MainMenu();
    Ui::MainMenu *ui;
private slots:
    void on_btn_retrun_clicked();

private :
};

#endif // MAINMENU_H
