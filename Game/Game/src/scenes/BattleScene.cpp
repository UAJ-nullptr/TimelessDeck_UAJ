#include "BattleScene.h"
#include "../components/Enemy components/RangeBehaviour.h"
#include "../components/Enemy components/MeleeBehaviour.h"
#include "../components/General Components/StatsTrackComponent.h"
#include "../gameObjects/UI/StatisticsUI.h"
#include "../components/General Components/CallbackDelayer.h"
#include "../gameObjects/UI/HandUI.h"

// Constructora
BattleScene::BattleScene(BattleType t_, bool tuto) : GameState(), type(t_) {
	SDLApplication::instance()->stopMainMusic();

	tutorial = tuto;
	//Mana
	PlayerData::instance()->resetMana();

	addBackgroundAndFloor();
	addMusic();

	//Creamos el jugador e informamos a la camara de que debe seguirle
	player = addGameObject<Player>(_grp_PLAYER, tuto);
	camera->startFollowObject(player);

	// Generador de enemigos
	if (!tuto) {
		createUI();
	}

	enemyGenerator = addGameObject();
	enemyGenerator->addComponent<EnemyGenerator>(player, this);
	enemyGenerator->addComponent<StatsTrackComponent>();

	//Música
	battleSceneOST = &sdlutils().musics().at("BattleMusic");
	battleSceneOST->play();
	sdlutils().focusMouseOnWindow();

	TelemetryTracker::instance()->addEvent(EventType::START_LEVEL, PlayerData::instance()->getLevel());
}

BattleScene::~BattleScene()
{
	battleSceneOST->haltMusic();
	sdlutils().unfocusMouseOnWindow();
}

void BattleScene::createUI() {
	// - UI -
	// Nos guardamos una referencia al componente de cartas del player
	CardComponent* cardComp = player->getComponent<CardComponent>();
	HealthComponent* healthComp = player->getComponent<HealthComponent>();

	// Añadimos el de estadísitcas
	hand = nullptr;
	cardContLeft = nullptr;
	cardContRight = nullptr;
	if (cardComp != nullptr) {
		statistics = nullptr;
		if (healthComp != nullptr) createStatistics(healthComp, cardComp);
		createCounters(cardComp);
		createHand(cardComp);
	}

	player->getComponent<PlayerInputComponent>()->setPortalComponent(statistics->getPortalComp());

	// El puntero sigue al player
	pointer->getComponent<PointerComponent>()->setFollowObject(player);
}

void BattleScene::createCounters(CardComponent* cardComp) {
	// Creamos los contadores de cartas y linkeamos el componente con el contador de mazo par ala animacion de barajar
	cardContLeft = addGameObject<CardCounter>(_grp_UI, true, cardComp);
	cardContRight = addGameObject<CardCounter>(_grp_UI, false, cardComp);
	cardComp->setCounter(cardContLeft);
}

void BattleScene::createHand(CardComponent* cardComp) {
	// Añadimos el objeto que muestra la mano de cartas en la UI
	hand = addGameObject<HandUI>(_grp_UI, cardComp);
}

void BattleScene::createStatistics(HealthComponent* healthComp, CardComponent* cardComp) {
	// Crear la barra de estadísticas
	statistics = addGameObject<StatisticsUI>(_grp_UI, healthComp->getLife(), cardComp->getMana());
}

void BattleScene::OnPlayerDies() {
	player->getComponent<Transform>()->setVel(Vector2D());
	player->removeComponent<PlayerMovementComponent>();
	player->removeComponent<PlayerInputComponent>();
	player->removeComponent<CardComponent>();
	pointer->removeComponent<Image>();
	TelemetryTracker::instance()->addEvent(EventType::END_LEVEL, false, PlayerData::instance()->getLevel());
}

void BattleScene::OnPlayerDamage(float value) {
	onHealthChanges(value);
}

void BattleScene::changeToGameOverScene() {
	player->removeComponent<PlayerAnimator>();

	GameObject* delay = addGameObject();

	if (tutorial) {
		delay->addComponent<CallbackDelayer>([&]() {
			SDLApplication::popGameState();
			SDLApplication::pushNewScene<GameOverScene>(type, true); }, DEATH_DELAY);
	}
	else {
		delay->addComponent<CallbackDelayer>([&]() {
			SDLApplication::popGameState();
			SDLApplication::pushNewScene<GameOverScene>(type); }, DEATH_DELAY);
	}
}

// Anade el fondo y suelo
void BattleScene::addBackgroundAndFloor() {
	//Fondo
	background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("BattleBackground"))->attachToCamera();
	background3 = addGameObject();
	background3->addComponent<Transform>(Vector2D(), Vector2D(), BATTLEBACKGROUND123_WIDTH, BATTLEBACKGROUND123_HEIGHT);
	background3->addComponent<Image>(SDLApplication::getTexture("BattleBackground3"))->setScrollFactor(BATTLEBACKGROUND3_SCROLLFACTOR);
	background2 = addGameObject();
	background2->addComponent<Transform>(Vector2D(), Vector2D(), BATTLEBACKGROUND123_WIDTH, BATTLEBACKGROUND123_HEIGHT);
	background2->addComponent<Image>(SDLApplication::getTexture("BattleBackground2"))->setScrollFactor(BATTLEBACKGROUND2_SCROLLFACTOR);
	background1 = addGameObject();
	background1->addComponent<Transform>(Vector2D(), Vector2D(), BATTLEBACKGROUND123_WIDTH, BATTLEBACKGROUND123_HEIGHT);
	background1->addComponent<Image>(SDLApplication::getTexture("BattleBackground1"))->setScrollFactor(BATTLEBACKGROUND1_SCROLLFACTOR);

	//Suelo
	floor = addGameObject();
	floor->addComponent<Transform>(Vector2D(50, 50), FLOOR_PAST_VELOCITY, FLOOR_WIDTH, FLOOR_HEIGHT);
	//Selección de textura
	switch (type) {
	case _PASTBATTLE:
		floor->addComponent<Image>(SDLApplication::getTexture("PastFloor"));
		break;
	case _PRESENTBATTLE:
		floor->addComponent<Image>(SDLApplication::getTexture("PresentFloor"));
		break;
	case _FUTUREBATTLE:
		floor->addComponent<Image>(SDLApplication::getTexture("FutureFloor"));
		break;
	case _BOSSBATTLE:
		floor->addComponent<Image>(SDLApplication::getTexture("BossFloor"));
		break;
	}
}

// Anade la musica
void BattleScene::addMusic() {
	//Música
	battleSceneOST = &sdlutils().musics().at(BATTLE_MUSIC);
	battleSceneOST->play();
}

// CAMBIOS DE UI
// Llamar a cambiar la carta seleccionada de la UI
void BattleScene::changeUISelected(bool key, int number) {
	if (hand != nullptr) hand->changeSelected(key, number);
}

// Llamar a borrar una carta de la UI
void BattleScene::discardUI(deque<Card*>::iterator discarded) {
	if (hand != nullptr) hand->discard(discarded);
}

// Llamar a la creaci�n de la UI
void BattleScene::recreateUI() {
	if (hand != nullptr) hand->createUI();
}

void BattleScene::changeAmmoUI(deque<Card*>::iterator used) {
	if (hand != nullptr) hand->changeAmmo(used);
}

// Llamar al cambio del valor de maná
void BattleScene::onManaChanges(float value) {
	if (statistics != nullptr) statistics->onManaChanges(value);
}

// Llamar al cambio del valor de maná
void BattleScene::onHealthChanges(float value) {
	if (statistics != nullptr) statistics->onHealthChanges(value);
}

// Llamar al cambio del valor de éter
void BattleScene::onEtherChanges(float value) {
	if (statistics != nullptr) statistics->onEtherChanges(value);
	if (value >= 100) {
		getTracker()->endTimeCouinting();
	}
}