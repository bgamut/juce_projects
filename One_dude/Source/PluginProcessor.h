/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>
#include "math.h"
//#include "PyoClass.h"


//==============================================================================
/**
*/

class LP12 {
public:
    LP12() :
    cutoff(0.1),
    resonance(0.0),
    buf0(0.0),
    buf1(0.0)
    {
        calculateFeedbackAmount();
    };
    float process(float inputValue);
    inline void set(float newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
    inline void setResonance(float newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
private:
    float cutoff;
    float resonance;
    float feedbackAmount;
    inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance/(1.0 - cutoff); }
    float buf0;
    float buf1;
};
class LP24 {
public:
    LP24() :
    cutoff(0.1),
    resonance(0.0),
    buf0(0.0),
    buf1(0.0),
    buf2(0.0),
    buf3(0.0)
    {
        calculateFeedbackAmount();
    };
    float process(float inputValue);
    inline void set(float newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
    inline void setResonance(float newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
private:
    float cutoff;
    float resonance;
    float feedbackAmount;
    inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance/(1.0 - cutoff); }
    float buf0;
    float buf1;
    float buf2;
    float buf3;
};
class LP36 {
public:
    LP36() :
    cutoff(0.1),
    resonance(0.0),
    buf0(0.0),
    buf1(0.0),
    buf2(0.0),
    buf3(0.0),
    buf4(0.0),
    buf5(0.0)
    {
        calculateFeedbackAmount();
    };
    float process(float inputValue);
    inline void set(float newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
    inline void setResonance(float newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
private:
    float cutoff;
    float resonance;
    float feedbackAmount;
    inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance/(1.0 - cutoff); }
    float buf0;
    float buf1;
    float buf2;
    float buf3;
    float buf4;
    float buf5;
};
class HP24 {
public:
    HP24():
    cutoff(0.1),
    resonance(0.0),
    buf0(0.0),
    buf1(0.0),
    buf2(0.0),
    buf3(0.0)
    {
        calculateFeedbackAmount();
    };
    float process(float inputValue);
    inline void set(float newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
    inline void setResonance(float newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
private:
    float cutoff;
    float resonance;
    float feedbackAmount;
    inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance/(1.0 - cutoff); }
    float buf0;
    float buf1;
    float buf2;
    float buf3;
};
class HP36 {
public:
    HP36():
    cutoff(0.1),
    resonance(0.0),
    buf0(0.0),
    buf1(0.0),
    buf2(0.0),
    buf3(0.0),
    buf4(0.0),
    buf5(0.0)
    {
        calculateFeedbackAmount();
    };
    float process(float inputValue);
    inline void set(float newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
    inline void setResonance(float newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
private:
    float cutoff;
    float resonance;
    float feedbackAmount;
    inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance/(1.0 - cutoff); }
    float buf0;
    float buf1;
    float buf2;
    float buf3;
    float buf4;
    float buf5;
};

class Notch12 {
public:
    Notch12() :
	cutoff(0.1),
	resonance(1.0),
	buf0(0.0),
	buf1(0.0),
	buf2(0.0),
	buf3(0.0)
    {
    calculateFeedbackAmount();
    };
    float process(float inputValue);
    inline void set(float newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
    inline void setResonance(float newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
private:
    float cutoff;
    float resonance;
    float feedbackAmount;
    inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance / (1.0 - cutoff); }
    float buf0;
    float buf1;
    float buf2;
    float buf3;
  
};
class AllpassDelay{
public:
    AllpassDelay():
    a1( 0.0 ),
    zm1( 0.0 )
    {
  
    };
    inline void Delay( float delay ){a1 = (1.0 - delay) / (1.0 + delay);}
    float process(float inputValue);
private:
    float a1;
    float zm1;
    float output;
};
/*
class Phaser{
public:
    Phaser():
    lfoPhase( 0.0 ),
    zm1( 0.0 )
    {
        setFeedback(0.99);
        setRange( 440.0, 1600.0 );
        setRate( 0.5);
        setDepth(1.0);
        setSamplerate(44100);
    }
    inline void setRange(float fMin,float fMax){dmin = fMin /(float(sampleRate)/2.0);dmax = fMax / (float(sampleRate)/2.0);}
    inline void setRate(float rate){lfoInc = 2.0 * 3.1415926535 * rate/float(sampleRate);}
    inline void setFeedback(float fb){fb = fb;}
    inline void setDepth(float depth){depth = depth;}
    inline void setSamplerate(int sampleRate){sampleRate=sampleRate;}
    inline void setLfoPhase(float lfoPhase){lfoPhase=lfoPhase;}
    float process(float inputValue);
private:
    AllpassDelay alps;
    float dmin, dmax, d;
    float fb;
    float lfoPhase;
    float lfoInc;
    float depth;
    float zm1;
    int sampleRate;
    float output;
};
*/

class Clipper {
public:
    float process(float inputValue);
private:
    float k;
};
class Limiter{
public:
    Limiter():
    attackCoeff(0.0),
    releaseCoeff(0.0),
    env(0.0),
    targetGain(1.0),
    currentGain(1.0),
    delayIndex(0)
    {
        set(20.0,20.0,-6.0,44100);
    };
    float process(float input);
    void set(float attackMs, float releaseMs, float thresholdDb,int sampleRate);
    void resetEnv();
private:
    float attackCoeff;
    float releaseCoeff;
    float env;
    float targetGain;
    float currentGain;
    int delayIndex;
    int delayLength;
    int sr;
    //float* delayLine;
    float threshold;
};
class Gate{
public:
    Gate():
    releaseTime(0.2),
    sr(44100),
    threshold(0.001),
    outputValue(0.0),
    gain(1.0),
    holdTime(1.0),
    attackTime(0.01)
    {
        set(44100.0);
    };
    float process(float inputValue);
    void set(float sampleRate);
private:
    float releaseTime;
    float sr;
    float release;
    float threshold;
    float outputValue;
    float gain;
    int tick;
    float hold;
    float holdTime;
    float attack;
    float attackTime;
};
class Phaser{
public:
    Phaser()  //initialise to some usefull defaults...
    : _fb( .38196601125f )
    , _lfoPhase( 0.f )
    , _depth( 1.f )
    , _zm1( 0.f )
    {
        Range( 2250.f, 22050.f, 44100.0);
        Rate( .5f, 44100.0 );
    }
    
    void Range( float fMin, float fMax ,double SR){ // Hz
        _dmin = fMin / (SR/2.f);
        _dmax = fMax / (SR/2.f);
    }
    
    void Rate( float rate ,double SR){ // cps
        _lfoInc = 2.f * 3.14159f * (rate / SR);
    }
    
    void Feedback( float fb ){ // 0 -> <1.
        _fb = fb;
    }
    
    void Depth( float depth ){  // 0 -> 1.
        _depth = depth;
    }
    
    float Update( float inSamp ){
        //calculate and update phaser sweep lfo...
        float d  = _dmin + (_dmax-_dmin) * ((sin( _lfoPhase ) +
                                             1.f)/2.f);
        _lfoPhase += _lfoInc;
        if( _lfoPhase >= 3.14159f * 2.f )
            _lfoPhase -= 3.14159f * 2.f;
        
        //update filter coeffs
        for( int i=0; i<6; i++ )
            _alps[i].Delay( d );
        
        //calculate output
        float y =     _alps[0].Update(
                      _alps[1].Update(
                      _alps[2].Update(
                      _alps[3].Update(
                      _alps[4].Update(
                      _alps[5].Update( inSamp + _zm1 * _fb ))))));
        _zm1 = y;
        
        return inSamp + y * _depth;
    }
    float _lfoPhase;
private:
    class AllpassDelay{
    public:
        AllpassDelay()
        : _a1( 0.f )
        , _zm1( 0.f )
        {}
        
        void Delay( float delay ){ //sample delay time
            _a1 = (1.f - delay) / (1.f + delay);
        }
        
        float Update( float inSamp ){
            float y = inSamp * -_a1 + _zm1;
            _zm1 = y * _a1 + inSamp;
            
            return y;
        }
    private:
        float _a1, _zm1;
    };
    
    AllpassDelay _alps[6];
    
    float _dmin, _dmax; //range
    float _fb; //feedback
    
    float _lfoInc;
    float _depth;
    
    float _zm1;
};
/*
enum EParams
{
    kParamGain,
    kNumParams
};
 */
class OneAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    OneAudioProcessor();
    ~OneAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    float targetLevel=0.5;
    float sliderLevel=0.5;
    float left;
    float l0;
    float l1;
    float l2;
    float l3;
    float l4;
    float l5;
    float l6;
    float l7;
    float l8;
    float l9;
    float right;
    float r0;
    float r1;
    float r2;
    float r3;
    float r4;
    float r5;
    float r6;
    float r7;
    float r8;
    float r9;
    float monoLevel;
    AudioParameterFloat* gainParam;
    //Pyo pyo;
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OneAudioProcessor)
    const float f1=40.0;
    const float f2=40.0;
    const float f3=2250.0;
    const float f4=3880.0;
    const float f5=7000.0;
    const float f6=4090.0;
    float envelope=0.0;
    float currentLevel= 0.5f;
    float increment=0.0f;
    float ramp;
    float sr1;
    float sr2;
    float bs1;
    float fq1;
    float fq2;
    float fq3;
    float fq4;
    float fq5;
    float fq6;
    float rs1;
    float mono=0.0;
    LP24 filter1;
    HP24 filter2;
    LP12 filter3;
    Notch12 filter4;
    Notch12 filter5;
    LP36 filter6;
    HP24 filter7;
    LP12 filter8;
    Notch12 filter9;
    Notch12 filter10;
    LP36 filter11;
    Notch12 filter12;
    Notch12 filter13;
    Phaser phaser1;
    Phaser phaser2;
    Gate gate1;
    Gate gate2;
    Clipper clipper1;
    Clipper clipper2;
    Clipper clipper3;
    Clipper clipper4;
    Limiter limiter1;
    Limiter limiter2;
    Limiter limiter3;
    Limiter limiter4;
    
   
};
