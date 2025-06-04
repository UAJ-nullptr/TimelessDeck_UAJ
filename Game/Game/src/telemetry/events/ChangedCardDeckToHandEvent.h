#pragma once
#include "GenericEvent.h"

class ChangedCardDeckToHandEvent : public GenericEvent
{
private:

public:
	ChangedCardDeckToHandEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID);

	virtual void serializeToYAML(std::string& endResult);
};