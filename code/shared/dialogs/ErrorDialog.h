#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class ErrorDialog : public QDialog
{
	Q_OBJECT
public:
	ErrorDialog(const char* msg, QWidget* parent = NULL);
	ErrorDialog(QString& msg, QWidget* parent = NULL);
	ErrorDialog(const char* msg, const char* title, QWidget* parent = NULL);
	ErrorDialog(QString& msg, QString& title, QWidget* parent = NULL);
private:
	void initialize(QString& msg, QString& title);
	QLabel* message;
	QPushButton *close;
};

#endif
