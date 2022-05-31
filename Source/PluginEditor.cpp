/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LowpassFilterAudioProcessorEditor::LowpassFilterAudioProcessorEditor(LowpassFilterAudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(400, 300);
	UpdateBandInfo();

	cutoffSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	cutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
	cutoffSlider.setRange(30.0, 20000.0, 1.0);
	cutoffSlider.setSkewFactorFromMidPoint(1024);
	cutoffSlider.setValue(m_currentFilterParams.getCutoff());
	cutoffSlider.addListener(this);
	cutoffSlider.setSize(200, 150);
	cutoffSlider.setTopLeftPosition(0, 150);
	addAndMakeVisible(cutoffSlider);
	
	resSlopeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	resSlopeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
	resSlopeSlider.addListener(this);
	resSlopeSlider.setSize(200, 150);
	resSlopeSlider.setTopLeftPosition(200, 150);
	addAndMakeVisible(resSlopeSlider);


	addAndMakeVisible(m_bandSelector);
	m_bandSelector.addItem("Band 1", 1);
	m_bandSelector.addItem("Band 2", 2);
	m_bandSelector.addItem("Band 3", 3);
	m_bandSelector.addItem("Band 4", 4);
	m_bandSelector.addItem("Band 5", 5);
	m_bandSelector.addItem("Band 6", 6);
	m_bandSelector.addItem("Band 7", 7);
	m_bandSelector.addItem("Band 8", 8);
	m_bandSelector.setSelectedId(1);
	m_bandSelector.onChange = [this] { UpdateBandInfo(); };
	m_bandSelector.setSize(400, 50);
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
	if (slider == &cutoffSlider)
	{
		audioProcessor.leftChannelEQ.setCutoff(currentBand, cutoffSlider.getValue());
		audioProcessor.rightChannelEQ.setCutoff(currentBand, cutoffSlider.getValue());
	}
	if (slider == &resSlopeSlider)
	{
		FilterTypeEnum type = m_currentFilterParams.getFilterType();
		if (type == FLAT_HIGHPASS || type == FLAT_LOWPASS)
		{
			audioProcessor.leftChannelEQ.setSlope(currentBand, (FilterSlopeEnum)((int)resSlopeSlider.getValue()));
			audioProcessor.rightChannelEQ.setSlope(currentBand, (FilterSlopeEnum)((int)resSlopeSlider.getValue()));
		}
		else
		{
			audioProcessor.leftChannelEQ.setResonance(currentBand, resSlopeSlider.getValue());
			audioProcessor.rightChannelEQ.setResonance(currentBand, resSlopeSlider.getValue());
		}
	}
}

//
//void LowpassFilterAudioProcessorEditor::comboBoxChanged(juce::ComboBox * combo)
//{
//
//}

void LowpassFilterAudioProcessorEditor::UpdateBandInfo()
{
	unsigned int selected = m_bandSelector.getSelectedId();
	if (selected)
		currentBand = selected - 1;
	else
		currentBand = selected;

	m_currentFilterParams = audioProcessor.leftChannelEQ.getFilterParameters(currentBand);
	cutoffSlider.setValue(m_currentFilterParams.getCutoff());
	UpdateResSlopeSlider();
}

void LowpassFilterAudioProcessorEditor::UpdateResSlopeSlider()
{
	resSlopeSlider.setEnabled(false);
	FilterTypeEnum type = m_currentFilterParams.getFilterType();
	if (type == FLAT_HIGHPASS || type == FLAT_LOWPASS)
	{
		resSlopeSlider.setRange(0, FOURTY_EIGHT_DB, 1);
		resSlopeSlider.setSkewFactorFromMidPoint(3);
		resSlopeSlider.setValue((double)m_currentFilterParams.getSlope());
		resSlopeSlider.setTooltip("Filter Slope");
	}
	else
	{
		resSlopeSlider.setRange(.01, 18.0, .001);
		resSlopeSlider.setSkewFactorFromMidPoint(.707);
		resSlopeSlider.setValue(m_currentFilterParams.getResonance());
		resSlopeSlider.setTooltip("Resonance");
	}
	resSlopeSlider.setEnabled(true);

}
