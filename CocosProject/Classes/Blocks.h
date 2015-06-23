#ifndef _BLOCKS_H_
#define _BLOCKS_H_

#include "cocos2d.h"


class Monster;

class Blocks {
  public:
  enum BlockTypes {
    HERO_BLOCK = 0x1,
    GROUND_BLOCK = 0x2,
    COIN_BLOCK = 0x4,
    PIT_BLOCK = 0x8,
    MONSTER_BLOCK = 0x10
  };
  Blocks() = default;
  ~Blocks();

  std::unordered_map<std::string, std::shared_ptr<Monster>> monsters_;



  cocos2d::Sprite*  createGroundBlock(const std::string&,
    cocos2d::Node* rootNode);
  void inflateTileMap(cocos2d::Node* rootNode);

  void parseCollidables(cocos2d::Node* rootNode, cocos2d::TMXObjectGroup* collisionsGroup,cocos2d::TMXTiledMap* map);
  void parseCoins(cocos2d::Node* rootNode, cocos2d::TMXObjectGroup* coinsGroup, cocos2d::TMXTiledMap* map);
  void parsePits(cocos2d::Node* rootNode, cocos2d::TMXObjectGroup* pitsGroup, cocos2d::TMXTiledMap* map);
  void parseMonsters(cocos2d::Node* rootNode, cocos2d::TMXObjectGroup* monstersGroup, cocos2d::TMXTiledMap* map);
  void parseHero(cocos2d::Node* rootNode, cocos2d::TMXObjectGroup* heroGroup, cocos2d::TMXTiledMap* map);

  static cocos2d::PhysicsBody* parseShape(const std::string &shape);

  std::shared_ptr<Monster> getMonsterByName(const std::string &name);

};

#endif
