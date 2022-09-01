/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Tether.hpp"
#include <base-logging/Logging.hpp>
#include <mars/plugins/tether_simulation/TetherSimulation.h>

using namespace mars;

Tether::Tether(std::string const& name)
    : TetherBase(name)
{
    targetSpeed.store(0);
}

Tether::~Tether()
{
}

// Operations
void Tether::dock()
{
    mars::interfaces::NodeId robot_node_id = getNodeID(_robot_link.get());
    mars::interfaces::NodeId tether_node_id = getNodeID(_tether_link.get());
    if ( tether_node_id != 0 &&
         robot_node_id  != 0 )
    {
        control->sim->connectNodes(robot_node_id, tether_node_id);
        std::cerr << "Successfully docked" << std::endl;
    } else {
        std::cerr << "Docking failed" << std::endl;
    }
}

void Tether::undock()
{
    mars::interfaces::NodeId robot_node_id = getNodeID(_robot_link.get());
    mars::interfaces::NodeId tether_node_id = getNodeID(_tether_link.get());
    if ( tether_node_id != 0 &&
         robot_node_id  != 0 )
    {
        control->sim->disconnectNodes(robot_node_id, tether_node_id);
        std::cerr << "Successfully undocked" << std::endl;
    } else {
        std::cerr << "Undocking failed" << std::endl;
    }
}

mars::interfaces::NodeId Tether::getNodeID(const std::string & link)
{
    if (link == "")
    {
        std::cerr << "Properties robot_link and tether_link must not be empty." << std::endl;
        return 0;
    }

    mars::interfaces::NodeId nodeID = control->nodes->getID(link);
    if ( nodeID == 0 )
    {
        std::cerr << "Could not determine nodeID for " << link << std::endl;
        return 0;
    } else {
        return nodeID;
    }
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
        tether_plugin = dynamic_cast<mars::plugins::tether_simulation::TetherSimulation*>(TetherPluginInterface);
        tether_plugin->updateSettings(_tether_settings.value());
        tether_plugin->init();
        printf("Plugin name : %s \n",tether_plugin->getLibName().c_str());
    }
    else
    {
        printf("Failed to obtain the Tether management plugin\n");
    }

    return true;
}
void Tether::updateHook()
{
    TetherBase::updateHook();
    printf("%s:%i\n", __PRETTY_FUNCTION__, __LINE__);

    base::samples::Joints cmd;

    while (_winch_command.read(cmd) == RTT::NewData ) {
        targetSpeed.store(cmd["winch"].speed);
    }

    float newspeed = 0;
    while (_winch_speed.read(newspeed) == RTT::NewData ) {
        targetSpeed.store(newspeed);
    }

    _rope_length.write(tether_plugin->length());

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

void  Tether::update( double time )
{
    if(!isRunning()) return; //Seems Plugin is set up but not active yet, we are not sure that we are initialized correctly so retuning
    
    // TODO: calculate speed properly based on time and desired speed
    float speed = targetSpeed.load();
    if (speed > 0) {
        tether_plugin->extendRope();
    } else if (speed < 0) {
        tether_plugin->retractRope();
    }
}
