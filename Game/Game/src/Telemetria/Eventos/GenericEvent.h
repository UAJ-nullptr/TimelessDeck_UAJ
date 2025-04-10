#pragma once
#include <string>

using namespace std;

enum eventType
{
	START_SESSION,
	END_SESSION,
	START_LEVEL,
	END_LEVEL,
	CARD_CHANGED,
	ABILITY_USED,
	USEFUL_ABILITY,
	PLAYER_HEALED,
	PERIODIC_HEALTH_STATUS,
	MANA_TAKEN,
	LEVEL_EXIT_POSSIBLE,
	LEVEL_LEFT,
	TRIED_LEAVING,
	CARD_PURCHASED,
	SHOP_LEFT,
	ENTERED_INVENTORY,
	MOVED_FROM_HAND,
	MOVED_TO_HAND,
	INVENTORY_LEFT
};
class GenericEvent
{
private:
	int eventId;
	long long timeStamp;
	eventType eType;
	string appName;
	string appVersion;
	long sessionId;
public:
	GenericEvent(int evntId, long long timeStmp, eventType evtType, string appNme, string appVrs, long sessionID) : eventId(evntId), timeStamp(timeStmp),
		eType(evtType), appName(appNme), appVersion(appVrs), sessionId(sessionID)
	{
	};
};

