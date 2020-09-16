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
// start values of the chorus effect
#define CHORUSENABLE 0
#define CHORUSRATE 5
#define CHORUSDEPTH 0.2
#define CHORUSCENTREDELAY 10
#define CHORUSFEEDBACK 0
#define CHORUSMIX 0.5

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
    ManfredSynthGUI ();
    ~ManfredSynthGUI() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ComboBox> instrument__comboBox;
    std::unique_ptr<juce::ToggleButton> reverb__toggleButton;
    std::unique_ptr<juce::ToggleButton> chorus__toggleButton;
    std::unique_ptr<juce::Slider> reverb__slider;
    std::unique_ptr<juce::Slider> chorus_rate_slider;
    std::unique_ptr<juce::Slider> chorus_depth_slider;
    std::unique_ptr<juce::Slider> chorus_centredelay_slider;
    std::unique_ptr<juce::Slider> chorus_feedback_slider;
    std::unique_ptr<juce::Slider> chorus_mix_slider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ManfredSynthGUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

