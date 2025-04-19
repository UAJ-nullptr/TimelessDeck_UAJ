#include "TelemetryTracker.h"

TelemetryTracker::TelemetryTracker()
{

}

TelemetryTracker::~TelemetryTracker()
{

}

void TelemetryTracker::addEvent(GenericEvent event)
{
	events.push(event);
}

GenericEvent TelemetryTracker::getOldestEvent()
{
	GenericEvent oldestEvent = events.front();
	events.pop();
	return oldestEvent;
}


