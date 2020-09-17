/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ManfredSynthGUI.h"


//bool ManfredSynthAudioProcessor::doChorus = CHORUSENABLE;
juce::dsp::Chorus<float> ManfredSynthAudioProcessor::chorus;    // Chorus effect

struct SineWaveSound : public juce::SynthesiserSound
{
    SineWaveSound() {}

    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }
};

struct SineWaveVoice : public juce::SynthesiserVoice
{
    SineWaveVoice() {}

    bool canPlaySound(juce::SynthesiserSound* sound) override
    {
        return dynamic_cast<SineWaveSound*> (sound) != nullptr;
    }

    void startNote(int midiNoteNumber, float velocity,
        juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    {
        currentAngle = 0.0;
        level = velocity * 0.15;
        tailOff = 0.0;

        auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        auto cyclesPerSample = cyclesPerSecond / getSampleRate();

        angleDelta = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;
    }

    void stopNote(float /*velocity*/, bool allowTailOff) override
    {
        if (allowTailOff)
        {
            if (tailOff == 0.0)
                tailOff = 1.0;
        }
        else
        {
            clearCurrentNote();
            angleDelta = 0.0;
        }
    }

    void pitchWheelMoved(int) override {}
    void controllerMoved(int, int) override {}

    void renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        if (angleDelta != 0.0)
        {
            if (tailOff > 0.0) // [7]
            {
                while (--numSamples >= 0)
                {
                    auto currentSample = (float)(std::sin(currentAngle) * level * tailOff);

                    for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample(i, startSample, currentSample);

                    currentAngle += angleDelta;
                    ++startSample;

                    tailOff *= 0.99; // [8]

                    if (tailOff <= 0.005)
                    {
                        clearCurrentNote(); // [9]

                        angleDelta = 0.0;
                        break;
                    }
                }
            }
            else
            {
                while (--numSamples >= 0) // [6]
                {
                    auto currentSample = (float)(std::sin(currentAngle) * level);

                    for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample(i, startSample, currentSample);

                    currentAngle += angleDelta;
                    ++startSample;
                }
            }
        }
    }

private:
    double currentAngle = 0.0, angleDelta = 0.0, level = 0.0, tailOff = 0.0;
};

//==============================================================================
ManfredSynthAudioProcessor::ManfredSynthAudioProcessor()
    :
#ifndef JucePlugin_PreferredChannelConfigurations
     AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif */
    parameters(*this, nullptr, juce::Identifier("ManfredSynth"),
        {
            std::make_unique<juce::AudioParameterBool>("chorusEnable",      // parameterID
                                                        "Chorus Enable",     // parameter name
                                                        CHORUSENABLE),              // default value
            std::make_unique<juce::AudioParameterFloat>("chorusRate",      // parameterID
                                                        "Chorus Rate",     // parameter name
                                                        0.0f,               // minimum
                                                        100.0f,             //maximum
                                                        CHORUSRATE),              // default value
            std::make_unique<juce::AudioParameterFloat>("chorusDepth",      // parameterID
                                                        "Chorus Depth",     // parameter name
                                                        0.0f,               // minimum
                                                        1.0f,             //maximum
                                                        CHORUSDEPTH)              // default value
        })
{    
    synth.addSound(new SineWaveSound());
    for (int i = 0; i < 6; ++i)
    {
        synth.addVoice(new SineWaveVoice());
    }
 
    chorusEnableParameter   = parameters.getRawParameterValue("chorusEnable");
    chorusRateParameter     = parameters.getRawParameterValue("chorusRate");
}

ManfredSynthAudioProcessor::~ManfredSynthAudioProcessor()
{
}

//==============================================================================
const juce::String ManfredSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ManfredSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ManfredSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ManfredSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ManfredSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ManfredSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ManfredSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ManfredSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ManfredSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void ManfredSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ManfredSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    // MV: prepare the Chorus effect
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getNumOutputChannels();
    chorus.prepare(spec);
    
    // MV: prepare dummy JUCE synthesizer
    synth.setCurrentPlaybackSampleRate(sampleRate);

    // MV: define default parameters of the chorus
    chorus.setCentreDelay(CHORUSCENTREDELAY);
    chorus.setFeedback(CHORUSFEEDBACK);
    chorus.setMix(CHORUSMIX);
    chorus.setRate(CHORUSRATE);
    chorus.setDepth(CHORUSDEPTH);

}

void ManfredSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ManfredSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ManfredSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    /* MV: we don't need this for the Midi Volume tutorial
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    */

    buffer.clear();

    juce::MidiBuffer processedMidi;
    int time;
    juce::MidiMessage m;

    for (juce::MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
    {
        if (m.isNoteOn())
        {
            //m = juce::MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
        }
        else if (m.isNoteOff())
        {
        }
        else if (m.isAftertouch())
        {
        }
        else if (m.isPitchWheel())
        {
        }

        processedMidi.addEvent(m, time);
    }

    midiMessages.swapWith(processedMidi);

    // play synth sound according to MIDI message
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);

    // add Chorus effect
    // alternative: if (*chorusEnableParameter)
    if (*parameters.getRawParameterValue("chorusEnable"))
    {
        chorus.process(context);
    }

}

//==============================================================================
bool ManfredSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ManfredSynthAudioProcessor::createEditor()
{
    return new ManfredSynthAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void ManfredSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ManfredSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ManfredSynthAudioProcessor();
}
