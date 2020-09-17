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

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
//[/Headers]

#include "ManfredSynthGUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ManfredSynthGUI::ManfredSynthGUI (juce::AudioProcessorValueTreeState& vts)
    : valueTreeState (vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    instrument__comboBox.reset (new juce::ComboBox ("select instrument"));
    addAndMakeVisible (instrument__comboBox.get());
    instrument__comboBox->setEditableText (false);
    instrument__comboBox->setJustificationType (juce::Justification::centredLeft);
    instrument__comboBox->setTextWhenNothingSelected (juce::String());
    instrument__comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    instrument__comboBox->addItem (TRANS("Flute"), 1);
    instrument__comboBox->addItem (TRANS("Guitar"), 2);
    instrument__comboBox->addItem (TRANS("Piano"), 3);
    instrument__comboBox->addListener (this);

    instrument__comboBox->setBounds (44, 36, 100, 30);

    chorus__toggleButton.reset (new juce::ToggleButton ("Chorus"));
    addAndMakeVisible (chorus__toggleButton.get());
    chorus__toggleButton->addListener (this);

    chorus__toggleButton->setBounds (416, 40, 100, 24);

    chorus_rate_slider.reset (new juce::Slider ("Chorus Rate Slider"));
    addAndMakeVisible (chorus_rate_slider.get());
    chorus_rate_slider->setRange (0, 100, 0.1);
    chorus_rate_slider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    chorus_rate_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    chorus_rate_slider->addListener (this);

    chorus_rate_slider->setBounds (392, 80, 150, 72);

    chorus_depth_slider.reset (new juce::Slider ("Chorus Depth Slider"));
    addAndMakeVisible (chorus_depth_slider.get());
    chorus_depth_slider->setRange (0, 1, 0.01);
    chorus_depth_slider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    chorus_depth_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    chorus_depth_slider->addListener (this);

    chorus_depth_slider->setBounds (392, 144, 150, 72);

    chorus_centredelay_slider.reset (new juce::Slider ("Chorus CentreDelay Slider"));
    addAndMakeVisible (chorus_centredelay_slider.get());
    chorus_centredelay_slider->setRange (0, 100, 1);
    chorus_centredelay_slider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    chorus_centredelay_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    chorus_centredelay_slider->addListener (this);

    chorus_centredelay_slider->setBounds (392, 208, 150, 72);

    chorus_feedback_slider.reset (new juce::Slider ("Chorus Feedback Slider"));
    addAndMakeVisible (chorus_feedback_slider.get());
    chorus_feedback_slider->setRange (-1, 1, 0.01);
    chorus_feedback_slider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    chorus_feedback_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    chorus_feedback_slider->addListener (this);

    chorus_feedback_slider->setBounds (392, 272, 150, 72);

    chorus_mix_slider.reset (new juce::Slider ("Chorus Mix Slider"));
    addAndMakeVisible (chorus_mix_slider.get());
    chorus_mix_slider->setRange (0, 1, 0.01);
    chorus_mix_slider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    chorus_mix_slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    chorus_mix_slider->addListener (this);

    chorus_mix_slider->setBounds (392, 336, 150, 72);


    //[UserPreSize]
    chorusEnableAttachment.reset(new ButtonAttachment(valueTreeState, "chorusEnable", *chorus__toggleButton.get()));
    chorusRateAttachment.reset(new SliderAttachment(valueTreeState, "chorusRate", *chorus_rate_slider.get()));
    //chorusDepthAttachment .reset(new SliderAttachment(valueTreeState, "chorusDepth",  *chorus_depth_slider .get()));
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    // set initial chorus values on sliders
    chorus_rate_slider->setValue(CHORUSRATE);
    chorus_depth_slider->setValue(CHORUSDEPTH);
    chorus_centredelay_slider->setValue(CHORUSCENTREDELAY);
    chorus_feedback_slider->setValue(CHORUSFEEDBACK);
    chorus_mix_slider->setValue(CHORUSMIX);

    // set initial enable state of the components
    //ManfredSynthAudioProcessor::doChorus = CHORUSENABLE;
    chorus_centredelay_slider->setEnabled(CHORUSENABLE);
    chorus_depth_slider->setEnabled(CHORUSENABLE);
    chorus_rate_slider->setEnabled(CHORUSENABLE);
    chorus_mix_slider->setEnabled(CHORUSENABLE);
    chorus_feedback_slider->setEnabled(CHORUSENABLE);

    //[/Constructor]
}

ManfredSynthGUI::~ManfredSynthGUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    chorusEnableAttachment = nullptr;
    chorusRateAttachment = nullptr;
    chorusDepthAttachment = nullptr;
    //[/Destructor_pre]

    instrument__comboBox = nullptr;
    chorus__toggleButton = nullptr;
    chorus_rate_slider = nullptr;
    chorus_depth_slider = nullptr;
    chorus_centredelay_slider = nullptr;
    chorus_feedback_slider = nullptr;
    chorus_mix_slider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

    //[/Destructor]
}

//==============================================================================
void ManfredSynthGUI::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    {
        int x = 380, y = 28, width = 164, height = 404;
        juce::Colour strokeColour = juce::Colours::green;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 5);

    }

    {
        int x = 396, y = 84, width = 80, height = 26;
        juce::String text (TRANS("Rate (Hz)"));
        juce::Colour fillColour = juce::Colours::azure;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 396, y = 140, width = 92, height = 26;
        juce::String text (TRANS("Depth"));
        juce::Colour fillColour = juce::Colours::azure;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 396, y = 204, width = 92, height = 26;
        juce::String text (TRANS("Centre Delay (ms)"));
        juce::Colour fillColour = juce::Colours::azure;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 396, y = 268, width = 92, height = 26;
        juce::String text (TRANS("Feedback"));
        juce::Colour fillColour = juce::Colours::azure;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 396, y = 332, width = 92, height = 26;
        juce::String text (TRANS("Mix"));
        juce::Colour fillColour = juce::Colours::azure;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ManfredSynthGUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ManfredSynthGUI::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == instrument__comboBox.get())
    {
        //[UserComboBoxCode_instrument__comboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_instrument__comboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void ManfredSynthGUI::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == chorus__toggleButton.get())
    {
        //[UserButtonCode_chorus__toggleButton] -- add your button handler code here..
        bool enabled = buttonThatWasClicked->getToggleState();  // read the new value into local variable
        //ManfredSynthAudioProcessor::doChorus = enabled;         // make new state available to the audio thread
        chorus_centredelay_slider->setEnabled(enabled);         // Enable or disable the corresponding parameter sliders
        chorus_depth_slider->setEnabled(enabled);
        chorus_rate_slider->setEnabled(enabled);
        chorus_mix_slider->setEnabled(enabled);
        chorus_feedback_slider->setEnabled(enabled);
        //[/UserButtonCode_chorus__toggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void ManfredSynthGUI::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == chorus_rate_slider.get())
    {
        //[UserSliderCode_chorus_rate_slider] -- add your slider handling code here..
        ManfredSynthAudioProcessor::chorus.setRate(sliderThatWasMoved->getValue());
        //ManfredSynthAudioProcessor::chorus.setRate(*valueTreeState.getRawParameterValue("chorusRate"));
        //[/UserSliderCode_chorus_rate_slider]
    }
    else if (sliderThatWasMoved == chorus_depth_slider.get())
    {
        //[UserSliderCode_chorus_depth_slider] -- add your slider handling code here..
        ManfredSynthAudioProcessor::chorus.setDepth(sliderThatWasMoved->getValue());
        //[/UserSliderCode_chorus_depth_slider]
    }
    else if (sliderThatWasMoved == chorus_centredelay_slider.get())
    {
        //[UserSliderCode_chorus_centredelay_slider] -- add your slider handling code here..
        ManfredSynthAudioProcessor::chorus.setCentreDelay(sliderThatWasMoved->getValue());
        //[/UserSliderCode_chorus_centredelay_slider]
    }
    else if (sliderThatWasMoved == chorus_feedback_slider.get())
    {
        //[UserSliderCode_chorus_feedback_slider] -- add your slider handling code here..
        ManfredSynthAudioProcessor::chorus.setFeedback(sliderThatWasMoved->getValue());
        //[/UserSliderCode_chorus_feedback_slider]
    }
    else if (sliderThatWasMoved == chorus_mix_slider.get())
    {
        //[UserSliderCode_chorus_mix_slider] -- add your slider handling code here..
        ManfredSynthAudioProcessor::chorus.setMix(sliderThatWasMoved->getValue());
        //[/UserSliderCode_chorus_mix_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ManfredSynthGUI" componentName=""
                 parentClasses="public juce::Component" constructorParams="juce::AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="valueTreeState (vts)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="380 28 164 404" fill="solid: 8a2aa5" hasStroke="1" stroke="5, mitered, butt"
          strokeColour="solid: ff008000"/>
    <TEXT pos="396 84 80 26" fill="solid: fff0ffff" hasStroke="0" text="Rate (Hz)"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
    <TEXT pos="396 140 92 26" fill="solid: fff0ffff" hasStroke="0" text="Depth"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
    <TEXT pos="396 204 92 26" fill="solid: fff0ffff" hasStroke="0" text="Centre Delay (ms)"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
    <TEXT pos="396 268 92 26" fill="solid: fff0ffff" hasStroke="0" text="Feedback"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
    <TEXT pos="396 332 92 26" fill="solid: fff0ffff" hasStroke="0" text="Mix"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
  </BACKGROUND>
  <COMBOBOX name="select instrument" id="5688c51200c22d75" memberName="instrument__comboBox"
            virtualName="" explicitFocusOrder="0" pos="44 36 100 30" editable="0"
            layout="33" items="Flute&#10;Guitar&#10;Piano" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="Chorus" id="a22b8495be480f90" memberName="chorus__toggleButton"
                virtualName="" explicitFocusOrder="0" pos="416 40 100 24" buttonText="Chorus"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="Chorus Rate Slider" id="9d4288d814062297" memberName="chorus_rate_slider"
          virtualName="" explicitFocusOrder="0" pos="392 80 150 72" min="0.0"
          max="100.0" int="0.1" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Chorus Depth Slider" id="d172cd517d235994" memberName="chorus_depth_slider"
          virtualName="" explicitFocusOrder="0" pos="392 144 150 72" min="0.0"
          max="1.0" int="0.01" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Chorus CentreDelay Slider" id="7e09c0474e28e150" memberName="chorus_centredelay_slider"
          virtualName="" explicitFocusOrder="0" pos="392 208 150 72" min="0.0"
          max="100.0" int="1.0" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Chorus Feedback Slider" id="c8f3fac5cde63f07" memberName="chorus_feedback_slider"
          virtualName="" explicitFocusOrder="0" pos="392 272 150 72" min="-1.0"
          max="1.0" int="0.01" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Chorus Mix Slider" id="28a4bd3fd08aa70f" memberName="chorus_mix_slider"
          virtualName="" explicitFocusOrder="0" pos="392 336 150 72" min="0.0"
          max="1.0" int="0.01" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

