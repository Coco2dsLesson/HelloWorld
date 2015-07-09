
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "SettingScene.h"



class HelloWorld : public cocos2d::Layer
{
	
public:
	cocos2d::TMXTiledMap* tiledmap;
	cocos2d::TMXLayer* barrier;
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void setNinjaPosition(cocos2d::Vec2 position);

	void setViewCentrePoint(cocos2d::Vec2 position);
	cocos2d::Vec2 tiledCoordFromPosition(cocos2d::Vec2 position);
//	cocos2d::TMXLayer* barrier;
//	cocos2d::Vec2 tiledCoordFromPosition(cocos2d::Vec2 position);
//	virtual void setNinjaPosition(cocos2d::Vec2 position);
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
