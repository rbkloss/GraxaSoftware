#ifndef _HERO_SPRITE_H__
#define _HERO_SPRITE_H__

#include "cocos2d.h"

class Hero {
	cocos2d::Sprite* sprite_;
protected:
	void setSprite(cocos2d::Sprite* sprite);
	bool onGround_;
	bool jumping_;
public:
	Hero();
	virtual ~Hero();

	static std::shared_ptr<Hero> create(cocos2d::Sprite* sprite);
	static std::string getTag();

	void moveHoriz(int direction);
	void jump();

	void update(float dt);
	
	cocos2d::Sprite* getSprite();

	void initOptions();
	void addEvents();
};

#endif