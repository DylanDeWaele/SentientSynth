/*
  ==============================================================================

	OscillatorComponent.cpp
	Created: 1 Jun 2023 7:35:31pm
	Author:  dewae

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorComponent.h"
#include "../HelperLibrary.h"

//==============================================================================
OscillatorComponent::OscillatorComponent(juce::AudioProcessorValueTreeState& audioProcessorValueTreeState, juce::String waveSelectorID, juce::String fmFrequencyID, juce::String fmDepthID) :
	m_OscillatorLabel{ "OscillatorLabel", "Wave Type" },
	m_FMFrequencyLabel{ "FMFrequencyLabel", "FM Freq" },
	m_FMDepthLabel{ "FMDepthLabel", "FM Depth" }
{
	HelperLibrary::InitComboBoxWithLabel(*this, m_OscillatorSelector, { "Sine", "Saw", "Square" }, m_OscillatorLabel, m_OscillatorAttachment, audioProcessorValueTreeState, waveSelectorID);
	HelperLibrary::InitSliderWithLabel(*this, m_FMFrequencySlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, m_FMFrequencyLabel, m_FMFrequencyAttachment, audioProcessorValueTreeState, fmFrequencyID);
	HelperLibrary::InitSliderWithLabel(*this, m_FMDepthSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, m_FMDepthLabel, m_FMDepthAttachment, audioProcessorValueTreeState, fmDepthID);
}

OscillatorComponent::~OscillatorComponent()
{
}

void OscillatorComponent::paint(juce::Graphics& g)
{
	HelperLibrary::PaintComponentBox("Oscillator", getLocalBounds(), g);
}

void OscillatorComponent::resized()
{
	const int paddingX = 15;
	const int paddingY = 5;

	const int comboBoxWidth = 100;
	const int comboBoxHeight = 25;
	const int labelYOffset = 20;
	const int labelHeight = 20;

	const int comboBoxX = getLocalBounds().getX() + paddingX;
	const int comboBoxY = getLocalBounds().getY() + comboBoxHeight + labelYOffset + paddingY;

	const int sliderWidth = 100;
	const int sliderHeight = 50;
	const int sliderX = getLocalBounds().getX() + comboBoxWidth + paddingX;
	const int sliderY = getLocalBounds().getY() + sliderHeight- 10;

	HelperLibrary::ResizeComboBoxWithLabel(m_OscillatorSelector, m_OscillatorLabel, comboBoxX, comboBoxY, comboBoxWidth, comboBoxHeight, labelYOffset, labelHeight);
	HelperLibrary::ResizeSliderWithLabel(m_FMFrequencySlider, m_FMFrequencyLabel, sliderX, sliderY, sliderWidth, sliderHeight, labelYOffset - 10, labelHeight);
	HelperLibrary::ResizeSliderWithLabel(m_FMDepthSlider, m_FMDepthLabel, sliderX + 75, sliderY, sliderWidth, sliderHeight, labelYOffset - 10, labelHeight);
}

void OscillatorComponent::SetFMFrequencySlider(double value)
{
	m_FMFrequencySlider.setValue(value);
}

void OscillatorComponent::SetFMDepthSlider(double value)
{
	m_FMDepthSlider.setValue(value);
}