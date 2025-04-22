#include "JSONSerializer.h"
#include <memory>

JSONSerializer::JSONSerializer()
{

}

JSONSerializer::~JSONSerializer()
{

}

std::string JSONSerializer::serialize(GenericEvent* event)
{
	JSONObject jEvent;

	event->serializeToJSON(jEvent);

	std::unique_ptr<JSONValue> fileJSON(new JSONValue(jEvent));

	return JSON::Stringify(&*fileJSON);
}
