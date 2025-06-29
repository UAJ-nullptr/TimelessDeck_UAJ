#include "JSONSerializer.h"
#include <memory>
#include <vector>

JSONSerializer::JSONSerializer() : first(true)
{

}

JSONSerializer::~JSONSerializer()
{

}

std::string JSONSerializer::startSerializing()
{
	return "[\n";
}

std::string JSONSerializer::serialize(EventQueue* event)
{
	string myFileText = "";

	while (event->size() > 0)
	{
		if (!first) myFileText += ",\n";
		else first = false;

		myFileText += "\t";

		JSONObject jEvent;
		event->front()->serializeToJSON(jEvent);

		std::unique_ptr<JSONValue> fileJSON(new JSONValue(jEvent));

		myFileText += JSON::Stringify(&*fileJSON);

		delete event->front();
		event->deQueue();
	}

	return myFileText;
}

std::string JSONSerializer::finishSerializing()
{
	return "]\n";
}

std::string JSONSerializer::getExtension()
{
	return ".json";
}
