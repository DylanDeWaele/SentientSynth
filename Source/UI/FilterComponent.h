/*
  ==============================================================================

    FilterComponent.h
    Created: 7 Jun 2023 3:20:06pm
    Author:  dewae

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& audioProcessorValueTreeState, juce::String filterTypeID, juce::String cutoffID, juce::String resonanceID);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void SetCutoffSliderValue(double value);
    void SetResonanceSliderValue(double value);

private:
    juce::ComboBox m_FilterTypeSelector;
    juce::Slider m_CutoffSlider;
    juce::Slider m_ResonanceSlider;

    juce::Label m_FilterTypeLabel;
    juce::Label m_CutoffLabel;
    juce::Label m_ResonanceLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> m_FilterTypeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_CutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_ResonanceAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};