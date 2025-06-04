#include "ExitFailedEvent.h"

ExitFailedEvent::ExitFailedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int levelid) :
	GenericEvent(evntId, timeStmp, LEAVE_FAILED, appName, appVrs, sessionID), levelId(levelid) { }

void ExitFailedEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);
	jsonEvent["levelId"] = new JSONValue(levelId);
}

void ExitFailedEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  levelId: " + std::to_string(levelId) + "\n";
	endResult += "\n";
}