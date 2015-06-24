#include "ClientGameOverScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "StartScreenScene.h"

USING_NS_CC;

cocos2d::Scene* ClientGameOverScene::createScene() {
  auto scene = Scene::create();

  // 'layer' is an autorelease object
  auto layer = ClientGameOverScene::create();

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

bool ClientGameOverScene::init() {
  if (!Layer::init()) {
    return false;
  }

  auto rootNode = CSLoader::createNode("GameOverClientScene.csb");

  auto startButton = static_cast<cocos2d::ui::Button*>(rootNode->getChildByName("Start"));
  auto exitButton = static_cast<cocos2d::ui::Button*>(rootNode->getChildByName("Exit"));


  startButton->addTouchEventListener([](Ref*sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
      auto director = cocos2d::Director::getInstance();
      auto scene = StartScreenScene::createScene();
      director->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 255, 255)));
    }
  });

  exitButton->addTouchEventListener([](Ref*sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
      exit(0);
    }
  });

  addChild(rootNode);

  return true;
}