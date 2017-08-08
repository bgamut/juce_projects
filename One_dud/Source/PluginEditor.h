/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
 */
class OneAudioProcessorEditor  : public AudioProcessorEditor,
private Timer
{
public:
    OneAudioProcessorEditor (OneAudioProcessor&);
    ~OneAudioProcessorEditor();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void sliderValueChanged(Slider* slider);
    
    
private:
    class ParameterSlider;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    OneAudioProcessor& processor;
    Slider volume;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OneAudioProcessorEditor)
    LookAndFeel_V4 otherLookAndFeel;
    Path path;
    GlowEffect glow;
};

