#include "Hero.h"


Hero::Hero() {}
Hero::~Hero() {}

Hero* Hero::create() {
	auto sprite = new Hero();
	if (sprite->initWithFile("sprite1.png")) {
		sprite->autorelease();
		sprite->addEvents();
		sprite->setTag(1);
		sprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
		
		auto physicsBody = cocos2d::PhysicsBody::createBox(sprite->getContentSize(), cocos2d::PhysicsMaterial(0.1f, 1.0f, 1.0f));
		physicsBody->setDynamic(true);
		physicsBody->setGravityEnable(true);
		physicsBody->addMass(30.0f);
		physicsBody->setContactTestBitmask(0xFFFFFFFF);
		sprite->setPhysicsBody(physicsBody);

		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
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
			this->runAction(forever);
			/*auto physBody = this->getPhysicsBody();
			physBody->applyForce(cocos2d::Vec2(-1000, 0));
			physBody->setVelocityLimit(100);*/
			break;
		}
		case (cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) :
		{
			auto moveAction = cocos2d::MoveBy::create(1, cocos2d::Vec3(50, 0, 0));
			auto forever = cocos2d::RepeatForever::create(moveAction);
			forever->setTag(27);
			this->runAction(forever);
			/*auto physBody = this->getPhysicsBody();
			physBody->setVelocity(cocos2d::Vec2(50, 0));
			physBody->setVelocityLimit(60);*/
			break;
		}
		case (cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) :
		{
			auto physBody = this->getPhysicsBody();
			physBody->applyImpulse(cocos2d::Vec2(0, 5000));
			physBody->setVelocityLimit(60);
			break;
		}
		}
	};

	listener->onKeyReleased = [=](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* evt) {
		switch (code) {
		case (cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) : {
			this->stopActionByTag(26);
			/*auto physBody = this->getPhysicsBody();
			physBody->applyImpulse(cocos2d::Vec2(5000, 0));*/
			break;
		}
		case (cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) : {
			this->stopActionByTag(27);
			/*auto physBody = this->getPhysicsBody();
			physBody->applyImpulse(cocos2d::Vec2(-50, 0));*/
			break;
		}
		}
	};

	
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
