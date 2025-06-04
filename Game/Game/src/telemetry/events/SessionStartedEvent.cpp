#include "SessionStartedEvent.h"

SessionStartedEvent::SessionStartedEvent(int evntId, long long timeStmp, string appName, string appVrs,
	long sessionID) : GenericEvent(evntId, timeStmp, START_SESSION, appName, appVrs, sessionID) { }


void SessionStartedEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "\n";
}