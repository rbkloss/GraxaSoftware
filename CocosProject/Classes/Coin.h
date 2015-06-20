#ifndef _GRAXA_COIN_H_
#define _GRAXA_COIN_H_

#include "cocos2d.h"

class Coin {
  cocos2d::Sprite* sprite_;
  cocos2d::EventListenerPhysicsContact* contactListener_;
  void coinContact(cocos2d::Sprite* coin);
  void animate(const std::string& imageName, const cocos2d::Rect& initRect
    , const int nStates);
  public:
  Coin();
  virtual ~Coin();
  
  void init(cocos2d::Node* rootNode, const int x, const int y);
};

#endif
