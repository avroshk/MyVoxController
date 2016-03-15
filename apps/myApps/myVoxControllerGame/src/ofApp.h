#pragma once

#include "ofMain.h"
#include "ofxLiquidFun.h"
#include "myReadAudio.h"
#include "myFeatures.h"

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
    
    void audioReceived(float* input, int bufferSize, int nChannels);
    void createCircles(int x, int y);
    void createBricks(int x, int y);

    ofxBox2d box2d;
    vector <ofPtr<ofxBox2dCircle> >	circles;		  //	default box2d circles
    vector <ofPtr<ofxBox2dRect> > boxes;			  //	defalut box2d rects
    ofxBox2dParticleSystem particles;			      //    LiquidFun particle system

    myFeatures *features;
    myReadAudio *audio;
    
    vector<float> drawInput, pitchChroma;
    ofSoundStream soundStream;
    int count = 4;
    
};
