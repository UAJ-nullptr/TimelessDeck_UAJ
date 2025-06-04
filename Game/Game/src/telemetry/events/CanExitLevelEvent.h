#pragma once
#include "GenericEvent.h"

class CanExitLevelEvent : public GenericEvent
{
private:
	int levelId;

public:
	CanExitLevelEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID,
		int levelid);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};