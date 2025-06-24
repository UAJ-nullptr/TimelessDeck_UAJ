#pragma once

#include "../utils/Singleton.h"
#include "events/GenericEvent.h"
#include "persistence/IPersistence.h"
#include <chrono>


class TelemetryTracker : public Singleton<TelemetryTracker> {
	friend Singleton<TelemetryTracker>;
private:
	IPersistence* persistence;
	
	int currentId;
	string appName;
	string appVersion;
	int sessionId;

	double elapsedTime;
	double timeLimit;

	TelemetryTracker();
	TelemetryTracker(string appName, string appVers, double timeLimit);

	long long getEpocTimestamp();

public:
	virtual ~TelemetryTracker();

	void update(double deltaTime);
	void flush();

	void addEvent(GenericEvent* event);
};

