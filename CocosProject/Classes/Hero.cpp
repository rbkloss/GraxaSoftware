#include "Hero.h"


Hero::Hero() {}
Hero::~Hero() {}

std::string Hero::getTag() {
	static const char* ans = "hero";
	return ans;
}
std::shared_ptr<Hero> Hero::create(cocos2d::Sprite* sprite) {
	std::shared_ptr<Hero> hero = std::make_shared<Hero>();
	hero->setSprite(sprite);
	hero->addEvents();


	auto physicsBody = cocos2d::PhysicsBody::createBox(sprite->getContentSize(), cocos2d::PhysicsMaterial(0.1f, 1.0f, 1.0f));
	//physicsBody->setResting(true);
	physicsBody->setDynamic(true);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(1);
	sprite->setPhysicsBody(physicsBody);
	return hero;
}

void Hero::setSprite(cocos2d::Sprite* sprite) {
	this->sprite_ = sprite;
}

cocos2d::Sprite* Hero::getSprite() {
	return this->sprite_;
}

void Hero::addEvents() {
	auto listener = cocos2d::EventListenerKeyboard::create();

	listener->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* evt) {
		switch (code) {
		case (cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) :
		{
			auto moveAction = cocos2d::MoveBy::create(1, cocos2d::Vec3(-50, 0, 0));
			auto forever = cocos2d::RepeatForever::create(moveAction);
			forever->setTag(26);
			getSprite()->runAction(forever);
			break;
		}
		case (cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) :
		{
			auto moveAction = cocos2d::MoveBy::create(1, cocos2d::Vec3(50, 0, 0));
			auto forever = cocos2d::RepeatForever::create(moveAction);
			forever->setTag(27);
			getSprite()->runAction(forever);
			/*auto physBody = this->getPhysicsBody();
			physBody->setVelocity(cocos2d::Vec2(50, 0));
			physBody->setVelocityLimit(60);*/
			break;
		}
		case (cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) :
		{
			auto physBody = getSprite()->getPhysicsBody();
			physBody->applyImpulse(cocos2d::Vec2(0, 5000));
			physBody->setVelocityLimit(60);
			break;
		}
		}
	};

	listener->onKeyReleased = [=](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* evt) {
		switch (code) {
		case (cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) : {
			getSprite()->stopActionByTag(26);
			/*auto physBody = this->getPhysicsBody();
			physBody->applyImpulse(cocos2d::Vec2(5000, 0));*/
			break;
		}
		case (cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) : {
			getSprite()->stopActionByTag(27);
			/*auto physBody = this->getPhysicsBody();
			physBody->applyImpulse(cocos2d::Vec2(-50, 0));*/
			break;
		}
		}
	};

	auto onContactBegin = [=](cocos2d::PhysicsContact& contact) {
		auto bodyA = contact.getShapeA()->getBody();
		auto bodyB = contact.getShapeB()->getBody();
		auto nodeA = bodyA->getNode();
		auto nodeB = bodyB->getNode();
		if (1 != nodeB->getTag()) {
			nodeB->removeFromParentAndCleanup(true);
		} else {
			nodeA->removeFromParentAndCleanup(true);
		}
		cocos2d::log("collision");

		return true;
	};

	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = onContactBegin;

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, getSprite());

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, getSprite());
}