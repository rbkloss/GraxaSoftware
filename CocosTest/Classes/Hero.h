#ifndef _HERO_SPRITE_H__
#define _HERO_SPRITE_H__

#include "cocos2d.h"

class Hero : public cocos2d::Sprite {
public:
	Hero();
	virtual ~Hero();

	static Hero* create();

	void initOptions();
	void addEvents();
};

#endif