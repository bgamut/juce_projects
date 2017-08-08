/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"
#include <string>
//#include <time.h>
class OneAudioProcessorEditor::ParameterSlider   : public Slider,
                                                   private Timer
{
public:
    ParameterSlider (AudioProcessorParameter& p)
    : Slider (p.getName (256)), param (p)
    {
        setRange (0.0, 1.0, 0.0);
        startTimerHz (30);
        updateSliderPos();
        
    }
    
    void valueChanged() override
    {
        if (isMouseButtonDown())
            param.setValueNotifyingHost ((float) Slider::getValue());
        else
            param.setValue ((float) Slider::getValue());
    }
    
    void timerCallback() override       { updateSliderPos(); }
    
    void startedDragging() override     { param.beginChangeGesture(); }
    void stoppedDragging() override     { param.endChangeGesture();   }
    
    double getValueFromText (const String& text) override   { return param.getValueForText (text); }
    String getTextFromValue (double value) override         { return param.getText ((float) value, 1024); }
    
    void updateSliderPos()
    {
        const float newValue = param.getValue();
        
        if (newValue != (float) Slider::getValue() && ! isMouseButtonDown())
            Slider::setValue (newValue);
    }
    
    AudioProcessorParameter &param;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterSlider)
};

//==============================================================================

OneAudioProcessorEditor::OneAudioProcessorEditor(OneAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    otherLookAndFeel.setColour(Slider::thumbColourId, juce::Colours::transparentBlack);
    //otherLookAndFeel.setColour(Slider::backgroundColourId, Colours::black);
    otherLookAndFeel.setColour(Slider::trackColourId, Colours::white);
    otherLookAndFeel.setColour(Slider::rotarySliderFillColourId, Colours::white);
    otherLookAndFeel.setColour(Slider::rotarySliderOutlineColourId, Colours::black);
    setSize (200, 200);
    
    //glow.setGlowProperties(5.0,Colours::grey);
    
    //glow.applyEffect(volume,g);
    //volume.setComponentEffect(glow);
    
    volume.setSliderStyle (Slider::Rotary);
    volume.setTextBoxStyle(Slider::NoTextBox,true,0,0);
    volume.setRange(0.0,1.0);
    volume.setValue(0.5);
    volume.setLookAndFeel(&otherLookAndFeel);
    volume.setScrollWheelEnabled(true);
    addAndMakeVisible(volume);
    startTimerHz(60);
    
}

OneAudioProcessorEditor::~OneAudioProcessorEditor()
{
}

//==============================================================================
void OneAudioProcessorEditor::paint (Graphics& g)
{
    float x=getWidth()/2.0;
    float y=getHeight()/2.0;
    g.fillAll (Colours::black);
    //g.setColour(Colours::black);
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.setColour(Colours::white);
    g.fillRect(0,int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.l7)));
    g.fillRect(0,int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.l6)));
    g.fillRect(0,int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.l5)));
    g.fillRect(0,int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.l4)));
    g.fillRect(0,int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.l3)));
    g.fillRect(0,int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.l2)));
    g.fillRect(0,int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.l1)));
    g.fillRect(0,int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.left)));
    g.fillRect(int(x),int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.r7)));
    g.fillRect(int(x),int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.r6)));
    g.fillRect(int(x),int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.r5)));
    g.fillRect(int(x),int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.r4)));
    g.fillRect(int(x),int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.r3)));
    g.fillRect(int(x),int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.r2)));
    g.fillRect(int(x),int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.r1)));
    g.fillRect(int(x),int(getHeight()),int(x),-(int)fabs(getHeight()*(processor.right)));
    
    
    g.setFont (10.0f);
    //g.drawFittedText (std::to_string(processor.monoLevel), getLocalBounds(), Justification::centred, 1);
    if (isnan(log(processor.left)/log(powf(2.0, 1.0/6.0))==0))
        {
            g.drawFittedText(std::to_string(log(processor.left)/log(powf(2.0, 1.0/6.0))),0,int(getHeight()-20),int(x),20,Justification::centred,1);
        }
    if (isnan(log(processor.right)/log(powf(2.0, 1.0/6.0))==0))
        {
            g.drawFittedText(std::to_string(log(processor.right)/log(powf(2.0, 1.0/6.0))),int(x),int(getHeight()-20),int(x),20,Justification::centred,1);
        }
    /*
    path.startNewSubPath(x*(1+processor.l5),y*(1-processor.r5));
    path.cubicTo(x,y,x*(1+processor.l0),y*(1-processor.r0),x*(1+processor.l1),y*(1-processor.r1));
    path.cubicTo(x*(1+processor.l1),y*(1-processor.r1),x*(1+processor.l2),y*(1-processor.r2),x*(1+processor.l3),y*(1-processor.r3));
    path.cubicTo(x*(1+processor.l3),y*(1-processor.r3),x*(1+processor.l4),y*(1-processor.r4),x*(1+processor.l5),y*(1-processor.r5));
    path.cubicTo(x*(1+processor.l5),y*(1-processor.r5),x*(1+processor.l6),y*(1-processor.r6),x*(1+processor.l7),y*(1-processor.r7));
    path.cubicTo(x*(1+processor.l7),y*(1-processor.r7),x*(1+processor.l8),y*(1-processor.r8),x*(1+processor.l9),y*(1-processor.r9));
    path.closeSubPath();
    g.strokePath(path,PathStrokeType (1.0f));
     */
    
    //g.stroke();
    setResizable(true,true);
    volume.setCentrePosition(x,y*1.05);
    sliderValueChanged(&volume);
    //tick+=1;
    //tick=tick%10;
}

void OneAudioProcessorEditor::resized()
{
    volume.setBounds(0,0,getWidth(),getHeight());
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
void OneAudioProcessorEditor::timerCallback()
{
    repaint();
}
void OneAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if(slider==&volume)
        {
            processor.sliderLevel=volume.getValue();
            //volume.setValue(processor.sliderLevel);
        }
    
}


