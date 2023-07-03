/*
  ==============================================================================

	FilterComponent.cpp
	Created: 7 Jun 2023 3:20:06pm
	Author:  dewae

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

#include "../HelperLibrary.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& audioProcessorValueTreeState, juce::String filterTypeSelectorID, juce::String cutoffID, juce::String resonanceID) :
	m_FilterTypeSelector{ "Filter Type" },
	m_FilterTypeLabel{ "FilterTypeLabel", "Filter Type" },
	m_CutoffSlider{},
	m_CutoffLabel{ "CutoffLabel", "Cutoff Freq" },
	m_ResonanceSlider{},
	m_ResonanceLabel{ "ResonanceLabel", "Resonance" }
{
	HelperLibrary::InitComboBoxWithLabel(*this, m_FilterTypeSelector, { "Lowpass", "Bandpass", "Highpass" }, m_FilterTypeLabel, m_FilterTypeAttachment, audioProcessorValueTreeState, filterTypeSelectorID);
	HelperLibrary::InitSliderWithLabel(*this, m_CutoffSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, m_CutoffLabel, m_CutoffAttachment, audioProcessorValueTreeState, cutoffID);
	HelperLibrary::InitSliderWithLabel(*this, m_ResonanceSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, m_ResonanceLabel, m_ResonanceAttachment, audioProcessorValueTreeState, resonanceID);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint(juce::Graphics& g)
{
	HelperLibrary::PaintComponentBox("Filter", getLocalBounds(), g);
}

void FilterComponent::resized()
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
	const int sliderY = getLocalBounds().getY() + sliderHeight - 10;

	HelperLibrary::ResizeComboBoxWithLabel(m_FilterTypeSelector, m_FilterTypeLabel, comboBoxX, comboBoxY, comboBoxWidth, comboBoxHeight, labelYOffset, labelHeight);
	HelperLibrary::ResizeSliderWithLabel(m_CutoffSlider, m_CutoffLabel, sliderX, sliderY, sliderWidth, sliderHeight, labelYOffset - 10, labelHeight);
	HelperLibrary::ResizeSliderWithLabel(m_ResonanceSlider, m_ResonanceLabel, sliderX + 75, sliderY, sliderWidth, sliderHeight, labelYOffset - 10, labelHeight);
}

void FilterComponent::SetCutoffSliderValue(double value)
{
	m_CutoffSlider.setValue(value);
}

void FilterComponent::SetResonanceSliderValue(double value)
{
	m_ResonanceSlider.setValue(value);
}