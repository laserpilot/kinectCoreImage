#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"
#include "ofxCoreImage.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void     setupFilters();
    void exit();
    
    ofxPanel panel;
    ofxSlider <int> minDistance;
    ofxSlider <int> maxDistance;
    ofxSlider<float> pixAmountSlide;
        ofxSlider<float> pixAmountSlide2;
        ofxSlider<float> pixAmountSlide3;
    
    ofParameter<float> pixAmount, pixAmount2, pixAmount3;
    
    ofxKinectV2 kinect;
    ofTexture texDepth;
    ofTexture texRGB;
    
    bool bDebug;
    
    ofxCI coreBase;
    ofxCIBlur ciBlur;
    ofxCIHue ciHue;
    ofxCIBloom ciBloom;
    ofxCIPixellate ciPixel;
        ofxCIPixellate ciPixel2;
        ofxCIPixellate ciPixel3;
    ofxCIGloom ciGloom;
    ofxCIColorInvert ciInvert;
    ofxCIZoomBlur ciZoomBlur;
    ofxCIAdditionCompositing ciAddComp;
    ofxCIMultiplyBlendMode ciMultComp;
        ofxCIMultiplyBlendMode ciMultComp2;
    
        ofFbo sourceFbo;
    

		
};
