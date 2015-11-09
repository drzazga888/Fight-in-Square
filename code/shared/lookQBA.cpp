#include "lookQBA.h"

void lookQBA(QByteArray array)
{
	for(int i=0;i<array.length();++i)
		std::cout<<(int)array.at(i)<<',';
	std::cout<<std::endl;
}