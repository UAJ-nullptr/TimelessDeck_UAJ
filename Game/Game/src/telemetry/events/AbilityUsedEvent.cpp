#include "AbilityUsedEvent.h"

AbilityUsedEvent::AbilityUsedEvent(int levelid) : GenericEvent(ABILITY_USED), levelId(levelid) {}

void AbilityUsedEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);
	jsonEvent["levelId"] = new JSONValue(levelId);
}

void AbilityUsedEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  levelId: " + std::to_string(levelId) + "\n";
	endResult += "\n";
}