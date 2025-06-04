#pragma once
#include "GenericEvent.h"

class SessionEndedEvent : public GenericEvent
{
private:

public:
	SessionEndedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID);

	virtual void serializeToYAML(std::string& endResult);
};