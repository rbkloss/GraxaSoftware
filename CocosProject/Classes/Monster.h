#ifndef _GRAXA_MONSTER_H_
#define _GRAXA_MONSTER_H_

#include "cocos2d.h"

class Monster {
  cocos2d::Sprite * sprite_;
  static void movimentation(cocos2d::Sprite* monster);

  int life_ = 5;
  bool alive_ = true;
  protected:
  explicit Monster(cocos2d::Sprite* sprite);
  public:
  static std::shared_ptr<Monster> init(int x, int y, int width, int height, cocos2d::Node* rootNode, const std::string &name);

  void harm(int value);
  void die();
};

#endif
