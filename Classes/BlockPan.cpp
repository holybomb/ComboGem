#include "BlockPan.h"
#include "GameDefine.h"

BlockPan::BlockPan(void)
{
}


BlockPan::~BlockPan(void)
{
}

bool BlockPan::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	mPanBg = createPanBg();
	addChild(mPanBg);
	return true;
}

CCLayer* BlockPan::createPanBg()
{
	int maxW = BLOCK_PAN_SIZE_W;
	int maxH = BLOCK_PAN_SIZE_H;
	for (int i = 0;i<maxH;i++)
	{
		for (int j = 0;j<maxW;j++)
		{
			CCSprite* blockBg = CCSprite::create(RESOURCE_PATH_CRYSTRAL("blocktiles.png"));
			blockBg->setPosition(ccp(0,0));
		}
	}
}
