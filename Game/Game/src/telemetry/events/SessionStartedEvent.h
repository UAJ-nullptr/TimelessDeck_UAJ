#pragma once
#include "GenericEvent.h"

class SessionStartedEvent : public GenericEvent
{
private:

public:
	SessionStartedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID);

	virtual void serializeToYAML(std::string& endResult);
};