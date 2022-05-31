/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class LowpassFilterAudioProcessorEditor  : public juce::AudioProcessorEditor, juce::Slider::Listener
{
public:
    LowpassFilterAudioProcessorEditor (LowpassFilterAudioProcessor&);
    ~LowpassFilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
	void sliderValueChanged(juce::Slider* slider) override;
	//void comboBoxChanged(juce::ComboBox* combo) override;

private:
    //Memeber Functions
	void UpdateBandInfo();
	void UpdateResSlopeSlider();
	// This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LowpassFilterAudioProcessor& audioProcessor;

	//This could be better implemeented maybe in another class?
	unsigned int currentBand = 0;
	FilterParameters m_currentFilterParams;
	juce::ComboBox m_bandSelector;
	juce::ComboBox filterTypeSelector;
	juce::Slider resSlopeSlider;
	juce::Slider cutoffSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LowpassFilterAudioProcessorEditor)
};
