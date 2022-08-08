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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_device_config
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *textEdit;
    QVBoxLayout *verticalLayout_3;
    QPushButton *button_open;
    QPushButton *button_connect;
    QPushButton *button_clear;
    QLineEdit *lineEdit_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *device_config)
    {
        if (device_config->objectName().isEmpty())
            device_config->setObjectName(QString::fromUtf8("device_config"));
        device_config->resize(1010, 595);
        gridLayout = new QGridLayout(device_config);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        textEdit = new QTextEdit(device_config);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setReadOnly(false);

        verticalLayout_4->addWidget(textEdit);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        button_open = new QPushButton(device_config);
        button_open->setObjectName(QString::fromUtf8("button_open"));

        verticalLayout_3->addWidget(button_open);

        button_connect = new QPushButton(device_config);
        button_connect->setObjectName(QString::fromUtf8("button_connect"));

        verticalLayout_3->addWidget(button_connect);

        button_clear = new QPushButton(device_config);
        button_clear->setObjectName(QString::fromUtf8("button_clear"));

        verticalLayout_3->addWidget(button_clear);

        lineEdit_2 = new QLineEdit(device_config);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout_3->addWidget(lineEdit_2);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label = new QLabel(device_config);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_5->addWidget(label);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_6->addItem(horizontalSpacer_6);


        horizontalLayout->addLayout(verticalLayout_6);


        verticalLayout_7->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_7->addLayout(horizontalLayout_2);

        verticalLayout_7->setStretch(0, 1);
        verticalLayout_7->setStretch(1, 3);

        gridLayout->addLayout(verticalLayout_7, 0, 0, 1, 1);


        retranslateUi(device_config);

        QMetaObject::connectSlotsByName(device_config);
    } // setupUi

    void retranslateUi(QWidget *device_config)
    {
        device_config->setWindowTitle(QApplication::translate("device_config", "device_config", nullptr));
        button_open->setText(QApplication::translate("device_config", "open", nullptr));
        button_connect->setText(QApplication::translate("device_config", "connect", nullptr));
        button_clear->setText(QApplication::translate("device_config", "clear", nullptr));
        lineEdit_2->setPlaceholderText(QApplication::translate("device_config", "ip:192.168.2.1", nullptr));
        label->setText(QApplication::translate("device_config", "\347\256\200\346\230\223\351\242\221\350\260\261\344\273\252", nullptr));
    } // retranslateUi

};

namespace Ui {
    class device_config: public Ui_device_config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICE_CONFIG_H
