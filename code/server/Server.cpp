#include "Server.h"

Server::Server()
{
	game = new Game(this);

	errorDialog = NULL;
	setWindowTitle("Fight In Square - server");

    port = new QLineEdit();
    logs = new QTextEdit();
	logs->setReadOnly(true);
	game->setLogOutput(logs);
    startButton = new QPushButton("Uruchom");
    stopButton = new QPushButton("Zatrzymaj");
	stopButton->hide();

    lay= new QVBoxLayout();
	lay->addWidget(port);
	lay->addWidget(startButton);
	lay->addWidget(stopButton);
	lay->addWidget(logs);

    window = new QWidget();
    window->setLayout(lay);
	setCentralWidget(window);

	status = new QLabel("Zatrzymany");
	status->setFrameStyle( QFrame:: Panel | QFrame::Sunken );
	statusBar()->addWidget( status, 1);

	connect(startButton, SIGNAL(clicked()), this, SLOT(startServer()));
	connect(stopButton, SIGNAL(clicked()), this, SLOT(stopServer()));

	QRect screenGeometry = QApplication::desktop()->screenGeometry();
	int x = (screenGeometry.width()-this->width()) / 2;
	int y = (screenGeometry.height()-this->height()) / 2;
	move(x,y);

	connect(game, SIGNAL(resultReady(QString)), this, SLOT(handleResults(QString)));
	connect(game, SIGNAL(finished()), game, SLOT(deleteLater()));
	game->start();
}

Server::~Server()
{
	delete window;
    if(errorDialog!=NULL)
		delete errorDialog;
}

void Server::startServer()
{
	if(port->text()=="" || port->text().toInt()==0)
	{
		if(errorDialog!=NULL)
			delete errorDialog;
		errorDialog = new ErrorDialog("Proszę podać poprawny port", "Błędna konfiguracja");
		errorDialog->show();
		return;
	}
	if(game->getServer()->start(port->text().toInt()))
	{
		startButton->hide();
		stopButton->show();
		port->setDisabled(true);
		status->setText("Uruchomiony");
	}
	else
	{
		if(errorDialog!=NULL)
			delete errorDialog;
		errorDialog = new ErrorDialog("Nie udało się uruchomić serwera na podanym porcie", "Błąd startu");
		errorDialog->show();
		return;
	}
}

void Server::stopServer()
{
	if(game->getServer()->stop())
	{
		stopButton->hide();
		startButton->show();
		port->setDisabled(false);
		status->setText("Zatrzymany");
	}
	else
	{
		if(errorDialog!=NULL)
			delete errorDialog;
		errorDialog = new ErrorDialog("Nie udało się zatrzymać serwera", "Błąd zatrzymania");
		errorDialog->show();
		return;
	}
}

void Server::handleResults(QString m)
{

}

void Server::closeEvent(QCloseEvent *event)
{
	game->close();game->quit();unisleep(500);
}

void Server::read(int id,QByteArray message)
{
	logs->append(QString::fromUtf8(message));
}
