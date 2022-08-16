/********************************************************************************
** Form generated from reading UI file 'device_config.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICE_CONFIG_H
#define UI_DEVICE_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "dial_change.h"
#include "qt/qcustomplot.h"
#include "selectnumber.h"

QT_BEGIN_NAMESPACE

class Ui_device_config
{
public:
    QGridLayout *gridLayout_2;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QCustomPlot *custom_plot;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *button_power;
    QPushButton *button_disconnect;
    QLineEdit *ip_edit;
    QLineEdit *status;
    QWidget *widget_2;
    QGridLayout *gridLayout_3;
    QSplitter *splitter_5;
    QSplitter *splitter_4;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *console;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *LO_label;
    QLabel *BandWidth_label;
    QSplitter *splitter_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    selectnumber *number_select_10;
    selectnumber *number_select_9;
    selectnumber *number_select_8;
    selectnumber *number_select_7;
    selectnumber *number_select_6;
    selectnumber *number_select_5;
    selectnumber *number_select_4;
    selectnumber *number_select_3;
    selectnumber *number_select_2;
    selectnumber *number_select_1;
    selectnumber *number_select_bw;
    QWidget *widget_3;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    dial_change *curson_switch;

    void setupUi(QWidget *device_config)
    {
        if (device_config->objectName().isEmpty())
            device_config->setObjectName(QString::fromUtf8("device_config"));
        device_config->resize(1134, 682);
        device_config->setMinimumSize(QSize(600, 400));
        device_config->setMaximumSize(QSize(1200, 2000));
        gridLayout_2 = new QGridLayout(device_config);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        splitter_2 = new QSplitter(device_config);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(600, 300));
        widget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        custom_plot = new QCustomPlot(widget);
        custom_plot->setObjectName(QString::fromUtf8("custom_plot"));
        custom_plot->setMinimumSize(QSize(600, 300));
        custom_plot->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(custom_plot);

        splitter->addWidget(widget);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        button_power = new QPushButton(layoutWidget);
        button_power->setObjectName(QString::fromUtf8("button_power"));
        button_power->setMinimumSize(QSize(30, 30));
        button_power->setStyleSheet(QString::fromUtf8("background-color: rgb(78, 154, 6);"));

        horizontalLayout->addWidget(button_power);

        button_disconnect = new QPushButton(layoutWidget);
        button_disconnect->setObjectName(QString::fromUtf8("button_disconnect"));
        button_disconnect->setStyleSheet(QString::fromUtf8("background-color: rgb(204, 0, 0);"));

        horizontalLayout->addWidget(button_disconnect);

        ip_edit = new QLineEdit(layoutWidget);
        ip_edit->setObjectName(QString::fromUtf8("ip_edit"));
        ip_edit->setStyleSheet(QString::fromUtf8("selection-color: rgb(252, 233, 79);\n"
"background-color: rgb(233, 185, 110);"));

        horizontalLayout->addWidget(ip_edit);

        status = new QLineEdit(layoutWidget);
        status->setObjectName(QString::fromUtf8("status"));
        status->setStyleSheet(QString::fromUtf8("background-color: rgb(239, 41, 41);"));
        status->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(status);

        splitter->addWidget(layoutWidget);
        splitter_2->addWidget(splitter);
        widget_2 = new QWidget(splitter_2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_3 = new QGridLayout(widget_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        splitter_5 = new QSplitter(widget_2);
        splitter_5->setObjectName(QString::fromUtf8("splitter_5"));
        splitter_5->setOrientation(Qt::Vertical);
        splitter_4 = new QSplitter(splitter_5);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        splitter_4->setOrientation(Qt::Vertical);
        widget1 = new QWidget(splitter_4);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        verticalLayout_3 = new QVBoxLayout(widget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        console = new QTextEdit(widget1);
        console->setObjectName(QString::fromUtf8("console"));
        console->setMinimumSize(QSize(200, 100));
        console->setMaximumSize(QSize(300, 200));
        console->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 87, 83);\n"
"color: rgb(237, 212, 0);"));

        verticalLayout_3->addWidget(console);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        LO_label = new QLabel(widget1);
        LO_label->setObjectName(QString::fromUtf8("LO_label"));
        LO_label->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 87, 83);\n"
"color: rgb(238, 238, 236);"));

        horizontalLayout_2->addWidget(LO_label);

        BandWidth_label = new QLabel(widget1);
        BandWidth_label->setObjectName(QString::fromUtf8("BandWidth_label"));
        BandWidth_label->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 87, 83);\n"
"color: rgb(238, 238, 236);"));

        horizontalLayout_2->addWidget(BandWidth_label);


        verticalLayout_2->addLayout(horizontalLayout_2);

        splitter_3 = new QSplitter(widget1);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        layoutWidget1 = new QWidget(splitter_3);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        number_select_10 = new selectnumber(layoutWidget1);
        number_select_10->setObjectName(QString::fromUtf8("number_select_10"));
        number_select_10->setMinimumSize(QSize(20, 30));
        number_select_10->setMaximumSize(QSize(100, 200));
        number_select_10->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_10);

        number_select_9 = new selectnumber(layoutWidget1);
        number_select_9->setObjectName(QString::fromUtf8("number_select_9"));
        number_select_9->setMinimumSize(QSize(20, 30));
        number_select_9->setMaximumSize(QSize(100, 200));
        number_select_9->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_9);

        number_select_8 = new selectnumber(layoutWidget1);
        number_select_8->setObjectName(QString::fromUtf8("number_select_8"));
        number_select_8->setMinimumSize(QSize(20, 30));
        number_select_8->setMaximumSize(QSize(100, 200));
        number_select_8->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_8);

        number_select_7 = new selectnumber(layoutWidget1);
        number_select_7->setObjectName(QString::fromUtf8("number_select_7"));
        number_select_7->setMinimumSize(QSize(20, 30));
        number_select_7->setMaximumSize(QSize(100, 200));
        number_select_7->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_7);

        number_select_6 = new selectnumber(layoutWidget1);
        number_select_6->setObjectName(QString::fromUtf8("number_select_6"));
        number_select_6->setMinimumSize(QSize(20, 30));
        number_select_6->setMaximumSize(QSize(100, 200));
        number_select_6->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_6);

        number_select_5 = new selectnumber(layoutWidget1);
        number_select_5->setObjectName(QString::fromUtf8("number_select_5"));
        number_select_5->setMinimumSize(QSize(20, 30));
        number_select_5->setMaximumSize(QSize(100, 200));
        number_select_5->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_5);

        number_select_4 = new selectnumber(layoutWidget1);
        number_select_4->setObjectName(QString::fromUtf8("number_select_4"));
        number_select_4->setMinimumSize(QSize(20, 30));
        number_select_4->setMaximumSize(QSize(100, 200));
        number_select_4->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_4);

        number_select_3 = new selectnumber(layoutWidget1);
        number_select_3->setObjectName(QString::fromUtf8("number_select_3"));
        number_select_3->setMinimumSize(QSize(20, 30));
        number_select_3->setMaximumSize(QSize(100, 200));
        number_select_3->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_3);

        number_select_2 = new selectnumber(layoutWidget1);
        number_select_2->setObjectName(QString::fromUtf8("number_select_2"));
        number_select_2->setMinimumSize(QSize(20, 30));
        number_select_2->setMaximumSize(QSize(100, 200));
        number_select_2->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_2);

        number_select_1 = new selectnumber(layoutWidget1);
        number_select_1->setObjectName(QString::fromUtf8("number_select_1"));
        number_select_1->setMinimumSize(QSize(20, 30));
        number_select_1->setMaximumSize(QSize(100, 200));
        number_select_1->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_1);

        splitter_3->addWidget(layoutWidget1);
        number_select_bw = new selectnumber(splitter_3);
        number_select_bw->setObjectName(QString::fromUtf8("number_select_bw"));
        number_select_bw->setMinimumSize(QSize(20, 30));
        number_select_bw->setMaximumSize(QSize(100, 200));
        number_select_bw->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));
        splitter_3->addWidget(number_select_bw);

        verticalLayout_2->addWidget(splitter_3);


        verticalLayout_3->addLayout(verticalLayout_2);

        splitter_4->addWidget(widget1);
        splitter_5->addWidget(splitter_4);
        widget_3 = new QWidget(splitter_5);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));
        gridLayout = new QGridLayout(widget_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        pushButton = new QPushButton(widget_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        verticalLayout_6->addWidget(pushButton);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        checkBox_1 = new QCheckBox(widget_3);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setStyleSheet(QString::fromUtf8("background-color: rgb(239, 41, 41);"));

        horizontalLayout_6->addWidget(checkBox_1);

        checkBox_3 = new QCheckBox(widget_3);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setStyleSheet(QString::fromUtf8("background-color: rgb(252, 175, 62);"));

        horizontalLayout_6->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(widget_3);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setStyleSheet(QString::fromUtf8("background-color: rgb(252, 233, 79);"));

        horizontalLayout_6->addWidget(checkBox_4);

        checkBox_5 = new QCheckBox(widget_3);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setStyleSheet(QString::fromUtf8("background-color: rgb(173, 127, 168);"));

        horizontalLayout_6->addWidget(checkBox_5);


        verticalLayout_6->addLayout(horizontalLayout_6);


        horizontalLayout_7->addLayout(verticalLayout_6);

        curson_switch = new dial_change(widget_3);
        curson_switch->setObjectName(QString::fromUtf8("curson_switch"));
        curson_switch->setStyleSheet(QString::fromUtf8("background-color: rgb(193, 125, 17);"));

        horizontalLayout_7->addWidget(curson_switch);


        gridLayout->addLayout(horizontalLayout_7, 0, 0, 1, 1);

        splitter_5->addWidget(widget_3);

        gridLayout_3->addWidget(splitter_5, 0, 0, 1, 1);

        splitter_2->addWidget(widget_2);

        gridLayout_2->addWidget(splitter_2, 0, 0, 1, 1);


        retranslateUi(device_config);

        QMetaObject::connectSlotsByName(device_config);
    } // setupUi

    void retranslateUi(QWidget *device_config)
    {
        device_config->setWindowTitle(QApplication::translate("device_config", "Spectrum", nullptr));
        button_power->setText(QApplication::translate("device_config", "Power", nullptr));
        button_disconnect->setText(QApplication::translate("device_config", "Disconnect", nullptr));
#ifndef QT_NO_STATUSTIP
        ip_edit->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        ip_edit->setText(QString());
        ip_edit->setPlaceholderText(QApplication::translate("device_config", "ip:192.168.2.1", nullptr));
        status->setText(QString());
        status->setPlaceholderText(QApplication::translate("device_config", "OFF", nullptr));
        LO_label->setText(QApplication::translate("device_config", "LO_hz", nullptr));
        BandWidth_label->setText(QApplication::translate("device_config", "Band_width", nullptr));
        pushButton->setText(QApplication::translate("device_config", "Marker", nullptr));
        checkBox_1->setText(QApplication::translate("device_config", "1", nullptr));
        checkBox_3->setText(QApplication::translate("device_config", "2", nullptr));
        checkBox_4->setText(QApplication::translate("device_config", "3", nullptr));
        checkBox_5->setText(QApplication::translate("device_config", "4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class device_config: public Ui_device_config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICE_CONFIG_H
