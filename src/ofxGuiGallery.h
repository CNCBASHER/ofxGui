

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_GALLERY
#define OFX_GUI_GALLERY

#include "ofxGuiTypes.h"
#include "ofxGuiObject.h"
#include "ofxGuiGalleryItem.h"
#include "ofxGuiButton.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiGallery : public ofxGuiObject
{
	
public:
	
	ofxGuiGallery();
	~ofxGuiGallery();

	
	void		init(string name, int x, int y, int width, int height, ofxPoint2f min, ofxPoint2f max, ofxPoint2f value, int display, int steps);
	
	//bool		update(int id, int task, void* data, int length);
	void		draw();
	
	ofxGuiObject*	mouseMoved(int x, int y);
	ofxGuiObject*	mouseDragged(int x, int y, int button);
	ofxGuiObject*	mousePressed(int x, int y, int button);
	ofxGuiObject*	mouseReleased(int x, int y, int button);
	ofxGuiObject*	keyPressed(int key);
	ofxGuiObject*	keyReleased(int key);
	
	void		buildFromXml();
	void		saveToXml();
	
	vector		<ofxGuiGalleryItem*> items;
	vector		<ofxGuiGalleryItem*>::iterator itemsIter;
		
	int selectedItem;

	ofxGuiButton* leftButton;
	ofxGuiButton* rightButton;
	
	int numRows;
	int numCols;

	
	
	
};

#endif

//	----------------------------------------------------------------------------------------------------
