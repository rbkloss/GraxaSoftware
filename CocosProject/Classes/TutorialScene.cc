#include "TutorialScene.h"

#include "cocostudio/CocoStudio.h"


#include "StageOneScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

cocos2d::Scene* TutorialScene::createScene(){
  // 'scene' is an autorelease object
  auto scene = Scene::create();
  
  // 'layer' is an autorelease object
  auto layer = TutorialScene::create();

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool TutorialScene::init(){
  // 1. super init first
  if (!Layer::init()) {
    return false;
  }
  auto sz = Director::getInstance()->getVisibleSize();

  auto rootNode = CSLoader::createNode("TutorialScene.csb");

  button_ = dynamic_cast<cocos2d::ui::Button*>(rootNode->getChildByName("button"));
  text_ = dynamic_cast<cocos2d::LabelTTF*>(rootNode->getChildByName("textBox"));

  button_->addClickEventListener([])
  


    return true;
}

