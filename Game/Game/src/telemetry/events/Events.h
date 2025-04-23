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

	virtual void serializeToYALM(std::string& endResult) {
		GenericEvent::serializeToYALM(endResult);
		endResult += "\n";
	}
};

// Implementado
class SessionEndedEvent : public GenericEvent
{
private:

public:
	SessionEndedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID) :
		GenericEvent(evntId, timeStmp, END_SESSION, appName, appVrs, sessionID) {}

	virtual void serializeToYALM(std::string& endResult) {
		GenericEvent::serializeToYALM(endResult);
		endResult += "\n";
	}
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

	virtual void serializeToYALM(std::string& endResult) {
		GenericEvent::serializeToYALM(endResult);
		endResult += "  levelId: " + std::to_string(levelId) + "\n";
		endResult += "\n";
	}
};

// Implementado
class LevelEndedEvent : public GenericEvent
{
private:
	int levelId;
	bool win;

public:
	LevelEndedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int levelid, bool victory) :
		GenericEvent(evntId, timeStmp, END_LEVEL, appName, appVrs, sessionID), levelId(levelid), win(victory) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["levelId"] = new JSONValue(levelId);
		jsonEvent["win"] = new JSONValue(win);
	}

	virtual void serializeToYALM(std::string& endResult) {
		GenericEvent::serializeToYALM(endResult);
		endResult += "  levelId: " + std::to_string(levelId) + "\n";
		endResult += "  win: " + std::to_string(win) + "\n";
		endResult += "\n";
	}
};

// Implementado (HAY QUE CAMBIAR EL cardId POR UN STRING
class ChangedCardPlayingEvent : public GenericEvent
{
private:
	int levelId;

public:
	ChangedCardPlayingEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int levelid) :
		GenericEvent(evntId, timeStmp, CARD_CHANGED, appName, appVrs, sessionID), levelId(levelid) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["levelId"] = new JSONValue(levelId);
	}

	virtual void serializeToYALM(std::string& endResult) {
		GenericEvent::serializeToYALM(endResult);
		endResult += "  levelId: " + std::to_string(levelId) + "\n";
		endResult += "\n";
	}
};

// Implementado (Lo mismo, va a recibir un string)
class AbilityUsedEvent : public GenericEvent
{
private:
	int levelId; // Para poder saber habilidadesUsadas/nivel

public:

	AbilityUsedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int levelid) :
		GenericEvent(evntId, timeStmp, ABILITY_USED, appName, appVrs, sessionID), levelId(levelid) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["levelId"] = new JSONValue(levelId);
	}

	virtual void serializeToYALM(std::string& endResult) {
		GenericEvent::serializeToYALM(endResult);
		endResult += "  levelId: " + std::to_string(levelId) + "\n";
		endResult += "\n";
	}
};

// Implementado
class PlayerHealedEvent : public GenericEvent
{
private:
	int lifeAfterHeal;
	int attemptedHeal;
	int lifeBeforeHeal;

public:
	PlayerHealedEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int heal, int attempt,
		int life) : GenericEvent(evntId, timeStmp, PLAYER_HEALED, appName, appVrs, sessionID), lifeAfterHeal(heal),
		attemptedHeal(attempt), lifeBeforeHeal(life) {}

	virtual void serializeToJSON(JSONObject& jsonEvent)
	{
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["lifeBeforeHeal"] = new JSONValue(lifeBeforeHeal);
		jsonEvent["attemptedHeal"] = new JSONValue(attemptedHeal);
		jsonEvent["lifeAfterHeal"] = new JSONValue(lifeAfterHeal);
	}

	virtual void serializeToYALM(std::string& endResult) {
		GenericEvent::serializeToYALM(endResult);
		endResult += "  lifeBeforeHeal: " + std::to_string(lifeBeforeHeal) + "\n";
		endResult += "  attemptedHeal: " + std::to_string(attemptedHeal) + "\n";
		endResult += "  lifeAfterHeal: " + std::to_string(lifeAfterHeal) + "\n";
		endResult += "\n";
	}
};

// Implementado (Lo mismo, recibe un string en vez de cardId)
class InsufficientManaEvent : public GenericEvent
{
private:
	int manaStatus;
	int manaCost;

public:
	InsufficientManaEvent(int evntId, long long timeStmp, string appName, string appVrs,
		long sessionID, int currentMana, int abilityCost) :
		GenericEvent(evntId, timeStmp, NOT_ENOUGH_MANA, appName, appVrs, sessionID), manaStatus(currentMana), manaCost(abilityCost) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["manaStatus"] = new JSONValue(manaStatus);
		jsonEvent["manaCost"] = new JSONValue(manaCost);
	}

	virtual void serializeToYALM(std::string& endResult) {
		GenericEvent::serializeToYALM(endResult);
		endResult += "  manaStatus: " + std::to_string(manaStatus) + "\n";
		endResult += "  manaCost: " + std::to_string(manaCost) + "\n";
		endResult += "\n";
	}
};

// Implementado
class ManaTakenEvent : public GenericEvent
{
private:
	int manaBefore;
	int manaAfter;

public:
	ManaTakenEvent(int evntId, long long timeStmp, string appName, string appVrs,
		long sessionID, int currentMana, int takenMana) :
		GenericEvent(evntId, timeStmp, MANA_TAKEN, appName, appVrs, sessionID), manaBefore(currentMana),
		manaAfter(takenMana) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["manaBefore"] = new JSONValue(manaBefore);
		jsonEvent["manaAfter"] = new JSONValue(manaAfter);
	}

	virtual void serializeToYALM(std::string& endResult) {
		GenericEvent::serializeToYALM(endResult);
		endResult += "  manaBefore: " + std::to_string(manaBefore) + "\n";
		endResult += "  manaAfter: " + std::to_string(manaAfter) + "\n";
		endResult += "\n";
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

	virtual void serializeToYALM(std::string& endResult) {
		GenericEvent::serializeToYALM(endResult);
		endResult += "  levelId: " + std::to_string(levelId) + "\n";
		endResult += "\n";
	}
};

// Implementado
class ExitFailed : public GenericEvent
{
private:
	int levelId;

public:
	ExitFailed(int evntId, long long timeStmp, string appName, string appVrs, long sessionID, int levelid) :
		GenericEvent(evntId, timeStmp, LEAVE_FAILED, appName, appVrs, sessionID), levelId(levelid) {}

	virtual void serializeToJSON(JSONObject& jsonEvent) {
		GenericEvent::serializeToJSON(jsonEvent);
		jsonEvent["levelId"] = new JSONValue(levelId);
	}

	virtual void serializeToYALM(std::string& endResult) {
		GenericEvent::serializeToYALM(endResult);
		endResult += "  levelId: " + std::to_string(levelId) + "\n";
		endResult += "\n";
	}
};

// Implementado
class ChangedCardDeckToHandEvent : public GenericEvent
{
private:

public:
	ChangedCardDeckToHandEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID) :
		GenericEvent(evntId, timeStmp, MOVED_TO_HAND, appName, appVrs, sessionID) {}

	virtual void serializeToYALM(std::string& endResult) {
		GenericEvent::serializeToYALM(endResult);
		endResult += "\n";
	}
};

// Implementado
class ChangedCardHandToDeckEvent : public GenericEvent
{
private:

public:
	ChangedCardHandToDeckEvent(int evntId, long long timeStmp, string appName, string appVrs, long sessionID) :
		GenericEvent(evntId, timeStmp, MOVED_FROM_HAND, appName, appVrs, sessionID) {}

	virtual void serializeToYALM(std::string& endResult) {
		GenericEvent::serializeToYALM(endResult);
		endResult += "\n";
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

	virtual void serializeToYALM(std::string& endResult) {
		GenericEvent::serializeToYALM(endResult);
		
		endResult += "  currentDeck:\n";
		for (int i : currentDeck) {
			endResult += "  - " + std::to_string(i) + "\n";
		}
		endResult += "\n";
	}
};
