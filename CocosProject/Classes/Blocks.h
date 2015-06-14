#ifndef _BLOCKS_H_
#define _BLOCKS_H_

#include <string>

#include "cocos2d.h"


class Hero;

class Blocks {
  public:
  enum BlockTypes {
    HERO_BLOCK = 0x1,
    GROUND_BLOCK = 0x2,
    COIN_BLOCK = 0x4,
    PIT_BLOCK = 0x8
  };
  static cocos2d::Sprite*  createGroundBlock(const std::string&,
    cocos2d::Node* rootNode);
  static void inflateTileMap(cocos2d::Node* rootNode);
  static void parseCollidables(cocos2d::TMXObjectGroup* collisionsGroup,
    cocos2d::TMXTiledMap* map);
  static void parseCoins(cocos2d::Node* rootNode, cocos2d::TMXObjectGroup* coinsGroup, cocos2d::TMXTiledMap* map);
  static void parsePits(cocos2d::Node* rootNode, cocos2d::TMXObjectGroup* pitsGroup,
    cocos2d::TMXTiledMap* map);

  static cocos2d::PhysicsBody* parseShape(const std::string &shape);

};

#endif
