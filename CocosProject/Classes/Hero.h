#ifndef _HERO_SPRITE_H__
#define _HERO_SPRITE_H__

#include "cocos2d.h"

class Hero {
	cocos2d::Sprite* sprite_;
  static std::shared_ptr<Hero> singleton_;
  cocos2d::EventListenerPhysicsContact* contactListener_;
  cocos2d::EventListenerKeyboard* keyListener_;
  const int ANIMATION = 0xA123;
  
protected:
	void setSprite(cocos2d::Sprite* sprite);
	int onGround_ = 0;
	int score_ = 0;
  size_t life_ = 3;
  const size_t MAX_LIFE_ = 3;

  void animateSetup();
  void animate(const cocos2d::Vector<cocos2d::SpriteFrame*> &frames);
  cocos2d::Vector<cocos2d::SpriteFrame*> idleFrames_;
  cocos2d::Vector<cocos2d::SpriteFrame*> runFrames_;
  cocos2d::Vector<cocos2d::SpriteFrame*> jumpFrames_;
  cocos2d::Vector<cocos2d::SpriteFrame*> shootFrames_;

  bool inHitState_ = false;
  bool dead_ = false;
  bool fired_ = false;
  bool running_ = false;
  int direction_ = 1;

  bool moveEnabled_ = false;
  bool jumpEnabled_ = false;
  bool fireEnabled_ = false;

  Hero();
public:
	
	virtual ~Hero();
  static void init(cocos2d::Node* rootNode, const int x, const int y);
	static std::shared_ptr<Hero> getInstance();
	static std::string getName();
	static int tag;

	void moveHoriz(int direction);
  void enableMove();
  void haltMove(int direction);
  
  void repel(const cocos2d::Vec2 &direction);
  void enableJump();
	void jump();
  void die();

  void fire();
  void enableFire();


  void harm(size_t dmg);
  void heal(size_t amount);

	void increaseScore(int value);

	void update(float dt);
	
	cocos2d::Sprite* getSprite();

	void initOptions();
	void addEvents();
};

#endif