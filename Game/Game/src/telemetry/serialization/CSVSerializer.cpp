#include "CSVSerializer.h"
#include <memory>

CSVSerializer::CSVSerializer()
{

}

CSVSerializer::~CSVSerializer()
{

}

std::string CSVSerializer::serialize(GenericEvent* event)
{
	std::string serialized = "";

	event->serializeToCSV(serialized);

	return serialized;
}