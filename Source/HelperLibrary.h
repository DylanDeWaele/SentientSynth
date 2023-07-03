/*
  ==============================================================================

	HelperLibrary.h
	Created: 8 Jun 2023 2:18:53pm
	Author:  dewae

  ==============================================================================
*/

#pragma once
#include <juceheader.h>

namespace HelperLibrary
{
	juce::Image GetBackgroundImage();
	juce::Image GetBrainImage();
	juce::Font GetFont();

	float GetSineWave(float xs);
	float GetSawWave(float xs);
	float GetSquareWave(float xs);

	void InitSliderWithLabel(juce::Component& component, juce::Slider& slider, juce::Slider::SliderStyle sliderStyle, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& audioProcessorValueTreeState, juce::String paramID);
	void InitComboBoxWithLabel(juce::Component& component, juce::ComboBox& comboBox, juce::StringArray choices, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>& attachment, juce::AudioProcessorValueTreeState& audioProcessorValueTreeState, juce::String paramID);

	void ResizeSliderWithLabel(juce::Slider& slider, juce::Label& label, int sliderX, int sliderY, int sliderWidth, int sliderHeight, int labelYOffset, int labelHeight);
	void ResizeComboBoxWithLabel(juce::ComboBox& comboBox, juce::Label& label, int comboBoxX, int comboboxY, int comboBoxWidth, int comboBoxHeight, int labelYOffset, int labelHeight);

	void PaintComponentBox(juce::String componentName, juce::Rectangle<int> componentBounds, juce::Graphics& g);
};