#ifndef _BLOCKS_H_
#define _BLOCKS_H_

#include <string>

#include "cocos2d.h"


class Hero;

class Blocks {
  public:
  enum BlockTypes {
    GROUND_BLOCK = 1
  };
  static cocos2d::Sprite*  createGroundBlock(const std::string&,
    cocos2d::Node* rootNode);
  static void inflateTileMap(cocos2d::Node* rootNode, const Hero* hero);
  static void parseCollidables(cocos2d::TMXObjectGroup* collisionsGroup,
    cocos2d::TMXTiledMap* map);
  static void parseCoins(cocos2d::Node* rootNode, cocos2d::TMXObjectGroup* coingsGroup,
    cocos2d::TMXTiledMap* map, const Hero* hero);
  static cocos2d::PhysicsBody* parseShape(const std::string &shape);

};

#endif
