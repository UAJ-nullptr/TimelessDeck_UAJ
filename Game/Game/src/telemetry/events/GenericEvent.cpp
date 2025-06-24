#include "GenericEvent.h"

GenericEvent::GenericEvent(EventType evtType) : eventId(-1), timeStamp(-1), eType(evtType), appName("null"),
	appVersion("null"), sessionId(-1) {}

void GenericEvent::setEventId(int id)
{
	eventId = id;
}

void GenericEvent::setEventTimeStamp(long long tmstmp)
{
	timeStamp = tmstmp;
}

void GenericEvent::setEventAppName(string name)
{
	appName = name;
}

void GenericEvent::setEventAppVersion(string version)
{
	appVersion = version;
}

void GenericEvent::setEventSessionId(long sssnId)
{
	sessionId = sssnId;
}

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

void GenericEvent::serializeToYAML(std::string& endResult)
{
	endResult += std::to_string(eventId) + ":\n";
	endResult += "  timeStamp: " + std::to_string(timeStamp) + "\n";
	endResult += "  eType: " + std::to_string(eType) + "\n";
	endResult += "  appName: " + appName + "\n";
	endResult += "  appVersion: " + appVersion + "\n";
	endResult += "  sessionId: " + std::to_string(sessionId) + "\n";
}
