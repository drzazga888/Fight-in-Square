#include "ServerFrameCoder.h"

QByteArray ServerFrameCoder::encodeBoard(Board* board)
{
	QByteArray frame;
	frame.append((char)2);
	return frame;
}

Frame* ServerFrameCoder::decode(QByteArray& frame)
{
	Frame* objframe;
	if((int)frame[0]==1)//connect
	{
		char length = frame[2];
		for(char i=0;i<length;++i)
			buffer[(int)i] = (char)frame[3+(int)i];
		buffer[(int)length]='\0';
		objframe = new ActionFrame(frame[1], buffer);
	}
	else if((int)frame[0]==2)//action
	{
		Shot::Direction::DirectionType dir;
		if((int)frame[2]==Shot::Direction::Up)
			dir = Shot::Direction::Up;
		else if((int)frame[2]==Shot::Direction::Down)
			dir = Shot::Direction::Down;
		else if((int)frame[2]==Shot::Direction::Left)
			dir = Shot::Direction::Left;
		else if((int)frame[2]==Shot::Direction::Right)
			dir = Shot::Direction::Right;
		else
			dir = Shot::Direction::None;
		bool shot = (bool)frame[3];
		objframe = new ActionFrame(frame[1], dir, shot);
	}
	else if((int)frame[0]==3)//disconnect
	{
		objframe = new ActionFrame(frame[1]);
	}
	else//other
	{
		objframe = new OtherFrame();
	}


	return objframe;
}

QByteArray ServerFrameCoder::encodeConnectResp(char id, Frame::ErrorCode::Code errorKey)
{
	QByteArray frame;
	frame.append((char)1);//typ ramki
	frame.append((char)id);//id gracza
	frame.append((char)errorKey);//kod błędu
	return frame;
}

QByteArray ServerFrameCoder::encodeDisconnectResp(char id, Frame::ErrorCode::Code errorKey)
{
	QByteArray frame;
	frame.append((char)3);//typ ramki
	frame.append((char)id);//id gracza
	frame.append((char)errorKey);//kod błędu
	return frame;
}