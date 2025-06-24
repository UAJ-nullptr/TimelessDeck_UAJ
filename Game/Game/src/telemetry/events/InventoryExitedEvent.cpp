#include "InventoryExitedEvent.h"

InventoryExitedEvent::InventoryExitedEvent(vector<CardId> card) :
	GenericEvent(INVENTORY_LEFT), currentDeck(card) { }

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