/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CElayAudioProcessorEditor::CElayAudioProcessorEditor(CElayAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(500, 300);
    
    // Time Slider
    timeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    timeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(timeSlider);
    
    // Feedback Slider
    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(feedbackSlider);
        
    // Drive Slider
    driveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(driveSlider);
    
    // Drive Toggle Button
    addAndMakeVisible(driveButton);
    
    // Mix Slider
    mixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(mixSlider);
        
    // Tempo sync values
    syncComboBox.addItemList({ "1/16", "1/8", "1/4", "1/2", "1/1" }, 1);
    addAndMakeVisible(syncButton);
    addAndMakeVisible(syncComboBox);
    
    // Attachments to values
    timeAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "time", timeSlider);
    feedbackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "feedback", feedbackSlider);
    mixAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "mix", mixSlider);
        
    driveButtonAttachment = std::make_unique<ButtonAttachment>(audioProcessor.apvts, "driveOn", driveButton);
    driveSliderAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "drive", driveSlider);
        
    syncButtonAttachment = std::make_unique<ButtonAttachment>(audioProcessor.apvts, "syncOn", syncButton);
    syncComboBoxAttachment = std::make_unique<ComboBoxAttachment>(audioProcessor.apvts, "syncDivision", syncComboBox);

    auto updateSyncState = [this]() {
        bool isSynced = syncButton.getToggleState();
        timeSlider.setEnabled(!isSynced);
        syncComboBox.setEnabled(isSynced);
    };

    syncButton.onClick = updateSyncState;
    updateSyncState();
}

CElayAudioProcessorEditor::~CElayAudioProcessorEditor() {
}

//==============================================================================
void CElayAudioProcessorEditor::paint(juce::Graphics& g) {
    // BG Color
    juce::ColourGradient gradient(
            juce::Colour(0xff38a3ca), 0.0f, 0.0f,
            juce::Colour(0xff141418), 0.0f, static_cast<float>(getHeight()),
            false // -> linear gradient
        );
        g.setGradientFill(gradient);
        g.fillAll();

    // Render title text
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("CElay", getLocalBounds().removeFromTop(40), juce::Justification::centred, true);

    // Knob Labels
    g.setFont(14.0f);
    g.drawText("Time", 50, 50, 100, 20, juce::Justification::centred);
    g.drawText("Feedback", 200, 50, 100, 20, juce::Justification::centred);
    g.drawText("Drive", 350, 50, 100, 20, juce::Justification::centred);
    
    // Mix Label for mix sliders
    g.drawText("Dry / Wet Mix", 30, 218, 440, 20, juce::Justification::centred);
}

void CElayAudioProcessorEditor::resized() {
    // knobs
    timeSlider.setBounds(50, 72, 100, 95);
    feedbackSlider.setBounds(200, 72, 100, 95);
    driveSlider.setBounds(350, 72, 100, 95);
    driveButton.setBounds(355, 170, 90, 20);

    // Sync controls centered under time knob
    syncButton.setBounds(60, 170, 80, 20);
    syncComboBox.setBounds(55, 192, 90, 22);
    
    // mix slider on the bottom
    mixSlider.setBounds(30, 240, 440, 45);
}
