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
//[/Headers]

#include "ManfredSynthGUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ManfredSynthGUI::ManfredSynthGUI ()
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

    reverb__toggleButton.reset (new juce::ToggleButton ("Reverb"));
    addAndMakeVisible (reverb__toggleButton.get());

    reverb__toggleButton->setBounds (224, 40, 100, 24);

    chorus__toggleButton.reset (new juce::ToggleButton ("Chorus"));
    addAndMakeVisible (chorus__toggleButton.get());
    chorus__toggleButton->addListener (this);

    chorus__toggleButton->setBounds (416, 40, 100, 24);

    reverb__slider.reset (new juce::Slider ("Reverb Slider"));
    addAndMakeVisible (reverb__slider.get());
    reverb__slider->setRange (0, 10, 0);
    reverb__slider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    reverb__slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    reverb__slider->setColour (juce::Slider::thumbColourId, juce::Colours::green);
    reverb__slider->addListener (this);

    reverb__slider->setBounds (224, 80, 150, 72);

    chorus__slider.reset (new juce::Slider ("Chorus Slider"));
    addAndMakeVisible (chorus__slider.get());
    chorus__slider->setRange (0, 10, 0);
    chorus__slider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    chorus__slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    chorus__slider->addListener (this);

    chorus__slider->setBounds (392, 80, 150, 72);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

    //[/Constructor]
}

ManfredSynthGUI::~ManfredSynthGUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    instrument__comboBox = nullptr;
    reverb__toggleButton = nullptr;
    chorus__toggleButton = nullptr;
    reverb__slider = nullptr;
    chorus__slider = nullptr;


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
        int x = 212, y = 28, width = 164, height = 140;
        juce::Colour strokeColour = juce::Colours::green;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 5);

    }

    {
        int x = 380, y = 28, width = 164, height = 140;
        juce::Colour strokeColour = juce::Colours::green;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 5);

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
        //[/UserButtonCode_chorus__toggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void ManfredSynthGUI::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == reverb__slider.get())
    {
        //[UserSliderCode_reverb__slider] -- add your slider handling code here..
        //[/UserSliderCode_reverb__slider]
    }
    else if (sliderThatWasMoved == chorus__slider.get())
    {
        //[UserSliderCode_chorus__slider] -- add your slider handling code here..
        //[/UserSliderCode_chorus__slider]
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
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="212 28 164 140" fill="solid: 8a2aa5" hasStroke="1" stroke="5, mitered, butt"
          strokeColour="solid: ff008000"/>
    <RECT pos="380 28 164 140" fill="solid: 8a2aa5" hasStroke="1" stroke="5, mitered, butt"
          strokeColour="solid: ff008000"/>
  </BACKGROUND>
  <COMBOBOX name="select instrument" id="5688c51200c22d75" memberName="instrument__comboBox"
            virtualName="" explicitFocusOrder="0" pos="44 36 100 30" editable="0"
            layout="33" items="Flute&#10;Guitar&#10;Piano" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="Reverb" id="9c249a027efacc8c" memberName="reverb__toggleButton"
                virtualName="" explicitFocusOrder="0" pos="224 40 100 24" buttonText="Reverb"
                connectedEdges="0" needsCallback="0" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="Chorus" id="a22b8495be480f90" memberName="chorus__toggleButton"
                virtualName="" explicitFocusOrder="0" pos="416 40 100 24" buttonText="Chorus"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="Reverb Slider" id="68b3e1a880e8c145" memberName="reverb__slider"
          virtualName="" explicitFocusOrder="0" pos="224 80 150 72" thumbcol="ff008000"
          min="0.0" max="10.0" int="0.0" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="Chorus Slider" id="9d4288d814062297" memberName="chorus__slider"
          virtualName="" explicitFocusOrder="0" pos="392 80 150 72" min="0.0"
          max="10.0" int="0.0" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

