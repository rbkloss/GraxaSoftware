#include <string>

#include "./Hero.h"
#include "ui/CocosGUI.h"
#include "Blocks.h"
#include "Projectile.h"


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
    .size, cocos2d::PhysicsMaterial(0.0f, 0.0f, 2.0f));
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
      case (EventKeyboard::KeyCode::KEY_SPACE) : {
        this->fire();
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
    if (!nodeA || !nodeB)return false;

    if (this->getName() == nodeA->getName()) {
      isHeroUp = normal.y < 0;
    } else if (this->getName() == nodeB->getName()) {
      isHeroUp = normal.y > 0;
    }
    if (isHeroUp)
      onGround_ = (onGround_ < 0) ? 1 : ++onGround_;
    auto check = static_cast<cocos2d::ui::CheckBox*>(this->getSprite()->
      getChildByName("check"));
    check->setSelected(onGround_ > 0);
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
    if (!nodeA || !nodeB)return;

    bool isHeroUp = false;
    if (this->getName() == nodeA->getName()) {
      isHeroUp = normal.y < 0;
    } else if (this->getName() == nodeB->getName()) {
      isHeroUp = normal.y > 0;
    }
    if (isHeroUp) {
      --onGround_;
    }

    auto check = static_cast<cocos2d::ui::CheckBox*>(this->getSprite()->
      getChildByName("check"));
    check->setSelected(onGround_ > 0);
  };

  contactListener_ = cocos2d::EventListenerPhysicsContact::create();
  contactListener_->onContactSeperate = onContactSeparate;
  contactListener_->onContactBegin = onContactBegin;
  cocos2d::Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(contactListener_, getSprite());

  cocos2d::Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(keyListener_, getSprite());
}

void Hero::update(float dt) {
  if (life_ == 0) {
    die();
  }
}

void Hero::jump() {
  if (this->onGround_ > 0 && !inHitState_) {
    this->onGround_ = 0;

    /*auto jump = cocos2d::JumpBy::create(0.5, cocos2d::Vec2(0, 0), 100, 1);
    getSprite()->runAction(jump);*/
    auto physBody = this->getSprite()->getPhysicsBody();
    physBody->applyImpulse(cocos2d::Vec2(0, 100000));
    this->onGround_ = false;
    auto check = dynamic_cast<cocos2d::ui::CheckBox*>(this->
      getSprite()->getChildByName("check"));
    check->setSelected(onGround_ > 0);

  }
}

void Hero::die() {
  if (dead_)
    return;
  dead_ = true;
  cocos2d::Director::getInstance()->getEventDispatcher()
    ->removeEventListener(contactListener_);
  cocos2d::Director::getInstance()->getEventDispatcher()
    ->removeEventListener(keyListener_);
  sprite_->removeAllChildrenWithCleanup(true);
  sprite_->removeFromParentAndCleanup(true);
}

void Hero::fire(){
  if (fired_)return;
  auto stepOne = cocos2d::CallFunc::create([this]() {
    int x, y;
    x = sprite_->getPositionX() + sprite_->getContentSize().width / 2;
    y = sprite_->getPositionY();
    HeroProjectile::setup(sprite_->getScene(), x, y, 
    { static_cast<float>(direction_), 0.0f }
    , "images/mfireball.png", { 0.0f, 0.0f, 64.0f, 32.0f });
    fired_ = true;

  });
  auto delay = cocos2d::DelayTime::create(1.0f);
  auto stepTwo = cocos2d::CallFunc::create([this]() {
    fired_ = false;
  });
  sprite_->runAction(cocos2d::Sequence::create(stepOne, 
    delay, stepTwo, nullptr));
}

void Hero::harm(size_t dmg) {
  life_ -= dmg;
  //TODO: Animation
  auto fadein = cocos2d::FadeIn::create(0.5f);
  auto fadeout = cocos2d::FadeOut::create(0.5f);

  auto delay = cocos2d::DelayTime::create(0.5f);

  auto blink = cocos2d::Sequence::create(fadeout, delay, fadein, nullptr);

  sprite_->runAction(blink);
}

void Hero::heal(size_t amount) {
  life_ += amount;
  life_ = std::max(MAX_LIFE_, life_);
  //TODO:
}

void Hero::increaseScore(int value) {
  this->score_ += value;
}

void Hero::moveHoriz(int direction) {
  auto body = this->getSprite()->getPhysicsBody();
  if (onGround_ > 0 && !inHitState_) {
    direction_ = direction;
    body->setVelocity(cocos2d::Vec2(direction * 0, 0));
    auto moveFunc = [this, body, direction]() {
      if (onGround_ > 0 && !inHitState_) {
        body->applyImpulse(cocos2d::Vec2(direction * 3000, 0));
      } else {
        body->applyImpulse(cocos2d::Vec2(direction * 200, 0));
      }
    };
    auto moveAction = cocos2d::CallFunc::create(moveFunc);
    auto forever = cocos2d::RepeatForever::create(
      cocos2d::Sequence::create(moveAction, nullptr));
    forever->setTag(25 + direction);
    getSprite()->runAction(forever);
  }
}

void Hero::repel(const cocos2d::Vec2& direction) {

  auto moveAction = cocos2d::CallFunc::create([this, direction]() {
    auto body = sprite_->getPhysicsBody();
    body->setVelocity({ 0, 0 });
    body->applyImpulse(direction);
    inHitState_ = true;
  });
  auto delay = cocos2d::DelayTime::create(0.1f);
  auto controlAction = cocos2d::CallFunc::create([this]() {
    inHitState_ = false;
  });
  sprite_->runAction(cocos2d::Sequence::create(moveAction, delay, controlAction, nullptr));
}