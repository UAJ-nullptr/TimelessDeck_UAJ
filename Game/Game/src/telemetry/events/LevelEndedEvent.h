#pragma once
#include "GenericEvent.h"

class LevelEndedEvent : public GenericEvent
{
private:
	int levelId;
	bool win;

public:
	LevelEndedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int levelid, bool victory);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};