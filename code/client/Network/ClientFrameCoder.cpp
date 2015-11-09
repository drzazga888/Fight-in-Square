#include "ClientFrameCoder.h"
#include <string.h>

ClientFrameCoder::ClientFrameCoder()
{
	clientId = 0;
}

QByteArray ClientFrameCoder::encodeConnect(char* name)
{
	QByteArray frame;
	char length = strlen(name);
	frame.append((char)1);//typ ramki
	frame.append((char)clientId);//id gracza
	frame.append((char)length);//rozmiar pola nazwy
	for(char i=0;i<length;++i)
		frame.append(name[(int)i]);//nazwa użytkownika
	return frame;
}

QByteArray ClientFrameCoder::encodeDisconnect()
{
	QByteArray frame;
	frame.append((char)3);//type ramki
	frame.append((char)clientId);//id gracza
	frame.append((char)0);//kod błędu
	clientId = 0;
	return frame;
}

QByteArray ClientFrameCoder::encodeAction(BoardElement::Direction::DirectionType dir, bool shot)
{
	QByteArray frame;
	if(clientId>0)
	{
		frame.append((char)2);
		frame.append((char)clientId);
		frame.append((char)dir);
		frame.append((char)shot);
	}
	return frame;
}

Frame* ClientFrameCoder::decodeMessage(QByteArray frame)
{
	Frame* objframe;
	if((int)frame[0]==1&&clientId!=frame[1])
		clientId=frame[0];
	if((int)frame[0]==1)//odpowiedź na połączenie
	{
		objframe = new ActionFrame(clientId, Frame::ActionType::Connect);
	}
	else if((int)frame[0]==3)//odpowiedź na rozłączenie
	{
		objframe = new ActionFrame(clientId, Frame::ActionType::Disconnect);
	}
	else if((int)frame[0]==2)//przysłanie planszy
	{
		objframe = new BoardFrame();
	}
	else//inna ramka
	{
		objframe = new OtherFrame();
	}
	return objframe;
}