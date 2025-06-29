#include "ManaTakenEvent.h"

ManaTakenEvent::ManaTakenEvent(int currentMana, int takenMana) : GenericEvent(MANA_TAKEN),
	manaBefore(currentMana), manaAfter(takenMana) {}

void ManaTakenEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);
	jsonEvent["manaBefore"] = new JSONValue(manaBefore);
	jsonEvent["manaAfter"] = new JSONValue(manaAfter);
}

void ManaTakenEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  manaBefore: " + std::to_string(manaBefore) + "\n";
	endResult += "  manaAfter: " + std::to_string(manaAfter) + "\n";
	endResult += "\n";
}