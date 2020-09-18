/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <sstream>
#include "ManfredSynthGUI.h"

//==============================================================================
/**
*/
class ManfredSynthAudioProcessorEditor  :   public juce::AudioProcessorEditor
{
public:
    ManfredSynthAudioProcessorEditor (ManfredSynthAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~ManfredSynthAudioProcessorEditor() override;

    //==============================================================================

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ManfredSynthAudioProcessor& audioProcessor;

    // This holds the APVTS which comes from the processor, and is handed over to the GUI
    juce::AudioProcessorValueTreeState& valueTreeState;

    // This is an instance of my gui class, the "main component"
    ManfredSynthGUI gui;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ManfredSynthAudioProcessorEditor)
};