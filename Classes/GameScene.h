﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BlockPan.h"
#define TOTAL_GAME_TIME 60
#define THINK_TIME 3
USING_NS_CC;
USING_NS_CC_EXT;
class GameScene : public cocos2d::CCLayer
{
private:
	
public:
	CCArray* mSelectBlock;
	int mapW;
	int mapH;
	int mBlockLeft;
	CCProgressTimer *  pr;
	int mTime;
	int mFreeTime;
	CCLayer* timeBoard;
	CCLabelBMFont* scoreTxt;
	BlockPan* mGamePan;

public:
	GameScene();

	~GameScene();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

	static GameScene* shareGameScene();
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
	void restartScene(CCObject* pSender);
	void showGameEnd();
	void countTime(float dt);

	void showGo();

	CCLayer* showTimerBoarder();
	void updateScore(float dt);
	void backToMainMenu();
	void backToMainMenu(CCObject* obj);
	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void updateThinkTimer(float dt);
	virtual void keyBackClicked();//Android 后退键
	virtual void keyMenuClicked();//Android 菜单键
	void ZhenPing(int t,CCNode* baseNode); //震屏效果
};
#endif // __HELLOWORLD_SCENE_H__
