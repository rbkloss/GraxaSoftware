#include "Projectile.h"
#include "Blocks.h"
#include "StageOneScene.h"

#include "Monster.h"

void HeroProjectile::setup(cocos2d::Node* rootNode, int x, int y,
  const cocos2d::Vec2& direction, const std::string& imageFilename, const cocos2d::Rect &from) {
  static size_t count = 0;
  auto sprite = cocos2d::Sprite::create(imageFilename, from);
  sprite->setPosition(x, y);
  sprite->setName("heroProjectile" + std::to_string(++count));

  animate();

  auto body = cocos2d::PhysicsBody::createBox({ 64, 16 });
  body->setGravityEnable(false);
  body->setRotationEnable(false);
  body->setCollisionBitmask(0);
  body->setContactTestBitmask(Blocks::MONSTER_BLOCK);

  sprite->setPhysicsBody(body);
  auto dir = direction;
  dir.normalize();
  body->setVelocity(256.0f * dir);

  auto contactListener = cocos2d::EventListenerPhysicsContact::create();

  contactListener->onContactBegin = [sprite](cocos2d::PhysicsContact &contact)->bool {
    auto shapeA = contact.getShapeA();
    auto bodyA = shapeA->getBody();
    auto shapeB = contact.getShapeB();
    auto bodyB = shapeB->getBody();

    auto nodeA = bodyA->getNode();
    auto nodeB = bodyB->getNode();

    if (!nodeA || !nodeB)return false;

    auto normal = contact.getContactData()->normal;

    auto aName = nodeA->getName();
    auto bName = nodeB->getName();
    auto scene = nodeA->getScene();
    auto stage = static_cast<StageOneScene*>(scene->getChildByName("StageOneSceneLayer"));
    std::shared_ptr<Monster> monster;
    bool ans = true;
    if (aName == sprite->getName()) {
      if (aName.find("monster") != aName.npos) {
        monster = stage->getMonsterByName(aName);
        ans = false;
      } else if (bName.find("monster") != bName.npos) {
        monster = stage->getMonsterByName(bName);
        ans = false;
      }
    } else if (bName == sprite->getName()){
      if (aName.find("ground") != aName.npos){
        groundCollision(sprite, nodeA);
        ans = false;
      } else if (bName.find("ground") != bName.npos) {
        groundCollision(sprite, nodeB);
        ans = false;
      }
    }
      
     
    return true;
  };
  cocos2d::Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(contactListener, sprite);

  rootNode->addChild(sprite);
}

void HeroProjectile::animate() {}

void HeroProjectile::monsterCollision(cocos2d::Sprite* sprite, std::shared_ptr<Monster> monster){
  monster->harm(1);
  sprite->removeAllChildrenWithCleanup(true);
  sprite->removeFromParentAndCleanup(true);
}

void HeroProjectile::groundCollision(cocos2d::Sprite* sprite, cocos2d::Node* ground){
  sprite->removeAllChildrenWithCleanup(true);
  sprite->removeFromParentAndCleanup(true);
}