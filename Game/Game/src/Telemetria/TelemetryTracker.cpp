#include "TelemetryTracker.h"

TelemetryTracker::TelemetryTracker()
{

}

TelemetryTracker::~TelemetryTracker()
{

}

void TelemetryTracker::addEvent(Event event)
{
	events.push(event);
}

Event TelemetryTracker::getOldestEvent()
{
	Event oldestEvent = events.front();
	events.pop();
	return oldestEvent;
}


