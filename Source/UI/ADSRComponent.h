/*
  ==============================================================================

	ADSRComponent.h
	Created: 1 Jun 2023 5:03:05pm
	Author:  dewae

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ADSRComponent : public juce::Component
{
public:
	ADSRComponent(juce::AudioProcessorValueTreeState& audioProcessorValueTreeState, juce::String attackID, juce::String decayID, juce::String sustainID, juce::String releaseID, juce::String componentDisplayName = "ADSR");
	~ADSRComponent() override;

	void paint(juce::Graphics&) override;
	void resized() override;

private:
	juce::String m_ComponentDisplayName;

	juce::Slider m_AttackSlider;
	juce::Slider m_DecaySlider;
	juce::Slider m_SustainSlider;
	juce::Slider m_ReleaseSlider;

	juce::Label m_AttackLabel;
	juce::Label m_DecayLabel;
	juce::Label m_SustainLabel;
	juce::Label m_ReleaseLabel;

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_AttackAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_DecayAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_SustainAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_ReleaseAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ADSRComponent)
};
