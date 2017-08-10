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

#include "JuceHeader.h"
#include "PluginEditor.h"
#include "math.h"
//==============================================================================
/**
 */
#define PI 3.14159265
float toDB (float inputValue){
    return log(inputValue)/log(powf(2.0, 1.0/6.0));
}
float toLinear(float dB){
    return powf(powf(2.0,1.0/6.0),(dB-6.0));
}
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
float LP12::process(float inputValue) {
    buf0 += cutoff * (inputValue - buf0);
    buf1 += cutoff * (buf0 - buf1);
    return buf1;
}
float LP24::process(float inputValue) {
    buf0 += cutoff * (inputValue - buf0);
    buf1 += cutoff * (buf0 - buf1);
    buf2 += cutoff * (buf1 - buf2);
    buf3 += cutoff * (buf2 - buf3);
    return buf3;
}
float LP36::process(float inputValue) {
    buf0 += cutoff * (inputValue - buf0);
    buf1 += cutoff * (buf0 - buf1);
    buf2 += cutoff * (buf1 - buf2);
    buf3 += cutoff * (buf2 - buf3);
    buf4 += cutoff * (buf3 - buf4);
    buf5 += cutoff * (buf4 - buf5);
    return buf5;
}

float HP36::process(float inputValue) {
    buf0 += cutoff * (inputValue - buf0 + feedbackAmount * (buf0 - buf1));
    //buf0 += cutoff * (inputValue - buf0);
    buf1 += cutoff * (buf0 - buf1);
    buf2 += cutoff * (buf1 - buf2);
    buf3 += cutoff * (buf2 - buf3);
    buf4 += cutoff * (buf3 - buf4);
    buf5 += cutoff * (buf4 - buf5);
    return inputValue - buf5;
}
float HP24::process(float inputValue) {
    buf0 += cutoff * (inputValue - buf0 + feedbackAmount * (buf0 - buf1));
    //buf0 += cutoff * (inputValue - buf0);
    buf1 += cutoff * (buf0 - buf1);
    buf2 += cutoff * (buf1 - buf2);
    buf3 += cutoff * (buf2 - buf3);
    return inputValue - buf3;
}

float Notch12::process(float inputValue){
    buf0 += cutoff * (inputValue - buf0);
    buf1 += cutoff * (buf0 - buf1);
    return inputValue - (buf0 - buf1);
}

float Clipper::process(float inputValue){
    k=atanf(inputValue)/atanf(1.0);
    return k;
}
float AllpassDelay::process(float inputValue){
    output = inputValue * (-1.0)*a1 + zm1;
    zm1 = output * a1 + inputValue;
    return output;
}
/*
 float Phaser::process(float inputValue){
 d  = dmin + (dmax-dmin) * ((sin( lfoPhase ) +1.0)/2.0);
 lfoPhase += lfoInc;
 if(lfoPhase >= 3.1415926535*2.0){
 lfoPhase -= 3.1415926535*2.0;
 }
 for( int i=0; i<6; i++ ){
 alps.Delay(d);
 }
 output =     alps.process(inputValue +zm1*fb);
 zm1 = output;
 
 return inputValue + output* depth;
 
 }
 */
void Gate::set(float sampleRate){
    sr=sampleRate;
    releaseTime=0.3;
    attackTime=0.02;
    threshold=0.001;
    release=1.0-exp(-1.0/(releaseTime*sr));
    hold=holdTime*sr;
    //attack=1.0-exp(-1.0/(attackTime*sr));
    attack=1.0-exp(-1.0/1.0);
}
float Gate::process(float inputValue){
    if(tick>int(hold)){
        if(threshold>(inputValue*inputValue)){
            gain*=release;
        }
        else{
            tick=0;
            gain*=attack;
        }
    }
    else{
        tick+=1;
        gain=1.0;
    }
    outputValue=inputValue*gain;
    return inputValue;
}
void Limiter::set(float attackMs, float releaseMs,float thresholdDb,int sampleRate){
    
    //attackCoeff=exp(-1*(attackMs*float(sampleRate)*1000.0));
    attackCoeff=1.0-exp(-1.0/(attackMs*float(sampleRate)*1000.0));
    //releaseCoeff=exp(-1*(releaseMs*float(sampleRate)*1000.0));
    releaseCoeff=1.0-exp(-1.0/(releaseMs*float(sampleRate)*1000.0));
    delayIndex=0;
    env=0.0;
    threshold=toLinear(thresholdDb);
    sr=sampleRate;
    currentGain=1.0;
    targetGain=1.0;
}
float Limiter::process(float input){
    delayIndex=(delayIndex+1)%(2*sr);
    env = fmax(fabs(input), env);
    if (env>threshold){
        targetGain=(2*threshold/env)-1.0;
    }
    else{
        targetGain=1.0;
    }
    env *= releaseCoeff;
    if (delayIndex==0){
        env=1.0;
    }
    currentGain=currentGain*attackCoeff+targetGain*(1-attackCoeff);
    return (input*targetGain);
}

class OneProcessor  : public AudioProcessor
{
public:
    
    //==============================================================================
    OneProcessor()
    {
        addParameter (gain = new AudioParameterFloat ("volume", // parameterID
                                                      "Volume", // parameter name
                                                      0.0f,   // mininum value
                                                      1.0f,   // maximum value
                                                      0.5f)); // default value
    }
    
    ~OneProcessor() {}
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override {
        mono=0.0;
        sr1=float(sampleRate);
        bs1=samplesPerBlock;
        fq1=2*sin((PI)*f1/sr1);
        fq2=2*sin((PI)*f2/sr1);
        fq3=2*sin((PI)*f3/sr1);
        fq4=2*sin((PI)*f4/sr1);
        fq5=2*sin((PI)*f5/sr1);
        fq6=2*sin((PI)*f6/sr1);
        filter1.set(fq1);
        filter2.set(fq2);
        filter3.set(fq3);
        filter4.set(fq4);
        filter5.set(fq5);
        filter6.set(fq5);
        filter7.set(fq2);
        filter8.set(fq3);
        filter9.set(fq4);
        filter10.set(fq5);
        filter11.set(fq5);
        filter12.set(fq6);
        filter13.set(fq6);
        //the following settings distort kicks in a nasty way
        /*
         limiter1.set(20.0,200.0,-12.0,sr1);
         limiter2.set(20.0,200.0,-12.0,sr1);
         limiter3.set(0.0008,500.0,-12.0,sr1);
         limiter4.set(0.0008,500.0,-12.0,sr1);
         */
        limiter1.set(20.0,200.0,0.0,sr1);
        limiter2.set(20.0,200.0,0.0,sr1);
        limiter3.set(0.0008,0.0008,0.0,sr1);
        limiter4.set(0.0008,0.0008,0.0,sr1);
        gate1.set(sr1);
        gate2.set(sr1);
        phaser1.Rate(0.0001,sr1);
        phaser1.Range(2250.f,22050.f,sr1);
        phaser1._lfoPhase=0;
        phaser2.Rate(0.0001,sr1);
        phaser2.Range(2250.f,22050.f,sr1);
        phaser2._lfoPhase=3.14159f;
        
    }
    void releaseResources() override {}
    
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override
    {
        buffer.applyGain (*gain);
        AudioSampleBuffer main=getBusBuffer(buffer,true,0);
        if(getNumInputChannels() ==1)
        {
            for (int j=0; j<main.getNumSamples(); ++j)
            {
                //main.applyGainRamp(0, 0, main.getNumSamples(), currentLevel, targetLevel);
                //main.applyGainRamp(1, 0, main.getNumSamples(), currentLevel, targetLevel);
                float mono = filter1.process(main.getSample(0,j));
                monoLevel = (fabs(mono));
                /*
                 if(isnan(monoLevel)==0 && monoLevel>0.5 && monoLevel!=0.0)
                 {
                 main.applyGain((1.0/monoLevel)*0.5);
                 }
                 else
                 {
                 main.applyGain(1.0);
                 }
                 */
                {
                    
                    
                    float newSample1=gate1.process(clipper1.process(filter12.process(filter2.process(filter3.process(filter4.process(filter5.process(filter6.process(phaser1.Update(main.getSample(0,j))+main.getSample(0,j))/2.0)))))+(mono))/0.25)*toLinear(-2.0);
                    left=newSample1;
                    float newSample2=gate2.process(clipper2.process(filter13.process(filter7.process(filter8.process(filter9.process(filter10.process(filter11.process(phaser2.Update(main.getSample(0,j))+main.getSample(0,j))/2.0)))))+(mono))/0.25)*toLinear(-2.0);
                    right=newSample2;
                    
                    
                    main.setSample(0,j,newSample1);
                    //main.setSample(1,j,newSample2);
                    l9=l8;
                    r9=r8;
                    l8=l7;
                    r8=r7;
                    l7=l6;
                    r7=r6;
                    l6=l5;
                    r6=r5;
                    l5=l4;
                    r5=r4;
                    l4=l3;
                    r4=r3;
                    l3=l2;
                    r3=r2;
                    l2=l1;
                    r2=r1;
                    l1=l0;
                    r1=r0;
                    l0=tanh(left*10);
                    r0=tanh(right*10);
                }
            }
                    
                    
        }
        else if(getNumInputChannels()==2)
        {
            for (int j=0; j<main.getNumSamples(); ++j)
            {
                //main.applyGainRamp(0, 0, main.getNumSamples(), currentLevel, targetLevel);
                //main.applyGainRamp(1, 0, main.getNumSamples(), currentLevel, targetLevel);
                float mono = filter1.process(main.getSample(0,j)+main.getSample(1,j));
                monoLevel = (fabs(mono)/2.0);
                /*
                 if(isnan(monoLevel)==0 && monoLevel>0.5 && monoLevel!=0.0)
                 {
                 main.applyGain((1.0/monoLevel)*0.5);
                 }
                 else
                 {
                 main.applyGain(1.0);
                 }
                 */
                {
                
                
                    float newSample1=gate1.process(clipper1.process(filter12.process(filter2.process(filter3.process(filter4.process(filter5.process(filter6.process(phaser1.Update(main.getSample(0,j))+main.getSample(0,j))/2.0)))))+(mono))/0.25)*toLinear(-2.0);
                    left=newSample1;
                    float newSample2=gate2.process(clipper2.process(filter13.process(filter7.process(filter8.process(filter9.process(filter10.process(filter11.process(phaser2.Update(main.getSample(1,j))+main.getSample(1,j))/2.0)))))+(mono))/0.25)*toLinear(-2.0);
                    right=newSample2;
                
                
                    main.setSample(0,j,newSample1);
                    main.setSample(1,j,newSample2);
                    l9=l8;
                    r9=r8;
                    l8=l7;
                    r8=r7;
                    l7=l6;
                    r7=r6;
                    l6=l5;
                    r6=r5;
                    l5=l4;
                    r5=r4;
                    l4=l3;
                    r4=r3;
                    l3=l2;
                    r3=r2;
                    l2=l1;
                    r2=r1;
                    l1=l0;
                    r1=r0;
                    l0=tanh(left*10);
                    r0=tanh(right*10);
                
                
                
                //main.applyGain(targetLevel);
                }
            }
        }
        
    }
    
    //==============================================================================
    AudioProcessorEditor* createEditor() override { return new GenericEditor (*this); }
    bool hasEditor() const override               { return true;   }
    
    //==============================================================================
    const String getName() const override               { return "One"; }
    bool acceptsMidi() const override                   { return false; }
    bool producesMidi() const override                  { return false; }
    double getTailLengthSeconds() const override        { return 0; }
    
    //==============================================================================
    int getNumPrograms() override                          { return 1; }
    int getCurrentProgram() override                       { return 0; }
    void setCurrentProgram (int) override                  {}
    const String getProgramName (int) override             { return String(); }
    void changeProgramName (int , const String& ) override { }
    
    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override
    {
        MemoryOutputStream (destData, true).writeFloat (*gain);
    }
    
    void setStateInformation (const void* data, int sizeInBytes) override
    {
        *gain = MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    }
    AudioParameterFloat* gain;
private:
    //==============================================================================
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OneProcessor)
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

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OneProcessor();
}

