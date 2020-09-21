/*
  ==============================================================================

    SynthVoice.h
    Created: 19 Sep 2020 7:19:52pm
    Author:  Manfred Valentan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "maximilian.h"

struct SynthVoice : public juce::SynthesiserVoice
{
    bool canPlaySound(juce::SynthesiserSound* sound) override
    {
        // check if our derived class is correct: down-cast a base-class object to our derived class. If the cast is unsuccessful, it will return nullptr.
        return dynamic_cast<SynthSound*> (sound) != nullptr;
    }

    void setEnvelopeParameters(float* attackPtr, float* decayPtr, float* sustainPtr, float* releasePtr)
    {
        env1.setAttack(*attackPtr);
        env1.setDecay(*decayPtr);
        env1.setSustain(*sustainPtr);
        env1.setRelease(*releasePtr);
    }

    void setOscType(float* selection)
    {
        theWave = *selection;
    }

    double oscType()
    {
        switch (theWave)
        {
        case 0: return osc1.sinewave(frequency);
        case 1: return osc1.square(frequency);
        case 2: return osc1.saw(frequency);
        case 3: return osc1.triangle(frequency);
        default: return osc1.sinewave(frequency);
        }
    }

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        env1.trigger = true; // the evnelope starts here
        level = velocity;
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }

    void stopNote(float velocity, bool allowTailOff) override
    {
        env1.trigger = false; // the envelope ends here

        allowTailOff = true;

        if (velocity == 0) clearCurrentNote();

    }

    void pitchWheelMoved(int newPitchWheelValue) override
    {

    }

    void controllerMoved(int controllerNumber, int newControllerValue) override
    {

    }

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {

        double theWave;
        double theSound;

        for (int sample = 0; sample < numSamples; ++sample)
        {
            //theWave = osc1.sinewave(frequency);
            theSound = env1.adsr(oscType(), env1.trigger) * level;

            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, theSound);
            }
            ++startSample;
        }
    }

private:
    double level;
    double frequency;
    maxiOsc osc1;   // Maximilian oscillator
    maxiEnv env1;   // Maximilian envelope, to prevent clicks at the start and end of the note
    int theWave;
};