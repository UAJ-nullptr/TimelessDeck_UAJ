#include "YAMLSerializer.h"

YAMLSerializer::YAMLSerializer()
{

}

YAMLSerializer::~YAMLSerializer()
{

}

std::string YAMLSerializer::serialize(EventQueue* event)
{
	std::string serialized = "";

	while (event->size() > 0)
	{
		event->front()->serializeToYAML(serialized);
		delete event->front();
		event->deQueue();
	}

	return serialized;
}