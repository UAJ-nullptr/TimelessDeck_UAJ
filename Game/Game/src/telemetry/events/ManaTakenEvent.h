#pragma once
#include "GenericEvent.h"

class ManaTakenEvent : public GenericEvent
{
private:
	int manaBefore;
	int manaAfter;

public:
	ManaTakenEvent(int evntId, long long timeStmp, string appName, string appVrs,
		long sessionID, int currentMana, int takenMana);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};