//
//  myReadAudio.cpp
//  myVoxPlay
//
//  Created by Avrosh Kumar on 3/14/16.
//
//

#include "myReadAudio.h"

myReadAudio::myReadAudio() {
    this->numHops = 0;
}

myReadAudio::~myReadAudio() {
//    soundStream.close();
    deallocateMemory();
}


void myReadAudio::init(ofBaseApp * app,
                       int bufferSize,
                       int overlapMultiple,
                       int sampleRate,
                       int numBuffers,
                       int numInputs,
                       int numOutputs,
                       int deviceId) {
    this->bufferSize = bufferSize;
    this->overlapMultiple = overlapMultiple;
    this->sampleRate = sampleRate;
    this->numBuffers = numBuffers;
    this->numInputs = numInputs;
    this->numOutputs = numOutputs;
    this->deviceId = deviceId;
    
    setupStream(app);
    allocateMemory();
    resetMemory();
}

void myReadAudio::setupStream(ofBaseApp * app) {
//    soundStream.listDevices(); //uncomment to print list of available devices
//    soundStream.setDeviceID(deviceId);
//    soundStream.setup(app, numOutputs, numInputs, sampleRate, bufferSize, numBuffers);
}

void myReadAudio::allocateMemory() {
    block = new float [bufferSize*overlapMultiple];
    middleInput.resize(bufferSize*overlapMultiple,0.0);
}

void myReadAudio::resetMemory() {
    memset(block, 0.0, sizeof(float)*bufferSize*overlapMultiple);
}

void myReadAudio::deallocateMemory() {
    delete [] block;
    block = 0;
    
    //no need to deallocate vector middleInput
}



void myReadAudio::initFeatures(myFeatures *features) {
    this->features = features;
}

void myReadAudio::audioReceived(float* input, int bufferSize, int nChannels) {

    //Assumption - in this case we will treat all audio as mono
    
    //We receive interleaved data
    
    blockAndProcessAudioData(input,bufferSize,nChannels);
    
}

void myReadAudio::blockAndProcessAudioData(float *input, int bufferSize, int nChannels) {
    
    if (numHops > overlapMultiple-1) {
        processBlock(block,bufferSize*overlapMultiple,nChannels);
        
        //Note: user ring buffer to improve performance
        
        //Shift block data to left
        memcpy(block, block+bufferSize, sizeof(float)*bufferSize*(overlapMultiple-1));

        //Push the last hop into the block
        memcpy(block+bufferSize*(overlapMultiple-1), input, sizeof(float)*bufferSize);
            }
    else {
        memcpy(block+numHops*bufferSize, input, sizeof(float)*bufferSize);
        numHops++;
    }
}

//-----------------------------------------------

void myReadAudio::processBlock(float* window, int windowBufferSize, int nChannels){
    
//    soundMutex.lock();
    for (int i=0; i<windowBufferSize; i++) {
        middleInput[i] = window[i];
    }
//    soundMutex.unlock();
    
    if (features != NULL) {
        features->extractFeatures(window,nChannels);
    }
    
//    audioBins = features->getNormalizedFftData();
//    
//    soundMutex.lock();
//    middleBins = audioBins;
//    soundMutex.unlock();
    
}

//------------------------------------------------
vector<float> myReadAudio::getInputVector() {
    return middleInput;
}
