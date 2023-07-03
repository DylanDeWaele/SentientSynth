/*
  ==============================================================================

    ADSRData.cpp
    Created: 1 Jun 2023 5:04:07pm
    Author:  dewae

  ==============================================================================
*/

#include "ADSRData.h"

void ADSRData::UpdateADSR(float attack, float decay, float sustain, float release)
{
	m_ADSRParameters.attack = attack;
	m_ADSRParameters.decay = decay;
	m_ADSRParameters.sustain = sustain;
	m_ADSRParameters.release = release;

	setParameters(m_ADSRParameters);
}