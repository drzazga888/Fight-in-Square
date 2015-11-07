#include "Client.h"

Client::Client()
{
	game = new Game(this);
	errorDialog = NULL;
	setWindowTitle("Fight In Square");

	host = new QLineEdit(this);
	port = new QLineEdit(this);
	connectButton = new QPushButton("Połącz",this);
	disconnectButton = new QPushButton("Rozłącz",this);
	disconnectButton->hide();

	status = new QLabel("Niepołączony");
	status->setFrameStyle( QFrame:: Panel | QFrame::Sunken );
	statusBar()->addWidget( status, 1);

	QLabel *hostLabel = new QLabel("Adres IP serwera");
	hostLabel->setFixedWidth(100);
	QLabel *portLabel = new QLabel("Port");
	portLabel->setFixedWidth(100);
	QHBoxLayout *hLayout = new QHBoxLayout();
	hLayout->addWidget(hostLabel);
	hLayout->addWidget(host);
	QHBoxLayout *pLayout = new QHBoxLayout();
	pLayout->addWidget(portLabel);
	pLayout->addWidget(port);
	QHBoxLayout *bLayout = new QHBoxLayout();
	bLayout->addWidget(connectButton);
	bLayout->addWidget(disconnectButton);
	QWidget *hWidget = new QWidget();
	hWidget->setLayout(hLayout);
	QWidget *pWidget = new QWidget();
	pWidget->setLayout(pLayout);
	QWidget *bWidget = new QWidget();
	bWidget->setLayout(bLayout);

	QVBoxLayout *connectLayout= new QVBoxLayout();
	connectLayout->addStretch(1);
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
	if(game->getClient()->connectToHost(address, port->text().toInt()))
	{
		connectButton->hide();
		disconnectButton->show();
		host->setDisabled(true);
		port->setDisabled(true);
		status->setText("Połączono");
	}
	else
	{
		if(errorDialog!=NULL)
			delete errorDialog;
		errorDialog = new ErrorDialog("Nie udało się połączyć z serwerem", "Błąd połączenia");
		errorDialog->show();
		return;
	}
}

void Client::disonnectFromServer()
{
	if(game->getClient()->disconnectFromHost())
	{
		disconnectButton->hide();
		connectButton->show();
		host->setDisabled(false);
		port->setDisabled(false);
		status->setText("Niepołączony");
	}
	else
	{
		if(errorDialog!=NULL)
			delete errorDialog;
		errorDialog = new ErrorDialog("Nie udało się rozłączyć z serwerem", "Błąd połączenia");
		errorDialog->show();
		return;
	}
}

void Client::handleResults(QString m)
{

}

void Client::closeEvent(QCloseEvent *event)
{
	game->close();game->quit();unisleep(500);
}
