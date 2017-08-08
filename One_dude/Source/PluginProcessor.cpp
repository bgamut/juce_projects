/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define PI 3.14159265
float toDB (float inputValue){
    return log(inputValue)/log(powf(2.0, 1.0/6.0));
}
float toLinear(float dB){
    return powf(powf(2.0,1.0/6.0),(dB-6.0));
}
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

//==============================================================================
OneAudioProcessor::OneAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif

{
    /*
    addParameter (gainParam  = new AudioParameterFloat ("volume","Volume", 0.0f, 1.0f, 0.5f));
    for (auto i = 0; i < kNumParams; i++)
    {
        JParam* param = new JParam();
        
        switch (i)
        {
            case kParamGain:
                param->InitFloat("Volume", 0., -70., 12., 0.1, "dB");
                param->SignDisplay();
                break;
            default:
                break;
        }
        
        addParameter(param);
    }
     */
    
}

OneAudioProcessor::~OneAudioProcessor()
{
}

//==============================================================================
const String OneAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OneAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OneAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double OneAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OneAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OneAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OneAudioProcessor::setCurrentProgram (int index)
{
}

const String OneAudioProcessor::getProgramName (int index)
{
    return {};
}

void OneAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void OneAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mono=0.0;
    sr1=sampleRate;
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
    
    //pyo.setup(2,samplesPerBlock,sampleRate);
    //pyo.exec(BinaryData::One_py);
}

void OneAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OneAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void OneAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{   
    /*
    pyo.process(buffer);
    for (int i=0; i<buffer.getNumSamples(); ++i)
    {
        left=buffer.getSample(0,i);
        right=buffer.getSample(1,i);
    }
    */
    /*
    if (currentLevel != targetLevel)
    {
        AudioSampleBuffer main=getBusBuffer(buffer,true,0);
        for (int j=0; j<main.getNumSamples(); ++j)
        {
            //main.applyGainRamp(0, 0, main.getNumSamples(), currentLevel, targetLevel);
            //main.applyGainRamp(1, 0, main.getNumSamples(), currentLevel, targetLevel);
            increment=(targetLevel-currentLevel)/((int)buffer.getNumSamples());
            float mono = filter1.process(main.getSample(0,j)+main.getSample(1,j));
        
            {
                float newSample1=gate1.process(clipper1.process(filter12.process(filter2.process(filter3.process(filter4.process(filter5.process(filter6.process(main.getSample(0,j))))))+(mono))*currentLevel)/4.1);
                main.setSample(0,j,newSample1);
                float newSample2=gate2.process(clipper2.process(filter13.process(filter7.process(filter8.process(filter9.process(filter10.process(filter11.process(main.getSample(1,j))))))+(mono))*currentLevel)/4.1);
                main.setSample(1,j,newSample2);
                currentLevel=currentLevel+increment;
            }
        }
    }
    else
     */
     
    {
        //dynamic_cast<JParam*>(getParameters()[kParamGain])->Set(sliderLevel);
        //targetLevel=dynamic_cast<JParam*>(getParameters()[kParamGain])->GetDBToAmp();
        //sliderLevel=targetLevel;
        buffer.applyGain(targetLevel);
        AudioSampleBuffer main=getBusBuffer(buffer,true,0);
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
                float newSample1=gate1.process(clipper1.process(filter12.process(filter2.process(filter3.process(filter4.process(filter5.process(filter6.process(phaser1.Update(main.getSample(0,j))+main.getSample(0,j))/2.0)))))+(mono)))*toLinear(-2.0);
                left=newSample1;
                float newSample2=gate2.process(clipper2.process(filter13.process(filter7.process(filter8.process(filter9.process(filter10.process(filter11.process(phaser2.Update(main.getSample(1,j))+main.getSample(0,j))/2.0)))))+(mono)))*toLinear(-2.0);
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
    
    
    
};

//==============================================================================
bool OneAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
};

AudioProcessorEditor* OneAudioProcessor::createEditor()
{
    return new OneAudioProcessorEditor (*this);
};

//==============================================================================
void OneAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
};

void OneAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
};

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OneAudioProcessor();
}
