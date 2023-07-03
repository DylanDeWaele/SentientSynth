/*
  ==============================================================================

	FilterData.cpp
	Created: 7 Jun 2023 1:11:57pm
	Author:  dewae

  ==============================================================================
*/

#include "FilterData.h"

FilterData::FilterData() :
	m_Filter{},
	m_IsPrepared{ false }
{
}

void FilterData::PrepareToPlay(const juce::dsp::ProcessSpec& spec)
{
	m_Filter.reset();
	m_Filter.prepare(spec);

	m_IsPrepared = true;
}

void FilterData::Process(juce::AudioBuffer<float>& buffer)
{
	jassert(m_IsPrepared);

	juce::dsp::AudioBlock<float> block{ buffer };
	m_Filter.process(juce::dsp::ProcessContextReplacing<float>{block});
}

void FilterData::UpdateParameters(FilterType filterType, float frequency, float resonance, float modulator)
{
	switch (filterType)
	{
	case FilterType::Lowpass:
		m_Filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
		break;
	case FilterType::Bandpass:
		m_Filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
		break;
	case FilterType::Highpass:
		m_Filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
		break;
	}

	float modFrequency = frequency * modulator; //We have a modulation ADSR affecting the filter
	modFrequency = std::fmin(std::fmax(modFrequency, 20.f) , 20000.f);

	m_Filter.setCutoffFrequency(modFrequency);
	m_Filter.setResonance(resonance);
}

void FilterData::Reset()
{
	m_Filter.reset();
}