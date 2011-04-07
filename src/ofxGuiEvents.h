#pragma once

#include "ofConstants.h"
#include "ofUtils.h"
#include "ofEvents.h"

#include "ofxGui.h"

class ofxGuiEvents {
public:

	ofEvent<ofxGuiButton>	ofxGuiButtonEvent;
	ofEvent<ofxGuiPanel>	ofxGuiPanelEvent;
	/*
	ofEvent<ofxGuiSlider>	ofxGuiSliderEvent;
	ofEvent<ofxGuiPanel>	ofxGuiFilesEvent;
	ofEvent<ofxGuiPanel>	ofxGuiColorEvent;
	ofEvent<ofxGuiPanel>	ofxGuiMatrixEvent;
	ofEvent<ofxGuiPanel>	ofxGuiScopeEvent;
	ofEvent<ofxGuiPanel>	ofxGuiKnobEvent;
	ofEvent<ofxGuiPanel>	ofxGuiRadarEvent;
	ofEvent<ofxGuiPanel>	ofxGuiSwitchEvent;
	 */
};
