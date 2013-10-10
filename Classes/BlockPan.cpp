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
	setContentSize(CCSizeMake(BLOCK_PAN_SIZE_W*BLOCK_SIZE_W-5*BLOCK_PAN_SIZE_W,BLOCK_PAN_SIZE_H*BLOCK_SIZE_H-5*BLOCK_PAN_SIZE_H));
	mPanBg = createPanBg();
	addChild(mPanBg);
	return true;
}

CCLayer* BlockPan::createPanBg()
{
	CCLayer* panBg = CCLayer::create();
	int maxW = BLOCK_PAN_SIZE_W;
	int maxH = BLOCK_PAN_SIZE_H;
	int blockW = BLOCK_SIZE_W;
	int blockH = BLOCK_SIZE_H;
	for (int i = 0;i<maxH;i++)
	{
		for (int j = 0;j<maxW;j++)
		{
			CCSprite* blockBg = CCSprite::create(RESOURCE_PATH_CRYSTRAL("blocktiles.png"));
			blockBg->setPosition(ccp(i*blockW-5*i,j*blockH-5*j));
			blockBg->setAnchorPoint(ccp(0,0));
			panBg->addChild(blockBg);
		}
	}
	return panBg;
}
