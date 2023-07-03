/*
  ==============================================================================

    ADSRData.h
    Created: 1 Jun 2023 5:04:07pm
    Author:  dewae

  ==============================================================================
*/

#pragma once

#include <juceHeader.h>

class ADSRData : public juce::ADSR
{
public:
    void UpdateADSR(float attack, float decay, float sustain, float release);

private:
    juce::ADSR::Parameters m_ADSRParameters;
};