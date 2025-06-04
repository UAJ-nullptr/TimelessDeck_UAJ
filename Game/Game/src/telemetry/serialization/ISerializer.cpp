#include "ISerializer.h"

ISerializer::ISerializer()
{
	
}

ISerializer::~ISerializer()
{

}

std::string ISerializer::startSerializing()
{
	return "";
}

std::string ISerializer::serialize(std::queue<GenericEvent*>* event)
{    
	return "";
}

std::string ISerializer::finishSerializing()
{
	return "";
}
