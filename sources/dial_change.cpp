//
// Created by jcc on 22-8-16.
//
#include "dial_change.h"

dial_change::dial_change(QWidget *parent)
        : QDial(parent)
{

}

dial_change::~dial_change() {

}
void dial_change::wheelEvent(QWheelEvent *event) {
    if(event->delta() > 0){
        this->setValue(this->value()-1);
        if(this->value() == this->minimum())
            this->setValue(this->maximum());
        emit dial_is_change(false);
    }
    else{
        this->setValue(this->value()+1);
        if(this->value() == this->maximum())
            this->setValue(this->minimum());
        emit dial_is_change(true);
    }
}