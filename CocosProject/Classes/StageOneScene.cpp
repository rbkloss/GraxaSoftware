#include <vector>

#include "StageOneScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Hero.h"
#include "Requirements.h"
#include <SimpleAudioEngine.h>


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
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
  audio->preloadEffect("sound/coin.mp3");
  audio->preloadEffect("sound/shot.mp3");

  auto sz = Director::getInstance()->getVisibleSize();
  auto rootNode = CSLoader::createNode("StageOneScene.csb");
  auto screenEdge = cocos2d::PhysicsBody::createEdgeBox(sz);
  auto screenNode = cocos2d::DrawNode::create();
  screenNode->setPosition(sz.width / 2, sz.height / 2);
  screenNode->setPhysicsBody(screenEdge);
  this->addChild(screenNode);
  this->addChild(rootNode);

  auto heart = rootNode->getChildByName("lifeHud");
  auto coins = rootNode->getChildByName("coinHud");
  auto heartLabel = cocos2d::ui::Text::create(std::to_string(3),
    "arial.ttf", 32);
  heartLabel->setName("heartLabel");
  heartLabel->setAnchorPoint({ 0.5f, 0.5f });
  heart->addChild(heartLabel);
  heartLabel->setPosition({ 32, 0 });

  auto coinLabel = cocos2d::ui::Text::create(std::to_string(0),
    "arial.ttf", 32);
  coinLabel->setName("coinsLabel");
  coinLabel->setAnchorPoint({ 0.5f, 0.5f });
  coins->addChild(coinLabel);
  coinLabel->setPosition({ 32, 0 });

  blocks_.inflateTileMap(rootNode);

  setRequirementsUp(rootNode);

  schedule(CC_SCHEDULE_SELECTOR(StageOneScene::update), 0.3f);

  return true;
}

void StageOneScene::setRequirementsUp(cocos2d::Node* rootNode) {
  Requirements::getInstance().create(rootNode, "listing",
    std::vector<bool>(2, true));
  auto sz = Director::getInstance()->getVisibleSize();
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
}

void StageOneScene::update(float dt) {
  Hero::getInstance()->update(dt);
}

std::shared_ptr<Monster> StageOneScene::getMonsterByName(const std::string& monsterName) {
  return blocks_.getMonsterByName(monsterName);
}