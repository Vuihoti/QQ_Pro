#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H
#include <QEvent>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QDesktopServices>
class MouseEvent : public QLabel
{
    Q_OBJECT
public:
    explicit MouseEvent(QWidget *parent = nullptr);

    void change();

    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
signals:

};

#endif // MOUSEEVENT_H
