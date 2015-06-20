#include "StartScreenScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "TutorialScene.h"
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
  auto panelNode = static_cast<cocos2d::ui::Layout*>(rootNode->getChildByName("PanelView"));
  auto startButton = static_cast<cocos2d::ui::Button*>(panelNode->getChildByName("startButton"));


  startButton->addTouchEventListener([](Ref*sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
      auto director = cocos2d::Director::getInstance();
      auto tutorialScene = StageOneScene::createScene();
      director->replaceScene(TransitionFade::create(0.5, tutorialScene, Color3B(0, 255, 255)));
    }
  });

  addChild(rootNode);

  return true;
}
