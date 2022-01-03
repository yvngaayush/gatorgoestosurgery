#ifndef __SCENE_13_H__
#define __SCENE_13_H__

#include "ResourceDefinitions.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

class Scene13 : public Layer {
public:
	Json* script;
	static Scene* createScene();
    FrameNav* frameNav;
    FrameNav* fn;
    Menu* menu;
	virtual bool init();
	void gotoNextScene(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
    void waitNextScene(float dt);
    void textAppears(float dt);
    void nextText(Ref* pSender);
    void prevText(Ref* pSender);
    cocos2d::Sprite* textBox;
	CREATE_FUNC(Scene13);
};
#endif // __SCENE_ONE_H__
