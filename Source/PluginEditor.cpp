/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ManfredSynthAudioProcessorEditor::ManfredSynthAudioProcessorEditor (ManfredSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 600); // MV: changed from (300, 400)

    // MV: these define the parameters of our slider object
    midiVolume.setSliderStyle(juce::Slider::LinearBarVertical);
    midiVolume.setRange(0.0, 127.0, 1.0);
    midiVolume.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    midiVolume.setPopupDisplayEnabled(true, false, this);
    midiVolume.setTextValueSuffix(" MIDI Volume");
    midiVolume.setValue(50.0);

    // MV: this function adds the slider to the editor
    addAndMakeVisible(&midiVolume);

    // MV: slider listener
    midiVolume.addListener(this);

    // MV: display gui elements
    addAndMakeVisible(&gui);   
}

ManfredSynthAudioProcessorEditor::~ManfredSynthAudioProcessorEditor()
{
}

// MV: this is the listener function that sets our public processor volume variable
void ManfredSynthAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    //audioProcessor.noteOnVel = midiVolume.getValue();
}


//==============================================================================
void ManfredSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    /*
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    */

    // fill the whole window grey
    g.fillAll(juce::Colour(0xff323e44));

    // set the current drawing colour to black (all subsequent drawings use the current drawing color)
    g.setColour(juce::Colours::white);

    // set the font size and draw text to the screen
    g.setFont(15.0f);

    g.drawFittedText("Midi Volume", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
    
}

void ManfredSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    // MV: sets the position and size of the slider with arguments (x, y, width, height)
    midiVolume.setBounds(40, 30, 20, getHeight() - 60);
    
    gui.setBounds(10, 10, getWidth(), getHeight());


}
