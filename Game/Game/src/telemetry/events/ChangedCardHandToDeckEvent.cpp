#include "ChangedCardHandToDeckEvent.h"

ChangedCardHandToDeckEvent::ChangedCardHandToDeckEvent() : GenericEvent(MOVED_FROM_HAND) {}

void ChangedCardHandToDeckEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "\n";
}