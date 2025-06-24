#pragma once
#include "GenericEvent.h"

class ChangedCardDeckToHandEvent : public GenericEvent
{
private:

public:
	ChangedCardDeckToHandEvent();

	virtual void serializeToYAML(std::string& endResult);
};