/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "HelperLibrary.h"

//==============================================================================
SentientSynthAudioProcessorEditor::SentientSynthAudioProcessorEditor(SentientSynthAudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p),
	m_Oscillator{ audioProcessor.GetAudioProcessorValueTreeState(), "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH" },
	m_ADSR{ audioProcessor.GetAudioProcessorValueTreeState(), "ATTACK", "DECAY", "SUSTAIN", "RELEASE", "Amp ADSR" },
	m_Filter{ audioProcessor.GetAudioProcessorValueTreeState(), "FILTERTYPE", "FILTERCUTOFF", "FILTERRES" },
	m_ModADSR{ audioProcessor.GetAudioProcessorValueTreeState(), "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE", "Mod ADSR" }
{
	setSize(900, 600); //Set screen size

	addAndMakeVisible(m_Oscillator);
	addAndMakeVisible(m_ADSR);
	addAndMakeVisible(m_Filter);
	addAndMakeVisible(m_ModADSR);
}

SentientSynthAudioProcessorEditor::~SentientSynthAudioProcessorEditor()
{
}

//==============================================================================
void SentientSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(juce::Colours::white);

	g.drawImage(HelperLibrary::GetBackgroundImage(), 0, 0, getWidth(), getHeight(), 0, 0, HelperLibrary::GetBackgroundImage().getWidth(), HelperLibrary::GetBackgroundImage().getHeight());
	g.drawImage(HelperLibrary::GetBrainImage(), int(getWidth() / 2.5), 0, int(getWidth() / 1.5f), getHeight(), 0, 0, HelperLibrary::GetBrainImage().getWidth(), HelperLibrary::GetBrainImage().getHeight());
	g.setColour(juce::Colours::black);
	g.setFont(HelperLibrary::GetFont());
	g.setFont(72.f);
	g.drawText("SentientSynth", 0, 0, getWidth(), int(getHeight() / 4.f), juce::Justification::centred);
}

void SentientSynthAudioProcessorEditor::resized()
{
	//const int paddingX = 20;
	const int paddingY = 10;
	const int componentWidth = 300;
	const int componentHeight = 100;
	const int startX = 100;
	const int startY = 125;

	m_Oscillator.setBounds(startX, startY, componentWidth, componentHeight);
	m_ADSR.setBounds(startX, startY + componentHeight + paddingY, componentWidth, componentHeight);
	m_Filter.setBounds(startX, startY + 2 * componentHeight + 2 * paddingY, componentWidth, componentHeight);
	m_ModADSR.setBounds(startX, +startY + 3 * componentHeight + 3 * paddingY, componentWidth, componentHeight);
}

FilterComponent& SentientSynthAudioProcessorEditor::GetFilter()
{
	return m_Filter;
}

OscillatorComponent& SentientSynthAudioProcessorEditor::GetOscillator()
{
	return m_Oscillator;
}