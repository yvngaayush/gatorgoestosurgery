#ifndef __SCENE_11_H__
#define __SCENE_11_H__

#include "ResourceDefinitions.h"
#include "editor-support/spine/Json.h"
#include "FrameNav.h"

class Scene11 : public Layer {
public:
	
	static Scene* createScene();
	virtual bool init();
	void gotoNextScene(Ref* pSender);
    void openDoors(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
    FrameNav* frameNav;
    FrameNav* fn;
    Menu* menu;
    void nextButtonAppears(float dt);
    void waitNextScene(float dt);
    void nextText(Ref* pSender);
    void prevText(Ref* pSender);
    cocos2d::Sprite* textBox;
    cocos2d::Sprite* glow;
    cocos2d::Sprite* doorhandle;
    cocos2d::Sprite* doorhandle2;
    bool glowon;
    void textAppears(float dt);
    Json* script;
    
	CREATE_FUNC(Scene11);
};
#endif // __SCENE_ONE_H__
