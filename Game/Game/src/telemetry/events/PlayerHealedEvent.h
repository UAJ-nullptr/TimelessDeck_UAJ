#pragma once
#include "GenericEvent.h"

class PlayerHealedEvent : public GenericEvent
{
private:
	int lifeAfterHeal;
	int attemptedHeal;
	int lifeBeforeHeal;

public:
	PlayerHealedEvent(int heal, int attempt,
		int life);

	virtual void serializeToJSON(JSONObject& jsonEvent);
	virtual void serializeToYAML(std::string& endResult);
};