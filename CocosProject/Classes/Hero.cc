#include <string>

#include "./Hero.h"
#include "ui/CocosGUI.h"
#include "Blocks.h"
#include "Projectile.h"

#include "cocos2d.h"


#include "SimpleAudioEngine.h"

USING_NS_CC;
std::shared_ptr<Hero> Hero::singleton_ = nullptr;

int Hero::tag = 0x1;

void Hero::animateSetup() {

  float w = 32, h = 32;
  float x = 0, y = 0;
  const int nStates = 4;
  idleFrames_.reserve(nStates);
  for (int i = 0; i < nStates; ++i) {
    auto frame = cocos2d::SpriteFrame::create("images/hero/idle.png", { x + w*i, y, w, h });
    idleFrames_.pushBack(frame);
  }

  runFrames_.reserve(nStates);
  for (int i = 0; i < nStates; ++i) {
    auto frame = cocos2d::SpriteFrame::create("images/hero/run.png", { x + w*i, y, w, h });
    runFrames_.pushBack(frame);
  }

  for (int i = 0; i < 1; ++i) {
    auto frame = cocos2d::SpriteFrame::create("images/hero/jump.png", { x + w*i, y, w, h });
    jumpFrames_.pushBack(frame);
  }

  for (int i = 0; i < 1; ++i) {
    auto frame = cocos2d::SpriteFrame::create("images/hero/shoot.png", { x + w*i, y, w, h });
    shootFrames_.pushBack(frame);
  }

  animate(idleFrames_);
}

void Hero::animate(const cocos2d::Vector<cocos2d::SpriteFrame*> &frames) {
  sprite_->stopActionByTag(ANIMATION);
  auto animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.1f);
  auto animate = cocos2d::Animate::create(animation);

  auto foreverAction = cocos2d::RepeatForever::create(animate);
  foreverAction->setTag(ANIMATION);
  sprite_->runAction(foreverAction);
}

Hero::Hero() {
  onGround_ = 0;
}
Hero::~Hero() {}

void Hero::init(cocos2d::Node* rootNode, const int x, const int y) {
  struct enable_shared :public Hero {};
  singleton_ = std::make_shared<enable_shared>();
  auto sprite = cocos2d::Sprite::create();
  sprite->setPosition(x, y);
  sprite->setName(getName());
  sprite->setTag(Blocks::HERO_BLOCK);

  singleton_->setSprite(sprite);
  singleton_->animateSetup();
  singleton_->addEvents();

  auto physicsBody = cocos2d::PhysicsBody::createBox({ 32, 32 }, cocos2d::PhysicsMaterial(0.0f, 0.0f, 2.0f));
  physicsBody->setDynamic(true);
  physicsBody->setRotationEnable(false);
  physicsBody->setContactTestBitmask(0xfffffff);
  //physicsBody->setCategoryBitmask(Blocks::HERO_BLOCK);
  physicsBody->setMass(600);
  physicsBody->setVelocityLimit(150);

  sprite->setPhysicsBody(physicsBody);
  rootNode->addChild(sprite);
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
        direction_ = -1;
        sprite_->setFlippedX(true);
        break;
      }
      case (cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) : {
        this->moveHoriz(1);
        direction_ = 1;
        sprite_->setFlippedX(false);
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
        haltMove(-1);
        break;
      }
      case (cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) : {
        haltMove(1);
        break;
      }
      default:
        break;
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
      if (onGround_ <= 0) {
        onGround_ = 1;
        if (running_)
          animate(runFrames_);
        else
          animate(idleFrames_);

      } else
        ++onGround_;
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
  if (dead_)
    return;
  auto root = sprite_->getParent();
  auto coinSprite = root->getChildByName("coinHud");


  auto coinLabel = static_cast<cocos2d::ui::Text*>(coinSprite->getChildByName("coinsLabel"));
  coinLabel->setString(std::to_string(score_));
}

void Hero::jump() {
  if (!jumpEnabled_)return;
  if (this->onGround_ > 0 && !inHitState_) {
    this->onGround_ = 0;
    animate(jumpFrames_);
    /*auto jump = cocos2d::JumpBy::create(0.5, cocos2d::Vec2(0, 0), 100, 1);
    getSprite()->runAction(jump);*/
    auto physBody = this->getSprite()->getPhysicsBody();
    physBody->applyImpulse(cocos2d::Vec2(0, 100000));
    this->onGround_ = false;
  }
}

void Hero::die() {
  if (dead_)
    return;
  dead_ = true;

  auto root = sprite_->getParent();
  auto heartSprite = root->getChildByName("lifeHud");
  auto lifeLabel = static_cast<cocos2d::ui::Text*>(heartSprite->getChildByName("heartLabel"));
  lifeLabel->setString(std::to_string(0));

  cocos2d::Director::getInstance()->getEventDispatcher()
    ->removeEventListener(contactListener_);
  cocos2d::Director::getInstance()->getEventDispatcher()
    ->removeEventListener(keyListener_);
  sprite_->removeAllChildrenWithCleanup(true);
  sprite_->removeFromParentAndCleanup(true);
}

void Hero::fire() {
  if (!fireEnabled_ || fired_)return;

  auto stepOne = cocos2d::CallFunc::create([this]() {
    animate(shootFrames_);
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("sound/shot.mp3", false, 0.0f, 0.0f, -0.5f);
    int x, y;
    x = sprite_->getPositionX() + direction_*
      (sprite_->getContentSize().width / 2 + 32);

    y = sprite_->getPositionY();
    HeroProjectile::setup(sprite_->getScene(), x, y,
    { static_cast<float>(direction_), 0.0f }
    , "images/mfireball.png", { 0.0f, 0.0f, 64.0f, 32.0f });
    fired_ = true;

  });
  auto delay = cocos2d::DelayTime::create(0.1f);
  auto stepTwo = cocos2d::CallFunc::create([this]() {
    if (onGround_ <= 0)
      animate(jumpFrames_);
    else if (running_)
      animate(runFrames_);
    else
      animate(idleFrames_);
  });
  auto delayLong = cocos2d::DelayTime::create(0.8f);
  auto stepThree = cocos2d::CallFunc::create([this]() {
    fired_ = false;
  });

  sprite_->runAction(cocos2d::Sequence::create(stepOne,
    delay, stepTwo, delayLong, stepThree, nullptr));
}

void Hero::enableFire() {
  fireEnabled_ = true;
}

void Hero::harm(size_t dmg) {
  life_ -= dmg;
  //TODO: Animation
  auto fadein = cocos2d::FadeIn::create(0.5f);
  auto fadeout = cocos2d::FadeOut::create(0.5f);

  auto delay = cocos2d::DelayTime::create(0.5f);

  auto blink = cocos2d::Sequence::create(fadeout, delay, fadein, nullptr);

  sprite_->runAction(blink);
  if (!dead_) {
    auto root = sprite_->getParent();
    auto heartSprite = root->getChildByName("lifeHud");
    auto lifeLabel = static_cast<cocos2d::ui::Text*>(heartSprite->getChildByName("heartLabel"));
    lifeLabel->setString(std::to_string(life_));
  }
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
  if (!moveEnabled_) return;
  auto body = this->getSprite()->getPhysicsBody();
  if (onGround_ > 0 && !inHitState_) {
    body->setVelocity(cocos2d::Vec2(direction * 0, 0));
    running_ = true;
    animate(runFrames_);
  }
  auto moveFunc = [this, body, direction]() {
    running_ = true;
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

void Hero::enableMove() {
  moveEnabled_ = true;
}

void Hero::haltMove(int direction) {
  this->getSprite()->stopActionByTag(25 + direction);
  if (this->onGround_) {
    this->getSprite()->getPhysicsBody()->
      applyImpulse(cocos2d::Vec2((-direction) * 3000, 0));
  } else {
    this->getSprite()->getPhysicsBody()->
      applyImpulse(cocos2d::Vec2((-direction) * 300, 0));
  }
  if (onGround_ > 0)
    animate(idleFrames_);
  running_ = false;
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

void Hero::enableJump() {
  jumpEnabled_ = true;
}