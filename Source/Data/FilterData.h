/*
  ==============================================================================

    FilterData.h
    Created: 7 Jun 2023 1:11:57pm
    Author:  dewae

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class FilterData 
{
public:
    enum class FilterType
    {
        Lowpass,
        Bandpass,
        Highpass
    };

    FilterData();

    void PrepareToPlay(const juce::dsp::ProcessSpec& spec);
    void Process(juce::AudioBuffer<float>& buffer);
    void UpdateParameters(FilterType filterType, float frequency, float resonance, float modulator = 1.f);
    void Reset();

private:
    juce::dsp::StateVariableTPTFilter<float> m_Filter;
    bool m_IsPrepared;
 };