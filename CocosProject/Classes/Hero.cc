#include <string>

#include "./Hero.h"
#include "ui/CocosGUI.h"

#include "Blocks.h"


USING_NS_CC;

Hero::Hero() {
  onGround_ = true;
  jumping_ = false;
}
Hero::~Hero() {}

std::string Hero::getTag() {
  static const char* ans = "hero";
  return ans;
}

std::shared_ptr<Hero> Hero::create(cocos2d::Sprite* sprite) {
  std::shared_ptr<Hero> hero = std::make_shared<Hero>();
  hero->setSprite(sprite);
  hero->addEvents();


  auto physicsBody = cocos2d::PhysicsBody::createBox(sprite->getBoundingBox()
    .size, cocos2d::PhysicsMaterial(0, 0.0f, 2.0f));
  physicsBody->setDynamic(true);
  physicsBody->setRotationEnable(false);
  physicsBody->setContactTestBitmask(0xfffffff);
  physicsBody->setMass(600);
  physicsBody->setVelocityLimit(150);

  sprite->setPhysicsBody(physicsBody);
  return hero;
}

void Hero::setSprite(cocos2d::Sprite* sprite) {
  this->sprite_ = sprite;
}

cocos2d::Sprite* Hero::getSprite() {
  return this->sprite_;
}

void Hero::addEvents() {
  auto listener = cocos2d::EventListenerKeyboard::create();

  listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode code,
    cocos2d::Event* evt) {
    switch (code) {
      case (cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) : {
        this->moveHoriz(-1);
        break;
      }
      case (cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) : {
        this->moveHoriz(1);
        break;
      }
      case (cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) : {
        this->jump();
        break;
      }
    }
  };

  listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode code,
    cocos2d::Event* evt) {
    switch (code) {
      case (cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) : {
        this->getSprite()->stopActionByTag(24);
        if (this->onGround_) {
          this->getSprite()->getPhysicsBody()->
            applyImpulse(cocos2d::Vec2(3000, 0));
        } else {
          this->getSprite()->getPhysicsBody()->
            applyImpulse(cocos2d::Vec2(300, 0));
        }
        break;
      }
      case (cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) : {
        this->getSprite()->stopActionByTag(26);
        if (this->onGround_) {
          this->getSprite()->getPhysicsBody()->
            applyImpulse(cocos2d::Vec2(-3000, 0));
        } else {
          this->getSprite()->getPhysicsBody()->
            applyImpulse(cocos2d::Vec2(-300, 0));
        }
        break;
      }
    }
  };

  auto onContactBegin = [this](cocos2d::PhysicsContact& contact)->bool {
    auto normal = contact.getContactData()->normal;
    auto shapeA = contact.getShapeA();
    auto bodyA = shapeA->getBody();
    auto shapeB = contact.getShapeB();
    auto bodyB = shapeB->getBody();

    auto nodeA = bodyA->getNode();
    auto nodeB = bodyB->getNode();
    bool isHeroUp = false;
    cocos2d::Node* heroNode = nullptr;
    cocos2d::Node* otherNode = nullptr;
    if (this->getTag() == nodeA->getName()) {
      heroNode = nodeA;
      otherNode = nodeB;
      isHeroUp = normal.y < 0;
    } else if (this->getTag() == nodeB->getName()) {
      heroNode = nodeB;
      otherNode = nodeA;
      isHeroUp = normal.y > 0;
    }
    if (isHeroUp)onGround_ = true;
    auto check = (cocos2d::ui::CheckBox*)this->getSprite()->
      getChildByName("check");
    check->setSelected(onGround_);
    return true;
  };
  auto onContactSeparate = [this](cocos2d::PhysicsContact& contact)->void {
    auto normal = contact.getContactData()->normal;
    auto shapeA = contact.getShapeA();
    auto bodyA = shapeA->getBody();
    auto shapeB = contact.getShapeB();
    auto bodyB = shapeB->getBody();

    auto nodeA = bodyA->getNode();
    auto nodeB = bodyB->getNode();

    cocos2d::Node* heroNode = nullptr;
    cocos2d::Node* otherNode = nullptr;
    bool isHeroUp = false;
    if (this->getTag() == nodeA->getName()) {
      heroNode = nodeA;
      otherNode = nodeB;
      isHeroUp = normal.y < 0;
    } else if (this->getTag() == nodeB->getName()) {
      heroNode = nodeB;
      otherNode = nodeA;
      isHeroUp = normal.y > 0;
    }
    if (isHeroUp) {
      onGround_ = false;
    }

    auto check = (cocos2d::ui::CheckBox*)this->getSprite()->
      getChildByName("check");
    check->setSelected(onGround_);
  };

  auto contactListener = cocos2d::EventListenerPhysicsContact::create();
  contactListener->onContactSeperate = onContactSeparate;
  contactListener->onContactBegin = onContactBegin;
  cocos2d::Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(contactListener, getSprite());

  cocos2d::Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(listener, getSprite());
}

void Hero::update(float dt) {}

void Hero::jump() {
  if (this->onGround_) {
    this->onGround_ = false;

    /*auto jump = cocos2d::JumpBy::create(0.5, cocos2d::Vec2(0, 0), 100, 1);
    getSprite()->runAction(jump);*/
    auto physBody = this->getSprite()->getPhysicsBody();
    physBody->applyImpulse(cocos2d::Vec2(0, 100000));
    this->onGround_ = false;
    auto check = dynamic_cast<cocos2d::ui::CheckBox*>(this->
      getSprite()->getChildByName("check"));
    check->setSelected(onGround_);

  }
}
void Hero::moveHoriz(int direction) {
  auto body = this->getSprite()->getPhysicsBody();
  if (onGround_)
    body->setVelocity(cocos2d::Vec2(direction * 0, 0));
  auto moveFunc = [this, body, direction]() {
    if (this->onGround_) {
      body->applyImpulse(cocos2d::Vec2(direction * 3000, 0));
    } else {
      body->applyImpulse(cocos2d::Vec2(direction * 200, 0));
    }
  };
  auto moveAction = cocos2d::CallFunc::create(moveFunc);
  auto forever = cocos2d::RepeatForever::create(
    cocos2d::Sequence::create(moveAction, nullptr));
  forever->setTag(25 + direction);
  this->getSprite()->runAction(forever);
}
