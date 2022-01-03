#ifndef __PUZZLE_SCENE_H__
#define __PUZZLE_SCENE_H__

#include "ResourceDefinitions.h"
#include "editor-support/spine/Json.h"

class PuzzleScene : public Layer {
public:
	// Added variable to ensure un-interrupted run actions
	bool _actionComplete = true;

	Menu* menu;
	Json* script;
    int obj = -1;
	static Scene* createScene();
	virtual bool init();
	void gotoPreviousScene(Ref* pSender);
	void gotoNextScene(Ref* pSender);
	CREATE_FUNC(PuzzleScene);

};
#endif // __PUZZLE_SCENE_H__
