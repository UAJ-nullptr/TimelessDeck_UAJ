#include "YALMSerializer.h"

YALMSerializer::YALMSerializer()
{

}

YALMSerializer::~YALMSerializer()
{

}

std::string YALMSerializer::serialize(std::queue<GenericEvent*>* event)
{
	std::string serialized = "";

	while (event->size() > 0)
	{
		event->front()->serializeToYALM(serialized);
		delete event->front();
		event->pop();
	}

	return serialized;
}