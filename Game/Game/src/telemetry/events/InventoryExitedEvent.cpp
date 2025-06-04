#include "InventoryExitedEvent.h"

InventoryExitedEvent::InventoryExitedEvent(int evntId, long long timeStmp, string appName, string appVrs,
	long sessionID, vector<CardId> card) :
	GenericEvent(evntId, timeStmp, INVENTORY_LEFT, appName, appVrs, sessionID), currentDeck(card) { }

InventoryExitedEvent::~InventoryExitedEvent()
{
	currentDeck.clear();
}

void InventoryExitedEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);

	vector<int> aux;
	for (int i : currentDeck) {
		aux.push_back(i);
	}

	jsonEvent["currentDeck"] = new JSONValue(aux);
}

void InventoryExitedEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  currentDeck:\n";
	for (int i : currentDeck) {
		endResult += "  - " + std::to_string(i) + "\n";
	}
	endResult += "\n";
}