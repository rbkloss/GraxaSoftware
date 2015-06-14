#include "Coin.h"

#include "./Hero.h"
#include "ui/CocosGUI.h"

Coin::Coin() {}

Coin::~Coin() {}

void Coin::init(cocos2d::Node* rootNode, const int x, const int y,
  const Hero* hero) {
  assert(hero);
  static unsigned count = 0;
  hero_ = const_cast<Hero*>(hero);
  std::string imagePath("images/spinning_coin_gold.png");
  sprite_ = cocos2d::Sprite::create();
  sprite_->initWithFile(imagePath, { 0, 0, 32, 32 });
  auto body = cocos2d::PhysicsBody::createBox({ 32, 32 });
  body->setDynamic(false);
  body->setCollisionBitmask(0);
  body->setContactTestBitmask(Hero::tag);
  sprite_->setPhysicsBody(body);

  sprite_->setAnchorPoint({ 0.0f, 1.0f });
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

    if (hero_->getName() == nodeA->getName()) {
      std::string name = nodeB->getName();
      if (name == sprite_->getName())
        coinContact(sprite_);
    } else if (hero_->getName() == nodeB->getName()) {
      std::string name = nodeA->getName();
      if (name == sprite_->getName())
        coinContact(sprite_);
    }

    return true;
  };

  cocos2d::Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(contactListener_, sprite_);
  rootNode->addChild(sprite_);
}

void Coin::coinContact(cocos2d::Sprite* coin) {
  hero_->increaseScore(10);
  coin->removeAllChildrenWithCleanup(true);
  coin->removeFromParentAndCleanup(true);

  cocos2d::Director::getInstance()->getEventDispatcher()->
    removeEventListener(contactListener_);
  this->~Coin();
}