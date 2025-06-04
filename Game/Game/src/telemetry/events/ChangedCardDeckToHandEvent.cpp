#include "ChangedCardDeckToHandEvent.h"

ChangedCardDeckToHandEvent::ChangedCardDeckToHandEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID) :
	GenericEvent(evntId, timeStmp, MOVED_TO_HAND, appName, appVrs, sessionID) { }

void ChangedCardDeckToHandEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "\n";
}