/*
  ==============================================================================

    Oscillator.h
    Created: 21 Sep 2020 11:53:33am
    Author:  Manfred Valentan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Oscillator  : public juce::Component
{
public:
    Oscillator();
    ~Oscillator() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscMenu;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
