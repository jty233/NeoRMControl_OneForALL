#ifndef __CHASSIS_STEERING_H__
#define __CHASSIS_STEERING_H__

#include <cstdint>
#include <memory>
#include <vector>

#include "pid_controller.hpp"
#include "robot.hpp"
#include "hardware.hpp"
#include "can.hpp"
#include "motor.hpp"
#include "types.hpp"
#include "utils.hpp"

namespace Chassis
{
    class Chassis_steering
    {
       public:
        Chassis_steering();
        ~Chassis_steering() = default;
        void update_data();
        void init(const std::shared_ptr<Robot::Robot_set> &robot);
        void decomposition_speed();
        void control_loop();

       public:
        fp32 vx_set = 0.f;
        // chassis set vertical speed,positive means forward,unit m/s.底盘设定速度 前进方向
        // 前为正，单位 m/s
        fp32 vy_set = 0.f;
        // chassis set horizontal speed,positive means left,unit m/s.底盘设定速度 左右方向
        // 左为正，单位 m/s
        fp32 wz_set = 0.f;

        bool no_force = true;

//        std::shared_ptr<Hardware::Can_interface> can_itrf;
       private:
        // chassis set rotation speed,positive means counterclockwise,unit
        // rad/s.底盘设定旋转角速度，逆时针为正 单位 rad/s
        fp32 vx = 0.f;
        // chassis vertical speed, positive means forward,unit m/s. 底盘速度 前进方向 前为正，单位 m/s
        fp32 vy = 0.f;
        // chassis horizontal speed, positive means letf,unit m/s.底盘速度 左右方向 左为正  单位 m/s
        fp32 wz = 0.f;
        // chassis rotation speed, positive means counterclockwise,unit rad/s.底盘旋转角速度，逆时针为正
        fp32 vz = 0.f;
        // 旋转速度wz在每个舵轮上用于旋转的线速度分量 单位 m/s
        fp32 wheel_speed[4] = {};

        fp32 wheel_angle[4] = {};
        // 转向轮与前进方向的夹角
        fp32 max_wheel_speed = 2.5f;

        std::vector<Hardware::Motor> speed_motors;
        std::vector<Hardware::Motor> turn_motors;
        std::shared_ptr<Robot::Robot_set> robot_set;
        std::vector<Pid::Pid_rad> turn_absolute_pid;
        std::vector<uint32_t> turn_motor_forward_ecd;
        std::vector<int> inverse_flag;
    };
}  // namespace Chassis

#endif