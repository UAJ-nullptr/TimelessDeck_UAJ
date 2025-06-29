#include "ExitFailedEvent.h"

ExitFailedEvent::ExitFailedEvent(int levelid) : GenericEvent(LEAVE_FAILED), levelId(levelid) {}

void ExitFailedEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);
	jsonEvent["levelId"] = new JSONValue(levelId);
}

void ExitFailedEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  levelId: " + std::to_string(levelId) + "\n";
	endResult += "\n";
}