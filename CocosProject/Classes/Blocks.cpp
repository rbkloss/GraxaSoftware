#include "Blocks.h"

#include "cocos2d.h"

cocos2d::Sprite*  Blocks::createGroundBlock(const std::string &name, cocos2d::Node* rootNode) {
	auto tempNode = rootNode->getChildByName(name);
	auto sprite = (cocos2d::Sprite*)tempNode;
	auto physBody = cocos2d::PhysicsBody::createBox(sprite->getBoundingBox().size, cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.9f));
	physBody->setDynamic(true);
	physBody->setGravityEnable(false);
	physBody->setRotationEnable(false);
	physBody->setMass(cocos2d::PHYSICS_INFINITY);
	physBody->setContactTestBitmask(1);
	sprite->setPhysicsBody(physBody);

	return sprite;
}