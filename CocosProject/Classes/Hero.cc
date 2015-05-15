#include <string>

#include "Hero.h"
#include "ui/CocosGUI.h"

#include "Blocks.h"


USING_NS_CC;

Hero::Hero() {
  onGround_ = true;
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
    .size, cocos2d::PhysicsMaterial(0, 0.0f, 0.85f));
  physicsBody->setDynamic(true);
  physicsBody->setRotationEnable(false);
  physicsBody->setContactTestBitmask(0xfffffff);
  physicsBody->setMass(600);
  physicsBody->setVelocityLimit(100);

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
  auto isHeroUp = [](cocos2d::Node* hero,
    cocos2d::Node* other, cocos2d::Vec2 &normal) {
    return (normal.y > 0);
  };
  /*auto onContactBegin = [=](cocos2d::PhysicsContact& contact) {
    auto normal = contact.getContactData()->normal;
    auto shapeA = contact.getShapeA();
    auto bodyA = shapeA->getBody();
    auto shapeB = contact.getShapeB();
    auto bodyB = shapeB->getBody();

    auto nodeA = bodyA->getNode();
    auto nodeB = bodyB->getNode();
    if (this->getTag() == nodeA->getName()) {
    if (isHeroUp(nodeA, nodeB, normal)) {
    this->onGround_ = true;
    }
    } else if (this->getTag() == nodeB->getName()) {
    if (isHeroUp(nodeB, nodeA, normal)) {
    this->onGround_ = true;
    }
    }
    if (this->onGround_) {
    auto check = (cocos2d::ui::CheckBox*)this->getSprite()->getChildByName("check");
    check->setSelected(true);
    }
    return true;
    };*/

  /*auto contactListener = cocos2d::EventListenerPhysicsContact::create();
  contactListener->onContactBegin = onContactBegin;
  contactListener->onContactSeperate = onContactEnd;*/

  //cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, getSprite());

  cocos2d::Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(listener, getSprite());
}

void Hero::update(float dt) {
  auto sprite = getSprite();
  auto scene = sprite->getScene();
  auto world = scene->getPhysicsWorld();
  auto groundBellow = [this](PhysicsWorld& world,
    const PhysicsRayCastInfo& info, void* data)->bool {
    auto shape = info.shape;
    auto body = shape->getBody();
    auto node = body->getNode();


    if (node->getTag() & Blocks::GROUND_BLOCK) {
      this->onGround_ = true;
    }
    auto check = (cocos2d::ui::CheckBox*)this->
      getSprite()->getChildByName("check");
    check->setSelected(this->onGround_);

    return true;
  };

  auto center = getSprite()->getPosition();
  auto sz = getSprite()->getBoundingBox().size;
  center.add(cocos2d::Vec2(0, -(sz.height / 2)));
  cocos2d::Vec2 end = center;
  end.add(cocos2d::Vec2(0, -2));
  world->rayCast(groundBellow, center, end, nullptr);
}

void Hero::jump() {
  if (this->onGround_) {
    this->onGround_ = false;
    /*auto jump = cocos2d::JumpBy::create(0.5, cocos2d::Vec2(0, 0), 100, 1);
    getSprite()->runAction(jump);*/
    auto physBody = this->getSprite()->getPhysicsBody();
    physBody->applyImpulse(cocos2d::Vec2(0, 60000));
    this->onGround_ = false;
    auto check = (cocos2d::ui::CheckBox*)this->
      getSprite()->getChildByName("check");
    check->setSelected(onGround_);
  }
}
void Hero::moveHoriz(int direction) {
  auto body = this->getSprite()->getPhysicsBody();
  if (onGround_)
    body->setVelocity(cocos2d::Vec2(direction * 25, 0));
  auto moveFunc = [this, body, direction]() {
    if (this->onGround_) {
      body->applyImpulse(cocos2d::Vec2(direction * 1000, 0));
    } else {
      body->applyImpulse(cocos2d::Vec2(direction * 100, 0));
    }
  };
  auto moveAction = cocos2d::CallFunc::create(moveFunc);
  auto forever = cocos2d::RepeatForever::create(
    cocos2d::Sequence::create(moveAction, nullptr));
  forever->setTag(25 + direction);
  this->getSprite()->runAction(forever);
}
