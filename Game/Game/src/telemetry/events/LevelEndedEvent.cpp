#include "LevelEndedEvent.h"

LevelEndedEvent::LevelEndedEvent(int evntId, long long timeStmp, string appName, string appVrs,
	long sessionID, int levelid,bool victory) :
	GenericEvent(evntId, timeStmp, END_LEVEL, appName, appVrs, sessionID), levelId(levelid), win(victory) { }

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