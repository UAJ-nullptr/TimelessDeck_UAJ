#include "EnemyAnimator.h"
#include "../../core/SDLApplication.h"

EnemyAnimator::EnemyAnimator(string txtr_key, int sprtW,int sprtH, int rws, int cols, Animation idle, Animation mvment, Animation atck) :
	CharacterAnimator(SDLApplication::getTexture(txtr_key), sprtW, sprtH, rws, cols, idle, mvment),
	_bhvr(nullptr) {
	addAttack(atck, [&]() { return attacking(); });
}
void EnemyAnimator::initComponent() {
	CharacterAnimator::initComponent();
	_bhvr = gObj->getComponent<EnemyBehaviour>();
	assert(_bhvr != nullptr);
}