#ifndef __VILLAIN_SPRITE_H__
#define __VILLAIN_SPRITE_H__

#include "cocos2d.h"

class VillainSprite : public cocos2d::Sprite {
	void registerEvents();
public:
	VillainSprite();
	~VillainSprite();

	static VillainSprite* create();
	
	
};


#endif