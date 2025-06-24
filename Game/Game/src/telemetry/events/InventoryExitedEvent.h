#pragma once
#include "GenericEvent.h"
#include "../../components/ecs.h"

class InventoryExitedEvent : public GenericEvent
{
private:
	vector<CardId> currentDeck;

public:
	InventoryExitedEvent(vector<CardId> card);
	virtual ~InventoryExitedEvent();

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};