#include "ChangedCardHandToDeckEvent.h"

ChangedCardHandToDeckEvent::ChangedCardHandToDeckEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID) :
	GenericEvent(evntId, timeStmp, MOVED_FROM_HAND, appName, appVrs, sessionID) { }

void ChangedCardHandToDeckEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "\n";
}