#pragma once
#include <string>
#include "../../data/json/JSON.h"

using namespace std;

enum EventType
{
	START_SESSION,
	END_SESSION,
	START_LEVEL,
	END_LEVEL,
	CARD_CHANGED,
	ABILITY_USED,
	PLAYER_HEALED,
	MANA_TAKEN,
	NOT_ENOUGH_MANA,
	LEVEL_EXIT_POSSIBLE,
	LEAVE_FAILED,
	MOVED_FROM_HAND,
	MOVED_TO_HAND,
	INVENTORY_LEFT
};

class GenericEvent
{
	friend class ISerializer;
protected:
	int eventId;
	long long timeStamp;
	EventType eType;
	string appName;
	string appVersion;
	long sessionId;
public:
	GenericEvent(EventType evtType) :
		eType(evtType)
	{};
	virtual void setEventId(int id);
	virtual void setEventTimeStamp(long long tmstmp);
	virtual void setEventAppName(string name);
	virtual void setEventAppVersion(string version);
	virtual void setEventSessionId(long sssnId);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToCSV(std::string& endResult);
	virtual void serializeToYAML(std::string& endResult);
};

