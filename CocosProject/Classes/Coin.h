#ifndef _GRAXA_COIN_H_
#define _GRAXA_COIN_H_

#include "cocos2d.h"
#include "./Hero.h"

class Coin {
  Hero* hero_;
  cocos2d::Sprite* sprite_;
  cocos2d::EventListenerPhysicsContact* contactListener_;
  void coinContact(cocos2d::Sprite* coin);
  public:
  Coin();
  virtual ~Coin();
  
  void init(cocos2d::Node* rootNode, const int x, const int y, const Hero* hero);
};

#endif
