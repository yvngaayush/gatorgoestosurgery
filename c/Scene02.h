#ifndef __SCENE_02_H__
#define __SCENE_02_H__

#include "ResourceDefinitions.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

class Scene02 : public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	FrameNav* frameNav;
	FrameNav* fn;
    Menu* menu;
    Json *script;
    cocos2d::Sprite* textBox;
    cocos2d::Sprite* glow;
    cocos2d::MenuItemImage* brace;
	void gotoNextScene(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
    void nextText(Ref* pSender);
    void prevText(Ref* pSender);
    void braceletButtonCallBack(Ref* pSender);
    void gotoDrawCallBack(Ref* pSender);
    void waitDrawCallBack(float dt);
    void runBegin();
    
    void toggleIcon(float dt);

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
	CREATE_FUNC(Scene02);
};
#endif // __SCENE_ONE_H__
