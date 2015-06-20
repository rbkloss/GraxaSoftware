#include <vector>

#include "StageOneScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Hero.h"
#include "Requirements.h"



USING_NS_CC;

using namespace cocostudio::timeline;

Scene* StageOneScene::createScene() {
  // 'scene' is an autorelease object
  auto scene = Scene::createWithPhysics();
  auto world = scene->getPhysicsWorld();
  world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
  world->setUpdateRate(0.5f);
  world->setSubsteps(4);
  // world->setSpeed(2.0);
  // 'layer' is an autorelease object
  auto layer = StageOneScene::create();
  layer->setName("StageOneSceneLayer");

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

// on "init" you need to initialize your instance
bool StageOneScene::init() {
  //////////////////////////////
  // 1. super init first
  if (!Layer::init()) {
    return false;
  }
  auto sz = Director::getInstance()->getVisibleSize();

  auto rootNode = CSLoader::createNode("StageOneScene.csb");
  auto screenEdge = cocos2d::PhysicsBody::createEdgeBox(sz);
  auto screenNode = cocos2d::DrawNode::create();
  screenNode->setPosition(sz.width / 2, sz.height / 2);
  screenNode->setPhysicsBody(screenEdge);
  this->addChild(screenNode);
  this->addChild(rootNode);

  auto tempNode = rootNode->getChildByName(Hero::getName());
  cocos2d::Sprite* heroSprite = dynamic_cast<cocos2d::Sprite*>(tempNode);
  Hero::init(heroSprite);
  blocks_.inflateTileMap(rootNode);


  Requirements::getInstance().create(rootNode, "listing",
    std::vector<bool>(2, true));

  auto button = static_cast<cocos2d::ui::Button*>(rootNode->getChildByName("starButton"));
  button->addTouchEventListener(
    [rootNode, sz](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
      auto score = Requirements::getInstance().evaluateScore();
      // label->setVisible(true);
      std::stringstream ss;
      ss << "Score is " << score;
      static cocos2d::Label* label = nullptr;
      if (label == nullptr) {
        label = cocos2d::Label::createWithSystemFont(ss.str(), "arial.ttf", 48);
      } else {
        label->removeFromParentAndCleanup(true);
        label = cocos2d::Label::createWithSystemFont(ss.str(), "arial.ttf", 48);
      }
      label->setPosition(sz.width / 2, sz.height / 2);
      label->setVisible(true);
      rootNode->addChild(label);
    }
  });

  schedule(CC_SCHEDULE_SELECTOR(StageOneScene::update), 0.3f);

  return true;
}

void StageOneScene::update(float dt) {
  Hero::getInstance()->update(dt);
}

std::shared_ptr<Monster> StageOneScene::getMonsterByName(const std::string& monsterName){
  return blocks_.getMonsterByName(monsterName);
}