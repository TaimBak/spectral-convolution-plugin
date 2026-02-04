#pragma once

#include <JuceHeader.h>
#include "FreqDomainConvolver.h"
#include "TimeDomainConvolver.h"
#include <memory>
#include <vector>

enum class ConvolverType
{
    FrequencyDomain,
    TimeDomain
};

class SpectralConvolverAudioProcessor : public juce::AudioProcessor
{
public:
    SpectralConvolverAudioProcessor();
    ~SpectralConvolverAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // IR Management
    
    void loadImpulseResponse (const std::vector<float>& ir);
    bool loadImpulseResponseFromFile (const juce::File& file);
    bool isIRLoaded() const { return irLoaded.load(); }
    int getIRLength() const { return irLength; }

    // Algorithm Selection
	void setConvolverType(ConvolverType type);
	ConvolverType getConvolverType() const { return currentConvolverType.load(); }

private:
    
    static int calculateFFTOrder (int irLength, int blockSize);
    void rebuildConvolvers();
    
    std::vector<std::unique_ptr<FreqDomainConvolver>> freqConvolvers;
    std::vector<std::unique_ptr<TimeDomainConvolver>> timeConvolvers;

	std::atomic<ConvolverType> currentConvolverType{ ConvolverType::FrequencyDomain };
    
    std::vector<float> currentIR;
    int irLength = 0;
    std::atomic<bool> irLoaded { false };
    
    double currentSampleRate = 44100.0;
    int currentBlockSize = 512;
    int fftOrder = 10;
    
    juce::SpinLock irLock;
    std::atomic<bool> irPendingRebuild { false };
    
    float dryWetMix = 1.0f;  // 1.0 = 100% wet
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectralConvolverAudioProcessor)
};
