#include "PlayerHealedEvent.h"

PlayerHealedEvent::PlayerHealedEvent(int heal, int attempt, int life) : GenericEvent(PLAYER_HEALED),
	lifeAfterHeal(heal), attemptedHeal(attempt), lifeBeforeHeal(life) {
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