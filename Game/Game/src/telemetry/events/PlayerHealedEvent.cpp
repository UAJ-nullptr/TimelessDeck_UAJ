#include "PlayerHealedEvent.h"

PlayerHealedEvent::PlayerHealedEvent(int evntId, long long timeStmp, string appName, string appVrs,
	long sessionID, int heal, int attempt, int life) : GenericEvent(evntId, timeStmp, PLAYER_HEALED,
		appName, appVrs, sessionID), lifeAfterHeal(heal), attemptedHeal(attempt), lifeBeforeHeal(life) {
}

void PlayerHealedEvent::serializeToJSON(JSONObject& jsonEvent) {
	GenericEvent::serializeToJSON(jsonEvent);
	jsonEvent["lifeBeforeHeal"] = new JSONValue(lifeBeforeHeal);
	jsonEvent["attemptedHeal"] = new JSONValue(attemptedHeal);
	jsonEvent["lifeAfterHeal"] = new JSONValue(lifeAfterHeal);
}

void PlayerHealedEvent::serializeToYAML(std::string& endResult) {
	GenericEvent::serializeToYAML(endResult);
	endResult += "  lifeBeforeHeal: " + std::to_string(lifeBeforeHeal) + "\n";
	endResult += "  attemptedHeal: " + std::to_string(attemptedHeal) + "\n";
	endResult += "  lifeAfterHeal: " + std::to_string(lifeAfterHeal) + "\n";
	endResult += "\n";
}