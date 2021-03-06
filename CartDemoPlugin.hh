/*--Version 17.3 map road2-v6.3 small vehicle-->
 * Copyright (C) 2012-2014 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef _GAZEBO_CART_DEMO_PLUGIN_HH_
#define _GAZEBO_CART_DEMO_PLUGIN_HH_

#include "gazebo/common/common.hh"    //for gazebo 3.0, need to add extra part of path
#include "gazebo/physics/physics.hh"
#include "gazebo/transport/TransportTypes.hh"
#include "gazebo/gazebo.hh"
#include "gazebo/transport/transport.hh"
//#include "gazebo/util/system.hh"

#define NUM_JOINTS 3

///Car internal dynamic properties
static const  double m=1000;                         // mass of car kg
static const 	double Tm = 900;                       // gas torque constant, Nm
static const 	double brake_Tm = 1900;								 //brake torque constant
static const 	double g = 9.8;                        // gravitational constant

static const  double brake_an = 12;
static const	double gears[5] = {40, 25, 16, 12, 10};	// gear ratios
static const 	int gear=4;            								 //gear
static const 	double an= gears[gear];
static const 	double wm = 420;                       // peak torque rate, rad/sec
static const 	double bbeta = 0.4;                    // torque coefficient
static const 	double Cr = 0.01;                      // coefficient of rolling friction
static const 	double rho = 1.3;                      // density of air, kg/m^3
static const 	double Cd = 0.32;                      // drag coefficient
static const 	double A = 2.4;                        // car area, m^2
static const 	double radius = 0.2;                        // wheelRadius

namespace gazebo
{
  /// \brief This plugin drives a four wheeled cart model forward and back
  /// by applying a small wheel torque.  Steering is controlled via
  /// a position pid.
  /// this is a test for general rolling contact stability.
  /// should refine the test to be more specific in the future.
  class CartDemoPlugin : public ModelPlugin
  {
    public: CartDemoPlugin();
    public: virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);
    public: virtual void Init();
    public: void pidCal(double &theta_e, double &v_e, double &a, double &b, double &b_g, 
    								double &kp, double &ki); //Calculate pid parameters
    public: void brakePidCal(double &theta_e, double &kp, double &ki);
    ///Calculate pi parameters for brake
    private: void OnUpdate();

    private: transport::NodePtr node;

    private: event::ConnectionPtr updateConnection;

    private: physics::ModelPtr model;

    private: physics::JointPtr joints[5];
    private: common::PID jointPIDs[NUM_JOINTS];
    private: double jointPositions[NUM_JOINTS];
    private: double jointVelocities[NUM_JOINTS];
    private: double jointMaxEfforts[NUM_JOINTS];
    
    private: physics::JointPtr gasJoint, brakeJoint;
    private: double aeroLoad;
    private: double frontPower;
    private: double tireAngleRange;
    private: double steeringRatio;
    private: double maxGas, maxBrake;
    private: double swayForce;
    private: double maxSpeed;
    private: double rearPower;
    private: double wheelRadius;
	  private: double gas_force, brake_force;
    private: common::Time prevUpdateTime;
    private: double v_e, u_e, a, b, b_g, kp, ki, theta_prev, x_orig,v_prev, i_store, target_prev, u_prev, 
    brake_i_store, brake_u_prev, brake_ki, brake_kp;
    private: double ITerm; // Integration part
    private: double vel_set; // Vel set to joints
    //SubscriberPtr to 
  };
}
#endif
