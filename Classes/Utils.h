#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Utils
{
public:
	static CCRect getRect(CCNode* pNode);
	static CCRect getRect(CCNode* pNode,CCNode* pBase);
	static int randomBetweenInt(int max, int min);
	static float randomBetweenFloat(float min, float max);
};

