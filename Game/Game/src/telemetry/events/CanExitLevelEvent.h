#pragma once
#include "GenericEvent.h"

class CanExitLevelEvent : public GenericEvent
{
private:
	int levelId;

public:
	CanExitLevelEvent(int levelid);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};