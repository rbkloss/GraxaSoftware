#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Hero.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}

	auto rootNode = CSLoader::createNode("MainScene.csb");

	auto action = CSLoader::createTimeline("MainScene.csb");

	rootNode->runAction(action);
	action->gotoFrameAndPlay(0, 60, true);
	//action->setFrameEventCallFunc(CC_CALLBACK_1(Hero::init, this));	
	auto tempNode = rootNode->getChildByName(Hero::getTag());
	auto heroSprite = (Sprite*)tempNode;
	static auto hero = Hero::create(heroSprite);

	tempNode = rootNode->getChildByName("Ground");
	auto sprite = (Sprite*)tempNode;
	auto physBody = cocos2d::PhysicsBody::createEdgeBox(sprite->getContentSize(), cocos2d::PhysicsMaterial(100.0f, 0.0f, 1.0f));
	physBody->setDynamic(false);
	physBody->setContactTestBitmask(1);
	sprite->setPhysicsBody(physBody);
	
	auto layerNode = (Layer*) (rootNode->getChildByName("layer_1"));

	tempNode = layerNode->getChildByName("monster");
	sprite = (Sprite*)tempNode;
	physBody = cocos2d::PhysicsBody::createBox(sprite->getContentSize());
	physBody->setDynamic(false);
	physBody->setContactTestBitmask(1);
	sprite->setPhysicsBody(physBody);



	addChild(rootNode);

	return true;
}
