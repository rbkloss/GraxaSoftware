#include "SplashScene.h"

#include "VillainSprite.h"
#include "Hero.h"

USING_NS_CC;

Scene* SplashScene::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// 'layer' is an autorelease object
	auto layer = SplashScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SplashScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add "HelloWorld" splash screen"
	//auto sprite = Sprite::create("sprite1.png");
	auto sprite = Hero::create();

	auto villain = VillainSprite::create();
	auto ground = Sprite::create("ground.png");
	ground->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	auto physBody = cocos2d::PhysicsBody::createBox(ground->getContentSize(), cocos2d::PhysicsMaterial(0, 0, 1));
	physBody->setDynamic(false);
	ground->setPhysicsBody(physBody);

	ground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200));
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	villain->setPosition(Vec2(visibleSize.width / 2 + origin.x + 50, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(ground, 0);
	this->addChild(sprite, 2);
	this->addChild(villain, 0);

	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(SplashScene::onContactBegin, this);

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

bool SplashScene::onContactBegin(PhysicsContact& contact) {
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
}

void SplashScene::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
