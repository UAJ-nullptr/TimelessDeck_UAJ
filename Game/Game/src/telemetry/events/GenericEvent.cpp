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
