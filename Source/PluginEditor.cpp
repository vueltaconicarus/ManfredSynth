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

    // MV: display gui elements
    addAndMakeVisible(&gui);
  }

ManfredSynthAudioProcessorEditor::~ManfredSynthAudioProcessorEditor()
{
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

}

void ManfredSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    gui.setBounds(10, 10, getWidth(), getHeight());


}
