#pragma once
#include "GenericEvent.h"

class ChangedCardHandToDeckEvent : public GenericEvent
{
private:

public:
	ChangedCardHandToDeckEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID);

	virtual void serializeToYAML(std::string& endResult);
};