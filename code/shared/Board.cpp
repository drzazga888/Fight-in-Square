#include "Board.h"
#include <iostream>

Board::Board(QWidget* parent)
: QWidget(parent)
{
    board = new QPainter();
    players.resize(MAX_PLAYERS);
    setFixedSize(1020,720);
	hidden = false;
	plCounter=0;
}

Board::~Board()
{
	delete board;
	plCounter=0;
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

Frame::ErrorCode::Code Board::addPlayer(int id, Player* p)
{
	if(plCounter<MAX_PLAYERS)
	{
		if(id>=MAX_PLAYERS)
			players.resize(players.size()+MAX_PLAYERS);
		players.insert(id-1,p);
		++plCounter;
		std::cout<<"insert:"<<id<<std::endl;
		return Frame::ErrorCode::Undefined;
	}
	else
		return Frame::ErrorCode::MaxPlayers;
}

Player* Board::removePlayer(int id)
{
	if(id<players.size())
	{
		Player *p = players[id-1];
		players.remove(id-1);
		--plCounter;std::cout<<"remove:"<<id<<std::endl;
		return p;
	}
	else
		return NULL;
}
