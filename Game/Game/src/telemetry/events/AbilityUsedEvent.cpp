#include "AbilityUsedEvent.h"

AbilityUsedEvent::AbilityUsedEvent(int evntId, long long timeStmp, string appName, string appVrs,
	long sessionID, int levelid) :
	GenericEvent(evntId, timeStmp, ABILITY_USED, appName, appVrs, sessionID), levelId(levelid) { }

void AbilityUsedEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);
	jsonEvent["levelId"] = new JSONValue(levelId);
}

void AbilityUsedEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  levelId: " + std::to_string(levelId) + "\n";
	endResult += "\n";
}