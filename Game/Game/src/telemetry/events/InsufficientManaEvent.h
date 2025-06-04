#pragma once
#include "GenericEvent.h"

class InsufficientManaEvent : public GenericEvent
{
private:
	int manaStatus;
	int manaCost;

public:
	InsufficientManaEvent(int evntId, long long timeStmp, string appName, string appVrs,
		long sessionID, int currentMana, int abilityCost);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};