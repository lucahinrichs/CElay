/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CElayAudioProcessor::CElayAudioProcessor()
    : AudioProcessor(BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput("Input", juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
      apvts(*this, nullptr, "PARAMETERS", createParameterLayout()) {
}

CElayAudioProcessor::~CElayAudioProcessor() {
}

//==============================================================================
const juce::String CElayAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool CElayAudioProcessor::acceptsMidi() const {
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CElayAudioProcessor::producesMidi() const {
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CElayAudioProcessor::isMidiEffect() const {
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CElayAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int CElayAudioProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CElayAudioProcessor::getCurrentProgram() {
    return 0;
}

void CElayAudioProcessor::setCurrentProgram(int index) {
}

const juce::String CElayAudioProcessor::getProgramName(int index) {
    return {};
}

void CElayAudioProcessor::changeProgramName(int index, const juce::String& newName) {
}

//==============================================================================
void CElayAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    // How many audio samples do we need for 2 seconds (our max delay time)?
    int delayBufferSize = static_cast<int>(sampleRate * 2.0);
    
    // change size of ring buffer (based on amount of channels, amount of samples)
    delayBuffer.setSize(getTotalNumInputChannels(), delayBufferSize);

    // deletes rest memory and garbage at startup (no unwanted noise and crackle at startup)
    delayBuffer.clear();
}

void CElayAudioProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CElayAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void CElayAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    int bufferLength = buffer.getNumSamples();
    int delayBufferLength = delayBuffer.getNumSamples();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());


    // fetch parameter values from the value tree
    float freeTimeMs = apvts.getRawParameterValue("time")->load();
    float currentFeedback = apvts.getRawParameterValue("feedback")->load();
    float currentMix = apvts.getRawParameterValue("mix")->load();
    
    bool driveEnabled = apvts.getRawParameterValue("driveOn")->load() > 0.5f;
    float driveDb = apvts.getRawParameterValue("drive")->load();
    
    // db -> linear factor (0 dB -> 1.0, 20 dB -> 10.0, 40 dB -> 100.0)
    float driveGain = juce::Decibels::decibelsToGain(driveDb);
    
    // Sync parameter
    bool syncEnabled = apvts.getRawParameterValue("syncOn")->load() > 0.5f;
    int divisionIndex = static_cast<int>(apvts.getRawParameterValue("syncDivision")->load());
    
    // set delay time
    float currentDelayTimeMs = freeTimeMs; // standard ms value
    
    if (syncEnabled) {
        double bpm = 120.0; // fall back value
        
        // read bpm value from playhead
        if (auto* playHead = getPlayHead()) {
            if (auto position = playHead->getPosition()) {
                if (position->getBpm().hasValue()) {
                    bpm = *position->getBpm();
                }
            }
        }
        // length of quarter note in ms (60000 ms / bpm)
        double quarterNoteMs = 60000.0 / bpm;
        
        // mulitpliers based on value array order
        static const float multipliers[] = { 0.25f, 0.5f, 1.0f, 2.0f, 4.0f };
        
        currentDelayTimeMs = static_cast<float>(quarterNoteMs * multipliers[divisionIndex]);
    }

    
    // dynamic calculation of samples (both channels at the same time)
    int delayInSamples = static_cast<int>(getSampleRate() * (currentDelayTimeMs / 1000.0f));
    
    

    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
        auto* channelData = buffer.getWritePointer(channel);
        auto* delayData = delayBuffer.getWritePointer(channel);

        // fetching local copy of write position in current channel
        int channelWritePosition = writePosition;

        // iterating through each sample in current audio block
        for (int sample = 0; sample < bufferLength; ++sample) {
            
            // // grab current dry audio sample
            float drySample = channelData[sample];
            
            float signalToDelay = drySample;
            // Apply tanh soft clipping
            if (driveEnabled) {
                signalToDelay = std::tanh(drySample * driveGain);
            }
            
            // setting read head position (delay time in the "past")
            int readPosition = channelWritePosition - delayInSamples;

            // ring buffer correction for read head
            if (readPosition < 0) {
                readPosition += delayBufferLength;
            }

            // reading delayed signal of the record head
            float delaySample = delayData[readPosition];

            // write sample into the delay buffer (recording head)
            delayData[channelWritePosition] = signalToDelay + (delaySample * currentFeedback);

            // Dry/Wet Mix (Dry * (1 - mix) + Wet * mix)
            channelData[sample] = (drySample * (1.0f - currentMix)) + (delaySample * currentMix);

            // move recording head to the next sample
            channelWritePosition++;
            // if the end of the buffer/tape is reached jump back to the start position (ring buffer principle)
            if (channelWritePosition >= delayBufferLength) {
                channelWritePosition = 0;
            }
        }
    }

    writePosition += bufferLength;
    writePosition %= delayBufferLength;
}

//==============================================================================
bool CElayAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CElayAudioProcessor::createEditor() {
    return new CElayAudioProcessorEditor(*this);
}

//==============================================================================
void CElayAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CElayAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new CElayAudioProcessor();
}

// Parameter Layout
juce::AudioProcessorValueTreeState::ParameterLayout CElayAudioProcessor::createParameterLayout() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    // Delay time: 10ms to 2000ms, Standard value: 500ms
    layout.add(std::make_unique<juce::AudioParameterFloat>("time", "Time", 10.0f, 2000.0f, 500.0f));
    // Feedback: 0.0 (0%) to 0.95 (95%), Standard value: 0.5 (50%)
    layout.add(std::make_unique<juce::AudioParameterFloat>("feedback", "Feedback", 0.0f, 0.95f, 0.5f));

    // Mix (Dry/Wet): 0.0 (0% Wet) to 1.0 (100% Wet)
    layout.add(std::make_unique<juce::AudioParameterFloat>("mix", "Mix", 0.0f, 1.0f, 0.5f));
    
    // Distortion Toggle (On/Off)
    layout.add(std::make_unique<juce::AudioParameterBool>("driveOn", "Drive On", false));
    // Distortion Drive Amount (1.0 = Clean/unity, 40.0 = High Gain)
    layout.add(std::make_unique<juce::AudioParameterFloat>("drive", "Drive", 0.0f, 40.0f, 0.0f));
    
    // Synced delay time toggle
    layout.add(std::make_unique<juce::AudioParameterBool>("syncOn", "Sync On", false));
    
    // Drop down with tempo divisions
    juce::StringArray divisions =  { "1/16", "1/8", "1/4", "1/2", "1/1" };
    layout.add(std::make_unique<juce::AudioParameterChoice>("syncDivision", "Division", divisions, 2));
    
    return layout;
}
