#ifndef _REQUIREMENTS_H_
#define _REQUIREMENTS_H_

#include "cocos2d.h"
#include "ui\CocosGUI.h"

#include <vector>

class Requirement;

class Requirements {
  //description groundTruth
  cocos2d::Vector<Requirement*> requirements_;;
  cocos2d::ui::ListView* rootNode_;
  public:

  static Requirements& getInstance();

  //x and y must be in [0,1]
  void create(cocos2d::ui::ListView* rootNode, const std::vector<std::pair<std::string, bool>> & reqs, const std::vector<std::function<void(void)>> &callback);

  void evaluate();

};

#endif