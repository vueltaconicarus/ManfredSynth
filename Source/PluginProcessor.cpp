/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ManfredSynthGUI.h"
#include "SynthSound.h"
#include "SynthVoice.h"

//bool ManfredSynthAudioProcessor::doChorus = CHORUSENABLE;

void ManfredSynthAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "chorusRate")
        chorus.setRate(newValue);
    else if(parameterID == "chorusDepth")
        chorus.setDepth(newValue);
    else if (parameterID == "chorusCentreDelay")
        chorus.setCentreDelay(newValue);
    else if (parameterID == "chorusFeedback")
        chorus.setFeedback(newValue);
    else if (parameterID == "chorusMix")
        chorus.setMix(newValue);     
}


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
                                                        99.0f,             //maximum
                                                        CHORUSRATE),              // default value
            std::make_unique<juce::AudioParameterFloat>("chorusDepth",      // parameterID
                                                        "Chorus Depth",     // parameter name
                                                        0.0f,               // minimum
                                                        1.0f,             //maximum
                                                        CHORUSDEPTH),              // default value
            std::make_unique<juce::AudioParameterFloat>("chorusCentreDelay",      // parameterID
                                                        "Chorus Centre Dealy",     // parameter name
                                                        1.0f,               // minimum
                                                        99.0f,             //maximum
                                                        CHORUSCENTREDELAY),              // default value
            std::make_unique<juce::AudioParameterFloat>("chorusFeedback",      // parameterID
                                                        "Chorus Feedback",     // parameter name
                                                        -1.0f,               // minimum
                                                        1.0f,             //maximum
                                                        CHORUSFEEDBACK),              // default value
            std::make_unique<juce::AudioParameterFloat>("chorusMix",      // parameterID
                                                        "Chorus Mix",     // parameter name
                                                        0.0f,               // minimum
                                                        1.0f,             //maximum
                                                        CHORUSMIX)              // default value
        })
{    

    //juce::dsp::Chorus<float> ManfredSynthAudioProcessor::chorus;    // Chorus effect

    synth.addSound(new SineWaveSound());
    for (int i = 0; i < 6; ++i)
    {
        synth.addVoice(new SineWaveVoice());
    }
 
    chorusEnableParameter       = parameters.getRawParameterValue("chorusEnable");
    chorusRateParameter         = parameters.getRawParameterValue("chorusRate");
    chorusDepthParameter        = parameters.getRawParameterValue("chorusDepth");
    chorusCentreDelayParameter  = parameters.getRawParameterValue("chorusCentreDelay");
    chorusFeedbackParameter     = parameters.getRawParameterValue("chorusFeedback");
    chorusMixParameter          = parameters.getRawParameterValue("chorusMix");

    // MV: add listeners
    parameters.addParameterListener("chorusRate", this);
    parameters.addParameterListener("chorusDepth", this);
    parameters.addParameterListener("chorusCentreDelay", this);
    parameters.addParameterListener("chorusFeedback", this);
    parameters.addParameterListener("chorusMix", this);
}

ManfredSynthAudioProcessor::~ManfredSynthAudioProcessor()
{
    parameters.removeParameterListener("chorusRate", this);
    parameters.removeParameterListener("chorusDepth", this);
    parameters.removeParameterListener("chorusCentreDelay", this);
    parameters.removeParameterListener("chorusFeedback", this);
    parameters.removeParameterListener("chorusMix", this);
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
    //chorus.setCentreDelay(CHORUSCENTREDELAY);
    //chorus.setFeedback(CHORUSFEEDBACK);
    //chorus.setMix(CHORUSMIX);
    //chorus.setRate(CHORUSRATE);
    //chorus.setDepth(CHORUSDEPTH);

    //bool b = CHORUSENABLE;


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
    float theWave = Oscillator.sinewave(440);
    buffer.clear();

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
    juce::MemoryOutputStream(destData, true).writeBool(*chorusEnableParameter);
    juce::MemoryOutputStream(destData, true).writeFloat(*chorusRateParameter);
    juce::MemoryOutputStream(destData, true).writeFloat(*chorusDepthParameter);
    juce::MemoryOutputStream(destData, true).writeFloat(*chorusCentreDelayParameter);
    juce::MemoryOutputStream(destData, true).writeFloat(*chorusFeedbackParameter);
    juce::MemoryOutputStream(destData, true).writeFloat(*chorusMixParameter);
}

void ManfredSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    *chorusEnableParameter = juce::MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readBool();
    *chorusRateParameter = juce::MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readFloat();
    *chorusDepthParameter = juce::MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readFloat();
    *chorusCentreDelayParameter = juce::MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readFloat();
    *chorusFeedbackParameter = juce::MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readFloat();
    *chorusMixParameter = juce::MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readFloat();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ManfredSynthAudioProcessor();
}
