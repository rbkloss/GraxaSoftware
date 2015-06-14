#ifndef _HERO_SPRITE_H__
#define _HERO_SPRITE_H__

#include "cocos2d.h"

class Hero {
	cocos2d::Sprite* sprite_;
protected:
	void setSprite(cocos2d::Sprite* sprite);
	bool onGround_;
	bool jumping_;
	int score_ = 0;
public:
	Hero();
	virtual ~Hero();

	static std::shared_ptr<Hero> create(cocos2d::Sprite* sprite);
	static std::string getName();
	static int tag;

	void moveHoriz(int direction);
	void jump();

	void increaseScore(int value);

	void update(float dt);
	
	cocos2d::Sprite* getSprite();

	void initOptions();
	void addEvents();
};

#endif