#pragma once
#include "GenericEvent.h"

class ChangedCardPlayingEvent : public GenericEvent
{
private:
	int levelId;

public:
	ChangedCardPlayingEvent(int levelid);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};