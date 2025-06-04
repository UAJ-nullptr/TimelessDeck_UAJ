#pragma once
#include "GenericEvent.h"

class ExitFailedEvent : public GenericEvent
{
private:
	int levelId;

public:
	ExitFailedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int levelid);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};