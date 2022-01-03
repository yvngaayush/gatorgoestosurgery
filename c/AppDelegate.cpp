#include "AppDelegate.h"
#include "LaunchScreen.h"
#include "Scene08.h"
#include "PuzzleScene.h"

// Defining Constructor (yes its currently empty, that's okay)
AppDelegate::AppDelegate() {}

// Defining Destructor (yes its currently empty, that's okay)
AppDelegate::~AppDelegate() {}

/*
*	If you want a different context, modify the value of glContextAttrs
*	It will affect all platforms
*/
void AppDelegate::initGLContextAttrs()
{
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };
	GLView::setGLContextAttrs(glContextAttrs);
}

/*
*	This method is esponsibe for loading the pre-scaled versions of the graphics
*	Third thing that happens when your application starts to go
*/
void AppDelegate::initMultiResolution()
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	// Set the design resolution
	glview->setDesignResolutionSize(
		designResolutionSize.width,
		designResolutionSize.height,
		ResolutionPolicy::NO_BORDER
	);

	float scaleFactor = 1.0f;
	Size frameSize = glview->getFrameSize();

	// if the frame's height is larger than the height of medium size
	if (frameSize.height > mediumResolutionSize.height)
	{
		scaleFactor = largeResolutionSize.height / designResolutionSize.height;
	}
	// if the frame's height is larger than the height of small size
	else if (frameSize.height > smallResolutionSize.height)
	{
		scaleFactor = mediumResolutionSize.height / designResolutionSize.height;
	}
	// if the frame's height is larger than the height of small size
	else
	{
		scaleFactor = smallResolutionSize.height / designResolutionSize.height;
	}

	director->setContentScaleFactor(scaleFactor);

	// Adding more resource folders to FilePaths
	std::vector<std::string> searchPaths;
	searchPaths.push_back("res");
	searchPaths.push_back("audio");
	FileUtils::getInstance()->setSearchPaths(searchPaths);
}

/*
*	This code is required to create the OpenGL view.
*	First thing that happens when your application starts to go
*/
void AppDelegate::initOpenGL()
{
	// gotta call the director to set up OpenGL view (i.e. make the window)
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		// Divide width and height by an integer to fit your screen as needed or try on other screen sizes
		float scaler = 1.4; // Default is 0.8
		glview = GLViewImpl::createWithRect("SurgeryU", cocos2d::Rect(0, 0, scaler *0.6* designResolutionSize.width, scaler * 0.6*designResolutionSize.height));
#else
		glview = GLViewImpl::create("SurgeryU");
#endif
		director->setOpenGLView(glview);
	}
}

/*
*	Initialize the director
*	Second thing that happens when your application starts to go
*/
void AppDelegate::initDirector()
{
	auto director = Director::getInstance();
	director->setAnimationInterval(1.0f / 60);
	director->setDisplayStats(false);
}

/*
* Create our scene and run it
* Note that the app will start at the launch scene screen and fade into the main menu
* Final thing that happens
*/
void AppDelegate::createAndRunScene()
{
    UserDefault * def = UserDefault::getInstance();
    auto musicVolume = def->getFloatForKey("MUSICVOLUME", 0.30f); // default is 30%
    auto effectsVolume = def->getFloatForKey("EFFECTSVOLUME", 0.70f); // default is 70%
    def->getBoolForKey("ISPYBPFOUND", false);
    def->getBoolForKey("ISPYNAMEFOUND", false);
    def->getBoolForKey("ISPYMASKFOUND", false);
    def->getBoolForKey("ISPYPULSEOXFOUND", false);
    def->getBoolForKey("ISPYELECFOUND", false);
    def->getBoolForKey("ISPYSMOCKFOUND", false);
    def->getBoolForKey("ISPYTHERMOFOUND", false);
    
    def->flush();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(musicVolume*0.8f);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(effectsVolume);
    
	auto director = Director::getInstance();
	auto scene = Launch::createScene(); // Edit this line to change start scene
	//auto scene = Scene08::createScene();
	director->runWithScene(scene);
}

// This is where all our logic will reside and works once application is loaded
bool AppDelegate::applicationDidFinishLaunching()
{
	initOpenGL();
	initDirector();
	initMultiResolution();
	createAndRunScene();
	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	// if you use SimpleAudioEngine, it must be paused

}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
