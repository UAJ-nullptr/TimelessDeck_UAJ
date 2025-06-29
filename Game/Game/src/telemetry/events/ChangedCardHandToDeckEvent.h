#pragma once
#include "GenericEvent.h"

class ChangedCardHandToDeckEvent : public GenericEvent
{
private:

public:
	ChangedCardHandToDeckEvent();

	virtual void serializeToYAML(std::string& endResult);
};