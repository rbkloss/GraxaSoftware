#ifndef _BLOCKS_H_
#define _BLOCKS_H_

#include <functional>
#include <string>

#include "cocos2d.h"



class Blocks {
 public:
  enum BlockTypes { GROUND_BLOCK = 1 };
  static cocos2d::Sprite*  createGroundBlock(const std::string&,
    cocos2d::Node* rootNode);
  static void Blocks::inflateTileMap(cocos2d::Node* rootNode);
  static cocos2d::PhysicsBody* parseShape(const std::string &shape);
};

#endif
