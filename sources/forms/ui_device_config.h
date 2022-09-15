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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplitter>
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
    QWidget *widget_3;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QPushButton *button_screen_shot;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QLineEdit *frequency_line_edit;
    dial_change *curson_switch;
    QSplitter *splitter_5;
    QSplitter *splitter_4;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *LO_label;
    QLineEdit *lineEdit_Fq;
    QHBoxLayout *horizontalLayout_4;
    QLabel *BandWidth_label;
    QLineEdit *lineEdit_Sp;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_14;
    QRadioButton *radioButton_RG_manual;
    QRadioButton *radioButton_RG_slow;
    QRadioButton *radioButton_RG_fast;
    QRadioButton *radioButton_RG_hybrid;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_rwb;
    dial_change *curson_rwb;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_15;
    QSplitter *splitter_3;
    QWidget *layoutWidget4;
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
    selectnumber *number_select_gain;

    void setupUi(QWidget *device_config)
    {
        if (device_config->objectName().isEmpty())
            device_config->setObjectName(QString::fromUtf8("device_config"));
        device_config->resize(1200, 547);
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
        widget_2->setMinimumSize(QSize(500, 0));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(193, 125, 17);"));
        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(10, 220, 471, 81));
        widget_3->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));
        gridLayout = new QGridLayout(widget_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        button_screen_shot = new QPushButton(widget_3);
        button_screen_shot->setObjectName(QString::fromUtf8("button_screen_shot"));
        button_screen_shot->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        verticalLayout_6->addWidget(button_screen_shot);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        checkBox_1 = new QCheckBox(widget_3);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setStyleSheet(QString::fromUtf8("background-color: rgb(239, 41, 41);"));

        horizontalLayout_6->addWidget(checkBox_1);

        checkBox_2 = new QCheckBox(widget_3);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(252, 175, 62);"));

        horizontalLayout_6->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(widget_3);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setStyleSheet(QString::fromUtf8("background-color: rgb(252, 233, 79);"));

        horizontalLayout_6->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(widget_3);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setStyleSheet(QString::fromUtf8("background-color: rgb(173, 127, 168);"));

        horizontalLayout_6->addWidget(checkBox_4);


        verticalLayout_6->addLayout(horizontalLayout_6);


        horizontalLayout_7->addLayout(verticalLayout_6);

        frequency_line_edit = new QLineEdit(widget_3);
        frequency_line_edit->setObjectName(QString::fromUtf8("frequency_line_edit"));
        frequency_line_edit->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        horizontalLayout_7->addWidget(frequency_line_edit);

        curson_switch = new dial_change(widget_3);
        curson_switch->setObjectName(QString::fromUtf8("curson_switch"));
        curson_switch->setStyleSheet(QString::fromUtf8("background-color: rgb(193, 125, 17);"));

        horizontalLayout_7->addWidget(curson_switch);


        gridLayout->addLayout(horizontalLayout_7, 0, 0, 1, 1);

        splitter_5 = new QSplitter(widget_2);
        splitter_5->setObjectName(QString::fromUtf8("splitter_5"));
        splitter_5->setGeometry(QRect(10, 10, 481, 201));
        splitter_5->setOrientation(Qt::Vertical);
        splitter_4 = new QSplitter(splitter_5);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        splitter_4->setOrientation(Qt::Horizontal);
        layoutWidget1 = new QWidget(splitter_4);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        LO_label = new QLabel(layoutWidget1);
        LO_label->setObjectName(QString::fromUtf8("LO_label"));
        LO_label->setMinimumSize(QSize(100, 30));
        LO_label->setMaximumSize(QSize(400, 30));
        LO_label->setStyleSheet(QString::fromUtf8("background-color: rgb(211, 215, 207);\n"
"color: rgb(46, 52, 54);"));
        LO_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(LO_label);

        lineEdit_Fq = new QLineEdit(layoutWidget1);
        lineEdit_Fq->setObjectName(QString::fromUtf8("lineEdit_Fq"));
        lineEdit_Fq->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);\n"
"color: rgb(78, 154, 6);"));
        lineEdit_Fq->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lineEdit_Fq);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        BandWidth_label = new QLabel(layoutWidget1);
        BandWidth_label->setObjectName(QString::fromUtf8("BandWidth_label"));
        BandWidth_label->setMinimumSize(QSize(100, 30));
        BandWidth_label->setMaximumSize(QSize(400, 30));
        BandWidth_label->setStyleSheet(QString::fromUtf8("color: rgb(46, 52, 54);\n"
"background-color: rgb(211, 215, 207);"));
        BandWidth_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(BandWidth_label);

        lineEdit_Sp = new QLineEdit(layoutWidget1);
        lineEdit_Sp->setObjectName(QString::fromUtf8("lineEdit_Sp"));
        lineEdit_Sp->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);\n"
"color: rgb(78, 154, 6);"));
        lineEdit_Sp->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(lineEdit_Sp);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        groupBox = new QGroupBox(layoutWidget1);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(500, 100));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(211, 215, 207);"));
        horizontalLayout_14 = new QHBoxLayout(groupBox);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        radioButton_RG_manual = new QRadioButton(groupBox);
        radioButton_RG_manual->setObjectName(QString::fromUtf8("radioButton_RG_manual"));
        radioButton_RG_manual->setStyleSheet(QString::fromUtf8("selection-color: rgb(115, 210, 22);"));

        horizontalLayout_14->addWidget(radioButton_RG_manual);

        radioButton_RG_slow = new QRadioButton(groupBox);
        radioButton_RG_slow->setObjectName(QString::fromUtf8("radioButton_RG_slow"));
        radioButton_RG_slow->setChecked(true);

        horizontalLayout_14->addWidget(radioButton_RG_slow);

        radioButton_RG_fast = new QRadioButton(groupBox);
        radioButton_RG_fast->setObjectName(QString::fromUtf8("radioButton_RG_fast"));

        horizontalLayout_14->addWidget(radioButton_RG_fast);

        radioButton_RG_hybrid = new QRadioButton(groupBox);
        radioButton_RG_hybrid->setObjectName(QString::fromUtf8("radioButton_RG_hybrid"));

        horizontalLayout_14->addWidget(radioButton_RG_hybrid);


        horizontalLayout_5->addWidget(groupBox);


        verticalLayout_3->addLayout(horizontalLayout_5);

        splitter_4->addWidget(layoutWidget1);
        layoutWidget2 = new QWidget(splitter_4);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_rwb = new QLabel(layoutWidget2);
        label_rwb->setObjectName(QString::fromUtf8("label_rwb"));
        label_rwb->setMinimumSize(QSize(0, 50));
        label_rwb->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);\n"
"color: rgb(238, 238, 236);"));
        label_rwb->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_rwb);

        curson_rwb = new dial_change(layoutWidget2);
        curson_rwb->setObjectName(QString::fromUtf8("curson_rwb"));

        verticalLayout_2->addWidget(curson_rwb);

        splitter_4->addWidget(layoutWidget2);
        splitter_5->addWidget(splitter_4);
        layoutWidget3 = new QWidget(splitter_5);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        horizontalLayout_15 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        splitter_3 = new QSplitter(layoutWidget3);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        layoutWidget4 = new QWidget(splitter_3);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        number_select_10 = new selectnumber(layoutWidget4);
        number_select_10->setObjectName(QString::fromUtf8("number_select_10"));
        number_select_10->setMinimumSize(QSize(20, 30));
        number_select_10->setMaximumSize(QSize(100, 200));
        number_select_10->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_10);

        number_select_9 = new selectnumber(layoutWidget4);
        number_select_9->setObjectName(QString::fromUtf8("number_select_9"));
        number_select_9->setMinimumSize(QSize(20, 30));
        number_select_9->setMaximumSize(QSize(100, 100));
        number_select_9->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_9);

        number_select_8 = new selectnumber(layoutWidget4);
        number_select_8->setObjectName(QString::fromUtf8("number_select_8"));
        number_select_8->setMinimumSize(QSize(20, 30));
        number_select_8->setMaximumSize(QSize(100, 100));
        number_select_8->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_8);

        number_select_7 = new selectnumber(layoutWidget4);
        number_select_7->setObjectName(QString::fromUtf8("number_select_7"));
        number_select_7->setMinimumSize(QSize(20, 30));
        number_select_7->setMaximumSize(QSize(100, 100));
        number_select_7->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_7);

        number_select_6 = new selectnumber(layoutWidget4);
        number_select_6->setObjectName(QString::fromUtf8("number_select_6"));
        number_select_6->setMinimumSize(QSize(20, 30));
        number_select_6->setMaximumSize(QSize(100, 100));
        number_select_6->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_6);

        number_select_5 = new selectnumber(layoutWidget4);
        number_select_5->setObjectName(QString::fromUtf8("number_select_5"));
        number_select_5->setMinimumSize(QSize(20, 30));
        number_select_5->setMaximumSize(QSize(100, 100));
        number_select_5->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_5);

        number_select_4 = new selectnumber(layoutWidget4);
        number_select_4->setObjectName(QString::fromUtf8("number_select_4"));
        number_select_4->setMinimumSize(QSize(20, 30));
        number_select_4->setMaximumSize(QSize(100, 100));
        number_select_4->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_4);

        number_select_3 = new selectnumber(layoutWidget4);
        number_select_3->setObjectName(QString::fromUtf8("number_select_3"));
        number_select_3->setMinimumSize(QSize(20, 30));
        number_select_3->setMaximumSize(QSize(100, 100));
        number_select_3->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_3);

        number_select_2 = new selectnumber(layoutWidget4);
        number_select_2->setObjectName(QString::fromUtf8("number_select_2"));
        number_select_2->setMinimumSize(QSize(20, 30));
        number_select_2->setMaximumSize(QSize(100, 100));
        number_select_2->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_2);

        number_select_1 = new selectnumber(layoutWidget4);
        number_select_1->setObjectName(QString::fromUtf8("number_select_1"));
        number_select_1->setMinimumSize(QSize(20, 30));
        number_select_1->setMaximumSize(QSize(100, 100));
        number_select_1->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_3->addWidget(number_select_1);

        splitter_3->addWidget(layoutWidget4);
        number_select_bw = new selectnumber(splitter_3);
        number_select_bw->setObjectName(QString::fromUtf8("number_select_bw"));
        number_select_bw->setMinimumSize(QSize(20, 30));
        number_select_bw->setMaximumSize(QSize(100, 100));
        number_select_bw->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));
        splitter_3->addWidget(number_select_bw);

        horizontalLayout_15->addWidget(splitter_3);

        number_select_gain = new selectnumber(layoutWidget3);
        number_select_gain->setObjectName(QString::fromUtf8("number_select_gain"));
        number_select_gain->setMinimumSize(QSize(50, 30));
        number_select_gain->setMaximumSize(QSize(100, 100));
        number_select_gain->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);"));

        horizontalLayout_15->addWidget(number_select_gain);

        splitter_5->addWidget(layoutWidget3);
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
        button_screen_shot->setText(QApplication::translate("device_config", "Screenshot", nullptr));
        checkBox_1->setText(QApplication::translate("device_config", "1", nullptr));
        checkBox_2->setText(QApplication::translate("device_config", "2", nullptr));
        checkBox_3->setText(QApplication::translate("device_config", "3", nullptr));
        checkBox_4->setText(QApplication::translate("device_config", "4", nullptr));
        LO_label->setText(QApplication::translate("device_config", "Frequency Hz", nullptr));
        lineEdit_Fq->setText(QString());
        BandWidth_label->setText(QApplication::translate("device_config", "Span MHz", nullptr));
        groupBox->setTitle(QApplication::translate("device_config", "Rx Gain Mode", nullptr));
        radioButton_RG_manual->setText(QApplication::translate("device_config", "manual", nullptr));
        radioButton_RG_slow->setText(QApplication::translate("device_config", "slow_attack", nullptr));
        radioButton_RG_fast->setText(QApplication::translate("device_config", "fast_attack", nullptr));
        radioButton_RG_hybrid->setText(QApplication::translate("device_config", "hybrid", nullptr));
        label_rwb->setText(QApplication::translate("device_config", "RWB:976Hz", nullptr));
    } // retranslateUi

};

namespace Ui {
    class device_config: public Ui_device_config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICE_CONFIG_H
