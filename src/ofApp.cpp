#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    if( !ofFile::doesFileExist("11to16.bin") ){
        ofSystemAlertDialog("Make sure you have 11to16.bin, xTable.bin and zTable.bin in your data folder!");
        ofExit();
    }
    
    ofBackground(30, 30, 30);
    
    pixAmount.set("Pix Amount", 40,0,100);
        pixAmount2.set("Pix Amount2", 40,0,100);
        pixAmount3.set("Pix Amount3", 40,0,100);
    
    panel.setup("distance in mm", "settings.xml", 10, 10);
    panel.add(kinect.minDistance);
    panel.add(kinect.maxDistance);
    panel.add(pixAmount);
        panel.add(pixAmount2);
        panel.add(pixAmount3);

    
    panel.loadFromFile("settings.xml");
    
    kinect.open();
    
    bDebug = true;
    
    setupFilters();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
    if( kinect.isFrameNew() ){
        texDepth.loadData( kinect.getDepthPixels() );
        texRGB.loadData( kinect.getRgbPixels() );
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    if(bDebug){
        ofSetColor(255);
        texDepth.draw(10, 100);
        texRGB.draw(10, 110 + texDepth.getHeight(), 1920/4, 1080/4);
    }
    
    ciBlur.setRadius(10);
    ciBlur.update(texDepth);
    //ciBloom.update(ciBlur.getCIImage());
    ciPixel.update(ciBlur.getCIImage());
    //ciGloom.update(ciPixel.getCIImage());
    ciPixel.setScale(pixAmount);
    ciZoomBlur.setAmount(3+2*sin(ofGetElapsedTimef()));
    ciZoomBlur.setCenter(300+150*sin(3*ofGetElapsedTimef()), 300+150*cos(3*ofGetElapsedTimef()));
    ciZoomBlur.update(texDepth);
    ciPixel2.setScale(pixAmount2);
    ciPixel2.update(texDepth);
    ciPixel3.setScale(pixAmount3);
    ciPixel3.update(ciBlur.getCIImage());
    ciGloom.update(ciPixel3.getCIImage());
    ciGloom.setIntensity(2);
    
    ciAddComp.update(ciPixel.getCIImage(), ciZoomBlur.getCIImage());
    
    ciMultComp.update(ciPixel2.getCIImage(),ciAddComp.getCIImage());
    
    ciMultComp2.update(ciMultComp.getCIImage(), ciGloom.getCIImage());
    
    
    
    if (!bDebug){
            ciMultComp2.draw(0,0, 720, (512/424)*720, 512, 424);
    }

    
    panel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='d'){
        bDebug =! bDebug;
    }
}

void ofApp::setupFilters(){
    coreBase.setup(); //really not sure if this is necessary yet - but i didnt want to set up multiple CI contexts
    ciBlur.setup(ofGetWidth(), ofGetHeight(), coreBase.getCIContext());
    ciHue.setup(ofGetWidth(), ofGetHeight(), coreBase.getCIContext());
    ciBloom.setup(ofGetWidth(), ofGetHeight(), coreBase.getCIContext());
    ciPixel.setup(ofGetWidth(), ofGetHeight(), coreBase.getCIContext());
     ciPixel2.setup(ofGetWidth(), ofGetHeight(), coreBase.getCIContext());
     ciPixel3.setup(ofGetWidth(), ofGetHeight(), coreBase.getCIContext());

    ciGloom.setup(ofGetWidth(), ofGetHeight(), coreBase.getCIContext());

    ciInvert.setup(ofGetWidth(), ofGetHeight(), coreBase.getCIContext());

    ciZoomBlur.setup(ofGetWidth(), ofGetHeight(), coreBase.getCIContext());
    ciAddComp.setup(ofGetWidth(), ofGetHeight(), coreBase.getCIContext());
    ciMultComp.setup(ofGetWidth(), ofGetHeight(), coreBase.getCIContext());
        ciMultComp2.setup(ofGetWidth(), ofGetHeight(), coreBase.getCIContext());


    
}

void ofApp::exit(){
    kinect.close();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
