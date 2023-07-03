/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/ADSRComponent.h"
#include "UI/OscillatorComponent.h"
#include "UI/FilterComponent.h"

//==============================================================================
/**
*/
class SentientSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
	SentientSynthAudioProcessorEditor(SentientSynthAudioProcessor&);
	~SentientSynthAudioProcessorEditor() override;

	//==============================================================================
	void paint(juce::Graphics&) override;
	void resized() override;

	FilterComponent& GetFilter();
	OscillatorComponent& GetOscillator();

private:
	SentientSynthAudioProcessor& audioProcessor;

	OscillatorComponent m_Oscillator;
	ADSRComponent m_ADSR;
	FilterComponent m_Filter;
	ADSRComponent m_ModADSR;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SentientSynthAudioProcessorEditor)
};
