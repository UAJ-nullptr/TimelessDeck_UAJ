#include "LevelStartedEvent.h"

LevelStartedEvent::LevelStartedEvent(int evntId, long long timeStmp, string appName, string appVrs,
	long sessionID, int levelid) :
	GenericEvent(evntId, timeStmp, START_LEVEL, appName, appVrs, sessionID), levelId(levelid) {}

void LevelStartedEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);
	jsonEvent["levelId"] = new JSONValue(levelId);
}

void LevelStartedEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  levelId: " + std::to_string(levelId) + "\n";
	endResult += "\n";
}