/*
 *  ofxGuiPanel.h
 *  openFrameworks
 *
 *  Copyright 2008 alphakanal/Stefan Kirch.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

//--------------------------------------------------------------
//#include "ofxGui.h"

#include "ofxGuiObject.h"
#include "ofxGuiGlobals.h"
#include "ofxGuiButton.h"
#include "ofxGuiSlider.h"

/*
#include "ofxGuiXYPad.h"
#include "ofxGuiPoints.h"
#include "ofxGuiFiles.h"
#include "ofxGuiColor.h"
#include "ofxGuiMatrix.h"
#include "ofxGuiScope.h"
#include "ofxGuiKnob.h"
#include "ofxGuiRadar.h"
#include "ofxGuiSwitch.h"
*/

//--------------------------------------------------------------
class ofxGuiPanel : public ofxGuiObject
{

	public:

		ofxGuiPanel();
		~ofxGuiPanel();
		

		void init(string name, int x, int y, int border, int spacing);

	
		//void setup();	// called when app starts
		//void update();	// called every frame to update object
		void draw();	// called every frame to draw object
		void exit();	// called when app quites
		
		// these behave very similar to those in flash
		void onRollOver(int x, int y);					// called when mouse enters object x, y, width, height
		void onRollOut();								// called when mouse leaves object x, y, width, height
		void onMouseMove(int x, int y);					// called when mouse moves while over object x, y, width, height
		void onDragOver(int x, int y, int button);		// called when mouse moves while over object and button is down
		void onDragging(int x, int y, int button);
		
	
	void onObjectDragStart(int x, int y, int button);
	void onObjectDragging(int x, int y, int button);
	
	
	void onObjectDropSent(int x, int y, int button, ofxGuiObject* sentObject); // called when an object is dropped 
	
	void onObjectDropReceived(int x, int y, int button, ofxGuiObject* receiverObject); // called by the receiver ON the sender when received
	
	
	
		void onDragOutside(int x, int y, int button);	// called when mouse moves while outside the object after being clicked on it
		void onPress(int x, int y, int button);			// called when mouse presses while over object
		void onPressOutside(int x, int y, int button);	// called when mouse presses while outside object
		void onRelease(int x, int y, int button);		// called when mouse releases while over object
		void onReleaseOutside(int x, int y, int button);// called when mouse releases outside of object after being pressed on object
		
		void onDropOver(int x, int y, int button, ofxGuiObject* object); // called when an object is dropped 
	
		void keyPressed( int key );
		void keyReleased( int key );
	
		ofxGuiButton*	addButton(string name, 
								  int width=OFXGUI_BUTTON_WIDTH, 
								  int height=OFXGUI_BUTTON_HEIGHT, 
								  int value=kofxGui_Button_Off, 
								  int mode=kofxGui_Button_Switch, 
								  string image="");
		
		
		ofxGuiButton*	addButtonTrigger(string name);
		ofxGuiButton*	addButtonSwitch(string name);
	
        ofxGuiSlider*	addSlider(string name, 
                                  int width, int height, 
                                  float min, float max, 
                                  float value, int display, 
                                  int steps=OFXGUI_STEPS);

        /*
		ofxGuiXYPad*	addXYPad(	string name, int width, int height, ofxPoint2f min, ofxPoint2f max, ofxPoint2f value, int display, int steps=OFXGUI_STEPS);
		ofxGuiPoints*	addPoints(	string name, int width, int height, ofxPoint2f min, ofxPoint2f max, ofxPoint2f value, int display, int steps=OFXGUI_STEPS);
	
	
	
	
		ofxGuiFiles*	addFiles(	string name, int width, int height, string value, string subPath, string suffix);
		ofxGuiColor*	addColor(	string name, int width, int height, ofRGBA value, int mode);
		ofxGuiMatrix*	addMatrix(	string name, int width, int height, int xGrid, int yGrid, int value, int mode, int spacing);
		ofxGuiScope*	addScope(	string name, int width, int height, int length, ofxPoint2f value, int mode);
		ofxGuiKnob*		addKnob(	string name, int width, int height, float min, float max, float value, int display, int steps=OFXGUI_STEPS);
		ofxGuiRadar*	addRadar(	string name, int width, int height, float min, float max, float value, int display, int steps=OFXGUI_STEPS);
		ofxGuiSwitch*	addSwitch(	string name, int width, int height, int min, int max, int value, const string* paramStrings);	
		*/
	
		void			adjustToNewContent(int w, int h);

		void			buildFromXml();
		void			saveToXml();

		int				mBorder, mSpacing;
		
		
		// bakercp
		bool			isMinimized;
		
		ofxGuiButton*	enableDisableButton;
		
		ofxGuiButton*	minMaxButton;
		void			minimize();
		void			maximize();
		void			toggleMaxMin();
		
		ofRectangle		minimizedRect;

		int				windowButtonWidth;	
		int				windowButtonHeight;
		
		void			buttonEvent(const void * sender, int & i);


	
	
private:
		
		void			addChild(ofxGuiObject* obj);
		int				getOffset();
		
};

//--------------------------------------------------------------

