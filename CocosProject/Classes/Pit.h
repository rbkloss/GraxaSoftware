#ifndef _PIT_H_
#define _PIT_H_
#include "cocos2d.h"

class PitBlock{
  PitBlock() = delete;
  public:
  static void setup(int x, int y, int width, int height, cocos2d::Node* rootNode, const std::string &name);

};

#endif