/*
 ==============================================================================
 
 This file is part of the JUCE library.
 Copyright (c) 2015 - ROLI Ltd.
 
 Permission is granted to use this software under the terms of either:
 a) the GPL v2 (or any later version)
 b) the Affero GPL v3
 
 Details of these licenses can be found at: www.gnu.org/licenses
 
 JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
 ------------------------------------------------------------------------------
 
 To release a closed-source product which uses JUCE, commercial licenses are
 available: visit www.juce.com for more information.
 
 ==============================================================================
 */
/*
#define JucePlugin_MaxNumInputChannels 2
#define JucePlugin_MaxNumOutputChannels 2
#define JucePlugin_PreferredChannelConfigurations {1, 1}, {2, 2}
*/


class GenericEditor : public AudioProcessorEditor,
public Slider::Listener,
private Timer
{
public:
    enum
    {
        kParamControlHeight = 40,
        kParamLabelWidth = 80,
        kParamSliderWidth = 300
    };
    
    GenericEditor (AudioProcessor& parent)
    : AudioProcessorEditor (parent),
    noParameterLabel ("noparam", "No parameters available")
    {
        otherLookAndFeel.setColour(Slider::thumbColourId, juce::Colours::transparentBlack);
        otherLookAndFeel.setColour(Slider::backgroundColourId, Colours::grey);
        otherLookAndFeel.setColour(Slider::trackColourId, Colours::white);
        otherLookAndFeel.setColour(Slider::rotarySliderFillColourId, Colours::white);
        otherLookAndFeel.setColour(Slider::rotarySliderOutlineColourId, Colours::black);
        float x=100;
        float y=100;
        
        setSize(200,200);
        const OwnedArray<AudioProcessorParameter>& params = parent.getParameters();
        
        for (int i = 0; i < params.size(); ++i)
        {
            /*
            if (const AudioParameterFloat* param = dynamic_cast<AudioParameterFloat*> (params[i]))
            {
                Slider* aSlider;
                
                paramSliders.add (aSlider = new Slider (param->name));
                aSlider->setRange (param->range.start, param->range.end);
                aSlider->setSliderStyle (Slider::LinearHorizontal);
                //aSlider->setSliderStyle (Slider::Rotary);
                //aSlider->setTextBoxStyle(Slider::NoTextBox,true,0,0);
                aSlider->setLookAndFeel(&otherLookAndFeel);
                aSlider->setValue (*param);
                aSlider->addListener (this);
                //aSlider->setCentrePosition(x,y*1.05);
                addAndMakeVisible (aSlider);
                
                Label* aLabel;
                paramLabels.add (aLabel = new Label (param->name, param->name));
                addAndMakeVisible (aLabel);
            }
             */
            if (const AudioParameterFloat* param = dynamic_cast<AudioParameterFloat*> (params[i]))
            {
                if(param->name=="Volume")
                {
                    Slider* aSlider;
                    
                    paramSliders.add (aSlider = new Slider (param->name));
                    aSlider->setRange (param->range.start, param->range.end);
                    //aSlider->setSliderStyle (Slider::LinearHorizontal);
                    aSlider->setSliderStyle (Slider::Rotary);
                    aSlider->setTextBoxStyle(Slider::NoTextBox,true,0,0);
                    aSlider->setLookAndFeel(&otherLookAndFeel);
                    aSlider->setValue (*param);
                    aSlider->addListener (this);
                    aSlider->setCentrePosition(x,y*1.05);
                    aSlider->setBounds(0,0,getWidth(),getHeight());
                    //aSlider->setCentrePosition(100,105);
                    addAndMakeVisible (aSlider);
                }
            }
        }
        
        
        
        //setSize (kParamSliderWidth + kParamLabelWidth,jmax (1, kParamControlHeight * paramSliders.size()));
        
        if (paramSliders.size() == 0)
            addAndMakeVisible (noParameterLabel);
        else
            startTimerHz (30);
    }
    
    ~GenericEditor()
    {
    }
    
    void resized() override
    {
        Rectangle<int> r = getLocalBounds();
        noParameterLabel.setBounds (r);
        
        for (int i = 0; i < paramSliders.size(); ++i)
        {
            Rectangle<int> paramBounds = r.removeFromTop (kParamControlHeight);
            Rectangle<int> labelBounds = paramBounds.removeFromLeft (kParamLabelWidth);
            
            paramLabels[i]->setBounds (labelBounds);
            paramSliders[i]->setBounds (paramBounds);
        }
    }
    
    void paint (Graphics& g) override
    {
        float x=getWidth()/2.0;
        float y=getHeight()/2.0;
        g.fillAll (Colours::black);
        //g.setColour(Colours::black);
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.setColour(Colours::white);
        
        
        //g.fillRect(0,int(getHeight()),int(x),-(int)fabs(getHeight()*(parent.left)));
        //g.fillRect(int(x),int(getHeight()),int(x),-(int)fabs(getHeight()*(parent.right)));
        g.setFont (10.0f);
        //g.drawFittedText (std::to_string(processor.monoLevel), getLocalBounds(), Justification::centred, 1);
        /*
        if (isnan(log(parent.left)/log(powf(2.0, 1.0/6.0))==0))
        {
            g.drawFittedText(std::to_string(log(parent.left)/log(powf(2.0, 1.0/6.0))),0,int(getHeight()-20),int(x),20,Justification::centred,1);
        }
        if (isnan(log(parent.right)/log(powf(2.0, 1.0/6.0))==0))
        {
            g.drawFittedText(std::to_string(log(processor.right)/log(powf(2.0, 1.0/6.0))),int(x),int(getHeight()-20),int(x),20,Justification::centred,1);
        }
        */
         
        
        setResizable(true,true);
        
    }
    
    //==============================================================================
    void sliderValueChanged (Slider* slider) override
    {
        if (AudioParameterFloat* param = getParameterForSlider (slider))
            *param = (float) slider->getValue();
    }
    
    void sliderDragStarted (Slider* slider) override
    {
        if (AudioParameterFloat* param = getParameterForSlider (slider))
            param->beginChangeGesture();
    }
    
    void sliderDragEnded (Slider* slider) override
    {
        if (AudioParameterFloat* param = getParameterForSlider (slider))
            param->endChangeGesture();
    }
    
private:
    class ParameterSlider   : public Slider,
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
        
        AudioProcessorParameter& param;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterSlider)
    };
    void timerCallback() override
    {
        const OwnedArray<AudioProcessorParameter>& params = getAudioProcessor()->getParameters();
        
        for (int i = 0; i < params.size(); ++i)
        {
            if (const AudioParameterFloat* param = dynamic_cast<AudioParameterFloat*> (params[i]))
            {
                if (i < paramSliders.size())
                    paramSliders[i]->setValue (*param);
            }
        }
    }
    
    AudioParameterFloat* getParameterForSlider (Slider* slider)
    {
        const OwnedArray<AudioProcessorParameter>& params = getAudioProcessor()->getParameters();
        return dynamic_cast<AudioParameterFloat*> (params[paramSliders.indexOf (slider)]);
    }
    LookAndFeel_V4 otherLookAndFeel;
    Label noParameterLabel;
    OwnedArray<Slider> paramSliders;
    OwnedArray<Label> paramLabels;
    ScopedPointer<ParameterSlider> gainSlider;
};

