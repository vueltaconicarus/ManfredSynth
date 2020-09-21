/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "maximilian.h"
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
/**
*/
class ManfredSynthAudioProcessor  : public juce::AudioProcessor,
                                    public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    ManfredSynthAudioProcessor();
    ~ManfredSynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // MV ===========================================================================
    juce::dsp::Chorus<float> chorus;    // Chorus effect
       
    void parameterChanged(const juce::String&, float) override;

    // default values for the chorus
    static constexpr bool  CHORUSENABLE = false;
    static constexpr float CHORUSRATE = 5;
    static constexpr float CHORUSDEPTH = 0.2;
    static constexpr float CHORUSCENTREDELAY = 10;
    static constexpr float CHORUSFEEDBACK = 0;
    static constexpr float CHORUSMIX = 0.5;
    static constexpr float SYNTHATTACK = 500;
    static constexpr float SYNTHDECAY = 500;
    static constexpr float SYNTHSUSTAIN = 0.8;
    static constexpr float SYNTHRELEASE = 1000;

    // from Maximilian Synth Tutorial
    juce::Synthesiser mySynth;          // synthesizer using the third-party Maximilian library
    SynthVoice* myVoice;
    double lastSampleRate;
    
private:
    //==============================================================================
    
    // define a APVTS for our plugin parameters
    juce::AudioProcessorValueTreeState parameters;
    std::atomic<float>* chorusEnableParameter       = nullptr;
    std::atomic<float>* chorusRateParameter         = nullptr;
    std::atomic<float>* chorusDepthParameter        = nullptr;
    std::atomic<float>* chorusCentreDelayParameter  = nullptr;
    std::atomic<float>* chorusFeedbackParameter     = nullptr;
    std::atomic<float>* chorusMixParameter          = nullptr;
    std::atomic<float>* synthAttackParameter        = nullptr;
    std::atomic<float>* synthDecayParameter         = nullptr;
    std::atomic<float>* synthSustainParameter       = nullptr;
    std::atomic<float>* synthReleaseParameter       = nullptr;
    std::atomic<float>* synthWaveParameter          = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ManfredSynthAudioProcessor)
};

