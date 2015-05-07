#ifndef _BLOCKS_H_
#define _BLOCKS_H_

#include "cocos2d.h"

#include <functional>

class Blocks {

public:
	static cocos2d::Sprite*  createGroundBlock(const std::string&, cocos2d::Node* rootNode);
};

#endif