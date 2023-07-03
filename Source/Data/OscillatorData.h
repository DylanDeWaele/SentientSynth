/*
  ==============================================================================

	OscillatorData.h
	Created: 1 Jun 2023 6:43:44pm
	Author:  dewae

  ==============================================================================
*/

#pragma once

#include <juceHeader.h>

class OscillatorData : public juce::dsp::Oscillator <float>
{
public:
	OscillatorData();

	enum class WaveType
	{
		Sine,
		Saw,
		Square
	};

	void PrepareToPlay(const juce::dsp::ProcessSpec& spec);
	void SetWaveType(WaveType choice);
	void SetWaveFrequency(int midiNoteNumber);
	void SetFMParams(float fmFrequency, float depth);
	void GetNextAudioBlock(juce::dsp::AudioBlock<float>& block);

private:
	juce::dsp::Oscillator<float> m_FMOscillator;
	float m_FMMod;
	float m_FMDepth;

	int m_LastMidiNote;
};