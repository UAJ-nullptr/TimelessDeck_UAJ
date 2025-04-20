#include "ISerializer.h"
#include <memory>

ISerializer::ISerializer()
{
	
}

ISerializer::~ISerializer()
{

}

std::string ISerializer::serialize(GenericEvent event)
{    
	JSONObject jEvent;
	event.serializeToJSON(jEvent);
	std::unique_ptr<JSONValue> fileJSON(new JSONValue(jEvent));

	return JSON::Stringify(&*fileJSON);
}
