#include "SessionEndedEvent.h"

SessionEndedEvent::SessionEndedEvent() : GenericEvent(END_SESSION) {}


void SessionEndedEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "\n";
}