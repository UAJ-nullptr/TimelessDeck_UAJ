#pragma once
#include "GenericEvent.h"
#include "../../components/ecs.h"
#include "../../data/CardData.h"
#include <vector>

// Implementado
class SessionStartedEvent: public GenericEvent
{
private:

public:
	SessionStartedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID) :
		GenericEvent(evntId, timeStmp, START_SESSION, appName, appVrs, sessionID) {}
};

// Implementado
class SessionEndedEvent : public GenericEvent
{
public:
	SessionEndedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID) :
		GenericEvent(evntId, timeStmp, END_SESSION, appName, appVrs, sessionID) {}
};

// Implementado
class LevelStartedEvent : public GenericEvent
{
private:
	int levelId;

public:
	LevelStartedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int levelid) :
		GenericEvent(evntId, timeStmp, START_LEVEL, appName, appVrs, sessionID), levelId(levelid) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["levelId"] = new JSONValue(levelId);
	}
};

// Implementado
class LevelEndedEvent : public GenericEvent
{
private:
	int levelId;

public:
	LevelEndedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int levelid) :
		GenericEvent(evntId, timeStmp, END_LEVEL, appName, appVrs, sessionID), levelId(levelid) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["levelId"] = new JSONValue(levelId);
	}
};

// Implementado (HAY QUE CAMBIAR EL cardId POR UN STRING
class ChangedCardPlayingEvent : public GenericEvent
{
private:
	int levelId;
	CardId currentCard;
public:
	ChangedCardPlayingEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int levelid, CardId card) :
		GenericEvent(evntId, timeStmp, CARD_CHANGED, appName, appVrs, sessionID), levelId(levelid), currentCard(card) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["levelId"] = new JSONValue(levelId);
		jsonEvent["currentCard"] = new JSONValue(currentCard);
	}
};

// Implementado (Lo mismo, va a recibir un string)
class AbilityUsedEvent : public GenericEvent
{
private:
	int levelId; // Para poder saber habilidadesUsadas/nivel (???)
	CardId cardFromAbility;

public:

	AbilityUsedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int levelid, CardId card) :
		GenericEvent(evntId, timeStmp, ABILITY_USED, appName, appVrs, sessionID), levelId(levelid), cardFromAbility(card) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["levelId"] = new JSONValue(levelId);
		jsonEvent["cardFromAbility"] = new JSONValue(cardFromAbility);
	}
};

// Implementado
class PlayerHealedEvent : public GenericEvent
{
private:
	int quantityHealed;

public:
	PlayerHealedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int heal) :
		GenericEvent(evntId, timeStmp, PLAYER_HEALED, appName, appVrs, sessionID), quantityHealed(heal) {}

	virtual void serializeToJSON(JSONObject& jsonEvent)
	{
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["quantityHealed"] = new JSONValue(quantityHealed);
	}
};

// Implementado
class PeriodicHealthEvent : public GenericEvent
{
private:
	int healthStatus;

public:
	PeriodicHealthEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int currentHealth) :
		GenericEvent(evntId, timeStmp, PERIODIC_HEALTH_STATUS, appName, appVrs, sessionID), healthStatus(currentHealth) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["healthStatus"] = new JSONValue(healthStatus);
	}
};

// Implementado (Lo mismo, recibe un string en vez de cardId)
class InsufficientManaEvent : public GenericEvent
{
private:
	int manaStatus;
	CardId cardFromAbility;
	int manaCost;

public:
	InsufficientManaEvent(int evntId, long long timeStmp, string appName, string appVrs,
		long sessionID, int currentMana, CardId ability, int abilityCost) :
		GenericEvent(evntId, timeStmp, NOT_ENOUGH_MANA, appName, appVrs, sessionID), manaStatus(currentMana), 
		cardFromAbility(ability), manaCost(abilityCost) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["manaStatus"] = new JSONValue(manaStatus);
		jsonEvent["cardFromAbility"] = new JSONValue(cardFromAbility);
		jsonEvent["manaCost"] = new JSONValue(manaCost);
	}
};

// Implementado
class ManaTakenEvent : public GenericEvent
{
private:
	int manaStatus;
	int manaTaken;

public:
	ManaTakenEvent(int evntId, long long timeStmp, string appName, string appVrs,
		long sessionID, int currentMana, int takenMana) :
		GenericEvent(evntId, timeStmp, MANA_TAKEN, appName, appVrs, sessionID), manaStatus(currentMana),
		manaTaken(takenMana) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["manaStatus"] = new JSONValue(manaStatus);
		jsonEvent["manaTaken"] = new JSONValue(manaTaken);
	}
};

// Implementado
class CanExitLevelEvent : public GenericEvent
{
private:
	int levelId;

public:
	CanExitLevelEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int levelid) :
		GenericEvent(evntId, timeStmp, LEVEL_EXIT_POSSIBLE, appName, appVrs, sessionID), levelId(levelid) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["levelId"] = new JSONValue(levelId);
	}
};

// Implementado
class TriedExitEvent : public GenericEvent
{
private:
	int levelId;
public:
	TriedExitEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int levelid) :
		GenericEvent(evntId, timeStmp, TRIED_LEAVING, appName, appVrs, sessionID), levelId(levelid) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["levelId"] = new JSONValue(levelId);
	}
};

class ChangedCardDeckToHandEvent : public GenericEvent
{
private:
	CardId cardChanged;

public:
	ChangedCardDeckToHandEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, CardId card) :
		GenericEvent(evntId, timeStmp, MOVED_TO_HAND, appName, appVrs, sessionID), cardChanged(card) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["cardChanged"] = new JSONValue(cardChanged);
	}
};

// Implementado
class ChangedCardHandToDeckEvent : public GenericEvent
{
private:
	CardId cardChanged;

public:
	ChangedCardHandToDeckEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, CardId card) :
		GenericEvent(evntId, timeStmp, MOVED_FROM_HAND, appName, appVrs, sessionID), cardChanged(card) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["cardChanged"] = new JSONValue(cardChanged);
	}
};

// Implementado
class InventoryExitedEvent : public GenericEvent
{
private:
	vector<CardId> currentDeck;

public:

	InventoryExitedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, vector<CardId> card) :
		GenericEvent(evntId, timeStmp, INVENTORY_LEFT, appName, appVrs, sessionID), currentDeck(card) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);

		vector<int> aux;
		for (int i : currentDeck) {
			aux.push_back(i);
		}

		jsonEvent["currentDeck"] = new JSONValue(aux);
	}
};
