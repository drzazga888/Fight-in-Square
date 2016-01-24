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
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerWindow
{
public:
    QWidget *serverCentralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *serverLayout;
    QHBoxLayout *mapConfigLayout;
    QLabel *selectMapLabel;
    QLabel *selectedMapLabel;
    QPushButton *selectMapButton;
    QHBoxLayout *serverConfigLayout;
    QLabel *portLabel;
    QLineEdit *portEdit;
    QLabel *timeLabel;
    QTimeEdit *timeEdit;
    QPushButton *onOffButton;
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
        mapConfigLayout = new QHBoxLayout();
        mapConfigLayout->setSpacing(6);
        mapConfigLayout->setObjectName(QStringLiteral("mapConfigLayout"));
        selectMapLabel = new QLabel(serverCentralWidget);
        selectMapLabel->setObjectName(QStringLiteral("selectMapLabel"));

        mapConfigLayout->addWidget(selectMapLabel);

        selectedMapLabel = new QLabel(serverCentralWidget);
        selectedMapLabel->setObjectName(QStringLiteral("selectedMapLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(selectedMapLabel->sizePolicy().hasHeightForWidth());
        selectedMapLabel->setSizePolicy(sizePolicy);

        mapConfigLayout->addWidget(selectedMapLabel);

        selectMapButton = new QPushButton(serverCentralWidget);
        selectMapButton->setObjectName(QStringLiteral("selectMapButton"));

        mapConfigLayout->addWidget(selectMapButton);


        serverLayout->addLayout(mapConfigLayout);

        serverConfigLayout = new QHBoxLayout();
        serverConfigLayout->setSpacing(6);
        serverConfigLayout->setObjectName(QStringLiteral("serverConfigLayout"));
        portLabel = new QLabel(serverCentralWidget);
        portLabel->setObjectName(QStringLiteral("portLabel"));

        serverConfigLayout->addWidget(portLabel);

        portEdit = new QLineEdit(serverCentralWidget);
        portEdit->setObjectName(QStringLiteral("portEdit"));

        serverConfigLayout->addWidget(portEdit);

        timeLabel = new QLabel(serverCentralWidget);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));

        serverConfigLayout->addWidget(timeLabel);

        timeEdit = new QTimeEdit(serverCentralWidget);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setTime(QTime(0, 10, 0));

        serverConfigLayout->addWidget(timeEdit);

        onOffButton = new QPushButton(serverCentralWidget);
        onOffButton->setObjectName(QStringLiteral("onOffButton"));

        serverConfigLayout->addWidget(onOffButton);


        serverLayout->addLayout(serverConfigLayout);

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
        gamersList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        gamersList->horizontalHeader()->setStretchLastSection(true);
        gamersList->verticalHeader()->setVisible(false);

        serverLayout->addWidget(gamersList);

        logsLabel = new QLabel(serverCentralWidget);
        logsLabel->setObjectName(QStringLiteral("logsLabel"));
        logsLabel->setAlignment(Qt::AlignCenter);

        serverLayout->addWidget(logsLabel);

        messageBox = new QTextEdit(serverCentralWidget);
        messageBox->setObjectName(QStringLiteral("messageBox"));
        messageBox->setReadOnly(true);

        serverLayout->addWidget(messageBox);


        gridLayout->addLayout(serverLayout, 2, 0, 1, 1);

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
        selectMapLabel->setText(QApplication::translate("ServerWindow", "Wybrana mapa:", 0));
        selectedMapLabel->setText(QApplication::translate("ServerWindow", "(brak)", 0));
        selectMapButton->setText(QApplication::translate("ServerWindow", "Wyb\303\263r mapy", 0));
        portLabel->setText(QApplication::translate("ServerWindow", "Port:", 0));
        portEdit->setText(QApplication::translate("ServerWindow", "8001", 0));
        timeLabel->setText(QApplication::translate("ServerWindow", "Czas gry:", 0));
        timeEdit->setDisplayFormat(QApplication::translate("ServerWindow", "mm:ss", 0));
        onOffButton->setText(QApplication::translate("ServerWindow", "Uruchom serwer", 0));
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
