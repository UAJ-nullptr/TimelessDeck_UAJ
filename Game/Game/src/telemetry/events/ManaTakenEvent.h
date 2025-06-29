#pragma once
#include "GenericEvent.h"

class ManaTakenEvent : public GenericEvent
{
private:
	int manaBefore;
	int manaAfter;

public:
	ManaTakenEvent(int currentMana, int takenMana);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};