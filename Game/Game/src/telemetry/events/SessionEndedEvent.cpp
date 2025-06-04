#include "SessionEndedEvent.h"

SessionEndedEvent::SessionEndedEvent(int evntId, long long timeStmp, string appName, string appVrs,
	long sessionID) : GenericEvent(evntId, timeStmp, END_SESSION, appName, appVrs, sessionID) { }


void SessionEndedEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "\n";
}