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
class ManfredSynthAudioProcessorEditor  :   public juce::AudioProcessorEditor,
                                            private juce::Slider::Listener  // MV: added Slider::Listener inheritance to Editor class
{
public:
    ManfredSynthAudioProcessorEditor (ManfredSynthAudioProcessor&);
    ~ManfredSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    void sliderValueChanged(juce::Slider* slider) override; // MV: default callback function

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ManfredSynthAudioProcessor& audioProcessor;

    // MV: create a slider for setting the MIDI volume (MIDI velocity)
    juce::Slider midiVolume;
    ManfredSynthGUI gui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ManfredSynthAudioProcessorEditor)
};
