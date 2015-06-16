#include "Monster.h"
#include "Blocks.h"
#include "Hero.h"


void Monster::movimentation(cocos2d::Sprite* monster) {
  auto body = monster->getPhysicsBody();
  auto moveLeft = cocos2d::CallFunc::create([body]() {
    body->setVelocity({ -32, 0 });
  });
  
  auto moveRight = cocos2d::CallFunc::create([body]() {
    body->setVelocity({ 32, 0 });
  });

  auto delay = cocos2d::DelayTime::create(1.0f);

  auto sequence = cocos2d::Sequence::create(moveLeft, delay, moveRight,
    delay->clone(), nullptr);
  monster->runAction(cocos2d::RepeatForever::create(sequence));
}

void Monster::init(int x, int y, int width, int height, cocos2d::Node* rootNode, const std::string &name) {
  std::string imagePath("images/monster.png");
  auto sprite = cocos2d::Sprite::create();
  sprite->initWithFile(imagePath);


  sprite->setName(name);

  auto body = cocos2d::PhysicsBody::createBox({ static_cast<float>(width),
    static_cast<float>(height) }, cocos2d::PhysicsMaterial(1.0f, 4.0f, 0.1f));
  body->setCollisionBitmask(Blocks::HERO_BLOCK | Blocks::GROUND_BLOCK);
  body->setContactTestBitmask(Blocks::MONSTER_BLOCK);

  float w = static_cast<float>(width) / 2;
  float h = static_cast<float>(height) / 2;
  sprite->setPosition(static_cast<float>(x)+w,
    static_cast<float>(y)+h);
  sprite->setPhysicsBody(body);


  auto contactListener = cocos2d::EventListenerPhysicsContact::create();

  contactListener->onContactBegin = [](cocos2d::PhysicsContact &contact)->bool {
    auto shapeA = contact.getShapeA();
    auto bodyA = shapeA->getBody();
    auto shapeB = contact.getShapeB();
    auto bodyB = shapeB->getBody();

    auto nodeA = bodyA->getNode();
    auto nodeB = bodyB->getNode();

    if (!nodeA || !nodeB)return false;

    auto normal = contact.getContactData()->normal;

    bool ans = false;
    if (nodeA->getName() == Hero::getName()) {
      auto bName = nodeB->getName();
      if (bName.find("monster") != bName.npos) {
        ans = true;
        Hero::getInstance()->harm(1);
        Hero::getInstance()->repel(cocos2d::Vec2(-80000.0f*normal.x, 80000.0f*normal.y));
      }

    } else if (nodeB->getName() == Hero::getName()) {
      auto aName = nodeA->getName();
      if (aName.find("monster") != aName.npos) {
        ans = true;
        Hero::getInstance()->harm(1);
        Hero::getInstance()->repel(cocos2d::Vec2(80000.0f*normal.x, 80000.0f*normal.y));
      }

    }

    return ans;
  };

  cocos2d::Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(contactListener, sprite);

  movimentation(sprite);

  rootNode->addChild(sprite);
}