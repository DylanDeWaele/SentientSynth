/*
  ==============================================================================

    MuseOSCReceiver.cpp
    Created: 7 Jun 2023 6:05:59pm
    Author:  dewae

  ==============================================================================
*/

#include "MuseOSCReceiver.h"

MuseOSCReceiver::MuseOSCReceiver(int port)
{
    DBG("Connecting to OSC port: " + std::to_string(port));
        
    // specify here on which UDP port number to receive incoming OSC messages
    if (!connect(port))                       // [3]
        DBG("Error: could not connect to UDP port " + port);

    // tell the component to listen for OSC messages matching this address:
    addListener(this, "/muse/elements/delta_absolute");    
    addListener(this, "/muse/elements/theta_absolute");    
    addListener(this, "/muse/elements/alpha_absolute");    
    addListener(this, "/muse/elements/beta_absolute");    
    addListener(this, "/muse/elements/gamma_absolute");    

    addListener(this, "/muse/acc");    
    addListener(this, "/muse/gyro");    

    addListener(this, "/muse/blink");    
    addListener(this, "/muse/jaw_Clench");    
}

void MuseOSCReceiver::oscMessageReceived(const juce::OSCMessage& message)
{
    if (message.size() == 1 && message[0].isFloat32()) 
    {
        DBG("RECEIVED OSC MESSAGE");
    }                       
}