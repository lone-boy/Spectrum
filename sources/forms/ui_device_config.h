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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_device_config
{
public:
    QSplitter *splitter_2;
    QSplitter *splitter;
    QWidget *widget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *button_power;
    QLineEdit *ip_edit;
    QSpacerItem *horizontalSpacer;
    QLineEdit *status;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *device_config)
    {
        if (device_config->objectName().isEmpty())
            device_config->setObjectName(QString::fromUtf8("device_config"));
        device_config->resize(1026, 600);
        device_config->setMinimumSize(QSize(800, 600));
        device_config->setMaximumSize(QSize(16777215, 16777215));
        splitter_2 = new QSplitter(device_config);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(10, 10, 1001, 581));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(600, 300));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
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

        ip_edit = new QLineEdit(layoutWidget);
        ip_edit->setObjectName(QString::fromUtf8("ip_edit"));
        ip_edit->setStyleSheet(QString::fromUtf8("selection-color: rgb(252, 233, 79);"
"background-color: rgb(233, 185, 110);"));

        horizontalLayout->addWidget(ip_edit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        status = new QLineEdit(layoutWidget);
        status->setObjectName(QString::fromUtf8("status"));
        status->setStyleSheet(QString::fromUtf8("background-color: rgb(239, 41, 41);"));
        status->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(status);

        splitter->addWidget(layoutWidget);
        splitter_2->addWidget(splitter);
        widget_2 = new QWidget(splitter_2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(342, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        splitter_2->addWidget(widget_2);

        retranslateUi(device_config);

        QMetaObject::connectSlotsByName(device_config);
    } // setupUi

    void retranslateUi(QWidget *device_config)
    {
        device_config->setWindowTitle(QApplication::translate("device_config", "Spectrum", nullptr));
        button_power->setText(QApplication::translate("device_config", "Power", nullptr));
#ifndef QT_NO_STATUSTIP
        ip_edit->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        ip_edit->setText(QString());
        ip_edit->setPlaceholderText(QApplication::translate("device_config", "ip:192.168.2.1", nullptr));
        status->setText(QString());
        status->setPlaceholderText(QApplication::translate("device_config", "OFF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class device_config: public Ui_device_config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICE_CONFIG_H
