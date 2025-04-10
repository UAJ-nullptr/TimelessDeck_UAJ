#pragma once
#include "queue"

using Event = int;

class TelemetryTracker
{
private:
	// Serialización
	// Cola en la que se van introduciendo los eventos generados
	std::queue<Event> events;
public:
	TelemetryTracker();
	~TelemetryTracker();

	void addEvent(Event event);
	Event getOldestEvent();
};

