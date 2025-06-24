#pragma once
#include "GenericEvent.h"

class ExitFailedEvent : public GenericEvent
{
private:
	int levelId;

public:
	ExitFailedEvent(int levelid);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};