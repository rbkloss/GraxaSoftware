#include "VictoryScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

cocos2d::Scene* VictoryScene::createScene() {
  auto scene = Scene::create();

  // 'layer' is an autorelease object
  auto layer = VictoryScene::create();

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

bool VictoryScene::init() {
  if (!Layer::init()) {
    return false;
  }

  auto rootNode = CSLoader::createNode("GameOverClientScene.csb");

  auto exitButton = static_cast<cocos2d::ui::Button*>(rootNode->getChildByName("Exit"));

  exitButton->addTouchEventListener([](Ref*sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
      exit(0);
    }
  });

  addChild(rootNode);

  return true;
}