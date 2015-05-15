#include <string>
#include "./Blocks.h"

#include "cocos2d.h"

cocos2d::Sprite*  Blocks::createGroundBlock(
  const std::string &name, cocos2d::Node* rootNode) {
  auto tempNode = rootNode->getChildByName(name);
  tempNode->setTag(BlockTypes::GROUND_BLOCK);
  auto sprite = (cocos2d::Sprite*)tempNode;
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

void Blocks::inflateTileMap(cocos2d::Node* rootNode) {
  auto map = (cocos2d::TMXTiledMap*)rootNode->getChildByName("tileMap");
  auto layer = map->getLayer("collidable");

  auto collisionGroup = map->getObjectGroup("collisions");
  auto collisionObjects = collisionGroup->getObjects();
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

cocos2d::PhysicsBody* Blocks::parseShape(const std::string &shapeName) {
  // TODO(rbkloss): implement this
  return nullptr;
}
