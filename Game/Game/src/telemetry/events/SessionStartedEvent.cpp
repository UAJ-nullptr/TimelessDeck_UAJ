#include "SessionStartedEvent.h"

SessionStartedEvent::SessionStartedEvent() : GenericEvent(START_SESSION) {}


void SessionStartedEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "\n";
}