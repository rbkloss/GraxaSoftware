#include "TestMovimentationScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Hero.h"
#include "Blocks.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using cocos2d::Sprite;

Scene* TestMovimentationScene::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	auto world = scene->getPhysicsWorld();
	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	world->setGravity(cocos2d::Vec2(0, -98));

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

	auto tempNode = rootNode->getChildByName(Hero::getName());
	Sprite* heroSprite = static_cast<Sprite*>(tempNode);
	static auto hero = Hero::create(heroSprite);

	auto bottom = Blocks::createGroundBlock("bottom", rootNode);
	auto top = Blocks::createGroundBlock("top", rootNode);
	auto left = Blocks::createGroundBlock("left", rootNode);
	auto right = Blocks::createGroundBlock("right", rootNode);

	auto leftRightContact = [rootNode](cocos2d::PhysicsContact& contact) {
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
				auto checkNode = static_cast<cocos2d::Sprite*>(rootNode->getChildByName("checkLeft"));
				checkNode->setVisible(true);
			} else if (nameB == "right") {
				auto checkNode = static_cast<cocos2d::Sprite*>(rootNode->getChildByName("checkRight"));
				checkNode->setVisible(true);
			}
		} else if ("hero" == nodeB->getName()) {
			if (nameA == "left") {
				auto checkNode = static_cast<cocos2d::Sprite*>(rootNode->getChildByName("checkLeft"));
				checkNode->setVisible(true);
			} else if (nameA == "right") {
				auto checkNode = static_cast<cocos2d::Sprite*>(rootNode->getChildByName("checkRight"));
				checkNode->setVisible(true);
			}
		}

		return true;
	};

	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = leftRightContact;

	cocos2d::Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(contactListener, left);
	cocos2d::Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(contactListener->clone(), right);

	static bool topHit = false;
	auto topBottomContact = [rootNode](cocos2d::PhysicsContact& contact) {
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

	cocos2d::Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(topBottomContactListener, top);
	cocos2d::Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(topBottomContactListener->clone(), bottom);

	return true;
}
