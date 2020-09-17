/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class ManfredSynthAudioProcessor  : public juce::AudioProcessor
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
    static juce::dsp::Chorus<float> chorus;    // Chorus effect
    juce::Synthesiser synth;            // built-in synth, to be replaced by a third-party one
    
private:
    //==============================================================================
    
    // define a APVTS for our plugin parameters
    juce::AudioProcessorValueTreeState parameters;
    std::atomic<float>* chorusEnableParameter = nullptr;
    std::atomic<float>* chorusRateParameter   = nullptr;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ManfredSynthAudioProcessor)
};

