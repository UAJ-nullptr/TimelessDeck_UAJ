#include "GenericEvent.h"

void GenericEvent::serializeToJSON(JSONObject& jsonEvent)
{
	jsonEvent["eventId"] = new JSONValue(eventId);
	jsonEvent["timeStamp"] = new JSONValue(timeStamp); 
	jsonEvent["eType"] = new JSONValue(eType);
	jsonEvent["appName"] = new JSONValue(appName);
	jsonEvent["appVersion"] = new JSONValue(appVersion);
	jsonEvent["sessionId"] = new JSONValue(sessionId);
}

void GenericEvent::serializeToCSV(std::string& endResult)
{

}

void GenericEvent::serializeToYALM(std::string& endResult)
{
	endResult += std::to_string(eventId) + ":\n";
	endResult += "  timeStamp: " + std::to_string(timeStamp) + "\n";
	endResult += "  eType: " + std::to_string(eType) + "\n";
	endResult += "  appName: " + appName + "\n";
	endResult += "  appVersion: " + appVersion + "\n";
	endResult += "  sessionId: " + std::to_string(sessionId) + "\n";
}
