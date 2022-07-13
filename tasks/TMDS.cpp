/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "TMDS.hpp"
#include <lib_manager/LibManager.hpp>
#include <mars/plugins/tether_simulation/TetherSimulation.h>

using namespace mars;

TMDS::TMDS(std::string const& name)
    : TMDSBase(name)
{
}

TMDS::~TMDS()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See TMDS.hpp for more detailed
// documentation about them.

bool TMDS::configureHook()
{
    if (! TMDSBase::configureHook())
        return false;
    return true;
}
bool TMDS::startHook()
{
    if (! TMDSBase::startHook())
        return false;
    
    mars::interfaces::SimulatorInterface *simulation = Task::getSimulatorInterface();
        if( !simulation ){
            std::cerr << "Plugin: could not get singleton instance of simulator interface." << std::endl;
            RTT::log(RTT::Error) << "Plugin: could not get singleton instance of simulator interface." << std::endl;
            return false;
        }

    mars::interfaces::ControlCenter *control = simulation->getControlCenter();

    lib_manager::LibManager *libManager = control->getLibManager();
    mars::interfaces::MarsPluginTemplate *tetherInterface = libManager.getLibraryAs<mars::interfaces::MarsPluginTemplate>("tether_simulation"); 
    if (tetherInterface) 
    {
    // tetherPlugin= dynamic_cast<tether_simulation::TetherSimulation*>(tetherInterface);
    std::cout << "Plugin found!" << std::endl;
  
    }

    return true;
}
void TMDS::updateHook()
{
    TMDSBase::updateHook();
}
void TMDS::errorHook()
{
    TMDSBase::errorHook();
}
void TMDS::stopHook()
{
    TMDSBase::stopHook();
}
void TMDS::cleanupHook()
{
    TMDSBase::cleanupHook();
}
