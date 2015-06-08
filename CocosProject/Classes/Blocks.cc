#include <string>
#include "./Blocks.h"

#include "cocos2d.h"
#include "Coin.h"

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
  physBody->setContactTestBitmask(1);
  sprite->setPhysicsBody(physBody);

  return sprite;
}

void Blocks::parseCollidables(cocos2d::TMXObjectGroup* collisionsGroup,
  cocos2d::TMXTiledMap* map) {
  auto layer = map->getLayer("foreground");
  auto collisionObjects = collisionsGroup->getObjects();
  for (auto object : collisionObjects) {
    auto propertyMap = object.asValueMap();
    int x = 0, y = 0, width = 0, height = 0;
    int tileWidth = 0, tileHeight = 0;
    tileWidth = map->getTileSize().width;
    tileHeight = map->getTileSize().height;
    cocos2d::Value tempValue;
    tempValue = (propertyMap["width"]);
    width = tempValue.asInt();
    tempValue = (propertyMap["height"]);
    height = tempValue.asInt();
    tempValue = (propertyMap["AnchorX"]);
    x = tempValue.asInt();
    tempValue = (propertyMap["AnchorY"]);
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
    auto tile = layer->getTileAt(cocos2d::Vec2(x, y));

    body->setDynamic(true);
    body->setGravityEnable(false);
    body->setRotationEnable(false);
    body->setMass(cocos2d::PHYSICS_INFINITY);
    body->setContactTestBitmask(Blocks::GROUND_BLOCK);
    auto tilePos = tile->getPosition();
    auto tileSize = tile->getContentSize();

    tile->setPhysicsBody(body);
    // setPhysicsBody messes with positions of nodes with anchor different
    // than {0.5, 0.5}
    auto correctPos = tilePos;
    correctPos.add(cocos2d::Vec2(tileWidth / 2, (tileHeight / 2)));

    tile->setPosition(correctPos);
    tile->setTag(Blocks::GROUND_BLOCK);
  }
}

void Blocks::parseCoins(cocos2d::Node* rootNode, cocos2d::TMXObjectGroup* coinsGroup, 
  cocos2d::TMXTiledMap* map, const Hero* hero) {
  auto sz = rootNode->getContentSize();
  auto coinObjects = coinsGroup->getObjects();
  auto mapPos = map->getPosition();
  auto mapSize = map->getContentSize();
  for (auto object : coinObjects) {
    auto propertyMap = object.asValueMap();
    int x = 0, y = 0, width = 0, height = 0;
    int tileWidth = 0, tileHeight = 0;
    tileWidth = map->getTileSize().width;
    tileHeight = map->getTileSize().height;
    cocos2d::Value tempValue;
    tempValue = (propertyMap["width"]);
    width = tempValue.asInt();
    tempValue = (propertyMap["height"]);
    height = tempValue.asInt();
    tempValue = (propertyMap["x"]);
    x = tempValue.asInt();
    tempValue = (propertyMap["y"]);
    y = tempValue.asInt();

    Coin* coin = new Coin();
    coin->init(rootNode, x, y, hero);
  }
}

void Blocks::inflateTileMap(cocos2d::Node* rootNode, const Hero* hero) {
  auto map = dynamic_cast<cocos2d::TMXTiledMap*>
    (rootNode->getChildByName("tileMap"));

  auto collisionGroup = map->getObjectGroup("collisions");
  auto coinsGroup = map->getObjectGroup("coins");
  parseCollidables(collisionGroup, map);
  parseCoins(rootNode, coinsGroup, map, hero);
}

cocos2d::PhysicsBody* Blocks::parseShape(const std::string &shapeName) {
  // TODO(rbkloss): implement this
  return nullptr;
}
