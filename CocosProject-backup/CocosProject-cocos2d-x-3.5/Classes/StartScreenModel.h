#ifndef _START_SCREEN_MODEL_H_
#define _START_SCREEN_MODEL_H_

#include "cocos2d.h"

class StartScreenModel {
	cocos2d::Scene* scene_;
public:
	StartScreenModel();
	virtual ~StartScreenModel();

	static void startGameListener();
	static void openAbout();
};

#endif