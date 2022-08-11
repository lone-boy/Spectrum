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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qt/qcustomplot.h"

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
    QGridLayout *gridLayout;
    QTextEdit *console;
    QGroupBox *groupBox_lo;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *le_lo_M;
    QLineEdit *le_lo_K;
    QLineEdit *le_lo_H;

    void setupUi(QWidget *device_config)
    {
        if (device_config->objectName().isEmpty())
            device_config->setObjectName(QString::fromUtf8("device_config"));
        device_config->resize(1184, 641);
        device_config->setMinimumSize(QSize(600, 400));
        device_config->setMaximumSize(QSize(16777215, 16777215));
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
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        console = new QTextEdit(widget_2);
        console->setObjectName(QString::fromUtf8("console"));
        console->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 87, 83);\n"
"color: rgb(237, 212, 0);"));

        gridLayout->addWidget(console, 0, 0, 1, 1);

        groupBox_lo = new QGroupBox(widget_2);
        groupBox_lo->setObjectName(QString::fromUtf8("groupBox_lo"));
        groupBox_lo->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 87, 83);"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_lo);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        le_lo_M = new QLineEdit(groupBox_lo);
        le_lo_M->setObjectName(QString::fromUtf8("le_lo_M"));
        le_lo_M->setStyleSheet(QString::fromUtf8("color: rgb(239, 41, 41);\n"
"background-color: rgb(211, 215, 207);"));
        le_lo_M->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(le_lo_M);

        le_lo_K = new QLineEdit(groupBox_lo);
        le_lo_K->setObjectName(QString::fromUtf8("le_lo_K"));
        le_lo_K->setStyleSheet(QString::fromUtf8("color: rgb(239, 41, 41);\n"
"background-color: rgb(211, 215, 207);"));
        le_lo_K->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(le_lo_K);

        le_lo_H = new QLineEdit(groupBox_lo);
        le_lo_H->setObjectName(QString::fromUtf8("le_lo_H"));
        le_lo_H->setStyleSheet(QString::fromUtf8("color: rgb(239, 41, 41);\n"
"background-color: rgb(211, 215, 207);"));
        le_lo_H->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(le_lo_H);


        gridLayout->addWidget(groupBox_lo, 1, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

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
        groupBox_lo->setTitle(QApplication::translate("device_config", "Lo_Hz", nullptr));
        le_lo_M->setText(QApplication::translate("device_config", "70", nullptr));
        le_lo_K->setText(QApplication::translate("device_config", "000", nullptr));
        le_lo_H->setText(QApplication::translate("device_config", "000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class device_config: public Ui_device_config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICE_CONFIG_H
