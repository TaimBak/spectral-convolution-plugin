/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

SpectralConvolverAudioProcessorEditor::SpectralConvolverAudioProcessorEditor(SpectralConvolverAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Algorithm toggle button
    algorithmToggle.setButtonText("Use Time Domain");
    algorithmToggle.setToggleState(
        audioProcessor.getConvolverType() == ConvolverType::TimeDomain,
        juce::dontSendNotification);
    algorithmToggle.addListener(this);
    addAndMakeVisible(algorithmToggle);

    // Label for the toggle
    algorithmLabel.setText("Convolution Algorithm:", juce::dontSendNotification);
    algorithmLabel.setJustificationType(juce::Justification::centredRight);
    addAndMakeVisible(algorithmLabel);

    // Status label showing current algorithm
    updateStatusLabel();
    statusLabel.setJustificationType(juce::Justification::centred);
    statusLabel.setFont(juce::FontOptions(18.0f));
    addAndMakeVisible(statusLabel);

    setSize(400, 300);
}

SpectralConvolverAudioProcessorEditor::~SpectralConvolverAudioProcessorEditor()
{
    algorithmToggle.removeListener(this);
}

void SpectralConvolverAudioProcessorEditor::updateStatusLabel()
{
    if (audioProcessor.getConvolverType() == ConvolverType::FrequencyDomain)
        statusLabel.setText("Current: Frequency Domain (FFT)", juce::dontSendNotification);
    else
        statusLabel.setText("Current: Time Domain (Direct)", juce::dontSendNotification);
}

void SpectralConvolverAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &algorithmToggle)
    {
        if (algorithmToggle.getToggleState())
            audioProcessor.setConvolverType(ConvolverType::TimeDomain);
        else
            audioProcessor.setConvolverType(ConvolverType::FrequencyDomain);

        updateStatusLabel();
    }
}

void SpectralConvolverAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(24.0f));
    g.drawFittedText("Spectral Convolver", getLocalBounds().removeFromTop(60),
        juce::Justification::centred, 1);

    // Draw IR info
    g.setFont(juce::FontOptions(14.0f));
    juce::String irInfo = audioProcessor.isIRLoaded()
        ? "IR Loaded: " + juce::String(audioProcessor.getIRLength()) + " samples"
        : "No IR Loaded";
    g.drawFittedText(irInfo, getLocalBounds().removeFromBottom(40),
        juce::Justification::centred, 1);
}

void SpectralConvolverAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    bounds.removeFromTop(70);  // Space for title
    bounds.removeFromBottom(50); // Space for IR info

    auto centerArea = bounds.reduced(20);

    // Status label at top of center area
    statusLabel.setBounds(centerArea.removeFromTop(30));

    centerArea.removeFromTop(20); // Spacing

    // Toggle row
    auto toggleRow = centerArea.removeFromTop(30);
    algorithmLabel.setBounds(toggleRow.removeFromLeft(150));
    toggleRow.removeFromLeft(10); // Spacing
    algorithmToggle.setBounds(toggleRow);
}
