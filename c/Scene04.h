#ifndef __SCENE_04_H__
#define __SCENE_04_H__

#include "ResourceDefinitions.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

class Scene04 : public Layer {
public:
	static Scene* createScene();
	virtual bool init();
    FrameNav* frameNav;
    FrameNav* fn;
    Menu* menu;
	void gotoNextScene(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
	void gotoGameCallback(Ref* pSender);
    void gameButtonCallBack(float dt);
    void waitNextScene(float dt);
    void nextText(Ref* pSender);
    void prevText(Ref* pSender);
    cocos2d::Sprite* textBox;
    
    void textAppears(float dt);
    Json* script;
    
	CREATE_FUNC(Scene04);
};
#endif // __SCENE_ONE_H__
