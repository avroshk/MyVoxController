//
//  myFeatures.hpp
//  myVoxPlay
//
//  Created by Avrosh Kumar on 3/14/16.
//
//

#ifndef myFeatures_h
#define myFeatures_h

#include <stdio.h>
#include "ofxFft.h"

class myFeatures {
public:
    
    myFeatures(int,int); //Constructor
    myFeatures(); //Constructor
    ~myFeatures(); //Destructor -- not implemented yet
    
    void extractFeatures(float*,int); //processes FFT data, time domain signal, and calculates features //calls other private functions to calculate each feature
    
    int getNumOfFeatures();
    int getFftSize();
    vector<float> getFftData();
    vector<float> getNormalizedInputSignal();
    vector<float> getNormalizedFftData(); //helpful for displaying fft graphs
    float getSpectralFlux(float);
    float getSpectralFluxLog(float);
    float getSpectralRollOff(float);
    float getSpectralCentroid();
    float getSpectralSpread();
    float getSpectralDecrease();
    float getSpectralFlatness();
    float getSpectralCrest();
    vector<float> getPitchChroma();
    float getPitch();
    float getPitchChromaFlatness();
    float getPitchChromaCrestFactor();
    bool spectralFluxLevelCrossingRateChanged();
    bool getMostNotableOnsets();
    float getAdaptiveThreshold();
    bool isSilenceDetected();
    float getRms();
    
    vector<float> getNormalizedFeatureSet();
    
    int LCRFluxThreshold = 50; //default
    float instantaneousFluxThreshold=0.5; //default
    
private:
    int numFeatures = 10;
    
    ofxFft* fft;
    ofMutex soundMutex;
    
    void allocateMemory();
    void deallocateMemory();
    
    //eq-filtering
    float* eqFunction;
    float* eqOutput;
    vector<float> ifftLowPassedInput,ifftHighPassedInput;
    
    int fftSize, sampleRate, bufferSize;
    float* signal;
    vector <float> fftData, fftDataPrev, pitchChroma, finalPitchChroma, middlePitchChroma, normalizedInput, normalizedFft;
    
    float instantaneousFlux, instantaneousFluxLog, instantaneousFluxLP, instantaneousFluxPrev=0, instantaneousFluxLogPrev=0;
    float instantaneousRollOff, instantaneousRollOffPrev = 0, instantaneousRollOffLP;
    float instantaneousSC, instantaneousSS, instantaneousSD, instantaneousSF, instantaneousPCF;
    float instantaneousPitch, instantaneousSCR, instantaneousPCC;
    float sumOfFftBins,sumOfNormFftBins,rms;
    
    int LCRFlux = 0; //global counter in myFeatures
    float adaptiveThreshold = 0.0000125; //global
    bool flagAdaptiveThreshold = false;
    bool prevFlagAdaptiveThreshold = false;
    int thresholdClockValue = 50;
    int thresholdClock = thresholdClockValue;
    
    float alphaFlux,alphaRollOff;
    
    float referencePitch, curFreq, chromaSum, harmonicsSum,binFreqMultiple;
    vector< vector<float> > filterWeightsForPitchChroma;
    int matchedBinsCount,prevBinMidiPitch,currentBinMidiPitch,numOctaves,chromaMidiPitch,numNotesInOctave;
    
    void resetFeatures();
    void calcRms();
    
    void normalizeInputAudioBlock();
    void normalizeFft();
    void initPitchChromaWeightFilter();
    void calcFft();
    vector<float> filterSignal(bool lowPass);
    void calcNormFft();
    void findMaxBin();
    void sumFftBins();
    void sumNormFftBins();
    void calcSpectralFlux(float);
    void calcSpectralFluxLog();
    void calcSpectralRollOff(float);
    void calcSpectralCentroid();
    void calcSpectralSpread();
    void calcSpectralDecrease();
    void calcSpectralFlatness();
    void calcSpectralCrest();
    void calcPitchChroma();
    void resetPitchChroma();
    void calcPitchChromaFlatness();
    float calcPitchChromaCrestFactor(float); //called from calcPitchChroma()
    
    //Normalize features
    //Expose features
    
};


#endif /* myFeatures_h */