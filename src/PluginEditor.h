/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SpectralConvolverAudioProcessorEditor : public juce::AudioProcessorEditor,
    public juce::Button::Listener
{
public:
    SpectralConvolverAudioProcessorEditor(SpectralConvolverAudioProcessor&);
    ~SpectralConvolverAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;

private:
    void updateStatusLabel();
    SpectralConvolverAudioProcessor& audioProcessor;

    juce::ToggleButton algorithmToggle;
    juce::Label algorithmLabel;
    juce::Label statusLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpectralConvolverAudioProcessorEditor)
};
