/*  ofxGui.h
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

//--------------------------------------------------------------
#pragma once

//--------------------------------------------------------------
#include "ofEvents.h"
#include "ofxGuiGlobals.h"
#include "ofxGuiTypes.h"

#include "ofxGuiObject.h"
#include "ofxGuiPanel.h"

#include "ofxKeyMap.h"

//class ofxGuiObject;
//class ofxGuiPanel;


//--------------------------------------------------------------
class ofxGui {
	
public:
	
	static			ofxGui* Instance();//ofxGuiListener* listener);

	//ofxGui();	// constructor
	//~ofxGui();	// destructor
	
	void			setup(ofEventArgs & args);
	void			update(ofEventArgs & args);
	void			draw(ofEventArgs & args);
	void			exit(ofEventArgs & args);
	
	
	
	void			activate(bool activate);
	void			forceUpdate(bool update);
	
	ofxGuiObject*	lastHandler;
	
	//ofxGuiObject*	lastKeyPressedHandler;  // we will check these each time, rather than checking all of them
	void			keyPressed(int key);
	void			keyPressed(ofKeyEventArgs & args);

	//ofxGuiObject*	lastKeyReleasedHandler;
	void			keyReleased(int key);
	void			keyReleased(ofKeyEventArgs & args);

	//ofxGuiObject*	lastMouseMovedHandler;
	void			mouseMoved(int x, int y );
	void			mouseMoved(ofMouseEventArgs & args);

	//ofxGuiObject*	lastMouseDraggedHandler;
	void			mouseDragged(int x, int y, int button);
	void			mouseDragged(ofMouseEventArgs & args);

	//ofxGuiObject*	lastMousePressedHandler;
	void			mousePressed(int x, int y, int button);
	void			mousePressed(ofMouseEventArgs & args);

	//ofxGuiObject*	lastMouseReleasedHandler;
	void			mouseReleased(int x, int y, int button);
	void			mouseReleased(ofMouseEventArgs & args);

	
	ofxGuiPanel*	addPanel(string name, int x, int y, int border=OFXGUI_PANEL_BORDER, int spacing=OFXGUI_PANEL_SPACING);
	bool			removePanel(ofxGuiPanel* panel);
	
	ofxGuiObject*	addGuiObject(ofxGuiObject* obj);
	bool			removeGuiObject(ofxGuiObject* obj);
	
	
	
	bool			buildFromXml(string file);
	void			saveToXml(string file);

	bool			mIsActive, mDoUpdate, mXmlDone;	
	
	ofxGuiGlobals*	mGlobals;
	
	vector			<ofxGuiObject*>				mObjects;
	vector			<ofxGuiObject*>::iterator	mObjectsIter;
	
	ofxGuiObject*	dragObject;	// the object that could be dragged
	ofxPoint2f		dragPreviousPosition;
	
	void			bringToFront(int index);
	void			bringForward(int index);	
	void			sendToBack(int index);
	void			sendBackward(int index);
	
	
	

	
	
private:
	
	// a private constructor only available to the single instance
	ofxGui();//ofxGuiListener* listener);
};

//--------------------------------------------------------------

