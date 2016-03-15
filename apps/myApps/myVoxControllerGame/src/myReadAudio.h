//
//  myReadAudio.hpp
//  myVoxPlay
//
//  Created by Avrosh Kumar on 3/14/16.
//
//

#ifndef myReadAudio_h
#define myReadAudio_h

#include <stdio.h>
#include "ofxLibsndFileRecorder.h"
#include "sndfile.h"
#include "myFeatures.h"

class myReadAudio {
public:
    myReadAudio();
    ~myReadAudio();

    void init(ofBaseApp * app,
              int bufferSize,
              int overlapMultiple,
              int sampleRate,
              int numBuffers,
              int numInputs,
              int numOutputs,
              int deviceId);
    
    void initFeatures(myFeatures *features);

    vector<float> getInputVector();
    
    void audioReceived(float* input, int bufferSize, int nChannels);
    
private:
    
//    ofSoundStream soundStream; //For live audio
    
    void setupStream(ofBaseApp * app);
    void allocateMemory();
    void deallocateMemory();
    void resetMemory();
    
   
    void blockAndProcessAudioData(float* input, int bufferSize, int nChannels);
    void processBlock(float* block, int windowBuffer, int nChannels);

    int bufferSize;
    int overlapMultiple;
    int numBuffers;
    int sampleRate;
    int numHops;
    int numInputs;
    int numOutputs;
    int deviceId;
    
//    vector<float> drawBins, middleBins, audioBins, leftInput, rightInput, downMixedInput, pitchChroma, normalizedInput,drawInput, middleInput, downMixed;
    
    vector<float> middleInput;
    
    float* block;
    myFeatures *features;
    
};

#endif /* myReadAudio_h */
