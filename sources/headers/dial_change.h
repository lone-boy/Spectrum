//
// Created by jcc on 22-8-16.
//

#ifndef SPECTRUM_DIAL_CHANGE_H
#define SPECTRUM_DIAL_CHANGE_H
#include "QWidget"
#include "QMouseEvent"
#include <QtWidgets/QDial>

class dial_change :public QDial
{
    Q_OBJECT
public:
    dial_change(QWidget *parent = 0);
    ~dial_change();

protected:
    void wheelEvent(QWheelEvent *event);

signals:
    void dial_is_change(bool is_add);

};


#endif //SPECTRUM_DIAL_CHANGE_H
