#ifndef FRAME_H
#define FRAME_H

#include <QObject>

class Frame : public QObject
{
	Q_OBJECT
public:
	enum Type {Action, Board};
protected:
	Type type;
};

#endif