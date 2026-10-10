/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CElayAudioProcessorEditor::CElayAudioProcessorEditor (CElayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p) {
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    // Time Slider
    timeSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    timeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(timeSlider);
    
    // Feedback Slider
    feedbackSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(feedbackSlider);
    
    // Mix Slider
    mixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (mixSlider);
    
    // Attachments to values
    timeAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "time", timeSlider);
    feedbackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "feedback", feedbackSlider);
    mixAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "mix", mixSlider);
    
}

CElayAudioProcessorEditor::~CElayAudioProcessorEditor() {
}

//==============================================================================
void CElayAudioProcessorEditor::paint (juce::Graphics& g) {
    // BG Color
    g.fillAll (juce::Colour (0xff1e1e24));

    // Render title text
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawText ("CElay", getLocalBounds().removeFromTop(40), juce::Justification::centred, true);

    // Knob text
    g.setFont (14.0f);
    g.drawText ("Time", 50, 60, 100, 20, juce::Justification::centred);
    g.drawText ("Feedback", 250, 60, 100, 20, juce::Justification::centred);
    g.drawText ("Dry / Wet Mix", 50, 210, 300, 20, juce::Justification::centred);
    
}

void CElayAudioProcessorEditor::resized() {
    // Positioning
    timeSlider.setBounds (50, 90, 100, 120);
    feedbackSlider.setBounds (250, 90, 100, 120);
    mixSlider.setBounds (50, 235, 300, 45);
}
