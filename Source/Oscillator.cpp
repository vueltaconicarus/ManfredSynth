/*
  ==============================================================================

    Oscillator.cpp
    Created: 21 Sep 2020 11:53:33am
    Author:  Manfred Valentan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);
    oscMenu.setJustificationType(juce::Justification::centred);

}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (juce::Graphics& g)
{
    
}

void Oscillator::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //juce::Rectangle<int> area = 

}
