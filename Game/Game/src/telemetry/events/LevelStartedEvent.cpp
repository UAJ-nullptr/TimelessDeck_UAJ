#include "LevelStartedEvent.h"

LevelStartedEvent::LevelStartedEvent(int levelid) :
	GenericEvent(START_LEVEL), levelId(levelid) {}

void LevelStartedEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);
	jsonEvent["levelId"] = new JSONValue(levelId);
}

void LevelStartedEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  levelId: " + std::to_string(levelId) + "\n";
	endResult += "\n";
}