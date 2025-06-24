#pragma once
#include "GenericEvent.h"

class InsufficientManaEvent : public GenericEvent
{
private:
	int manaStatus;
	int manaCost;

public:
	InsufficientManaEvent(int currentMana, int abilityCost);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};