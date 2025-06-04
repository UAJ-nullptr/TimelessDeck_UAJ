#include "InsufficientManaEvent.h"

InsufficientManaEvent::InsufficientManaEvent(int evntId, long long timeStmp, string appName, string appVrs,
	long sessionID, int currentMana, int abilityCost) :
	GenericEvent(evntId, timeStmp, NOT_ENOUGH_MANA, appName, appVrs, sessionID), manaStatus(currentMana), manaCost(abilityCost) { }

void InsufficientManaEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);
	jsonEvent["manaStatus"] = new JSONValue(manaStatus);
	jsonEvent["manaCost"] = new JSONValue(manaCost);
}

void InsufficientManaEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  manaStatus: " + std::to_string(manaStatus) + "\n";
	endResult += "  manaCost: " + std::to_string(manaCost) + "\n";
	endResult += "\n";
}