#include "StartScreenScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Hero.h"

#include "StartScreenModel.h"

#include "StageOneScene.h"

#include "TestMovimentationScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* StartScreenScene::createScene() {
	// Creates An auto-release scene object for the start screen
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartScreenScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool StartScreenScene::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}

	auto rootNode = CSLoader::createNode("StartScreen.csb");
	auto panelNode = (cocos2d::ui::Layout*)rootNode->getChildByName("PanelView");
	auto startButton = (cocos2d::ui::Button*) panelNode->getChildByName("startButton");
	auto testButton = (cocos2d::ui::Button*) panelNode->getChildByName("Test");


	startButton->addTouchEventListener([=](Ref*sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = cocos2d::Director::getInstance();
			auto stageOneScene = StageOneScene::createScene();
			director->replaceScene(TransitionFade::create(0.5, stageOneScene, Color3B(0, 255, 255)));
		}
	});

	testButton->addTouchEventListener([=](Ref*sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = cocos2d::Director::getInstance();
			auto scene = TestMovimentationScene::createScene();
			director->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 255, 255)));
		}
	});

	addChild(rootNode);

	return true;
}
