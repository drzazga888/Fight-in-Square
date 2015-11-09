#include "Board.h"

Board::Board(QWidget* parent)
: QWidget(parent)
{
    board = new QPainter();
    
    setFixedSize(1020,720);
	hidden = false;
}

Board::~Board()
{
	delete board;
}

void Board::paintEvent(QPaintEvent* pe)
{
	if(!hidden)
	{
	    board->begin(this);
	    pusteTlo(pe);
	    board->end();
	}
}

void Board::hide()
{
	hidden = true;
}

void Board::pusteTlo(QPaintEvent* pe)
{
    board->setRenderHint(QPainter::Antialiasing, true);
    board->setBackground(QBrush(Qt::red, Qt::SolidPattern));
    board->setBackgroundMode(Qt::TransparentMode);
    board->setPen(Qt::black);
    board->setCompositionMode (QPainter::CompositionMode_Source);
    board->fillRect(pe->rect(), Qt::red);
    board->setCompositionMode (QPainter::CompositionMode_SourceOver);
}

void Board::addPlayer(int id, Player* p)
{
	players.insert(id-1, p);
}

Player* Board::removePlayer(int id)
{
	Player *p = players[id-1];
	players.remove(id);
	return p;
}