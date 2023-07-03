/*
  ==============================================================================

	HelperLibrary.cpp
	Created: 8 Jun 2023 2:32:38pm
	Author:  dewae

  ==============================================================================
*/

#include "HelperLibrary.h"

juce::Image HelperLibrary::GetBackgroundImage()
{
	return juce::ImageCache::getFromMemory(BinaryData::PluginBackground_jpg, BinaryData::PluginBackground_jpgSize);
}

juce::Image HelperLibrary::GetBrainImage()
{
	return juce::ImageCache::getFromMemory(BinaryData::_12brainfreepngimage_800x800_png, BinaryData::_12brainfreepngimage_800x800_pngSize);
}

juce::Font HelperLibrary::GetFont()
{
	return juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::SuperBrigade2O8Ao_otf, BinaryData::SuperBrigade2O8Ao_otfSize));
}

float HelperLibrary::GetSineWave(float x)
{
	return std::sin(x);
}
float HelperLibrary::GetSawWave(float x)
{
	return x / juce::MathConstants<float>::pi;
}
float HelperLibrary::GetSquareWave(float x)
{
	return x < 0.0f ? -1.0f : 1.0f;
}

void HelperLibrary::InitSliderWithLabel(juce::Component& component, juce::Slider& slider, juce::Slider::SliderStyle sliderStyle, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& audioProcessorValueTreeState, juce::String paramID)
{
	attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessorValueTreeState, paramID, slider);

	slider.setSliderStyle(sliderStyle);
	slider.setColour(juce::Label::ColourIds::textColourId, juce::Colours::cyan);
	slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 25, 10);
	component.addAndMakeVisible(slider);

	label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
	label.setJustificationType(juce::Justification::centred);
	label.setFont(15.f);
	component.addAndMakeVisible(label);
}

void HelperLibrary::InitComboBoxWithLabel(juce::Component& component, juce::ComboBox& comboBox, juce::StringArray choices, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>& attachment, juce::AudioProcessorValueTreeState& audioProcessorValueTreeState, juce::String paramID)
{
	attachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessorValueTreeState, paramID, comboBox);

	comboBox.addItemList(choices, 1);
	comboBox.setSelectedId(int(audioProcessorValueTreeState.getRawParameterValue(paramID)->load() + 1));
	component.addAndMakeVisible(comboBox);

	label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
	label.setJustificationType(juce::Justification::left);
	label.setFont(GetFont());
	label.setFont(15.f);
	component.addAndMakeVisible(label);
}

void HelperLibrary::ResizeSliderWithLabel(juce::Slider& slider, juce::Label& label, int sliderX, int sliderY, int sliderWidth, int sliderHeight, int labelYOffset, int labelHeight)
{
	slider.setBounds(sliderX, sliderY, sliderWidth, sliderHeight);
	label.setBounds(slider.getX(), slider.getY() - labelYOffset, slider.getWidth(), labelHeight);
}

void HelperLibrary::ResizeComboBoxWithLabel(juce::ComboBox& comboBox, juce::Label& label, int comboBoxX, int comboboxY, int comboBoxWidth, int comboBoxHeight, int labelYOffset, int labelHeight)
{
	comboBox.setBounds(comboBoxX, comboboxY, comboBoxWidth, comboBoxHeight);
	label.setBounds(comboBox.getX(), comboBox.getY() - labelYOffset, comboBox.getWidth(), labelHeight);
}

void HelperLibrary::PaintComponentBox(juce::String componentName, juce::Rectangle<int> componentBounds, juce::Graphics& g)
{
	auto labelSpace = componentBounds.removeFromTop(25);

	//g.fillAll(juce::Colours::white);
	g.setColour(juce::Colours::black);
	g.setFont(HelperLibrary::GetFont());
	g.setFont(32.f);
	g.drawText(componentName, labelSpace, juce::Justification::left);
	g.drawRoundedRectangle(componentBounds.toFloat(), 5.f, 2.f);
}