#pragma once
#include "GenericEvent.h"
#include "../../components/ecs.h"

class InventoryExitedEvent : public GenericEvent
{
private:
	vector<CardId> currentDeck;

public:
	InventoryExitedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID,
		vector<CardId> card);
	~InventoryExitedEvent();

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};