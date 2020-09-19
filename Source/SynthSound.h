/*
  ==============================================================================

    SynthSound.h
    Created: 19 Sep 2020 7:19:33pm
    Author:  Manfred Valentan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct SineWaveSound : public juce::SynthesiserSound
{
    SineWaveSound() {}

    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }
};

struct SynthSound : public juce::SynthesiserSound
{
    bool appliesToNote(int /*midi note number*/) override { return true; }
    bool appliesToChannel(int /*channel number*/) override { return true; }
};