/*
 *  ofxGuiObject.h
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
#include "ofxGuiTypes.h"
#include "ofxGuiGlobals.h"
#include "ofEvents.h"


//--------------------------------------------------------------

class ofxGuiObject;

typedef void (ofxGuiObject::*pt2Member)(void);	// function pointer for keymaps
									// all key mapped functions will have to point to 
									// methods that do not take any variables



//--------------------------------------------------------------
class ofxGuiObject : public ofRectangle
{
	
public:

	ofxGuiObject();
	~ofxGuiObject();
	
	// program events
	void			_setup(ofEventArgs &e);
	virtual void	setup()	{}	// called when app starts
	void			_update(ofEventArgs &e);
	virtual void	update() {}	// called every frame to update object
    void			_draw(ofEventArgs &e);
    virtual void	draw()	{}	// called every frame to draw object
	void			_exit(ofEventArgs &e);
	virtual void	exit() {}	// called when app quites
	
	// mouse events
	ofxGuiObject*	_mouseMoved(ofMouseEventArgs &e,	ofxGuiObject* handled); // handled is the object that handled the event
	ofxGuiObject*	_mousePressed(ofMouseEventArgs &e,	ofxGuiObject* handled);
	ofxGuiObject*	_mouseDragged(ofMouseEventArgs &e,	ofxGuiObject* handled, ofxGuiObject* dragObject);
	ofxGuiObject*	_mouseReleased(ofMouseEventArgs &e,	ofxGuiObject* handled, ofxGuiObject* dragObject);
	
	// keyboard events
	ofxGuiObject*	_keyPressed(ofKeyEventArgs &e,	ofxGuiObject* handled);
	ofxGuiObject*	_keyReleased(ofKeyEventArgs &e,	ofxGuiObject* handled);
		
	
	// interaction events
	virtual void onRollOver(int x, int y)					{}		// called when mouse enters object x, y, width, height
	virtual void onRollOut()								{}		// called when mouse leaves object x, y, width, height
	virtual void onMouseMove(int x, int y)					{}		// called when mouse moves while over object x, y, width, height
	
	virtual void onPress(int x, int y, int button)			{}		// called when mouse presses while over object
	virtual void onPressOutside(int x, int y, int button)	{}		// called when mouse presses while outside object
	
	virtual void onObjectDragStart(int x, int y, int button)	{}
	virtual void onObjectDragEnd(int x, int y, int button)		{}

	virtual void onObjectDragging(int x, int y, int button)		{}		// called when the mouse is dragging this object

	virtual void onObjectDropSent(int x, int y, int button, ofxGuiObject* sentObject) {} // called when an object is dropped 

	virtual void onObjectDropReceived(int x, int y, int button, ofxGuiObject* receiverObject) {} // called by the receiver ON the sender when received
	
	virtual void onDragOver(int x, int y, int button)		{}		// called when mouse moves while over object and button is down (but not dragging object)
	virtual void onDragOutside(int x, int y, int button)	{}		// called when mouse moves while outside the object after being clicked on it
	
	
	virtual void onRelease(int x, int y, int button)		{}		// called when mouse releases while over object
	virtual void onReleaseOutside(int x, int y, int button)	{}		// called when mouse releases outside of object after being pressed on object
	
	
	virtual void onKeyPressed( int key )					{}		// called when a key is pressed with the object in focus
	virtual void onKeyReleased( int key )					{}		// called when a key is released with the obejct in focus
	
	virtual void onEnabled()								{}		// called when the object is enabled
	virtual void onDisabled()								{}		// called when the object is disabled
	virtual void onTooltipEnabled()							{}		// called when tooltips are disabled
	virtual void onTooltipDisabled()						{}		// called when tooltips are disabled
	
	virtual void onDragCancelled(int originalLocalPositionX, int originalLocalPositionY) {}	// this gets called when a drag gets cancelled
	virtual void onDragReleased(int newLocalPositionX, int newLocalPositionY) {}	// these values should already be set
	
	// positioning
	string			getTagName();
	
	// params
	int				mParamType, mMode, mDisplay, mSteps;
	string			mParamName, mDisplaySting;
	void			drawHeadString(float x, float y, string text, bool center);
	void			drawParamString(float x, float y, string text, bool center);

	// xml
	int				saveObjectData();
	virtual	void	buildFromXml(){}
	virtual	void	saveToXml(){}

	
	
	// hit regions
	void			setHitRegion(int x, int y, int width, int height);
	ofRectangle		cRect;
	bool			hasCustomHitRegion();
	ofRectangle     getHitRegion();
	virtual bool	hitTest(int tx, int ty);		// returns true if given (x, y) coordinates (in screen space) are over the object (based on position and size)
	
	
	
	
	bool			mouseDown;
	bool			mouseOver;
	int				mouseX, pMouseX;
	int				mouseY, pMouseY;
	int				mouseButton, pMouseButton;
	
	int				key, pKey;
	
	ofxGuiGlobals*	mGlobals;

	
	// tool tips
	string			tooltip;					// the tooltip string
	void			setTooltip(string tooltip);	// a tooltip setter

	bool			isTooltipEnabled;			// is tooltip enabled
	void			enableTooltip();			// enable the tooltip
	void			disableTooltip();			// disable the tool tip
	void			setTooltipEnaled(bool isTooltipEnabled);

	ofxPoint2f		lastTooltipPoint;			// tooltip 
	long			nextTooltipTime;			// the tooltip reveal delay
	
	long			tooltipWaitTime;			// time we wait for tooltip to show up under still mouse
	
	void			drawTooltip(float x, float y);

	
	// enabled / disabled
	bool			isEnabled;	// is this object active?
	bool			canDisable;
	
	void			enable();
	void			disable();
	void			toggleEnable();
	void			setEnabled(bool enabled);
	
	// key mappings 
	map <int, pt2Member> keyMap;
	
	bool			addKeyMap(int k, pt2Member m);
	bool			removeKeyMap(int k);
	
	virtual	bool	isKeyMapped(int key, ofxGuiObject* handled) {return true;};

	// dragging
	
	//bool			isDraggable;	
	bool			isDragMoveable; // can we drag this thing around
	bool			isDragging;		// is dragging
	
	void			cancelDrag();   // immediate cancel the dragging
	//void			releaseDrag();	// release the dragging
	
	ofxPoint2f		preDragPosition; // where we were before the dragging started

	// dropping
	bool			isDropSender; // can we drop this thing on something
	bool			isDropSenderReady;
	bool			isDropReceiver; // can we receive a dropped object
	bool			isDropReceiverReady;
	
	virtual bool	isDropReceiverForObject(ofxGuiObject* dragObject);
	
	
	// events
	ofEvent<int> genericOfxGuiEvent;

	
	// children
	vector			<ofxGuiObject*>				childObjects;
	vector			<ofxGuiObject*>::iterator	childObjectsIter;

	// parents
	ofxGuiObject*	parentObject;
	bool			hasParent();
	
	
	// utilities
	string			floatToString(float value, int display);
	string			pointToString(ofxPoint2f value, int display);
	string			rgbaToString(ofRGBA value, int display);
	
	//	ofxPoint2f		screenToFraction(ofxPoint2f mouse);
	//	ofxPoint2f		fractionToLocal(ofxPoint2f fraction);
	
	
	ofxPoint2f		getScreenPosition();
	
	ofxPoint2f		screenToLocal(ofxPoint2f p);
	ofxPoint2f		localToScreen(ofxPoint2f p);
	
	
private:
	void saveMouseEvent(ofMouseEventArgs &e); // convenience

	
//	ofNotifyEvent(newofxGuiEvent, (1), NULL);
};

//--------------------------------------------------------------

