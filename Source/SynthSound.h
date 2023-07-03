#/*
  ==============================================================================

    SynthSound.h
    Created: 1 Jun 2023 2:17:22pm
    Author:  dewae

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound 
{
public:
    virtual bool appliesToNote(int) override { return true; } //Implementation of pure virtual function of abstract synthesiserSound class
    virtual bool appliesToChannel(int) override { return true; } //Implementation of pure virtual function of abstract synthesiserSound class
};