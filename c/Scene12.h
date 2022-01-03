#ifndef __SCENE_12_H__
#define __SCENE_12_H__

#include "ResourceDefinitions.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

class Scene12 : public Layer {
public:
	Json* script;
	static Scene* createScene();
	virtual bool init();
    FrameNav* frameNav;
    cocos2d::Sprite* textBox;
    cocos2d::Sprite* glow;
	void gotoNextScene(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
    void nextButtonAppears(float dt);
    void maskButtonCallBack(Ref* pSender);
    void waitNextScene(float dt);
    void foundStarCallBack(float dt);
    void textAppears(float dt);
	CREATE_FUNC(Scene12);
};
#endif // __SCENE_ONE_H__
