#ifndef __SCENE_10_H__
#define __SCENE_10_H__

#include "ResourceDefinitions.h"
#include "editor-support/spine/Json.h"

class Scene10 : public Layer {
public:
	
	static Scene* createScene();
	virtual bool init();
	void gotoNextScene(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
    void gameButtonCallBack(float dt);
    void gotoGameCallback(Ref* pSender);
    bool on;
    cocos2d::Sprite* textBox;
    void waitNextScene(float dt);
    
    void textAppears(float dt);
    Json* script;
    
	CREATE_FUNC(Scene10);
};
#endif // __SCENE_ONE_H__
