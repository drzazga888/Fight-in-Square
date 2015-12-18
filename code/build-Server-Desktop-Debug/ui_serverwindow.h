/********************************************************************************
** Form generated from reading UI file 'serverwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERWINDOW_H
#define UI_SERVERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerWindow
{
public:
    QWidget *serverCentralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *serverLayout;
    QHBoxLayout *configLayout;
    QLabel *portLabel;
    QLineEdit *portEdit;
    QPushButton *onOffButton;
    QPushButton *selectMapButton;
    QLabel *gamersLabel;
    QTableWidget *gamersList;
    QLabel *logsLabel;
    QTextEdit *messageBox;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ServerWindow)
    {
        if (ServerWindow->objectName().isEmpty())
            ServerWindow->setObjectName(QStringLiteral("ServerWindow"));
        ServerWindow->resize(576, 489);
        serverCentralWidget = new QWidget(ServerWindow);
        serverCentralWidget->setObjectName(QStringLiteral("serverCentralWidget"));
        gridLayout = new QGridLayout(serverCentralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        serverLayout = new QVBoxLayout();
        serverLayout->setSpacing(6);
        serverLayout->setObjectName(QStringLiteral("serverLayout"));
        configLayout = new QHBoxLayout();
        configLayout->setSpacing(6);
        configLayout->setObjectName(QStringLiteral("configLayout"));
        portLabel = new QLabel(serverCentralWidget);
        portLabel->setObjectName(QStringLiteral("portLabel"));

        configLayout->addWidget(portLabel);

        portEdit = new QLineEdit(serverCentralWidget);
        portEdit->setObjectName(QStringLiteral("portEdit"));

        configLayout->addWidget(portEdit);

        onOffButton = new QPushButton(serverCentralWidget);
        onOffButton->setObjectName(QStringLiteral("onOffButton"));

        configLayout->addWidget(onOffButton);

        selectMapButton = new QPushButton(serverCentralWidget);
        selectMapButton->setObjectName(QStringLiteral("selectMapButton"));

        configLayout->addWidget(selectMapButton);


        serverLayout->addLayout(configLayout);

        gamersLabel = new QLabel(serverCentralWidget);
        gamersLabel->setObjectName(QStringLiteral("gamersLabel"));
        gamersLabel->setAlignment(Qt::AlignCenter);

        serverLayout->addWidget(gamersLabel);

        gamersList = new QTableWidget(serverCentralWidget);
        if (gamersList->columnCount() < 3)
            gamersList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        gamersList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        gamersList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        gamersList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        gamersList->setObjectName(QStringLiteral("gamersList"));
        gamersList->horizontalHeader()->setStretchLastSection(true);

        serverLayout->addWidget(gamersList);

        logsLabel = new QLabel(serverCentralWidget);
        logsLabel->setObjectName(QStringLiteral("logsLabel"));
        logsLabel->setAlignment(Qt::AlignCenter);

        serverLayout->addWidget(logsLabel);

        messageBox = new QTextEdit(serverCentralWidget);
        messageBox->setObjectName(QStringLiteral("messageBox"));
        messageBox->setReadOnly(true);

        serverLayout->addWidget(messageBox);


        gridLayout->addLayout(serverLayout, 0, 0, 1, 1);

        ServerWindow->setCentralWidget(serverCentralWidget);
        statusBar = new QStatusBar(ServerWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ServerWindow->setStatusBar(statusBar);

        retranslateUi(ServerWindow);

        QMetaObject::connectSlotsByName(ServerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ServerWindow)
    {
        ServerWindow->setWindowTitle(QApplication::translate("ServerWindow", "Fight in square - serwer", 0));
        portLabel->setText(QApplication::translate("ServerWindow", "Port:", 0));
        portEdit->setText(QApplication::translate("ServerWindow", "8001", 0));
        onOffButton->setText(QApplication::translate("ServerWindow", "Uruchom serwer", 0));
        selectMapButton->setText(QApplication::translate("ServerWindow", "Wyb\303\263r mapy", 0));
        gamersLabel->setText(QApplication::translate("ServerWindow", "Gracze:", 0));
        QTableWidgetItem *___qtablewidgetitem = gamersList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ServerWindow", "ID", 0));
        QTableWidgetItem *___qtablewidgetitem1 = gamersList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ServerWindow", "Dru\305\274yna", 0));
        QTableWidgetItem *___qtablewidgetitem2 = gamersList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ServerWindow", "Imi\304\231", 0));
        logsLabel->setText(QApplication::translate("ServerWindow", "Logi:", 0));
    } // retranslateUi

};

namespace Ui {
    class ServerWindow: public Ui_ServerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERWINDOW_H
