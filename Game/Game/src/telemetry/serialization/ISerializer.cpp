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

std::string ISerializer::serialize(EventQueue* event)
{    
	return "";
}

std::string ISerializer::finishSerializing()
{
	return "";
}

std::string ISerializer::getExtension()
{
	return "";
}