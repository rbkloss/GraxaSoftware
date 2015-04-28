
#include "VillainSprite.h"

VillainSprite::VillainSprite() {}

VillainSprite::~VillainSprite() {};

VillainSprite* VillainSprite::create() {
	auto sprite = new VillainSprite();
	if (sprite->initWithFile("sprite2.png")) {
		sprite->autorelease();
		sprite->registerEvents();

		auto physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(21.0f, 22.0f), cocos2d::PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody->setDynamic(true);
		physicsBody->setContactTestBitmask(0xFFFFFFFF);
		sprite->setPhysicsBody(physicsBody);

		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void VillainSprite::registerEvents() {
	//empty
}