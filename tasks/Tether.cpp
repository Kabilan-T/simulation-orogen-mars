/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Tether.hpp"
#include <lib_manager/LibManager.hpp>
#include <mars/plugins/tether_simulation/TetherSimulation.h>

#include <base-logging/Logging.hpp>
using namespace mars;

Tether::Tether(std::string const& name)
    : TetherBase(name)
{
}

Tether::~Tether()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Tether.hpp for more detailed
// documentation about them.

bool Tether::configureHook()
{
    if (! TetherBase::configureHook())
        return false;
    return true;
}
bool Tether::startHook()
{
    if (! TetherBase::startHook())
        return false;
    

    mars::interfaces::MarsPluginTemplate *TetherPluginInterface;
    if (Task::getPlugin("tether_simulation", TetherPluginInterface))
    {
        LOG_DEBUG("The Tether management plugin from the simulation has been obtained");
        tether_plugin = dynamic_cast<mars::plugins::tether_simulation::TetherSimulation*>(TetherPluginInterface);
        state(RELEASING);
    }
    else
    {
        LOG_DEBUG("Failed to obtain the Tether management plugin");
        state(RETRIEVING);
    }

    return true;
}
void Tether::updateHook()
{
    TetherBase::updateHook();
}
void Tether::errorHook()
{
    TetherBase::errorHook();
}
void Tether::stopHook()
{
    TetherBase::stopHook();
}
void Tether::cleanupHook()
{
    TetherBase::cleanupHook();
}
