//
// Created by jcc on 22-8-6.
//

#ifndef SPECTRUM_DEVICE_CONFIG_H
#define SPECTRUM_DEVICE_CONFIG_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class device_config; }
QT_END_NAMESPACE

class device_config : public QWidget {
Q_OBJECT

public:
    explicit device_config(QWidget *parent = nullptr);

    ~device_config() override;


public slots:
    void on_button_connect_clicked();
    void on_button_clear_clicked();

private:
    Ui::device_config *ui;
};


#endif //SPECTRUM_DEVICE_CONFIG_H
