// Test_CocosProject.cpp : Defines the entry point for the console application.
//

#include "gtest\gtest.h"

#include "cocos2d.h"

#if _MSC_VER > 1700
#pragma comment(lib,"libcocos2d_2013.lib")
#pragma comment(lib,"libbox2d_2013.lib")
#pragma comment(lib,"libSpine_2013.lib")
#else
#pragma comment(lib,"libcocos2d_2012.lib")
#pragma comment(lib,"libbox2d_2012.lib")
#pragma comment(lib,"libSpine_2012.lib")
#endif

TEST(SumTest, TwoTwo) {
	EXPECT_EQ(4, 2 + 2);
}