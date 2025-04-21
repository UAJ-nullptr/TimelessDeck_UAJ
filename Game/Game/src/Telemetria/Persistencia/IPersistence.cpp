#include "IPersistence.h"
#include "../Serialización/JSONSerializer.h"

IPersistence::IPersistence(SerializerType serType) : serType(serType)
{
	switch (serType)
	{
	case JSON_SER:
		serializer = new JSONSerializer();
		break;
	case CSV_SER:
		break;
	default:
		serializer = new JSONSerializer();
		break;
	}
}

IPersistence::~IPersistence()
{
	delete serializer;
}

void IPersistence::send(GenericEvent* event)
{
	events.push(event);
}

void IPersistence::flush()
{

}
