/*
  ==============================================================================

	SynthVoice.cpp
	Created: 1 Jun 2023 2:17:02pm
	Author:  dewae

  ==============================================================================
*/

#include "SynthVoice.h"

SynthVoice::SynthVoice()
	: juce::SynthesiserVoice{},
	m_SynthBuffer{},
	m_Oscillator{},
	m_ADSR{},
	m_Filter{},
	m_ModADSR{},
	m_Gain{},
	m_IsPrepared{ false }
{
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
	juce::dsp::ProcessSpec spec{};
	spec.maximumBlockSize = samplesPerBlock;
	spec.sampleRate = sampleRate;
	spec.numChannels = outputChannels;

	m_Oscillator.PrepareToPlay(spec);
	m_ADSR.setSampleRate(sampleRate);
	m_Filter.PrepareToPlay(spec);
	m_ModADSR.setSampleRate(sampleRate);

	m_Gain.setGainLinear(0.5f);
	m_Gain.prepare(spec);

	m_IsPrepared = true;
}

void SynthVoice::UpdateOscillator(OscillatorData::WaveType waveType, float fmFrequency, float fmDepth)
{
	m_Oscillator.SetWaveType(waveType);
	m_Oscillator.SetFMParams(fmFrequency, fmDepth);
}

void SynthVoice::UpdateADSR(float attack, float decay, float sustain, float release)
{
	m_ADSR.UpdateADSR(attack, decay, sustain, release);
}

void SynthVoice::UpdateFilter(FilterData::FilterType filterType, float filterCutoff, float filterResonance)
{
	float modulator = m_ModADSR.getNextSample();
	m_Filter.UpdateParameters(filterType, filterCutoff, filterResonance, modulator);
}

void SynthVoice::UpdateModADSR(float attack, float decay, float sustain, float release)
{
	m_ModADSR.UpdateADSR(attack, decay, sustain, release);
}


bool SynthVoice::canPlaySound(juce::SynthesiserSound* psound)
{
	return dynamic_cast<juce::SynthesiserSound*>(psound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float /*velocity*/, juce::SynthesiserSound* /*psound*/, int /*currentPitchWheelPosition*/)
{
	m_Oscillator.SetWaveFrequency(midiNoteNumber);

	//m_ADSR.reset(); //Causes clicks
	m_ADSR.noteOn();

	//m_ModADSR.reset(); //Causes clicks
	m_ModADSR.noteOn();
}

void SynthVoice::stopNote(float /*velocity*/, bool allowTailOff)
{
	m_ADSR.noteOff();
	m_ModADSR.noteOff();

	if (!allowTailOff || !m_ADSR.isActive())
		clearCurrentNote();
}

void SynthVoice::controllerMoved(int /*controllerNumber*/, int /*newControllerValue*/)
{

}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	jassert(m_IsPrepared);	//Stop project if we forget to prepare to play

	if (!isVoiceActive())
		return;

	m_SynthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true); //Dont reallocate more memory each time, only when necessary
	m_ModADSR.applyEnvelopeToBuffer(m_SynthBuffer, 0, numSamples); //Doesnt actually do anything to the audio buffer since it is cleared right after, but we need it in order for the ADSR to activate
	m_SynthBuffer.clear();

	juce::dsp::AudioBlock<float> audioBlock{ m_SynthBuffer };

	m_Oscillator.GetNextAudioBlock(audioBlock);
	m_ADSR.applyEnvelopeToBuffer(m_SynthBuffer, 0, m_SynthBuffer.getNumSamples());
	m_Filter.Process(m_SynthBuffer);
	m_Gain.process(juce::dsp::ProcessContextReplacing<float>{ audioBlock });

	for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++) //Adding synthbuffer to the current buffer so we dont get clicks when playing new notes
	{
		outputBuffer.addFrom(channel, startSample, m_SynthBuffer, channel, 0, numSamples);

		if (!m_ADSR.isActive())
			clearCurrentNote();
	}
}

void SynthVoice::pitchWheelMoved(int /*newPitchWheelValue*/)
{
}