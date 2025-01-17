/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ManfredSynthGUI  : public juce::Component,
                         public juce::ComboBox::Listener,
                         public juce::Button::Listener,
                         public juce::Slider::Listener
{
public:
    //==============================================================================
    ManfredSynthGUI (juce::AudioProcessorValueTreeState& vts);
    ~ManfredSynthGUI() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    // Shortcuts for long commands
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    typedef juce::AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

    // this holds the APVTS which originated in the processor, and came here via the editor
    juce::AudioProcessorValueTreeState& valueTreeState;

    // Component attachments
    std::unique_ptr<ButtonAttachment> chorusEnableAttachment;
    std::unique_ptr<SliderAttachment> chorusRateAttachment;
    std::unique_ptr<SliderAttachment> chorusDepthAttachment;
    std::unique_ptr<SliderAttachment> chorusCentreDelayAttachment;
    std::unique_ptr<SliderAttachment> chorusFeedbackAttachment;
    std::unique_ptr<SliderAttachment> chorusMixAttachment;
    std::unique_ptr<SliderAttachment> synthAttackAttachment;
    std::unique_ptr<SliderAttachment> synthDecayAttachment;
    std::unique_ptr<SliderAttachment> synthSustainAttachment;
    std::unique_ptr<SliderAttachment> synthReleaseAttachment;
    std::unique_ptr<ComboBoxAttachment> synthWaveAttachment;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ComboBox> synth_wave_comboBox;
    std::unique_ptr<juce::ToggleButton> chorus__toggleButton;
    std::unique_ptr<juce::Slider> chorus_rate_slider;
    std::unique_ptr<juce::Slider> chorus_depth_slider;
    std::unique_ptr<juce::Slider> chorus_centredelay_slider;
    std::unique_ptr<juce::Slider> chorus_feedback_slider;
    std::unique_ptr<juce::Slider> chorus_mix_slider;
    std::unique_ptr<juce::Slider> synth_attack_slider;
    std::unique_ptr<juce::Slider> synth_decay_slider;
    std::unique_ptr<juce::Slider> synth_sustain_slider;
    std::unique_ptr<juce::Slider> synth_release_slider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ManfredSynthGUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

