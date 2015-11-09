#include "Client.h"


Client::Client()
{
	game = new Game(this);
	isConnected = false;
	errorDialog = NULL;
	setWindowTitle("Fight In Square");

	playerName = new QLineEdit("Tom",this);
	host = new QLineEdit("127.0.0.1",this);
	port = new QLineEdit("5432",this);
	connectButton = new QPushButton("Połącz",this);
	disconnectButton = new QPushButton("Rozłącz",this);
	disconnectButton->hide();

	status = new QLabel("Niepołączony");
	status->setFrameStyle( QFrame:: Panel | QFrame::Sunken );
	statusBar()->addWidget( status, 1);

	QLabel *pnLabel = new QLabel("Nazwa gracza");
	pnLabel->setFixedWidth(100);
	QLabel *hostLabel = new QLabel("Adres IP serwera");
	hostLabel->setFixedWidth(100);
	QLabel *portLabel = new QLabel("Port");
	portLabel->setFixedWidth(100);
	QHBoxLayout *pnLayout = new QHBoxLayout();
	pnLayout->addWidget(pnLabel);
	pnLayout->addWidget(playerName);
	QHBoxLayout *hLayout = new QHBoxLayout();
	hLayout->addWidget(hostLabel);
	hLayout->addWidget(host);
	QHBoxLayout *pLayout = new QHBoxLayout();
	pLayout->addWidget(portLabel);
	pLayout->addWidget(port);
	QHBoxLayout *bLayout = new QHBoxLayout();
	bLayout->addWidget(connectButton);
	bLayout->addWidget(disconnectButton);
	QWidget *pnWidget = new QWidget();
	pnWidget->setLayout(pnLayout);
	QWidget *hWidget = new QWidget();
	hWidget->setLayout(hLayout);
	QWidget *pWidget = new QWidget();
	pWidget->setLayout(pLayout);
	QWidget *bWidget = new QWidget();
	bWidget->setLayout(bLayout);

	QVBoxLayout *connectLayout= new QVBoxLayout();
	connectLayout->addStretch(1);
	connectLayout->addWidget(pnWidget);
	connectLayout->addWidget(hWidget);
	connectLayout->addWidget(pWidget);
	connectLayout->addWidget(bWidget);

	QWidget *connectWidget = new QWidget();
	connectWidget->setLayout(connectLayout);

	QHBoxLayout *lay = new QHBoxLayout();
	lay->addWidget(game->getBoard());
	lay->addWidget(connectWidget);
	QWidget *window = new QWidget();
    	window->setLayout(lay);
	setCentralWidget(window);

	connect(connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
	connect(disconnectButton, SIGNAL(clicked()), this, SLOT(disonnectFromServer()));

	setFixedSize(1366,768);

	QRect screenGeometry = QApplication::desktop()->screenGeometry();
	int x = (screenGeometry.width()-this->width()) / 2;
	int y = (screenGeometry.height()-this->height()) / 2;
	move(x,y);

	connect(game->getClient(), SIGNAL(connecting()), this, SLOT(detectConnecting()));
	connect(game->getClient(), SIGNAL(disconnecting()), this, SLOT(detectDisconnecting()));

	connect(game, SIGNAL(resultReady(QString)), this, SLOT(handleResults(QString)));
	connect(game, SIGNAL(finished()), game, SLOT(deleteLater()));
	game->start();
}

Client::~Client()
{
	delete connectButton;
	delete disconnectButton;
	delete status;
	delete host;
	delete port;
	if(errorDialog!=NULL)
		delete errorDialog;
}

void Client::connectToServer()
{
	if(host->text()=="")
	{
		if(errorDialog!=NULL)
			delete errorDialog;
		errorDialog = new ErrorDialog("Proszę podać poprawny adres IP", "Błędne dane serwera");
		return;
	}
	else if(port->text()=="" || port->text().toInt()==0)
	{
		if(errorDialog!=NULL)
			delete errorDialog;
		errorDialog = new ErrorDialog("Proszę podać poprawny port", "Błędne dane serwera");
		errorDialog->show();
		return;
	}
	QHostAddress address(host->text());
	game->setPlayerName(playerName->text());
	game->getClient()->connectToHost(address, port->text().toInt());
}

void Client::disonnectFromServer()
{
	game->disconnect();
}

void Client::handleResults(QString m)
{

}

void Client::closeEvent(QCloseEvent *event)
{
	game->close();game->quit();unisleep(500);
}


void Client::keyPressEvent( QKeyEvent *k )
{
	if(k->type() == QEvent::KeyPress && isConnected)
	{
		if(k->text()=="w")
			game->move(BoardElement::Direction::Up);
		else if(k->text()=="a")
			game->move(BoardElement::Direction::Left);
		else if(k->text()=="s")
			game->move(BoardElement::Direction::Down);
		else if(k->text()=="d")
			game->move(BoardElement::Direction::Right);
		else if(k->key()==Qt::Key_Space)
			game->shot();
	}
}

void Client::detectConnecting()
{
	isConnected = true;
	playerName->setDisabled(true);
	host->setDisabled(true);
	port->setDisabled(true);
	connectButton->hide();
	disconnectButton->show();
	connectButton->clearFocus();
	status->setText("Połączono");
}

void Client::detectDisconnecting()
{
	isConnected = false;
	playerName->setDisabled(false);
	host->setDisabled(false);
	port->setDisabled(false);
	disconnectButton->hide();
	connectButton->show();
	disconnectButton->clearFocus();
	status->setText("Niepołączony");
}
