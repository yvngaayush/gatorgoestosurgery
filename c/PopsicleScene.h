#ifndef __POPSICLE_SCENE_H__
#define __POPSICLE_SCENE_H__

#include "ResourceDefinitions.h"
#include "editor-support/spine/Json.h"

class Popsicle : public Layer {
public:
	// Added variable to ensure un-interrupted run actions
	bool _actionComplete = true;

	Menu* menu;
	Json* script;
    int bites = 0;
    int obj = -1;
	static Scene* createScene();
	virtual bool init();
	void gotoPreviousScene(Ref* pSender);
	void gotoNextScene(Ref* pSender);
    void doneCallBack(float dt);
    void textAppears(float dt);
    cocos2d::Sprite* textBox;
    
	CREATE_FUNC(Popsicle);

};
#endif // __POPSICLE_SCENE_H__
