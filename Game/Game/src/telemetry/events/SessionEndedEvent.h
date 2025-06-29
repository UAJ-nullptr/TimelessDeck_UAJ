#pragma once
#include "GenericEvent.h"

class SessionEndedEvent : public GenericEvent
{
private:

public:
	SessionEndedEvent();

	virtual void serializeToYAML(std::string& endResult);
};