#ifndef _STAGE_ONE_SCENE_H_
#define _STAGE_ONE_SCENE_H_

#include "cocos2d.h"
#include <memory>

class Hero;
class StageOneScene : public cocos2d::Layer {
	std::shared_ptr<Hero> hero_;
public:
	// Creates An auto-release scene object for the first stage
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init() override;

	void update(float dt) override;

	// implement the "static create()" method manually
	CREATE_FUNC(StageOneScene);
};

#endif