#pragma once
#include "GenericEvent.h"

class AbilityUsedEvent : public GenericEvent
{
private:
	int levelId;

public:
	AbilityUsedEvent(int levelid);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};