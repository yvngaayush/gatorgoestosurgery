#ifndef __SCENE_08_H__
#define __SCENE_08_H__

#include "ResourceDefinitions.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

class Scene08 : public Layer {
public:
	
	static Scene* createScene();
	virtual bool init();
    bool _actionComplete = true;
	void gotoNextScene(Ref* pSender);
    cocos2d::Sprite* textBox;
    cocos2d::Sprite* meetContainer;
    FrameNav* frameNav;
    FrameNav* fn;
    Menu* menu;
    void gotoCloserLook(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
    void nextButtonAppears(float dt);
    void anethesiologistAppears(float dt);
    void surgeonAppears(float dt);
    void resAppears(float dt);
    void closerlookAppears(float dt);
    void callNext();
    void nextText(Ref* pSender);
    void prevText(Ref* pSender);
    void nextText2(Ref* pSender);
    void prevText2(Ref* pSender);
    
    void waitNextScene(float dt);
    
    void textAppears(float dt);
    void anesAppears(float dt);
    Json* script;
    
	CREATE_FUNC(Scene08);
};
#endif // __SCENE_ONE_H__
