#ifndef __SCENE_15_H__
#define __SCENE_15_H__

#include "ResourceDefinitions.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

class Scene15 : public Layer {
public:
	Json* script;
	FrameNav* frameNav;
	static Scene* createScene();
	virtual bool init();
    int counter = 0;
	void gotoNextScene(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
    void textAppears(float dt);
	CREATE_FUNC(Scene15);
};
#endif // __SCENE_ONE_H__
