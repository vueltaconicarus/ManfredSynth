/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ManfredSynthGUI.h"

//bool ManfredSynthAudioProcessor::doChorus = CHORUSENABLE;

void ManfredSynthAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "chorusRate")
        chorus.setRate(newValue);
    else if (parameterID == "chorusDepth")
        chorus.setDepth(newValue);
    else if (parameterID == "chorusCentreDelay")
        chorus.setCentreDelay(newValue);
    else if (parameterID == "chorusFeedback")
        chorus.setFeedback(newValue);
    else if (parameterID == "chorusMix")
        chorus.setMix(newValue);
    /*else if (parameterID == "synthAttack")
        myVoice.env1.setAttack(newValue);
    else if (parameterID == "synthDecay")
        myVoice.env1.setDecay(newValue);
    else if (parameterID == "synthSustain")
        myVoice.env1.setSustain(newValue);
    else if (parameterID == "synthRelease")
        myVoice.env1.setRelease(newValue);
    else if (parameterID == "chorusEnable")
    {
        chorus_centredelay_slider->setEnabled(newValue);         // Enable or disable the corresponding parameter sliders
        chorus_depth_slider->setEnabled(newValue);
        chorus_rate_slider->setEnabled(newValue);
        chorus_mix_slider->setEnabled(newValue);
        chorus_feedback_slider->setEnabled(newValue);
    }*/

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
                                                        CHORUSMIX),              // default value
            std::make_unique<juce::AudioParameterFloat>("synthAttack",      // parameterID
                                                        "Synth Attack",     // parameter name
                                                        0.0f,               // minimum
                                                        5000.0f,             //maximum
                                                        SYNTHATTACK),              // default value
            std::make_unique<juce::AudioParameterFloat>("synthDecay",      // parameterID
                                                        "Synth Decay",     // parameter name
                                                        0.0f,               // minimum
                                                        5000.0f,             //maximum
                                                        SYNTHDECAY),              // default value
            std::make_unique<juce::AudioParameterFloat>("synthSustain",      // parameterID
                                                        "Synth Sustain",     // parameter name
                                                        0.0f,               // minimum
                                                        1.0f,             //maximum
                                                        SYNTHSUSTAIN),              // default value
            std::make_unique<juce::AudioParameterFloat>("synthRelease",      // parameterID
                                                        "Synth Release",     // parameter name
                                                        0.0f,               // minimum
                                                        5000.0f,             //maximum
                                                        SYNTHRELEASE)              // default value
        })
{    

    //std::make_unique<juce::AudioParameterChoice>("synthWave",
    //    "Synth Waveform",
    //    const juce::StringArray & ("Sine", "Square", "Saw", "Triangle"),
    //    "Sine")

    // prepare the third-party Maximilian synth
    // make sure there are no remaining data in the buffer before playing a synth sound
    mySynth.clearVoices();
    for (int i = 0; i < 6; ++i) // polyphonic with 6 voices
    {
        mySynth.addVoice(new SynthVoice());
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());

    // get the raw values out of my APVTS
    chorusEnableParameter       = parameters.getRawParameterValue("chorusEnable");
    chorusRateParameter         = parameters.getRawParameterValue("chorusRate");
    chorusDepthParameter        = parameters.getRawParameterValue("chorusDepth");
    chorusCentreDelayParameter  = parameters.getRawParameterValue("chorusCentreDelay");
    chorusFeedbackParameter     = parameters.getRawParameterValue("chorusFeedback");
    chorusMixParameter          = parameters.getRawParameterValue("chorusMix");
    synthAttackParameter        = parameters.getRawParameterValue("synthAttack");
    synthDecayParameter         = parameters.getRawParameterValue("synthDecay");
    synthSustainParameter       = parameters.getRawParameterValue("synthSustain");
    synthReleaseParameter       = parameters.getRawParameterValue("synthRelease");
    //synthWaveParameter          = parameters.getRawParameterValue("synthWave");

    // MV: add listeners
    parameters.addParameterListener("chorusRate", this);
    parameters.addParameterListener("chorusDepth", this);
    parameters.addParameterListener("chorusCentreDelay", this);
    parameters.addParameterListener("chorusFeedback", this);
    parameters.addParameterListener("chorusMix", this);
    parameters.addParameterListener("synthAttack", this);
    parameters.addParameterListener("synthRelease", this);
    parameters.addParameterListener("synthSustain", this);
    parameters.addParameterListener("synthRelease", this);
    //parameters.addParameterListener("synthWave", this);
}

ManfredSynthAudioProcessor::~ManfredSynthAudioProcessor()
{
    parameters.removeParameterListener("chorusRate", this);
    parameters.removeParameterListener("chorusDepth", this);
    parameters.removeParameterListener("chorusCentreDelay", this);
    parameters.removeParameterListener("chorusFeedback", this);
    parameters.removeParameterListener("chorusMix", this);
    parameters.removeParameterListener("synthAttack", this);
    parameters.removeParameterListener("synthRelease", this);
    parameters.removeParameterListener("synthSustain", this);
    parameters.removeParameterListener("synthRelease", this);
    //parameters.removeParameterListener("synthWave", this);
    //myVoice = nullptr;
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
    
    lastSampleRate = sampleRate; // make sure we use the same sample rate throughout this buffer. Just in case the sample rate should vary suddenly.
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

    /*
    // MV prepare the synth
    myVoice.env1.setAttack(SYNTHATTACK);
    myVoice.env1.setDecay(SYNTHDECAY);
    myVoice.env1.setSustain(SYNTHSUSTAIN);
    myVoice.env1.setRelease(SYNTHRELEASE);
    */

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

    for (int i = 0; i < mySynth.getNumVoices(); ++i)
    {
        myVoice.getParam((float*)synthAttackParameter);
    }

    buffer.clear();
    // play Maximilian synth sound according to MIDI message
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    // prepare objects for adding the chorus effect   
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
