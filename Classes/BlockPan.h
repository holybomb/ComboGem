#pragma once
#include "cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;
class BlockPan : public CCLayer
{

public:
	BlockPan(void);
	~BlockPan(void);
	bool init();
	CREATE_FUNC(BlockPan);
	CCLayer* createPanBg();
	CCLayer* mPanBg;
};

