//
// Created by andrea on 29/04/16.
//

#include "CallbackHandler.h"

CallbackHandler::CallbackHandler() {

    _position_sp.setPosition(0,0,0);
    _position_sp_ready = false;
    _position_sp.setOrientation(1,0,0,0);
    _position_sp.setYaw(0);

    _vision_pos.setPosition(0,0,0);
    _estimate_ready = false;
    _vision_pos.setOrientation(1,0,0,0);
    _vision_pos.setYaw(0);
}

void CallbackHandler::positionSetpointCallback(const lcm::ReceiveBuffer *rbuf, const std::string &chan,
                                               const geometry::pose *msg) {

    _position_sp.setPosition((float)msg->position[0],(float)msg->position[1],(float)msg->position[2]);

    _position_sp.setOrientation((float)msg->orientation[0],(float)msg->orientation[1],(float)msg->orientation[2],(float)msg->orientation[3]);

    _position_sp.setYaw((float)msg->yaw);

}

void CallbackHandler::visionEstimateCallback(const lcm::ReceiveBuffer *rbuf, const std::string &chan,
                                             const geometry::pose *msg) {

    _vision_pos.setPosition((float)msg->position[0],(float)msg->position[1],(float)msg->position[2]);

    _vision_pos.setOrientation((float)msg->orientation[0],(float)msg->orientation[1],(float)msg->orientation[2],(float)msg->orientation[3]);

    _estimate_ready = true;

}

MavState CallbackHandler::lcmPose2MavState(const geometry::pose lcmPose) {

    MavState temp;
    temp.setPosition((float)lcmPose.position[0],(float)lcmPose.position[1],(float)lcmPose.position[2]);
    temp.setOrientation((float)lcmPose.orientation[0],(float)lcmPose.orientation[1],(float)lcmPose.orientation[2],(float)lcmPose.orientation[3]);
    temp.setYaw(lcmPose.yaw);

    temp.timestamp = lcmPose.timestamp;
    return temp;

}

geometry::pose CallbackHandler::mavState2LcmPose(MavState mavPose) {

    geometry::pose temp;

    temp.position[0] = mavPose.getX();
    temp.position[1] = mavPose.getY();
    temp.position[2] = mavPose.getZ();

    temp.yaw = mavPose.getYaw();

    temp.orientation[0] = mavPose.getQw();
    temp.orientation[1] = mavPose.getQx();
    temp.orientation[2] = mavPose.getQy();
    temp.orientation[3] = mavPose.getQz();

    temp.timestamp = mavPose.timestamp;

    return temp;

}