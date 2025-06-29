#include "CanExitLevelEvent.h"

CanExitLevelEvent::CanExitLevelEvent(int levelid) : GenericEvent(LEVEL_EXIT_POSSIBLE), levelId(levelid) {}

void CanExitLevelEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);
	jsonEvent["levelId"] = new JSONValue(levelId);
}

void CanExitLevelEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  levelId: " + std::to_string(levelId) + "\n";
	endResult += "\n";
}