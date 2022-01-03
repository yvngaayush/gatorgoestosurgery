#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "ResourceDefinitions.h"
using namespace CocosDenshion;

class MainMenu : public Layer
{
public:

	// Added variable to ensure un-interrupted run actions
	bool _actionComplete = true;
    Menu* menu;
    
	static Scene* createScene();
	virtual bool init();
	void gotoNextScene(Ref* pSender);
	void gotoPreviousScene(Ref* pSender);
	void exitCallBack(Ref* pSender);
    void careButtonCallBack(Ref* pSender);
    void gameButtonCallBack(Ref* pSender);
    void gotoCredits(Ref* pSender);
    void resetProgress(Ref* pSender);
    void gotoLaunch(float dt);
	CREATE_FUNC(MainMenu);
};
#endif // __MAINMENU_H__
