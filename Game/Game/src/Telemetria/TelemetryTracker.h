#pragma once

#include "queue"
#include "../utils/Singleton.h"
#include "Eventos/GenericEvent.h"
#include "Persistencia/IPersistence.h"


class TelemetryTracker : public Singleton<TelemetryTracker> {
	friend Singleton<TelemetryTracker>;
private:
	
	IPersistence persistence;

	// Serialización
	// Cola en la que se van introduciendo los eventos generados
	std::queue<GenericEvent> events;

	TelemetryTracker();

public:
	virtual ~TelemetryTracker();

	void addEvent(GenericEvent event);
	GenericEvent getOldestEvent();
};

