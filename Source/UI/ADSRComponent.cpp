/*
  ==============================================================================

	ADSRComponent.cpp
	Created: 1 Jun 2023 5:03:05pm
	Author:  dewae

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"
#include "../HelperLibrary.h"

//==============================================================================
ADSRComponent::ADSRComponent(juce::AudioProcessorValueTreeState& audioProcessorValueTreeState, juce::String attackID, juce::String decayID, juce::String sustainID, juce::String releaseID, juce::String componentDisplayName)
	: m_ComponentDisplayName{ componentDisplayName },
	m_AttackLabel{ "AttackLabel", "A" },
	m_DecayLabel{ "DecayLabel", "D" },
	m_SustainLabel{ "SustainLabel", "S" },
	m_ReleaseLabel{ "ReleaseLabel", "R" }
{
	HelperLibrary::InitSliderWithLabel(*this, m_AttackSlider, juce::Slider::SliderStyle::LinearVertical, m_AttackLabel, m_AttackAttachment, audioProcessorValueTreeState, attackID);
	HelperLibrary::InitSliderWithLabel(*this, m_DecaySlider, juce::Slider::SliderStyle::LinearVertical, m_DecayLabel, m_DecayAttachment, audioProcessorValueTreeState, decayID);
	HelperLibrary::InitSliderWithLabel(*this, m_SustainSlider, juce::Slider::SliderStyle::LinearVertical, m_SustainLabel, m_SustainAttachment, audioProcessorValueTreeState, sustainID);
	HelperLibrary::InitSliderWithLabel(*this, m_ReleaseSlider, juce::Slider::SliderStyle::LinearVertical, m_ReleaseLabel, m_ReleaseAttachment, audioProcessorValueTreeState, releaseID);
}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint(juce::Graphics& g)
{
	HelperLibrary::PaintComponentBox(m_ComponentDisplayName, getLocalBounds(), g);
}

void ADSRComponent::resized()
{
	const juce::Rectangle<int> bounds = getLocalBounds().reduced(10);
	const int padding = 10;

	const int sliderWidth = bounds.getWidth() / 4 - padding;
	const int sliderHeight = bounds.getHeight() - (2 * padding);
	const int sliderStartX = 0;
	const int sliderStartY = padding;

	const int labelYOffset = 10;
	const int labelHeight = 20;


	HelperLibrary::ResizeSliderWithLabel(m_AttackSlider, m_AttackLabel, sliderStartX, sliderStartY + labelHeight + labelYOffset, sliderWidth, sliderHeight, labelYOffset, labelHeight);
	HelperLibrary::ResizeSliderWithLabel(m_DecaySlider, m_DecayLabel, m_AttackSlider.getRight() + padding, sliderStartY + labelHeight + labelYOffset, sliderWidth, sliderHeight, labelYOffset, labelHeight);
	HelperLibrary::ResizeSliderWithLabel(m_SustainSlider, m_SustainLabel, m_DecaySlider.getRight() + padding, sliderStartY + labelHeight + labelYOffset, sliderWidth, sliderHeight, labelYOffset, labelHeight);
	HelperLibrary::ResizeSliderWithLabel(m_ReleaseSlider, m_ReleaseLabel, m_SustainSlider.getRight() + padding, sliderStartY + labelHeight + labelYOffset, sliderWidth, sliderHeight, labelYOffset, labelHeight);
}