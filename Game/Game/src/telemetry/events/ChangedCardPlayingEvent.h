#pragma once
#include "GenericEvent.h"

class ChangedCardPlayingEvent : public GenericEvent
{
private:
	int levelId;

public:
	ChangedCardPlayingEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int levelid);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};