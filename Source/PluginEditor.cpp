/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LowpassFilterAudioProcessorEditor::LowpassFilterAudioProcessorEditor (LowpassFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	cutoffSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
	cutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
	cutoffSlider.setRange(40.0, 20000.0, 1.0);
	cutoffSlider.setValue(15000.0);
	cutoffSlider.addListener(this);
	addAndMakeVisible(cutoffSlider);
}

LowpassFilterAudioProcessorEditor::~LowpassFilterAudioProcessorEditor()
{
}

//==============================================================================
void LowpassFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void LowpassFilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	cutoffSlider.setBounds(getLocalBounds());
}

void LowpassFilterAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
	if (slider != &cutoffSlider)
		return;
	audioProcessor.leftChannelEQ.setCutoff(cutoffSlider.getValue());
	audioProcessor.rightChannelEQ.setCutoff(cutoffSlider.getValue());
}