#pragma once

#include <ros/ros.h>
#include "mios_msg/StartTask.h"
#include "mios_msg/StopTask.h"
#include "mios_msg/RemoveTask.h"
#include "mios_msg/WaitForTask.h"
#include "mios_msg/IsBusy.h"
#include "mios_msg/PostEvent.h"
#include "mios_msg/GetEvent.h"
#include "mios_msg/SetGraspedObject.h"
#include "mios_msg/GraspObject.h"
#include "mios_msg/Grasp.h"
#include "mios_msg/ReleaseObject.h"
#include "mios_msg/MoveGripper.h"
#include "mios_msg/HomeGripper.h"

namespace mios{

class Core;
class TaskEngine;
class Portal;
class Memory;

class RosNode{
public:
    RosNode(Core *core, TaskEngine *task_engine, Portal *portal, Memory* memory);

    void start();
    void stop();
    ros::NodeHandle* get_node_handle();

private:

    bool start_task(mios_msg::StartTask::Request& request,mios_msg::StartTask::Response& response);
    bool stop_task(mios_msg::StopTask::Request& request,mios_msg::StopTask::Response& response);
    bool remove_task(mios_msg::RemoveTask::Request& request,mios_msg::RemoveTask::Response& response);
    bool wait_for_task(mios_msg::WaitForTask::Request& request,mios_msg::WaitForTask::Response& response);
    bool is_busy(mios_msg::IsBusy::Request& request, mios_msg::IsBusy::Response& response);
    bool post_event(mios_msg::PostEvent::Request& request, mios_msg::PostEvent::Response& response);
    bool get_event(mios_msg::GetEvent::Request& request, mios_msg::GetEvent::Response& response);

    bool set_grasped_object(mios_msg::SetGraspedObject::Request& request, mios_msg::SetGraspedObject::Response& response);
    bool grasp_object(mios_msg::GraspObject::Request& request, mios_msg::GraspObject::Response& response);
    bool grasp(mios_msg::Grasp::Request& request, mios_msg::Grasp::Response& response);
    bool release_object(mios_msg::ReleaseObject::Request& request, mios_msg::ReleaseObject::Response& response);
    bool move_gripper(mios_msg::MoveGripper::Request& request, mios_msg::MoveGripper::Response& response);
    bool home_gripper(mios_msg::HomeGripper::Request& request, mios_msg::HomeGripper::Response& response);

private:
    ros::NodeHandle m_node;
    ros::AsyncSpinner m_spinner;

    Core* m_core;
    TaskEngine* m_task_engine;
    Portal* m_portal;
    Memory* m_memory;

private:
    ros::ServiceServer m_srv_start_task;
};

}
