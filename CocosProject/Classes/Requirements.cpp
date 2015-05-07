
#include "Requirements.h"

#include "ui\CocosGUI.h"

#include <cassert>

Requirements& Requirements::getInstance() {
	static Requirements req;
	return req;
}


void Requirements::create(cocos2d::Node* rootNode, const std::string &viewName, const std::vector<bool> &reqs) {
	requirements_ = reqs;
	rootNode_ = rootNode->getChildByName(viewName);
}

int Requirements::evaluateScore() {
	auto children = rootNode_->getChildren();
	int counter = 0;
	int score = 0;
	for (auto child : children) {
		//children are all labels
		auto checkBox = (cocos2d::ui::CheckBox*) (child->getChildren().at(0));
		auto ans = checkBox->isSelected();
		if (requirements_[counter++] == ans)++score;
	}
	return score;
}