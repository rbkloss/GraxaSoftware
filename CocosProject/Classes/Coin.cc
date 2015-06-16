#include "Coin.h"

#include "./Hero.h"
#include "Blocks.h"

Coin::Coin() {}

Coin::~Coin() {}

void Coin::init(cocos2d::Node* rootNode, const int x, const int y) {
  static unsigned count = 0;
  std::string imagePath("images/spinning_coin_gold.png");
  sprite_ = cocos2d::Sprite::create();
  sprite_->initWithFile(imagePath, { 0, 0, 32, 32 });
  auto body = cocos2d::PhysicsBody::createBox({ 32, 32 });
  body->setDynamic(false);
  body->setCollisionBitmask(0);
  body->setContactTestBitmask(Blocks::COIN_BLOCK);
  sprite_->setPhysicsBody(body);

  sprite_->setPosition(x, y);
  sprite_->setName("coin" + std::to_string(++count));

  contactListener_ = cocos2d::EventListenerPhysicsContact::create();

  contactListener_->onContactBegin = [this](cocos2d::PhysicsContact &contact)->bool {
    auto shapeA = contact.getShapeA();
    auto bodyA = shapeA->getBody();
    auto shapeB = contact.getShapeB();
    auto bodyB = shapeB->getBody();

    auto nodeA = bodyA->getNode();
    auto nodeB = bodyB->getNode();
    if (!nodeA || !nodeB)return false;

    auto spriteName = sprite_->getName();
    if (Hero::getInstance()->getName() == nodeA->getName()) {
      std::string name = nodeB->getName();
      if (name == spriteName)
        coinContact(sprite_);
    } else if (Hero::getInstance()->getName() == nodeB->getName()) {
      std::string name = nodeA->getName();
      if (name == spriteName)
        coinContact(sprite_);
    }

    return true;
  };

  cocos2d::Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(contactListener_, sprite_);
  rootNode->addChild(sprite_);
}

void Coin::coinContact(cocos2d::Sprite* coin) {
  Hero::getInstance()->increaseScore(10);
  coin->removeAllChildrenWithCleanup(true);
  coin->removeFromParentAndCleanup(true);

  cocos2d::Director::getInstance()->getEventDispatcher()->
    removeEventListener(contactListener_);
  this->~Coin();
}