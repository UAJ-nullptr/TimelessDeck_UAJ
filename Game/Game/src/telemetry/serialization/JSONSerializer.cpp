#include "JSONSerializer.h"
#include <memory>

JSONSerializer::JSONSerializer()
{

}

JSONSerializer::~JSONSerializer()
{

}

std::string JSONSerializer::startSerializing()
{
	return "[\n";
}

std::string JSONSerializer::serialize(std::queue<GenericEvent*>* event)
{
	JSONObject jEvent;
	string myFileText = "";

	while (event->size() > 0) 
	{
		myFileText += "\t";
		event->front()->serializeToJSON(jEvent);

		std::unique_ptr<JSONValue> fileJSON(new JSONValue(jEvent));
		delete event->front();

		myFileText+= JSON::Stringify(&*fileJSON);
		event->pop();
		myFileText += ",\n";
	}
	return myFileText;
}

std::string JSONSerializer::finishSerializing()
{
	return "]\n";
}
