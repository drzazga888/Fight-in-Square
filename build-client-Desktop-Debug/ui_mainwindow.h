/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QStackedWidget *stackedWidget;
    QWidget *menu;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *menuLayout;
    QGridLayout *connectionLayout;
    QLabel *playerNameLabel;
    QLabel *serverIpLabel;
    QLineEdit *serverPortEdit;
    QLineEdit *serverIpEdit;
    QLabel *serverPortLabel;
    QLineEdit *playerNameEdit;
    QPushButton *connectButton;
    QSpacerItem *connectionSpacer;
    QPushButton *helpButton;
    QPushButton *exitButton;
    QWidget *game;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *gameLayout;
    QWidget *canvasBack;
    QVBoxLayout *gameInfo;
    QLabel *title;
    QSpacerItem *titlePlayerSpacer;
    QLabel *playerName;
    QSpacerItem *playerBarsSpacer;
    QLabel *healthLabel;
    QProgressBar *healthBar;
    QSpacerItem *betweenBarsSpacer;
    QLabel *powerLabel;
    QProgressBar *powerBar;
    QSpacerItem *powerTopSpacer;
    QLabel *pointsLabel;
    QSpacerItem *pointsTimeSpacer;
    QLabel *timeLabel;
    QSpacerItem *timeTopSpacer;
    QLabel *topLabel;
    QTableWidget *top;
    QSpacerItem *exitGameSpacer;
    QPushButton *exitGameButton;
    QStatusBar *statusbar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1134, 692);
        MainWindow->setStyleSheet(QLatin1String("* {\n"
"	color: #fff;\n"
"}\n"
"\n"
"QStatusBar {\n"
"	background-color: #666;\n"
"	color: #fff;\n"
"}\n"
"\n"
"QLineEdit {\n"
"	color: #000;\n"
"}\n"
"\n"
"QPushButton {\n"
"	padding: 5px;\n"
"}\n"
"\n"
"QProgressBar,\n"
"QPushButton {\n"
"	background-color: #666;\n"
"	border: none;\n"
"}\n"
"\n"
"QHeaderView,\n"
"QTableWidget {\n"
"	background-color: #222;\n"
"}\n"
"\n"
"QTableCornerButton::section,\n"
"QHeaderView::section {\n"
"	background-color: #666;\n"
"	border: none;\n"
"	padding: 2px 4px;\n"
"}\n"
"\n"
"QProgressBar#healthBar::chunk {\n"
"	background-color: #f00;\n"
"}\n"
"\n"
"QProgressBar#powerBar::chunk {\n"
"	background-color: #0c0;\n"
"}\n"
"\n"
"QWidget#menu {\n"
"	background-image: url(../img/welcome_screen.png);\n"
"}\n"
"\n"
"QWidget#game {\n"
"	background-color: #000;\n"
"}\n"
"\n"
"QWidget#canvasBack {\n"
"	background-image: url(../img/canvas_outline.png);\n"
"}\n"
"\n"
"QLabel#title{\n"
"	color: rgb(241, 203, 11);\n"
"	font-size: 36px;\n"
"}\n"
"\n"
"QLabel#playerName{\n"
"	color: #f00;\n"
""
                        "	font-size: 26px;\n"
"}"));
        stackedWidget = new QStackedWidget(MainWindow);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        menu = new QWidget();
        menu->setObjectName(QStringLiteral("menu"));
        verticalLayoutWidget = new QWidget(menu);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(750, 350, 301, 241));
        menuLayout = new QVBoxLayout(verticalLayoutWidget);
        menuLayout->setObjectName(QStringLiteral("menuLayout"));
        menuLayout->setContentsMargins(0, 0, 0, 0);
        connectionLayout = new QGridLayout();
        connectionLayout->setObjectName(QStringLiteral("connectionLayout"));
        playerNameLabel = new QLabel(verticalLayoutWidget);
        playerNameLabel->setObjectName(QStringLiteral("playerNameLabel"));

        connectionLayout->addWidget(playerNameLabel, 0, 0, 1, 1);

        serverIpLabel = new QLabel(verticalLayoutWidget);
        serverIpLabel->setObjectName(QStringLiteral("serverIpLabel"));

        connectionLayout->addWidget(serverIpLabel, 1, 0, 1, 1);

        serverPortEdit = new QLineEdit(verticalLayoutWidget);
        serverPortEdit->setObjectName(QStringLiteral("serverPortEdit"));

        connectionLayout->addWidget(serverPortEdit, 2, 1, 1, 1);

        serverIpEdit = new QLineEdit(verticalLayoutWidget);
        serverIpEdit->setObjectName(QStringLiteral("serverIpEdit"));

        connectionLayout->addWidget(serverIpEdit, 1, 1, 1, 1);

        serverPortLabel = new QLabel(verticalLayoutWidget);
        serverPortLabel->setObjectName(QStringLiteral("serverPortLabel"));

        connectionLayout->addWidget(serverPortLabel, 2, 0, 1, 1);

        playerNameEdit = new QLineEdit(verticalLayoutWidget);
        playerNameEdit->setObjectName(QStringLiteral("playerNameEdit"));

        connectionLayout->addWidget(playerNameEdit, 0, 1, 1, 1);


        menuLayout->addLayout(connectionLayout);

        connectButton = new QPushButton(verticalLayoutWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));

        menuLayout->addWidget(connectButton);

        connectionSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        menuLayout->addItem(connectionSpacer);

        helpButton = new QPushButton(verticalLayoutWidget);
        helpButton->setObjectName(QStringLiteral("helpButton"));

        menuLayout->addWidget(helpButton);

        exitButton = new QPushButton(verticalLayoutWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));

        menuLayout->addWidget(exitButton);

        stackedWidget->addWidget(menu);
        game = new QWidget();
        game->setObjectName(QStringLiteral("game"));
        horizontalLayoutWidget = new QWidget(game);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 1131, 731));
        gameLayout = new QHBoxLayout(horizontalLayoutWidget);
        gameLayout->setObjectName(QStringLiteral("gameLayout"));
        gameLayout->setContentsMargins(0, 0, 0, 60);
        canvasBack = new QWidget(horizontalLayoutWidget);
        canvasBack->setObjectName(QStringLiteral("canvasBack"));
        canvasBack->setMinimumSize(QSize(930, 670));
        canvasBack->setMaximumSize(QSize(930, 670));
        canvasBack->setFocusPolicy(Qt::StrongFocus);

        gameLayout->addWidget(canvasBack);

        gameInfo = new QVBoxLayout();
        gameInfo->setObjectName(QStringLiteral("gameInfo"));
        gameInfo->setContentsMargins(5, 10, 5, 10);
        title = new QLabel(horizontalLayoutWidget);
        title->setObjectName(QStringLiteral("title"));
        title->setAlignment(Qt::AlignCenter);

        gameInfo->addWidget(title);

        titlePlayerSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gameInfo->addItem(titlePlayerSpacer);

        playerName = new QLabel(horizontalLayoutWidget);
        playerName->setObjectName(QStringLiteral("playerName"));
        playerName->setAlignment(Qt::AlignCenter);

        gameInfo->addWidget(playerName);

        playerBarsSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gameInfo->addItem(playerBarsSpacer);

        healthLabel = new QLabel(horizontalLayoutWidget);
        healthLabel->setObjectName(QStringLiteral("healthLabel"));
        healthLabel->setAlignment(Qt::AlignCenter);

        gameInfo->addWidget(healthLabel);

        healthBar = new QProgressBar(horizontalLayoutWidget);
        healthBar->setObjectName(QStringLiteral("healthBar"));
        healthBar->setAlignment(Qt::AlignCenter);

        gameInfo->addWidget(healthBar);

        betweenBarsSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gameInfo->addItem(betweenBarsSpacer);

        powerLabel = new QLabel(horizontalLayoutWidget);
        powerLabel->setObjectName(QStringLiteral("powerLabel"));
        powerLabel->setAlignment(Qt::AlignCenter);

        gameInfo->addWidget(powerLabel);

        powerBar = new QProgressBar(horizontalLayoutWidget);
        powerBar->setObjectName(QStringLiteral("powerBar"));
        powerBar->setAlignment(Qt::AlignCenter);

        gameInfo->addWidget(powerBar);

        powerTopSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gameInfo->addItem(powerTopSpacer);

        pointsLabel = new QLabel(horizontalLayoutWidget);
        pointsLabel->setObjectName(QStringLiteral("pointsLabel"));
        pointsLabel->setAlignment(Qt::AlignCenter);

        gameInfo->addWidget(pointsLabel);

        pointsTimeSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gameInfo->addItem(pointsTimeSpacer);

        timeLabel = new QLabel(horizontalLayoutWidget);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));
        timeLabel->setAlignment(Qt::AlignCenter);

        gameInfo->addWidget(timeLabel);

        timeTopSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gameInfo->addItem(timeTopSpacer);

        topLabel = new QLabel(horizontalLayoutWidget);
        topLabel->setObjectName(QStringLiteral("topLabel"));
        topLabel->setAlignment(Qt::AlignCenter);

        gameInfo->addWidget(topLabel);

        top = new QTableWidget(horizontalLayoutWidget);
        if (top->columnCount() < 2)
            top->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        top->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        top->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (top->rowCount() < 8)
            top->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        top->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        top->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        top->setVerticalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        top->setVerticalHeaderItem(3, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        top->setVerticalHeaderItem(4, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        top->setVerticalHeaderItem(5, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        top->setVerticalHeaderItem(6, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        top->setVerticalHeaderItem(7, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        top->setItem(0, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        top->setItem(0, 1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        top->setItem(1, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        top->setItem(1, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        top->setItem(2, 0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        top->setItem(2, 1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        top->setItem(3, 0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        top->setItem(3, 1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        top->setItem(4, 0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        top->setItem(4, 1, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        top->setItem(5, 0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        top->setItem(5, 1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        top->setItem(6, 0, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        top->setItem(6, 1, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        top->setItem(7, 0, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        top->setItem(7, 1, __qtablewidgetitem25);
        top->setObjectName(QStringLiteral("top"));
        top->setMinimumSize(QSize(0, 189));
        top->setFrameShape(QFrame::NoFrame);
        top->setEditTriggers(QAbstractItemView::NoEditTriggers);
        top->setSelectionMode(QAbstractItemView::NoSelection);
        top->setCornerButtonEnabled(false);
        top->horizontalHeader()->setDefaultSectionSize(90);
        top->horizontalHeader()->setStretchLastSection(true);
        top->verticalHeader()->setDefaultSectionSize(21);

        gameInfo->addWidget(top);

        exitGameSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gameInfo->addItem(exitGameSpacer);

        exitGameButton = new QPushButton(horizontalLayoutWidget);
        exitGameButton->setObjectName(QStringLiteral("exitGameButton"));

        gameInfo->addWidget(exitGameButton);


        gameLayout->addLayout(gameInfo);

        stackedWidget->addWidget(game);
        MainWindow->setCentralWidget(stackedWidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        statusbar->setSizeGripEnabled(false);
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1134, 25));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Fight in square", 0));
        playerNameLabel->setText(QApplication::translate("MainWindow", "Nazwa gracza", 0));
        serverIpLabel->setText(QApplication::translate("MainWindow", "Adres IP serwera", 0));
        serverPortEdit->setText(QApplication::translate("MainWindow", "8001", 0));
        serverIpEdit->setText(QApplication::translate("MainWindow", "92.222.1.215", 0));
        serverPortLabel->setText(QApplication::translate("MainWindow", "Port serwera", 0));
        playerNameEdit->setText(QApplication::translate("MainWindow", "Tester", 0));
        connectButton->setText(QApplication::translate("MainWindow", "Po\305\202\304\205cz", 0));
        helpButton->setText(QApplication::translate("MainWindow", "Pomoc", 0));
        exitButton->setText(QApplication::translate("MainWindow", "Wyjd\305\272", 0));
        title->setText(QApplication::translate("MainWindow", "Fight\n"
"in\n"
"square", 0));
        playerName->setText(QApplication::translate("MainWindow", "Nazwa gracza", 0));
        healthLabel->setText(QApplication::translate("MainWindow", "\305\273ycie", 0));
        powerLabel->setText(QApplication::translate("MainWindow", "Moc wystrza\305\202\303\263w", 0));
        pointsLabel->setText(QApplication::translate("MainWindow", "Punkty: 212", 0));
        timeLabel->setText(QApplication::translate("MainWindow", "Czas: 23:45", 0));
        topLabel->setText(QApplication::translate("MainWindow", "TOP", 0));
        QTableWidgetItem *___qtablewidgetitem = top->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Gracz", 0));
        QTableWidgetItem *___qtablewidgetitem1 = top->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Punkty", 0));
        QTableWidgetItem *___qtablewidgetitem2 = top->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "1", 0));
        QTableWidgetItem *___qtablewidgetitem3 = top->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "2", 0));
        QTableWidgetItem *___qtablewidgetitem4 = top->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "3", 0));
        QTableWidgetItem *___qtablewidgetitem5 = top->verticalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "4", 0));
        QTableWidgetItem *___qtablewidgetitem6 = top->verticalHeaderItem(4);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "5", 0));
        QTableWidgetItem *___qtablewidgetitem7 = top->verticalHeaderItem(5);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "6", 0));
        QTableWidgetItem *___qtablewidgetitem8 = top->verticalHeaderItem(6);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "7", 0));
        QTableWidgetItem *___qtablewidgetitem9 = top->verticalHeaderItem(7);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "8", 0));

        const bool __sortingEnabled = top->isSortingEnabled();
        top->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem10 = top->item(0, 0);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem11 = top->item(0, 1);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem12 = top->item(1, 0);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem13 = top->item(1, 1);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem14 = top->item(2, 0);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem15 = top->item(2, 1);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem16 = top->item(3, 0);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem17 = top->item(3, 1);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem18 = top->item(4, 0);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem19 = top->item(4, 1);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem20 = top->item(5, 0);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem21 = top->item(5, 1);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem22 = top->item(6, 0);
        ___qtablewidgetitem22->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem23 = top->item(6, 1);
        ___qtablewidgetitem23->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem24 = top->item(7, 0);
        ___qtablewidgetitem24->setText(QApplication::translate("MainWindow", "---", 0));
        QTableWidgetItem *___qtablewidgetitem25 = top->item(7, 1);
        ___qtablewidgetitem25->setText(QApplication::translate("MainWindow", "---", 0));
        top->setSortingEnabled(__sortingEnabled);

        exitGameButton->setText(QApplication::translate("MainWindow", "Roz\305\202\304\205cz z serwerem", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
