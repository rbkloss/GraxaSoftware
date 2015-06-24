#include <vector>

#include "StageOneScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Hero.h"
#include "Monster.h"
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

  audio->playBackgroundMusic("sound/technology.mp3", true);

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
  std::vector<std::pair<std::string, bool>> reqs;
  std::vector<std::function<void()>> fixCallBacks;
  reqs.push_back(std::make_pair("- Personagem se move?", false));
  fixCallBacks.push_back([]() {
    Hero::getInstance()->enableMove();
  });
  reqs.push_back(std::make_pair("- Personagem Pula?", false));
  fixCallBacks.push_back([]() {
    Hero::getInstance()->enableJump();
  });
  reqs.push_back(std::make_pair("- Personagem coleta moedas?", false));
  fixCallBacks.push_back([]() {});
  reqs.push_back(std::make_pair("- Personagem atira?", false));
  fixCallBacks.push_back([]() {
    Hero::getInstance()->enableFire();
  });
  reqs.push_back(std::make_pair("- Inimigo morre?", true));
  fixCallBacks.push_back([]() {});
  reqs.push_back(std::make_pair("- Inimigo move?", false));
  fixCallBacks.push_back([]() {
    Monster::enableMove();
  });
  reqs.push_back(std::make_pair("- Hero'i morre?", true));
  fixCallBacks.push_back([]() {});

  auto listView = static_cast<cocos2d::ui::ListView*>(
    rootNode->getChildByName("listing"));

  Requirements::getInstance().create(listView, reqs, fixCallBacks);

  auto sz = Director::getInstance()->getVisibleSize();
  auto button = static_cast<cocos2d::ui::Button*>(rootNode->getChildByName("starButton"));
  button->addTouchEventListener(
    [rootNode, sz](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
      Requirements::getInstance().evaluate();
    }
  });
}

void StageOneScene::update(float dt) {
  Hero::getInstance()->update(dt);
}

std::shared_ptr<Monster> StageOneScene::getMonsterByName(const std::string& monsterName) {
  return blocks_.getMonsterByName(monsterName);
}