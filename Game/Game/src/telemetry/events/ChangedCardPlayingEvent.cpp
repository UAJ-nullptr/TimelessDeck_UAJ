#include "ChangedCardPlayingEvent.h"

ChangedCardPlayingEvent::ChangedCardPlayingEvent(int evntId, long long timeStmp, string appName, string appVrs,
	long sessionID, int levelid) :
	GenericEvent(evntId, timeStmp, CARD_CHANGED, appName, appVrs, sessionID), levelId(levelid) { }

void ChangedCardPlayingEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);
	jsonEvent["levelId"] = new JSONValue(levelId);
}

void ChangedCardPlayingEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  levelId: " + std::to_string(levelId) + "\n";
	endResult += "\n";
}