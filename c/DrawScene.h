#ifndef __DRAW_SCENE_H__
#define __DRAW_SCENE_H__

#include "ResourceDefinitions.h"
#include "editor-support/spine/Json.h"

class DrawScene : public Layer {
private:
	Color4F prevColor = Color4F(0, 0, 0.2, 1.0); // Default same as curColor
	Color4F curColor = Color4F(0, 0, 0.2, 1.0); // Default set to black

public:
	// Added variable to ensure un-interrupted run actions
	bool _actionComplete = true;
    cocos2d::Sprite* textBox;
	Menu* menu;
	Json* script;
	static Scene* createScene();
	virtual bool init();
	void gotoPreviousScene(Ref* pSender);
	void gotoNextScene(Ref* pSender);
    void makeScene(Ref* pSender);
	void setInkColor(int colorVal);
	CREATE_FUNC(DrawScene);

};
#endif // __DRAW_SCENE_H__
