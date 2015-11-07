#include "ErrorDialog.h"

ErrorDialog::ErrorDialog(QString& msg, QWidget* parent)
: QDialog(parent)
{
	QString tmpTitle = QString("Błąd");
	initialize(msg, tmpTitle);
}

ErrorDialog::ErrorDialog(const char* msg, QWidget* parent)
: QDialog(parent)
{
	QString tmp = QString(msg);
	QString tmpTitle = QString("Błąd");
	initialize(tmp, tmpTitle);
}

ErrorDialog::ErrorDialog(QString& msg, QString& title, QWidget* parent)
: QDialog(parent)
{
	initialize(msg, title);
}

ErrorDialog::ErrorDialog(const char* msg, const char* title, QWidget* parent)
: QDialog(parent)
{
	QString tmpMsg = QString(msg);
	QString tmpTitle = QString(title);
	initialize(tmpMsg, tmpTitle);
}

void ErrorDialog::initialize(QString& msg, QString& title)
{
	message = new QLabel(msg);
	close = new QPushButton(tr("Zamknij"));
	connect(close, SIGNAL(clicked()), this, SLOT(close()));

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(message);
	layout->addStretch();
	layout->addWidget(close);
	setLayout(layout);
	setModal(true);
	setWindowTitle(title);
	show();
}