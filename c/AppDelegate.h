#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "ResourceDefinitions.h"

class AppDelegate : public Application
{
public:
    AppDelegate(); // Declaring constructor
    virtual ~AppDelegate(); // Declaring destructor

    virtual void initGLContextAttrs();

	// This is where your implement the Director and Scene init code
	virtual bool applicationDidFinishLaunching();

	// This function will be called when the application enters background.
	virtual void applicationDidEnterBackground();

	// This function will be called when the application enters foreground.
	virtual void applicationWillEnterForeground();

private:
    void initOpenGL(); // Opens the default program responsible for making windows
    void initMultiResolution(); // Get correct scaling for device
    void initDirector(); // Create a Director to control the whole program
    void createAndRunScene(); // Start the program with your first scene
};

#endif // __APP_DELEGATE_H__
