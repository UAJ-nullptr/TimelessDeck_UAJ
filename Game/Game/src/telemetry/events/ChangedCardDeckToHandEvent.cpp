#include "ChangedCardDeckToHandEvent.h"

ChangedCardDeckToHandEvent::ChangedCardDeckToHandEvent() :
	GenericEvent(MOVED_TO_HAND) { }

void ChangedCardDeckToHandEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "\n";
}