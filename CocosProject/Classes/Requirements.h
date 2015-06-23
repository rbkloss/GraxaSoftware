#ifndef _REQUIREMENTS_H_
#define _REQUIREMENTS_H_

#include "cocos2d.h"

#include <vector>

class Requirements {
	//description groundTruth
	std::vector<bool> requirements_;
	cocos2d::Node* rootNode_;
public:

	static Requirements& getInstance();

	//x and y must be in [0,1]
	void create(cocos2d::Node* rootNode, const std::string &viewName, const std::vector<bool> &reqs);

	int evaluateScore();

};

#endif