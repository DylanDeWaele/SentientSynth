/*
  ==============================================================================

    SynthVoice.h
    Created: 1 Jun 2023 2:17:02pm
    Author:  dewae

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/ADSRData.h"
#include "Data/OscillatorData.h"
#include "Data/FilterData.h"

class SynthVoice : public juce::SynthesiserVoice 
{
public:
    SynthVoice();

    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void UpdateOscillator(OscillatorData::WaveType waveType, float fmFrequency, float fmDepth);
    void UpdateADSR(float attack, float decay, float sustain, float release);
    void UpdateModADSR(float attack, float decay, float sustain, float release);
    void UpdateFilter(FilterData::FilterType filterType, float filterCutoff, float filterResonance);

    virtual bool canPlaySound(juce::SynthesiserSound* psound) override;
    virtual void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* psound, int currentPitchWheelPosition) override;
    virtual void stopNote(float velocity, bool allowTailOff) override;
    virtual void controllerMoved(int controllerNumber, int newControllerValue) override;
    virtual void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int  numSamples) override;
    virtual void pitchWheelMoved(int newPitchWheelValue) override;

private:
    juce::AudioBuffer<float> m_SynthBuffer;

    OscillatorData m_Oscillator;
    ADSRData m_ADSR;
    FilterData m_Filter;
    ADSRData m_ModADSR;

    juce::dsp::Gain<float> m_Gain;

    bool m_IsPrepared;
};