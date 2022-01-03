#ifndef __RESOURCE_DEFINITIONS_H__
#define __RESOURCE_DEFINITIONS_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <stdio.h>
#include "ui/CocosGUI.h"

/*
 Flow chart:
 [Opening] - audio: MUSICLAUNCH
 
    0: Launch
    1: Menu - Credits
 
 [Before Room] - audio: MUSICWAIT
 
    2: NameTag (Scene02) - DrawName
    3: WaitingRoom (Scene04) - PuzzleScene
    4: Elevator (Scene06)
 
 [Pre-Op] - audio: MUSICPREOP
 
    5: Scale (Scene07)
    6: Room (Scene08) - CloserLook (Scene09)
    7: OR Doors (Scene11)
 
 [OR] - audio: MUSICOR
 
    8: OR (Scene10) - Closer (Scene12)
    9: Choose Flavor (Scene13)
 
 [Post-Op] - audio: MUSICPOSTOP
 
    10: Room (Scene14) - PopsicleScene
    11: Congrats! (Scene15)
 
 [FrameNav]
 [IconBar]
 */

// A macro that does the same thing as "using namespace cocos2d;"
USING_NS_CC;

// Namespace for using cocos simple audio engine
using namespace CocosDenshion;

// Size of the game
static cocos2d::Size designResolutionSize = cocos2d::Size(2048.0/2, 1536.0/2);
static cocos2d::Size smallResolutionSize = cocos2d::Size(512.0, 384.0);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024.0, 768.0);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048.0, 1536.0);

// General
const float TEMPO = 1.0f / 1.0f; // works inversely to control app speed
const float SCENETRANSITIONTIME = 2.0f*TEMPO; // times for screen wipes
const float LAUNCHTRANSITIONTIME = 0.2f*TEMPO;
const float DRAWSCENEBRUSHSIZE = 0.01f; // 0.004 too small?

// Script
const std::string SCRIPT = "scripts/masterscript.txt";
//const std::string BOLD = "fonts/Coiny-Regular.ttf";
const std::string NOTOSANS = "fonts/NotoSans.ttf";
//const std::string BOLD = "fonts/NotoSansBold.ttf";
const std::string COUNTERFONT = "fonts/Coiny-Regular.ttf"; // Scene font
const std::string BLACK = "fonts/Nunito-Black.ttf";
const std::string BOLD = "fonts/Nunito-Bold.ttf";
const std::string SEMIBOLD = "fonts/Nunito-SemiBold.ttf";
const std::string LIGHT = "fonts/Nunito-Light.ttf";
const float TEXTSIZE = 1.0f / 30; // 20

// Audio
const float VOLUMEMUSIC = 0.8f;
const char MUSICLAUNCH[19] = "audio/surgeryu.wav";
const char MUSICWAIT[19] = "audio/ch3music.wav";
const char MUSICPREOP[19] = "audio/surgeryu.wav";
const char MUSICOR[19] = "audio/ch3music.wav";
const char MUSICPOSTOP[19] = "audio/surgeryu.wav";

// General Sprites
const std::string STARSHINE = "Star.png"; // Scene Sprite
const std::string BIGRIDICULOUSARROW = "arrow.png"; // Scene Sprite
const std::string TEXTBOX = "TextBox.png"; // Scene TextBox
const std::string DONEBUTTON = "doneButton.png"; // Navigation Sprite
const std::string BACKBUTTON = "backButton.png"; // Navigation Sprite
const std::string GLOW = "glow.png";

// 0: Launch
const std::string LAUNCHIMAGE = "0Launch/title_background.png"; // Scene Sprite
const std::string HELICOPTER = "0Launch/helicopter.png"; // Scene Sprite
const std::string SCOOTER = "0Launch/gatorscooter.png"; // Scene Sprite
const std::string STARTBUTTON = "0Launch/start_button.png"; // Scene Sprite
const std::string STARTTEXT = "0Launch/start.png"; // Scene Sprite
const std::string WELCOMEBUTTON = "0Launch/welcome_bubble.png"; // Scene Sprite
const std::string WELCOMETEXT = "0Launch/welcome_shands.png"; // Scene Sprite

// 1: Menu
const std::string MENUBKGD = "1Menu/Background.png"; // Background Sprite
const std::string WELCOMEBUTTON01 = "1Menu/WelcomeBubble.png"; // Scene Script
const std::string CAREGIVERBUTTON01 = "1Menu/CaregiverButton.png"; // Scene Sprite
const std::string GAMEBUTTON01 = "1Menu/IspyButton.png"; // Scene Sprite
const std::string ICONGAME = "1Menu/IconGame.png"; // popup sprite
const std::string GAMEGOTIT = "1Menu/got_it.png"; // popup sprite button
const std::string CLIPBOARD = "1Menu/Clipboard.png"; // popup sprite
const std::string CLIPGOTIT = "1Menu/clip-got-it.png"; // popup sprite button

// 2: NameTag
const std::string NAMETAGBKGD = "2NameTagScene/Background.png"; // Background Sprite
const std::string BRACELET = "2NameTagScene/Bracelet.png"; // Scene Sprite
const std::string BRACELETCLICKED = "2NameTagScene/braceletClicked.png"; // Scene Sprite
const std::string DRAWBACKGROUND = "2NameTagScene/BackgroundDraw.png"; // Background Sprite

const std::string ClearButton = "2NameTagScene/Clear_Logo.png";
const std::string BLUEDOT = "2NameTagScene/BlueDot.png"; 
const std::string GREENDOT = "2NameTagScene/GreenDot.png";
const std::string ORANGEDOT = "2NameTagScene/OrangeDot.png";
const std::string REDDOT = "2NameTagScene/RedDot.png";
const std::string YELLOWDOT = "2NameTagScene/YellowDot.png";

// 3: Waiting Room
const std::string WAITINGBKGD = "3WaitingRoom/Background.png"; // Background Sprite
const std::string GAMEBUTTON04 = "3WaitingRoom/playbutton.png"; // Scene sprite

const std::string YELLOWBKGD = "3WaitingRoom/PuzzleBackground.png"; // Background Sprite
const std::string PUZZLESW = "3WaitingRoom/PuzzleSW.png"; // Puzzle Sprite
const std::string PUZZLENE = "3WaitingRoom/PuzzleNE.png"; // Puzzle Sprite
const std::string PUZZLESE = "3WaitingRoom/PuzzleSE.png"; // Puzzle Sprite
const std::string PUZZLENW = "3WaitingRoom/PuzzleNW.png"; // Puzzle Sprite

// 4: Elevator
const std::string ELEVATORBKGD = "4Elevator/Background.png"; // Background Sprite
const std::string PATIENT05 = "4Elevator/Gator.png"; // Character Sprite
const std::string MOM05 = "4Elevator/Parent.png"; // Character Sprite
const std::string NURSE05 = "4Elevator/Nurse.png"; // Character Sprite
const std::string GREENELEVATORBUTTON = "4Elevator/elevatorGreen.png";
const std::string ELEVATORBUTTONUP = "4Elevator/elevatorUp.png";
const std::string ELEVATORBUTTONDOWN = "4Elevator/elevatorDown.png";
const std::string BUTTON06 = "4Elevator/meetyournursebutton.png";
const std::string HINURSE = "4Elevator/nurseScreenshot.png"; // Replace this!!

// 5: Scale
const std::string SCALEBKGD = "5Scale/Background.png"; // Background Sprite
const std::string Gown = "5Scale/Gown.png";
const std::string DressedGator = "5Scale/GatorwGown.png";
const std::string Gator = "5Scale/GatornoGown.png";

// 6: Room
const std::string ROOMBKGD = "6Room/Background.png"; //New Background Sprite
const std::string MOMROOM = "6Room/ParentRoom.png"; // Scene Sprite
const std::string WINDOW = "6Room/window.png"; //Window Sprite
const std::string takeACloserLook = "6Room/closerlookButton.png";
const std::string meetyouranestesiologist = "6Room/DoctorButton.png";
const std::string meetyouranestesiologist2 = "6Room/DButton2.png";
const std::string meetyouranestesiologist3 = "6Room/DButton3.png";
const std::string HIANES = "6Room/anesScreenshot.png"; // Replace this!!
const std::string HISURGEON = "6Room/surgeon.png";
const std::string HIRESIDENTS = "6Room/residents.png";

const std::string CLOSERLOOKBKGD = "6Room/BackgroundCloser.png"; // Background Sprite
const std::string cuff = "6Room/cuff.png";
const std::string thermometer = "6Room/thermometer.png";
const std::string thermometerclicked = "6Room/thermometerClicked.png";
const std::string electrodes = "6Room/electrodes.png";
const std::string electrodesclicked = "6Room/electrodesClicked.png";
const std::string pulseox = "6Room/pulseox.png";
const std::string pulseoxclicked = "6Room/pulseoxClicked.png";

// 7: OR Doors
const std::string ORDOORSBKGD = "7ORDoors/Background.png"; // Background Sprite
const std::string S11DOORS = "7ORDoors/doors.png"; // Background Sprite
const std::string S11PPL = "7ORDoors/people.png"; // Background Sprite
const std::string S11DOORHANDLES = "7ORDoors/doorhandle.png";

// 8: OR Room
const std::string ORBKGD = "8OR/Background.png"; // Background Sprite
const std::string SleepMach = "8OR/machine.png";
const std::string Bed = "8OR/GatorBed.png";
const std::string Nurse = "8OR/nurse.png";
const std::string LightOn = "8OR/lightOn.png";
const std::string LightOff = "8OR/lightOff.png";
const std::string Anes = "8OR/anesthesiologist.png";

const std::string S12BKGD = "8OR/BackgroundMachine.png"; // Background Sprite
const std::string ANES = "8OR/anesthesiologistnoMask.png"; // Anesthesiologist Sprite
const std::string MACHINE = "8OR/machineGlow.png"; // Anesthesia Machine
const std::string Mask32 = "8OR/mask.png";
const std::string PICKFLAVORBUTTON = "8OR/pickyourflavor.png";

// 9: Flavor
const std::string FLAVORBKGD = "9Flavor/Background.png"; // Background Sprite
const std::string ANESMASK = "9Flavor/maskFlavor.png"; // Mask Sprite
const std::string ANESMELON = "9Flavor/anes_melon.png"; // Watermelon Flavor Sprite
const std::string ANESGUM = "9Flavor/anes_gum.png"; // Bubblegum Flavor Sprite
const std::string ANESBERRY = "9Flavor/anes_berry.png"; // Strawberry Flavor Sprite

// 10: Post-OP
const std::string POSTOPBKGD = "10PostOp/Background.png"; // Background Sprite
const std::string postIV = "10PostOp/IV.png"; // iv bag
const std::string postchair = "10PostOp/chair.png"; // chair
const std::string postbed = "10PostOp/GatorBedPost.png";
const std::string postdoc = "10PostOp/doctor.png";
const std::string postmom = "10PostOp/ParentPost.png";
const std::string TRYPOPBUTTON = "10PostOp/TryPopsicle.png";

const std::string POPSICLEBKGD = "10PostOp/popsicle_bkgd.png"; // Background Sprite
const std::string POP0 = "10PostOp/pop.png";
const std::string POP1 = "10PostOp/bite1.png";
const std::string POP2 = "10PostOp/bite2.png";
const std::string POP3 = "10PostOp/bite3.png";
const std::string POP4 = "10PostOp/bite4.png";
const std::string POP5 = "10PostOp/stick.png";
const std::string YUM = "10PostOp/YUM.png";

// 11: Congrats
const std::string S15BKGD = "11Congrats/Background.png"; // Background Sprite
const std::string bubble = "11Congrats/collectionBubble.png";
const std::string confetti = "11Congrats/confetti.png";
const std::string depgator = "11Congrats/gatorCongrats.png";
const std::string thankyou = "11Congrats/thanks.png";

// Frame Navigation
const std::string MOVEFWD = "arrowR.png";
const std::string MOVEBWD = "arrowL.png";
const std::string PAGEFWD = "pageRight.png";
const std::string PAGEBWD = "pageLeft.png";
const std::string VOLUMEBUTTON = "framebuttons/Volume.png";
const std::string TAPTHESCREEN = "framebuttons/touchhint.png";
const float SCALEY1 = 0.06f; // Scale Y1 position based on screen size
const float SCALEY2 = 0.94f; // Scale Y2 position based on screen size
const float SCALEX1 = 0.06f; // Scale X1 position based on screen size
const float SCALEX2 = 0.94f; // Scale X2 position based on screen size
const std::string HOMEBUTTON = "framebuttons/homeButton.png"; // Button Sprite
const std::string FRAMEFRAME = "framebuttons/Frame.png"; // Button Sprite
const std::string EXITBUTTONON = "framebuttons/exitButton.png"; // Button Sprite
const std::string EXITBUTTONOFF = "framebuttons/Frame-03.png"; // Button Sprite
const int BORDERTAG = 1101; // Child tag to toggle boarder
const int ISPYTAG = 1500; // Child tag for I-SPY game icon bar
const int FRAMEDRAW = 1000; // Control tag for graphy priorty drawing of frame stuff

// Icon Bar
const std::string ICONBAR = "IconBar/IconBar.png";
const std::string CUFF  = "IconBar/BloodPressureCuff.png";
const std::string BRACE = "IconBar/Bracelet.png";
const std::string MASK  = "IconBar/Mask.png";
const std::string PULSEOX = "IconBar/PulseOX.png";
const std::string EKG = "IconBar/EKG.png";
const std::string GOWN =  "IconBar/HospitalGown.png";
const std::string THERMO = "IconBar/Thermometer.png";
const std::string STAR = "IconBar/star.png";


#endif // __RESOURCE_DEFINITIONS_H__
