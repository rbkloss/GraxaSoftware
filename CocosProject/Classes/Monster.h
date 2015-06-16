#ifndef _GRAXA_MONSTER_H_
#define _GRAXA_MONSTER_H_

#include "cocos2d.h"

class Monster{
  Monster() = delete;
  static void movimentation(cocos2d::Sprite* monster);
  public:

  static void init(int x, int y, int width, int height, cocos2d::Node* rootNode, const std::string &name);
};

#endif
