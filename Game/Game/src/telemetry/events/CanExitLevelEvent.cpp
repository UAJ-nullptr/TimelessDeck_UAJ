#include "CanExitLevelEvent.h"

CanExitLevelEvent::CanExitLevelEvent(int evntId, long long timeStmp, string appName, string appVrs,
	long sessionID, int levelid) :
	GenericEvent(evntId, timeStmp, LEVEL_EXIT_POSSIBLE, appName, appVrs, sessionID), levelId(levelid) { }

void CanExitLevelEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);
	jsonEvent["levelId"] = new JSONValue(levelId);
}

void CanExitLevelEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  levelId: " + std::to_string(levelId) + "\n";
	endResult += "\n";
}