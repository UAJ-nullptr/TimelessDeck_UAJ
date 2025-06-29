#pragma once
#include "GenericEvent.h"

class LevelStartedEvent : public GenericEvent
{
private:
	int levelId;

public:
	LevelStartedEvent(int levelid);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};