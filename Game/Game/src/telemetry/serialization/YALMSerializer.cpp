#include "YALMSerializer.h"

YALMSerializer::YALMSerializer()
{

}

YALMSerializer::~YALMSerializer()
{

}

std::string YALMSerializer::serialize(GenericEvent* event)
{
	std::string serialized = "";

	event->serializeToYALM(serialized);

	return serialized;
}