﻿#include "GameScene.h"
#include "GameData.h"
#include "MainMenuScene.h"
USING_NS_CC;
USING_NS_CC_EXT;
static GameScene* gameScene = NULL;
GameScene* GameScene::shareGameScene()
{
	if (!gameScene)
	{
		gameScene = new GameScene();
	}
	return gameScene;
}
CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    // 'layer' is an autorelease object
	gameScene = GameScene::create();

    // add layer as a child to scene
    scene->addChild(gameScene);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(RESOURCE_PATH_AUDIO("loop.mp3"),true);
	GameData::shareData()->init();
	mTime = -4;
	mSelectBlock = NULL;
	CCSprite* bgSprite = CCSprite::create(RESOURCE_PATH_GAME("background.png"));
	bgSprite->setAnchorPoint(ccp(0.0f,0.0f));
    this->addChild(bgSprite);
	mGamePan = BlockPan::create();
	this->addChild(mGamePan);
	mGamePan->setPosition(ccp(DESIGN_SCREEN_SIZE_W/2-mGamePan->getContentSize().width/2,(DESIGN_SCREEN_SIZE_H-158)/2-mGamePan->getContentSize().height/2));
	timeBoard = showTimerBoarder();
	timeBoard->setPosition(ccp(0,DESIGN_SCREEN_SIZE_H+158));
	timeBoard->runAction(CCMoveTo::create(0.3f,ccp(0,DESIGN_SCREEN_SIZE_H-158)));
	addChild(timeBoard,10);
    return true;
}
void GameScene::countTime(float dt)
{
	mTime++;
	CCLOG("countTime = %d",mTime);
	if (mTime == -3)
	{
		
	}
	if(mTime == -1)
	{
		showGo();

	}
	if(mTime==0)
	{
		pr->setPercentage(0);
		CCProgressTo* to = CCProgressTo::create(TOTAL_GAME_TIME,100);
		pr->setReverseProgress(true);
		pr->runAction(to);
		mFreeTime = 0;
		schedule(schedule_selector(GameScene::updateThinkTimer),1);
	}
	
	if (mTime==TOTAL_GAME_TIME*80/100)
	{
		if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(RESOURCE_PATH_AUDIO("timer.wav"),true);
	}
	if (mTime>=TOTAL_GAME_TIME*80/100)
	{
		pr->runAction(CCBlink::create(0.3f,4));
	}
	if (mTime>=TOTAL_GAME_TIME)
	{
		showGameEnd();
		unschedule(schedule_selector(GameScene::countTime));
	}
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void GameScene::restartScene( CCObject* pSender )
{
	mFreeTime = -1;
	timeBoard->runAction(CCMoveTo::create(0.3f,ccp(0,DESIGN_SCREEN_SIZE_H+158)));
	this->runAction(CCSequence::create(CCDelayTime::create(1.5f),CCCallFunc::create(this,callfunc_selector(GameScene::backToMainMenu)),NULL));
	SimpleAudioEngine::sharedEngine()->preloadEffect( RESOURCE_PATH_AUDIO("click.wav"));
}
void GameScene::backToMainMenu(CCObject* obj)
{
	CCDirector::sharedDirector()->sharedDirector()->replaceScene(MainScene::scene());
}

void GameScene::backToMainMenu()
{
	backToMainMenu(NULL);
}

CCLayer* GameScene::showTimerBoarder()
{
	CCLayer* board = CCLayer::create();
	CCSprite* boardBG = CCSprite::create(RESOURCE_PATH_GAME("header.png"));
	boardBG->setPosition(ccp(DESIGN_SCREEN_SIZE_W/2,0));
	boardBG->setAnchorPoint(ccp(0.5f,0));
	board->addChild(boardBG);
	CCMenuItemImage* imageItem = CCMenuItemImage::create(RESOURCE_PATH_GAME("btn-pause.png"),RESOURCE_PATH_GAME("btn-pause-down.png"), this,menu_selector(GameScene::restartScene));
	imageItem->setAnchorPoint(ccp(0,1));
	CCMenu* menu = CCMenu::create(imageItem,NULL);
	menu->setAnchorPoint(ccp(0,1));
	menu->setPosition(ccp(0,158));
	pr = CCProgressTimer::create(CCSprite::create(RESOURCE_PATH_GAME("timer.png")));
	pr->setPosition(ccp(DESIGN_SCREEN_SIZE_W/2,16));
	pr->setAnchorPoint(ccp(0.5,0));
	pr->setPercentage(1.0f);
	pr->setType(kCCProgressTimerTypeBar);
	pr->setMidpoint(ccp(1,0));
	pr->setBarChangeRate(ccp(1,0));
	this->schedule(schedule_selector(GameScene::countTime),1.0f);

	scoreTxt = CCLabelBMFont::create("0",RESOURCE_PATH_FONT("scorefont.fnt"));
	scoreTxt->setAnchorPoint(ccp(1,0.5f));
	scoreTxt->setScale(1.0f);
	scoreTxt->setAlignment(kCCTextAlignmentRight);
	scoreTxt->setPosition(ccp(DESIGN_SCREEN_SIZE_W,110));
	board->addChild(scoreTxt,10);
	board->addChild(pr);
	board->addChild(menu);
	return board;
}
void GameScene::showGameEnd()
{
	mFreeTime = -1;
	timeBoard->runAction(CCMoveTo::create(0.3f,ccp(0,DESIGN_SCREEN_SIZE_H+158)));
	CCLayer* gameEndLayer = CCLayer::create();
	CCSprite* bgSprite = CCSprite::create(RESOURCE_PATH_MENU("about-fade.png"));
	scoreTxt = CCLabelBMFont::create(GameData::shareData()->getScoreString(),RESOURCE_PATH_FONT("scorefont.fnt"));
	scoreTxt->setPosition(ccp(DESIGN_SCREEN_SIZE_W/2,700));
	scoreTxt->setScale(0.0f);
	CCScaleTo* scaleTo = CCScaleTo::create(0.9f,2.5f);
	CCEaseElasticInOut* scoreEff = CCEaseElasticInOut::create(scaleTo);
	scoreTxt->runAction(scoreEff);
	if(!scoreTxt->getParent())
		gameEndLayer->addChild(scoreTxt);
	bgSprite->setAnchorPoint(ccp(0,0));
	gameEndLayer->addChild(bgSprite);
	CCLabelTTF* txt = CCLabelTTF::create("Game End",RESOURCE_PATH_FONT("Marker Felt.ttf"),40.0f);
	txt->setPosition(ccp(DESIGN_SCREEN_SIZE_W/2,DESIGN_SCREEN_SIZE_H/2));
	gameEndLayer->addChild(txt);
	CCMenuItemImage* imageItem = CCMenuItemImage::create("CloseNormal.png","CLoseSelected.png", this,menu_selector(GameScene::backToMainMenu));
	CCMenu* menu = CCMenu::create(imageItem,NULL);
	menu->setAnchorPoint(ccp(0,0));
	menu->setPosition(ccp(DESIGN_SCREEN_SIZE_W/2,300));
	imageItem->setScale(3.0f);
	gameEndLayer->addChild(menu);
	this->addChild(gameEndLayer,100,this->getChildrenCount());
	if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(RESOURCE_PATH_AUDIO("endgame.wav"));
}
void GameScene::updateScore(float dt)
{
	scoreTxt->setCString(CCString::createWithFormat("%d",GameData::shareData()->getScore())->getCString());
}
GameScene::GameScene()
{

}

void GameScene::showGo()
{
	CCSprite* goSprite = CCSprite::create(RESOURCE_PATH_GAME("go.png"));
	goSprite->setPosition(ccp(DESIGN_SCREEN_SIZE_W/2,DESIGN_SCREEN_SIZE_H/2));
	this->addChild(goSprite);
	CCScaleTo* scaleBig = CCScaleTo::create(0.5f,1);
	CCScaleTo* scaleSmall = CCScaleTo::create(0.0001f,0);
	CCEaseBounceOut* eff = CCEaseBounceOut::create(scaleBig);
	eff->bounceTime(3);
	CCSequence* act = CCSequence::create(CCHide::create(),scaleSmall,CCShow::create(),eff,CCDelayTime::create(0.2f),CCScaleTo::create(0.5f,0),CCRemoveSelf::create(),NULL);
	goSprite->setVisible(false);
	goSprite->runAction(act);
	setTouchEnabled(true);
}


void GameScene::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-1,false);
}


bool GameScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	
	return false;
}

void GameScene::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	
}
void GameScene::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

GameScene::~GameScene()
{
	
}

void GameScene::ZhenPing(int t,CCNode* baseNode)
{
	CCScene* f = CCDirector::sharedDirector()->getRunningScene();
	CCPoint size = baseNode->getPosition();
	CCMoveTo* left1 = CCMoveTo::create(0.05f,ccp(size.x+5,size.y));
	CCMoveTo* right1 = CCMoveTo::create(0.05f,ccp(size.x-5,size.y));
	CCMoveTo* top1 = CCMoveTo::create(0.05f,ccp(size.x,size.y+5));
	CCMoveTo* rom1 = CCMoveTo::create(0.05f,ccp(size.x,size.y-5));
	CCFiniteTimeAction* action3 = CCSequence::create(left1,right1,top1,rom1,NULL);
	baseNode->runAction(action3);
}

void GameScene::updateThinkTimer(float dt)
{
	if(mFreeTime < 0)
	{
		return;
	}

	mFreeTime++;
	if(mFreeTime>THINK_TIME)
	{
		mFreeTime = -1;
	}
}

void GameScene::keyBackClicked()
{

}

void GameScene::keyMenuClicked()
{

}
