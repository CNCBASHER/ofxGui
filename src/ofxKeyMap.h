#pragma once


/************************************************************

OpenFrameworks Library

File: 			ofxKeyMap.h
Description: 	Keeps track of pressed keys
Notes:

Last Modified: 2009.09.17
Creator: Rick Companje

************************************************************/

#include "ofMain.h"

#define NUM_KEYS 512

class ofxKeyMap {
public:

    ofxKeyMap();
	~ofxKeyMap();
	
    bool isKeyDown(int key);
    bool isAltDown();
    bool isShiftDown();
    bool isControlDown();

	void _keyPressed(ofKeyEventArgs &e);
	void _keyReleased(ofKeyEventArgs &e);

private:
    bool keys[NUM_KEYS];
};
