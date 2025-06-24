#include "LevelEndedEvent.h"

LevelEndedEvent::LevelEndedEvent(int levelid,bool victory) :
	GenericEvent(END_LEVEL), levelId(levelid), win(victory) { }

void LevelEndedEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);
	jsonEvent["levelId"] = new JSONValue(levelId);
	jsonEvent["win"] = new JSONValue(win);
}

void LevelEndedEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  levelId: " + std::to_string(levelId) + "\n";
	endResult += "  win: " + std::to_string(win) + "\n";
	endResult += "\n";
}