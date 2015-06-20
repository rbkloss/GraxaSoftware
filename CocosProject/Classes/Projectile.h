#ifndef _GRAXA_HERO_PROJECTILE_H_
#define _GRAXA_HERO_PROJECTILE_H_

#include "cocos2d.h"

class Monster;

class HeroProjectile {
  static void animate();
  static void monsterCollision(cocos2d::Sprite* sprite, std::shared_ptr<Monster> monster);
  static void groundCollision(cocos2d::Sprite* sprite, cocos2d::Node* ground);
  public:
  static void setup(cocos2d::Node* rootNode, int x, int y,
    const cocos2d::Vec2 &direction, const std::string &imageFilename,
    const cocos2d::Rect &from);

};

#endif