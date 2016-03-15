#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //Setup audio
    int bufferSize = 1024;
    int overlapMultiple = 4;
    int sampleRate = 44100;
    int numBuffers = 1;
    int numInputs = 1;
    int numOutputs = 0;
    int deviceId = 0; //machine dependent
    
    soundStream.listDevices(); //uncomment to print list of available devices
    soundStream.setDeviceID(deviceId);
    soundStream.setup(this, numOutputs, numInputs, sampleRate, bufferSize, numBuffers);
    
    audio = new myReadAudio();
    audio->init(this, bufferSize, overlapMultiple,sampleRate, numBuffers, numInputs, numOutputs, deviceId);

    features = new myFeatures(sampleRate,bufferSize);
    audio->initFeatures(features);
    
    drawInput.resize(bufferSize*overlapMultiple,0.0);
    pitchChroma.resize(12,0.0);
    
    ofSetFrameRate(60);
    ofBackgroundHex(0x00000);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.setFPS(30.0);
    
    box2d.registerGrabbing();
    box2d.createBounds();
    
    particles.setup(box2d.getWorld());
    
    for (int i = 0; i < 5000; i++) {
        ofVec2f position = ofVec2f(ofRandom(100),
                                   ofRandom(ofGetHeight()));
        ofVec2f velocity = ofVec2f(0, 0);
        particles.createParticle(position, velocity);
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    drawInput = audio->getInputVector();
    pitchChroma = features->getPitchChroma();
    
    ofGetScreenWidth();
    for (int i = 0; i<12; i++) {
        if (pitchChroma[i] > 0.8) {
            createBricks(ofGetScreenWidth()/(i+1),200);
        } else {
            if (pitchChroma[i] > 0.5) {
                createCircles(ofGetScreenWidth()/(i+1),200);
            }
        }
    }
    
    box2d.update();
    
}

//--------------------------------------------------------------
void ofApp::audioReceived(float* input, int bufferSize, int nChannels) {
    audio->audioReceived(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i=0; i<circles.size(); i++) {
        ofFill();
        ofSetHexColor(0xf6c738);
        circles[i].get()->draw();
    }
    
    for(int i=0; i<boxes.size(); i++) {
        ofFill();
        ofSetHexColor(0xBF2545);
        boxes[i].get()->draw();
    }
    
    particles.draw();
    
    string info = "";
    info += "Press [c] for circles\n";
    info += "Press [b] for blocks\n";
    info += "Mouse Drag for particles\n";
    info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
    info += "Total Particles: "+ofToString(particles.getParticleCount())+"\n\n";
    info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
    ofSetHexColor(0xffffff);
    ofDrawBitmapString(info, 30, 30);
    
    // draw the left channel:
    ofPushMatrix();
    ofTranslate(0, 200, 0);
    ofSetColor(225);
    ofDrawBitmapString("Input Channel", 4, 18);
    
    ofSetColor(245, 58, 135);
    ofSetLineWidth(3);

    
    if (count < 1) {
        ofBeginShape();
        
        for (unsigned int i = 0; i < drawInput.size(); i++){
            ofVertex(2*i, 100 - drawInput[i]*180.0f);
        }
        ofEndShape(false);
       
        //Draw every second frame save some resources
        count = 2;
    }
    else {
        count--;
    }
    
    
    ofTranslate(300, -180, 0);
    //    ofSetColor(225);
    //    ofDrawBitmapString("feature:"+ ofToString(features->getPitch()), 4, 18);
    
    ofSetColor(245, 58, 135);
    ofSetLineWidth(3);
    
    string pitches[] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
    
    for(int i =0; i<12;i++){
        ofRect(0+40*i,0,40, pitchChroma[i]*200);
        ofDrawBitmapString(pitches[i], 0+40*i,-4);
    }
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'c') {
        createCircles(mouseX,mouseY);
    }
    if(key == 'b') {
        createBricks(mouseX,mouseY);
    }
}
//-------------------------------------------------------------
void ofApp::createCircles(int x, int y) {
    float r = ofRandom(4, 20);
    circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
    circles.back().get()->setPhysics(0.9, 0.9, 0.1);
    circles.back().get()->setup(box2d.getWorld(), x, y, r);
}

void ofApp::createBricks(int x, int y) {
    float w = ofRandom(20, 40);
    float h = ofRandom(20, 40);
    boxes.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
    boxes.back().get()->setPhysics(4.0, 0.53, 0.1);
    boxes.back().get()->setup(box2d.getWorld(), x, y, w, h);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for (int i = 0; i < 20; i++) {
        float radius = 40;
        float x = cos(ofRandom(PI*2.0)) * radius + mouseX;
        float y = sin(ofRandom(PI*2.0)) * radius + mouseY;
        ofVec2f position = ofVec2f(x, y);
        ofVec2f velocity = ofVec2f(ofRandom(-200, 200), ofRandom(-200, 200));
        particles.createParticle(position, velocity);
    }
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
