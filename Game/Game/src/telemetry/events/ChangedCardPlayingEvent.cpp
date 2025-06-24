#include "ChangedCardPlayingEvent.h"

ChangedCardPlayingEvent::ChangedCardPlayingEvent(int levelid) :
	GenericEvent(CARD_CHANGED), levelId(levelid) { }

void ChangedCardPlayingEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);
	jsonEvent["levelId"] = new JSONValue(levelId);
}

void ChangedCardPlayingEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  levelId: " + std::to_string(levelId) + "\n";
	endResult += "\n";
}