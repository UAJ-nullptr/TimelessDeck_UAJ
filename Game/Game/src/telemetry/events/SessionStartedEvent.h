#pragma once
#include "GenericEvent.h"

class SessionStartedEvent : public GenericEvent
{
private:

public:
	SessionStartedEvent();

	virtual void serializeToYAML(std::string& endResult);
};