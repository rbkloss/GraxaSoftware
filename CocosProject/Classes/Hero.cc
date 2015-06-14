#include <string>

#include "./Hero.h"
#include "ui/CocosGUI.h"
#include "Blocks.h"


USING_NS_CC;
std::shared_ptr<Hero> Hero::singleton_ = nullptr;

int Hero::tag = 0x1;

Hero::Hero() {
  onGround_ = true;
  jumping_ = false;
}
Hero::~Hero() {}

void Hero::init(cocos2d::Sprite* sprite) {
  struct enable_shared :public Hero {};
  singleton_ = std::make_shared<enable_shared>();
  sprite->setTag(Blocks::HERO_BLOCK);
  singleton_->setSprite(sprite);
  singleton_->addEvents();


  auto physicsBody = cocos2d::PhysicsBody::createBox(sprite->getBoundingBox()
    .size, cocos2d::PhysicsMaterial(0, 0.0f, 2.0f));
  physicsBody->setDynamic(true);
  physicsBody->setRotationEnable(false);
  physicsBody->setContactTestBitmask(0xfffffff);
  //physicsBody->setCategoryBitmask(Blocks::HERO_BLOCK);
  physicsBody->setMass(600);
  physicsBody->setVelocityLimit(150);

  sprite->setPhysicsBody(physicsBody);
}

std::string Hero::getName() {
  static const char* ans = "hero";
  return ans;
}

std::shared_ptr<Hero> Hero::getInstance() {
  return singleton_;
}

void Hero::setSprite(cocos2d::Sprite* sprite) {
  this->sprite_ = sprite;
}

cocos2d::Sprite* Hero::getSprite() {
  return this->sprite_;
}

void Hero::initOptions() {
  //TODO:
}

void Hero::addEvents() {
  keyListener_ = cocos2d::EventListenerKeyboard::create();

  keyListener_->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode code,
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
      default: break;
    }
  };

  keyListener_->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode code,
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
    if (!nodeA)return false;
    if (!nodeB)return false;
    if (this->getName() == nodeA->getName()) {
      isHeroUp = normal.y < 0;
    } else if (this->getName() == nodeB->getName()) {
      isHeroUp = normal.y > 0;
    }
    if (isHeroUp)
      onGround_ = true;
    auto check = static_cast<cocos2d::ui::CheckBox*>(this->getSprite()->
      getChildByName("check"));
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
    if (!nodeA)return;
    if (!nodeB)return;

    bool isHeroUp = false;
    if (this->getName() == nodeA->getName()) {
      isHeroUp = normal.y < 0;
    } else if (this->getName() == nodeB->getName()) {
      isHeroUp = normal.y > 0;
    }
    if (isHeroUp) {
      onGround_ = false;
    }

    auto check = static_cast<cocos2d::ui::CheckBox*>(this->getSprite()->
      getChildByName("check"));
    check->setSelected(onGround_);
  };

  contactListener_ = cocos2d::EventListenerPhysicsContact::create();
  contactListener_->onContactSeperate = onContactSeparate;
  contactListener_->onContactBegin = onContactBegin;
  cocos2d::Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(contactListener_, getSprite());

  cocos2d::Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(keyListener_, getSprite());
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

void Hero::die() {
  sprite_->removeAllChildrenWithCleanup(true);
  cocos2d::Director::getInstance()->getEventDispatcher()
    ->removeEventListener(contactListener_);
  cocos2d::Director::getInstance()->getEventDispatcher()
    ->removeEventListener(keyListener_);
  sprite_->removeFromParentAndCleanup(true);
}

void Hero::increaseScore(int value) {
  this->score_ += value;
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
