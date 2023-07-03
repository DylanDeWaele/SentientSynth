/*
  ==============================================================================

    OscillatorComponent.h
    Created: 1 Jun 2023 7:35:31pm
    Author:  dewae

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscillatorComponent  : public juce::Component
{
public:
    OscillatorComponent(juce::AudioProcessorValueTreeState& audioProcessorValueTreeState, juce::String waveSelectorID, juce::String fmFrequencyID, juce::String fmDepthID);
    ~OscillatorComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void SetFMFrequencySlider(double value);
    void SetFMDepthSlider(double value);

private:
    juce::ComboBox m_OscillatorSelector;
    juce::Slider m_FMDepthSlider;
    juce::Slider m_FMFrequencySlider;

    juce::Label m_OscillatorLabel;
    juce::Label m_FMFrequencyLabel;
    juce::Label m_FMDepthLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> m_OscillatorAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_FMDepthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_FMFrequencyAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorComponent)
};