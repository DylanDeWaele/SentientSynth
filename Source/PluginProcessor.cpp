/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SentientSynthAudioProcessor::SentientSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
	),
#endif
	m_AudioProcessorValueTreeState{ *this, nullptr, "Parameters", createParams() }
{
	m_Synth.addSound(new SynthSound());
	m_Synth.addVoice(new SynthVoice());

	connect(5000);
	juce::OSCReceiver::addListener(this);
}

SentientSynthAudioProcessor::~SentientSynthAudioProcessor()
{

}

//==============================================================================
const juce::String SentientSynthAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool SentientSynthAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool SentientSynthAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool SentientSynthAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double SentientSynthAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int SentientSynthAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
	// so this should be at least 1, even if you're not really implementing programs.
}

int SentientSynthAudioProcessor::getCurrentProgram()
{
	return 0;
}

void SentientSynthAudioProcessor::setCurrentProgram(int /*index*/)
{
}

const juce::String SentientSynthAudioProcessor::getProgramName(int /*index*/)
{
	return {};
}

void SentientSynthAudioProcessor::changeProgramName(int /*index*/, const juce::String& /*newName*/)
{
}

//==============================================================================
void SentientSynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	m_Synth.setCurrentPlaybackSampleRate(sampleRate);

	for (int i = 0; i < m_Synth.getNumVoices(); i++)
	{
		if (auto voice = dynamic_cast<SynthVoice*>(m_Synth.getVoice(i)))
		{
			voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
		}
	}
}

void SentientSynthAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SentientSynthAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	// Some plugin hosts, such as certain GarageBand versions, will only
	// load plugins that support stereo bus layouts.
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void SentientSynthAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	juce::ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	//Update parameters
	for (int i = 0; i < m_Synth.getNumVoices(); i++)
	{
		if (auto voice = dynamic_cast<SynthVoice*>(m_Synth.getVoice(i)))
		{
			//OSC
			std::atomic<float>& oscillatorWaveType = *m_AudioProcessorValueTreeState.getRawParameterValue("OSC1WAVETYPE");

			std::atomic<float>& fmFrequency = *m_AudioProcessorValueTreeState.getRawParameterValue("OSC1FMFREQ");
			std::atomic<float>& fmDepth = *m_AudioProcessorValueTreeState.getRawParameterValue("OSC1FMDEPTH");

			//AMP ADSR
			std::atomic<float>& attack = *m_AudioProcessorValueTreeState.getRawParameterValue("ATTACK"); //returns atomic float ptr
			std::atomic<float>& decay = *m_AudioProcessorValueTreeState.getRawParameterValue("DECAY");
			std::atomic<float>& sustain = *m_AudioProcessorValueTreeState.getRawParameterValue("SUSTAIN");
			std::atomic<float>& release = *m_AudioProcessorValueTreeState.getRawParameterValue("RELEASE");

			//FILTER
			std::atomic<float>& filterType = *m_AudioProcessorValueTreeState.getRawParameterValue("FILTERTYPE");
			std::atomic<float>& filterCutoff = *m_AudioProcessorValueTreeState.getRawParameterValue("FILTERCUTOFF");
			std::atomic<float>& filterResonance = *m_AudioProcessorValueTreeState.getRawParameterValue("FILTERRES");

			//MOD ADSR
			std::atomic<float>& modAttack = *m_AudioProcessorValueTreeState.getRawParameterValue("MODATTACK");
			std::atomic<float>& modDecay = *m_AudioProcessorValueTreeState.getRawParameterValue("MODDECAY");
			std::atomic<float>& modSustain = *m_AudioProcessorValueTreeState.getRawParameterValue("MODSUSTAIN");
			std::atomic<float>& modRelease = *m_AudioProcessorValueTreeState.getRawParameterValue("MODRELEASE");

			voice->UpdateOscillator(OscillatorData::WaveType(int(oscillatorWaveType.load())), fmFrequency.load(), fmDepth.load());
			voice->UpdateADSR(attack.load(), decay.load(), sustain.load(), release.load()); //Atomic floats so .load()
			voice->UpdateFilter(FilterData::FilterType(int(filterType.load())), filterCutoff.load(), filterResonance.load());
			voice->UpdateModADSR(modAttack.load(), modDecay.load(), modSustain.load(), modRelease.load()); //Atomic floats so .load()
		}
	}

	m_Synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SentientSynthAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SentientSynthAudioProcessor::createEditor()
{
	m_PluginEditor = new SentientSynthAudioProcessorEditor(*this); //we dont need to delete this

	return m_PluginEditor;
}

//==============================================================================
void SentientSynthAudioProcessor::getStateInformation(juce::MemoryBlock& /*destData*/)
{
	////https://docs.juce.com/master/tutorial_audio_processor_value_tree_state.html
	//auto state = m_AudioProcessorValueTreeState.copyState();
	//std::unique_ptr<juce::XmlElement> xml(state.createXml());
	//copyXml/ToBinary(*xml, destData);
}

void SentientSynthAudioProcessor::setStateInformation(const void* /*data*/, int /*sizeInBytes*/)
{
	////https://docs.juce.com/master/tutorial_audio_processor_value_tree_state.html
	//std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
	//
	//if (xmlState.get() != nullptr)
	//	if (xmlState->hasTagName(m_AudioProcessorValueTreeState.state.getType()))
	//		m_AudioProcessorValueTreeState.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessorValueTreeState& SentientSynthAudioProcessor::GetAudioProcessorValueTreeState()
{
	return m_AudioProcessorValueTreeState;
}

void SentientSynthAudioProcessor::oscBundleReceived(const juce::OSCBundle& bundle)
{
	for (int i = 0; i < bundle.size(); ++i)
	{
		juce::OSCBundle::Element element = bundle[i];
		if (element.isMessage())
			oscMessageReceived(element.getMessage());
		else if (element.isBundle())
			oscBundleReceived(element.getBundle());
	}
}

void SentientSynthAudioProcessor::oscMessageReceived(const juce::OSCMessage& message)
{
	const float oscMin = 0;
	const float oscMax = 1;

	const float minResonance = 1;
	const float maxResonance = 10;
	const float minCutoff = 1;
	const float maxCutoff = 20000;
	const float minFMFreq = 1;
	const float maxFMFreq = 100;
	const float minFMDepth = 1;
	const float maxFMDepth = 100;

	if (message.getAddressPattern() == "/muse/elements/theta_absolute")
	{
		m_PluginEditor->GetFilter().SetResonanceSliderValue(double(ConvertToNewRange(message[0].getFloat32(), oscMin, oscMax, minResonance, maxResonance)));
	}
	else if (message.getAddressPattern() == "/muse/elements/alpha_absolute")
	{
		m_PluginEditor->GetOscillator().SetFMFrequencySlider(double(ConvertToNewRange(message[0].getFloat32(), oscMin, oscMax, minFMFreq, maxFMFreq)));
	}
	else if (message.getAddressPattern() == "/muse/elements/beta_absolute")
	{
		m_PluginEditor->GetFilter().SetCutoffSliderValue(double(ConvertToNewRange(message[0].getFloat32(), oscMin, oscMax, minCutoff, maxCutoff)));
	}
	else if (message.getAddressPattern() == "/muse/elements/gamma_absolute")
	{
		m_PluginEditor->GetOscillator().SetFMDepthSlider(double(ConvertToNewRange(message[0].getFloat32(), oscMin, oscMax, minFMDepth, maxFMDepth)));
	}
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new SentientSynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout SentientSynthAudioProcessor::createParams()
{
	std::vector<std::unique_ptr<juce::RangedAudioParameter> > params{};

	//ADRS
	params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "ATTACK", 1 }, "Attack", juce::NormalisableRange<float> {0.1f, 1.0f, }, 0.1f)); 
	params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "DECAY", 2 }, "Decay", juce::NormalisableRange<float> {0.1f, 1.0f, }, 0.1f));
	params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "SUSTAIN", 3 }, "Sustain", juce::NormalisableRange<float> {0.1f, 1.0f, }, 1.0f));
	params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "RELEASE", 4 }, "Release", juce::NormalisableRange<float> {0.1f, 3.0f, }, 0.4f));

	//Oscillator
	params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Oscillator 1 Wave Type", juce::StringArray{ "Sin", "Saw", "Square" }, 0));

	//FM Depth & Frequency
	params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "OSC1FMFREQ", 1 }, "FM Frequency", juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f }, 0.0f)); //Skewfactor
	params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "OSC1FMDEPTH", 1 }, "FM Depth", juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f }, 0.0f)); //Skewfactor

	//Filter
	params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray{ "Lowpass", "Bandpass", "Highpass" }, 0));
	params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "FILTERCUTOFF", 1 }, "Filter Cutoff", juce::NormalisableRange<float> {20.f, 20000.f, 1.f, 0.6f}, 20000.f));
	params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "FILTERRES", 1 }, "Filter Resonance", juce::NormalisableRange<float> {1.f, 10.f, 0.1f, }, 0.0f));

	//Modulation ADSR
	params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "MODATTACK", 1 }, "Mod Attack", juce::NormalisableRange<float> {0.1f, 1.0f, }, 0.1f));
	params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "MODDECAY", 2 }, "Mod Decay", juce::NormalisableRange<float> {0.1f, 1.0f, }, 0.1f));
	params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "MODSUSTAIN", 3 }, "Mod Sustain", juce::NormalisableRange<float> {0.1f, 1.0f, }, 1.0f));
	params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "MODRELEASE", 4 }, "Mod Release", juce::NormalisableRange<float> {0.1f, 3.0f, }, 0.4f));

	return { params.begin(), params.end() };
}

float SentientSynthAudioProcessor::ConvertToNewRange(float oldValue, float oldMin, float oldMax, float newMin, float newMax)
{
	return (((oldValue - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
}
