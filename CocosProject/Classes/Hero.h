#ifndef _HERO_SPRITE_H__
#define _HERO_SPRITE_H__

#include "cocos2d.h"

class Hero {
	cocos2d::Sprite* sprite_;
  static std::shared_ptr<Hero> singleton_;
  cocos2d::EventListenerPhysicsContact* contactListener_;
  cocos2d::EventListenerKeyboard* keyListener_;
protected:
	void setSprite(cocos2d::Sprite* sprite);
	int onGround_ = 0;
	bool jumping_;
	int score_ = 0;
  size_t life_ = 3;
  const size_t MAX_LIFE_ = 3;

  bool inHitState_ = false;
  bool dead_ = false;
  bool fired_ = false;
  int direction_ = 1;

  Hero();
public:
	
	virtual ~Hero();
  static void init(cocos2d::Sprite* sprite);
	static std::shared_ptr<Hero> getInstance();
	static std::string getName();
	static int tag;

	void moveHoriz(int direction);
  void repel(const cocos2d::Vec2 &direction);
	void jump();
  void die();

  void fire();


  void harm(size_t dmg);
  void heal(size_t amount);

	void increaseScore(int value);

	void update(float dt);
	
	cocos2d::Sprite* getSprite();

	void initOptions();
	void addEvents();
};

#endif