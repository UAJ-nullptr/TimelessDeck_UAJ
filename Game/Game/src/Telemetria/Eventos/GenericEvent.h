#pragma once
#include <string>
#include "../../data/json/JSON.h"

using namespace std;

enum eventType
{
	START_SESSION,
	END_SESSION,
	START_LEVEL,
	END_LEVEL,
	CARD_CHANGED,
	ABILITY_USED,
	PLAYER_HEALED,
	PERIODIC_HEALTH_STATUS,
	MANA_TAKEN,
	NOT_ENOUGHT_MANA,
	LEVEL_EXIT_POSSIBLE,
	LEVEL_LEFT,
	TRIED_LEAVING,
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
	eventType eType;
	string appName;
	string appVersion;
	long sessionId;
public:
	GenericEvent(int evntId, long long timeStmp, eventType evtType, string appName, string appVrs, long sessionID) : eventId(evntId), timeStamp(timeStmp),
		eType(evtType), appName(appName), appVersion(appVrs), sessionId(sessionID)
	{
	};

	virtual void serializeToJSON(JSONObject& jsonEvent);
};

