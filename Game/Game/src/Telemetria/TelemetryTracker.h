#pragma once

#include "queue"
#include "../utils/Singleton.h"
#include "Eventos/Events.h"
#include "Persistencia/IPersistence.h"
#include <chrono>


class TelemetryTracker : public Singleton<TelemetryTracker> {
	friend Singleton<TelemetryTracker>;
private:
	
	IPersistence persistence;

	// Serialización
	// Cola en la que se van introduciendo los eventos generados
	std::queue<GenericEvent> events;
	int currentId;
	string appName;
	string appVersion;
	int sessionId;

	TelemetryTracker(string appName, string appVers, int sessionId);

public:
	virtual ~TelemetryTracker();

	void addEvent(GenericEvent event);
	void addSessionStartedEvent();
	void addSessionEndedEvent();
	void addLevelStartedEvent(int levelId);
	void addLevelEndedEvent(int levelId);
	void addChangedCardEvent(int levelId, CardId card);
	void addAbilityUsedEvent(int levelId, CardId card);
	void addPlayerHealedEvent(int heal);
	void addPeriodicHealthStatusEvent(int health);
	void addInsuficientManaEvent(int currentMana, CardId cardAbility, int abilityCost);
	void addManaTakenEvent(int currentMana, int manaTaken);
	void addExitPossibleEvent(int levelId);
	void addTriedExitEvent(int levelId, int currentEter);
	void addChangedToHandEvent(CardId card);
	void addChangedToDeckEvent(CardId card);
	void addInventoryExitedEvent(vector<CardId> deck);
	GenericEvent getOldestEvent();
};

