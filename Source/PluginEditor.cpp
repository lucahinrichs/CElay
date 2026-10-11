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
    
    // Attachments to values
    timeAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "time", timeSlider);
    feedbackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "feedback", feedbackSlider);
    mixAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "mix", mixSlider);
        
    driveButtonAttachment = std::make_unique<ButtonAttachment>(audioProcessor.apvts, "driveOn", driveButton);
    driveSliderAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "drive", driveSlider);
    
}

CElayAudioProcessorEditor::~CElayAudioProcessorEditor() {
}

//==============================================================================
void CElayAudioProcessorEditor::paint(juce::Graphics& g) {
    // BG Color
    g.fillAll(juce::Colour(0xff1e1e24));

    // Render title text
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("CElay", getLocalBounds().removeFromTop(40), juce::Justification::centred, true);

    // Knob text
    g.setFont(14.0f);
    g.drawText("Time", 30, 60, 100, 20, juce::Justification::centred);
    g.drawText("Feedback", 150, 60, 100, 20, juce::Justification::centred);
    g.drawText("Drive", 270, 60, 100, 20, juce::Justification::centred);
    g.drawText("Dry / Wet Mix", 30, 210, 440, 20, juce::Justification::centred);
    
}

void CElayAudioProcessorEditor::resized() {
    timeSlider.setBounds(30, 90, 100, 120);
    feedbackSlider.setBounds(150, 90, 100, 120);
    driveSlider.setBounds(270, 90, 100, 120);
    driveButton.setBounds(380, 120, 90, 30);
    mixSlider.setBounds(30, 235, 440, 45);
}
