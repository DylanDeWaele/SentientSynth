/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
/**
*/
class SentientSynthAudioProcessorEditor; //Class forward declaration in order to avoid conflicting headers

class SentientSynthAudioProcessor : public juce::AudioProcessor, private juce::OSCReceiver, private juce::OSCReceiver::Listener<juce::OSCReceiver::MessageLoopCallback>
#if JucePlugin_Enable_ARA
	, public juce::AudioProcessorARAExtension
#endif
{
public:
	//==============================================================================
	SentientSynthAudioProcessor();
	~SentientSynthAudioProcessor() override;

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

	//==============================================================================
	juce::AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const juce::String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const juce::String getProgramName(int index) override;
	void changeProgramName(int index, const juce::String& newName) override;

	//==============================================================================
	void getStateInformation(juce::MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;

	juce::AudioProcessorValueTreeState& GetAudioProcessorValueTreeState();

	//==============================================================================
	virtual void oscBundleReceived(const juce::OSCBundle& bundle) override;
	virtual void oscMessageReceived(const juce::OSCMessage& message) override;

private:
	//ptr to editor in order to change slider values by muse brainwave headset
	SentientSynthAudioProcessorEditor* m_PluginEditor;

	//Synthesizer
	juce::Synthesiser m_Synth;

	//Audio Processor Value Tree State
	juce::AudioProcessorValueTreeState m_AudioProcessorValueTreeState;
	juce::AudioProcessorValueTreeState::ParameterLayout createParams();

	float ConvertToNewRange(float oldValue, float oldMin, float oldMax, float newMin, float newMax);
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SentientSynthAudioProcessor)
};
