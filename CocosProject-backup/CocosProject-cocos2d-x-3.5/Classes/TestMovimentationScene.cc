#include "TestMovimentationScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Hero.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* TestMovimentationScene::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// 'layer' is an autorelease object
	auto layer = TestMovimentationScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestMovimentationScene::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}

	auto rootNode = CSLoader::createNode("JumpTest.csb");
	this->addChild(rootNode);

	auto tempNode = rootNode->getChildByName(Hero::getTag());
	auto heroSprite = (Sprite*)tempNode;
	static auto hero = Hero::create(heroSprite);
	auto createBlock = [=](std::string name) {
		auto tempNode = rootNode->getChildByName(name);
		auto sprite = (Sprite*)tempNode;
		auto physBody = cocos2d::PhysicsBody::createBox(sprite->getBoundingBox().size, cocos2d::PhysicsMaterial(1.0f, 0.0f, 0));
		physBody->setDynamic(false);
		physBody->setContactTestBitmask(1);
		sprite->setPhysicsBody(physBody);

		return sprite;
	};
	auto bottom = createBlock("bottom");
	auto top = createBlock("top");
	auto left = createBlock("left");
	auto right = createBlock("right");

	auto leftRightContact = [=](cocos2d::PhysicsContact& contact) {
		auto normal = contact.getContactData()->normal;
		auto shapeA = contact.getShapeA();
		auto bodyA = shapeA->getBody();
		auto shapeB = contact.getShapeB();
		auto bodyB = shapeB->getBody();



		auto nodeA = bodyA->getNode();
		auto nodeB = bodyB->getNode();
		auto nameA = nodeA->getName();
		auto nameB = nodeB->getName();
		if ("hero" == nodeA->getName()) {
			if (nameB == "left") {
				auto checkNode = (cocos2d::Sprite*) rootNode->getChildByName("checkLeft");
				checkNode->setVisible(true);
			} else if (nameB == "right") {
				auto checkNode = (cocos2d::Sprite*) rootNode->getChildByName("checkRight");
				checkNode->setVisible(true);
			}
		} else if ("hero" == nodeB->getName()) {
			if (nameA == "left") {
				auto checkNode = (cocos2d::Sprite*) rootNode->getChildByName("checkLeft");
				checkNode->setVisible(true);
			} else if (nameA == "right") {
				auto checkNode = (cocos2d::Sprite*) rootNode->getChildByName("checkRight");
				checkNode->setVisible(true);
			}
		}

		return true;
	};

	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = leftRightContact;

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, left);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener->clone(), right);

	static bool topHit = false;
	auto topBottomContact = [=](cocos2d::PhysicsContact& contact) {
		auto normal = contact.getContactData()->normal;
		auto shapeA = contact.getShapeA();
		auto bodyA = shapeA->getBody();
		auto shapeB = contact.getShapeB();
		auto bodyB = shapeB->getBody();

		auto nodeA = bodyA->getNode();
		auto nodeB = bodyB->getNode();
		auto nameA = nodeA->getName();
		auto nameB = nodeB->getName();
		if ("hero" == nodeA->getName()) {
			if (nameB == "top") {
				topHit = true;
			} else if (nameB == "bottom" && topHit) {
				auto checkNode = (cocos2d::Sprite*) rootNode->getChildByName("checkJump");
				checkNode->setVisible(true);
			}
		} else if ("hero" == nodeB->getName()) {
			if (nameA == "top") {
				topHit = true;
			} else if (nameA == "bottom" && topHit) {
				auto checkNode = (cocos2d::Sprite*) rootNode->getChildByName("checkJump");
				checkNode->setVisible(true);
			}
		}
		return true;
	};

	auto topBottomContactListener = cocos2d::EventListenerPhysicsContact::create();
	topBottomContactListener->onContactBegin = topBottomContact;

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(topBottomContactListener, top);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(topBottomContactListener->clone(), bottom);

	return true;
}
