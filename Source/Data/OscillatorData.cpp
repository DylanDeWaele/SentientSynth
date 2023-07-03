/*
  ==============================================================================

	OscillatorData.cpp
	Created: 1 Jun 2023 6:43:44pm
	Author:  dewae

  ==============================================================================
*/

#include "OscillatorData.h"
#include "../HelperLibrary.h"

OscillatorData::OscillatorData() :
	m_FMOscillator{ [](float x) {return HelperLibrary::GetSineWave(x); } }, //Default wave of the FM wave type is sine
	m_FMMod{},
	m_FMDepth{},
	m_LastMidiNote{}
{
}

void OscillatorData::PrepareToPlay(const juce::dsp::ProcessSpec& spec)
{
	prepare(spec);
	m_FMOscillator.prepare(spec);
}

void OscillatorData::SetWaveType(WaveType choice)
{
	switch (choice)
	{
	case OscillatorData::WaveType::Sine:
		initialise([](float x) {return HelperLibrary::GetSineWave(x); });
		break;
	case OscillatorData::WaveType::Saw:
		initialise([](float x) {return HelperLibrary::GetSawWave(x); });
		break;
	case OscillatorData::WaveType::Square:
		initialise([](float x) {return HelperLibrary::GetSquareWave(x); });
		break;
	default:
		jassertfalse;
		break;
	}
}

void OscillatorData::SetWaveFrequency(int midiNoteNumber)
{
	setFrequency(float(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)) + m_FMMod);
	m_LastMidiNote = midiNoteNumber;
}

void OscillatorData::SetFMParams(float fmFrequency, float depth)
{
	m_FMOscillator.setFrequency(fmFrequency);
	m_FMDepth = depth;
	float currentFrequency = float(juce::MidiMessage::getMidiNoteInHertz(m_LastMidiNote)) + m_FMMod;
	setFrequency(currentFrequency >= 0 ? currentFrequency : currentFrequency * -1.f); //Keeps the current frequency always in the positive, even with extremes caused by the FM modulation
}


void OscillatorData::GetNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
	for (int channel = 0; channel < block.getNumChannels(); channel++)
	{
		for (int sample = 0; sample < block.getNumSamples(); sample++)
		{
			m_FMMod = m_FMOscillator.processSample(block.getSample(channel, sample)) * m_FMDepth;
		}
	}

	process((juce::dsp::ProcessContextReplacing<float>{ block }));
}