/*
 *  ofxGuiSlider.h
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
#include "ofxGuiTypes.h"
#include "ofxGuiObject.h"
#include "ofEvents.h"


//--------------------------------------------------------------
class ofxGuiSlider : public ofxGuiObject
{

	public:
    
		ofxGuiSlider();
    
		void		init(string _name, 
                         int _x, int _y, 
                         int _width, int _height, 
                         float _min, float _max, 
                         float _value, int _display, 
                         int _steps);

		void		setValue(float value);
		void		setRange(float min, float max);

        //void setup();	// called when app starts
        //void update();	// called every frame to update object
        void draw();	// called every frame to draw object
        //void exit();	// called when app quites
        
        // these behave very similar to those in flash
        void onRollOver(int x, int y);					// called when mouse enters object x, y, width, height
        void onRollOut();								// called when mouse leaves object x, y, width, height
        void onMouseMove(int x, int y);					// called when mouse moves while over object x, y, width, height
        void onDragOver(int x, int y, int button);		// called when mouse moves while over object and button is down
        
        void onDragOutside(int x, int y, int button);	// called when mouse moves while outside the object after being clicked on it
        void onPress(int x, int y, int button);			// called when mouse presses while over object
        void onPressOutside(int x, int y, int button);	// called when mouse presses while outside object
        void onRelease(int x, int y, int button);		// called when mouse releases while over object
        void onReleaseOutside(int x, int y, int button);// called when mouse releases outside of object after being pressed on object
    
        void onObjectDragStart(int x, int y, int button) {
            cout << "SLIDER DRAG STARTED " << endl;
        }
        
        void onObjectDragEnd(int x, int y, int button) {
            cout << "SLIDER DRAG ENDED " << endl;
        }
    
    
        void sliderDragging(int x, int y, int button);
        
        void keyPressed( int key );

        void keyReleased( int key );

		void		buildFromXml();
		void		saveToXml();

		float		valueToFraction(float value);
		float		fractionToValue(float fraction);
		
		float		mValue, mMinVal, mMaxVal, mValDlt;

        ofEvent<float> ofxGuiSliderEvent;

    
};

//--------------------------------------------------------------

