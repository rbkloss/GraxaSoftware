#include <string>
#include "./Blocks.h"

#include "cocos2d.h"
#include "Coin.h"
#include "Pit.h"
#include "Monster.h"
#include "Hero.h"

Blocks::~Blocks() {
  monsters_.clear();
}

cocos2d::Sprite*  Blocks::createGroundBlock(
  const std::string &name, cocos2d::Node* rootNode) {
  auto tempNode = rootNode->getChildByName(name);
  tempNode->setTag(BlockTypes::GROUND_BLOCK);
  auto sprite = dynamic_cast<cocos2d::Sprite*>(tempNode);
  auto physBody = cocos2d::PhysicsBody::
    createBox(sprite->
    getBoundingBox().size,
    cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.9f));
  physBody->setDynamic(true);
  physBody->setGravityEnable(false);
  physBody->setRotationEnable(false);
  physBody->setMass(cocos2d::PHYSICS_INFINITY);
  physBody->setContactTestBitmask(BlockTypes::HERO_BLOCK);
  sprite->setPhysicsBody(physBody);

  return sprite;
}

void Blocks::parseCollidables(cocos2d::Node* rootNode, cocos2d::TMXObjectGroup* collisionsGroup, cocos2d::TMXTiledMap* map) {
  static size_t count = 0;
  auto collisionObjects = collisionsGroup->getObjects();
  for (auto object : collisionObjects) {
    auto propertyMap = object.asValueMap();
    int x = 0, y = 0, width = 0, height = 0;
    cocos2d::Value tempValue;
    tempValue = (propertyMap["width"]);
    width = tempValue.asInt();
    tempValue = (propertyMap["height"]);
    height = tempValue.asInt();
    tempValue = (propertyMap["x"]);
    x = tempValue.asInt();
    tempValue = (propertyMap["y"]);
    y = tempValue.asInt();
    tempValue = propertyMap["Shape"];
    cocos2d::PhysicsBody* body = nullptr;
    if (!tempValue.isNull()) {
      body = parseShape(tempValue.asString());
    } else {
      body = cocos2d::PhysicsBody::createBox(
        cocos2d::Size(width, height),
        cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.9f));
    }
    auto sprite = cocos2d::DrawNode::create();
    sprite->setPosition(x + width / 2, y + height / 2);
    sprite->setName("ground" + std::to_string(++count));

    body->setDynamic(true);
    body->setGravityEnable(false);
    body->setRotationEnable(false);
    body->setMass(cocos2d::PHYSICS_INFINITY);
    body->setContactTestBitmask(Blocks::GROUND_BLOCK);

    sprite->setTag(Blocks::GROUND_BLOCK);
    sprite->setPhysicsBody(body);

    rootNode->addChild(sprite);
    // setPhysicsBody messes with positions of nodes with anchor different
    // than {0.5, 0.5}
  }
}

void Blocks::parseCoins(cocos2d::Node* rootNode, cocos2d::TMXObjectGroup* coinsGroup, cocos2d::TMXTiledMap* map) {
  //auto sz = rootNode->getContentSize();
  auto coinObjects = coinsGroup->getObjects();
  auto mapPos = map->getPosition();
  //auto mapSize = map->getContentSize();
  for (auto object : coinObjects) {
    auto propertyMap = object.asValueMap();
    int x = 0, y = 0;
    cocos2d::Value tempValue;
    tempValue = (propertyMap["x"]);
    x = tempValue.asInt();
    tempValue = (propertyMap["y"]);
    y = tempValue.asInt();

    Coin* coin = new Coin();
    coin->init(rootNode, x, y);
  }
}

void Blocks::parsePits(cocos2d::Node* rootNode, cocos2d::TMXObjectGroup* pitsGroup, cocos2d::TMXTiledMap* map) {
  auto pits = pitsGroup->getObjects();
  auto mapPos = map->getPosition();

  size_t count = 0;
  for (auto object : pits) {
    auto propertyMap = object.asValueMap();
    int x = 0, y = 0, width = 0, height = 0;

    cocos2d::Value tempValue;
    tempValue = (propertyMap["width"]);
    width = tempValue.asInt();
    tempValue = (propertyMap["height"]);
    height = tempValue.asInt();
    tempValue = (propertyMap["x"]);
    x = tempValue.asInt();
    tempValue = (propertyMap["y"]);
    y = tempValue.asInt();

    PitBlock::setup(x, y, width, height, rootNode, "pit" + std::to_string(++count));
  }
}

void Blocks::parseMonsters(cocos2d::Node* rootNode, cocos2d::TMXObjectGroup* monstersGroup, cocos2d::TMXTiledMap* map) {
  auto monsters = monstersGroup->getObjects();
  auto mapPos = map->getPosition();

  size_t count = 0;
  for (auto object : monsters) {
    auto propertyMap = object.asValueMap();
    int x = 0, y = 0, width = 0, height = 0;

    cocos2d::Value tempValue;
    tempValue = (propertyMap["width"]);
    width = tempValue.asInt();
    tempValue = (propertyMap["height"]);
    height = tempValue.asInt();
    tempValue = (propertyMap["x"]);
    x = tempValue.asInt();
    tempValue = (propertyMap["y"]);
    y = tempValue.asInt();

    auto monsterName = "monster" + std::to_string(++count);
    auto monster = Monster::init(x, y, width, height, rootNode, monsterName);
    monsters_.insert(std::make_pair(monsterName, monster));
  }
}

void Blocks::parseHero(cocos2d::Node* rootNode, cocos2d::TMXObjectGroup* heroGroup, cocos2d::TMXTiledMap* map) {
  auto hero = heroGroup->getObjects();
  auto mapPos = map->getPosition();
  size_t count = 0;
  for (auto object : hero) {
    auto propertyMap = object.asValueMap();
    int x = 0, y = 0, width = 0, height = 0;

    cocos2d::Value tempValue;
    tempValue = (propertyMap["width"]);
    width = tempValue.asInt();
    tempValue = (propertyMap["height"]);
    height = tempValue.asInt();
    tempValue = (propertyMap["x"]);
    x = tempValue.asInt();
    tempValue = (propertyMap["y"]);
    y = tempValue.asInt();

    auto monsterName = "monster" + std::to_string(++count);
    Hero::init(rootNode, x + width / 2, y + height / 2);
  }
}

void Blocks::inflateTileMap(cocos2d::Node* rootNode) {
  auto map = dynamic_cast<cocos2d::TMXTiledMap*>
    (rootNode->getChildByName("tileMap"));

  auto collisionGroup = map->getObjectGroup("collisions");
  auto coinsGroup = map->getObjectGroup("coins");
  auto pitsGroup = map->getObjectGroup("pits");
  auto monstersGroup = map->getObjectGroup("monsters");
  auto heroGroup = map->getObjectGroup("hero");
  if (heroGroup)
    parseHero(rootNode, heroGroup, map);
  if (collisionGroup)
    parseCollidables(rootNode, collisionGroup, map);
  if (coinsGroup)
    parseCoins(rootNode, coinsGroup, map);
  if (pitsGroup)
    parsePits(rootNode, pitsGroup, map);
  if (monstersGroup)
    parseMonsters(rootNode, monstersGroup, map);

}

cocos2d::PhysicsBody* Blocks::parseShape(const std::string &shapeName) {
  // TODO(rbkloss): implement this
  return nullptr;
}

std::shared_ptr<Monster> Blocks::getMonsterByName(const std::string& name) {
  auto it = monsters_.find(name);
  std::shared_ptr<Monster> ans(nullptr);
  if (it != monsters_.end())
    ans = it->second;
  return ans;
}