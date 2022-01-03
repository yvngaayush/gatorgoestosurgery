#ifndef __SCENE_07_H__
#define __SCENE_07_H__

#include "ResourceDefinitions.h"
#include "editor-support/spine/Json.h"
#include "FrameNav.h"

class Scene07 : public Layer {
public:
    Menu* menu;
	static Scene* createScene();
	virtual bool init();
    cocos2d::Sprite* gator;
    cocos2d::Sprite* textBox;
    FrameNav* frameNav;
	void gotoNextScene(Ref* pSender);
    void gotoNextScene2();
    void nextButtonAppears(float dt);
    void toggleIcon(float dt);
	void gotoPreviousScene(Ref* pSender);
    
    void createGatorListener(float dt);
    void createArrowListener(float dt);
    void ispyCallBack();
    
    void waitNextScene(float dt);
    
    void textAppears(float dt);
    Json* script;
    
	CREATE_FUNC(Scene07);
};
#endif // __SCENE_ONE_H__
