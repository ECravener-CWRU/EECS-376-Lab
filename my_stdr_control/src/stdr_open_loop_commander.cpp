#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
//node to send Twist commands to the Simple 2-Dimensional Robot Simulator via cmd_vel
int main(int argc, char **argv) {
    ros::init(argc, argv, "stdr_commander"); 
    ros::NodeHandle n; // two lines to create a publisher object that can talk to ROS
    ros::Publisher twist_commander = n.advertise<geometry_msgs::Twist>("/robot0/cmd_vel", 1);
    //some "magic numbers"
    const double PI = 2*acos(0.0); //Set a value for Pi
    double sample_dt = 0.01; //specify a sample period of 10ms  
    double speed = 1.0; // 1m/s speed command
    double slow_yaw_rate = 1* PI/8; //Pi/8 rad/sec yaw rate command
    double yaw_rate = PI/4; //Pi/4 rad/sec yaw rate command
    double fast_yaw_rate=  PI/2; //Pi/2 rad/sec yaw rate command
    double time_quarter_sec = 0.25; //should move .25meter or Pi/16 rad in .25 sec
    double time_half_sec = 0.5; //should move .5 meters or Pi/8 rad in .5 seconds
    double time_1_sec = 1.0; // should move 1 meter or Pi/4 rad in 1 second
    double time_2_sec = 2.0; // should move 2 meters or Pi/2 rad in 1 second
    double time_3_sec = 3.0; // should move 3 meters or 3Pi/4 rad in 3 seconds
    double time_4_sec = 4.0; // should move 4 meters or Pi rad in 4 seconds
    
      
    geometry_msgs::Twist twist_cmd; //this is the message type required to send twist commands to STDR 
    // start with all zeros in the command message; should be the case by default, but just to be safe..
    twist_cmd.linear.x=0.0;
    twist_cmd.linear.y=0.0;    
    twist_cmd.linear.z=0.0;
    twist_cmd.angular.x=0.0;
    twist_cmd.angular.y=0.0;
    twist_cmd.angular.z=0.0;   

    ros::Rate loop_timer(1/sample_dt); //create a ros object from the ros “Rate” class; set 100Hz rate     
    double timer=0.0;
    //start sending some zero-velocity commands, just to warm up communications with STDR
    for (int i=0;i<10;i++) {
      twist_commander.publish(twist_cmd);
      loop_timer.sleep();
    }
    //Move Right 3 meters
    twist_cmd.linear.x=speed; //command to move forward
    while(timer<time_3_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    //Turn ccw 45 degrees and continue moving forward
    twist_cmd.angular.z=yaw_rate; //Turn 45 Degrees ccw
    timer=0.0; //reset the timer
    while(timer<time_1_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    //Stop turning and move forward 4 meters
    twist_cmd.angular.z=0.0; //and stop spinning in place 
    timer=0.0; //reset the timer
    while(timer<time_4_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    //Turn ccw 90 degrees and continue moving forward
    twist_cmd.angular.z=yaw_rate; //Turn 90 Degrees ccw
    timer=0.0; //reset the timer
    while(timer<time_2_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    //Stop turning and move forward.5 meters
    twist_cmd.angular.z=0.0; //and stop spinning in place 
    timer=0.0; //reset the timer
    while(timer<time_half_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    //Turn cw 45  degrees and continue moving forward
    twist_cmd.angular.z=-yaw_rate; //Turn 45 Degrees cw
    timer=0.0; //reset the timer
    while(timer<time_1_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    //Stop turning and move forward 4 meters
    twist_cmd.angular.z=0.0; //and stop spinning in place 
    timer=0.0; //reset the timer
    while(timer<time_4_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    //Move forward .25 meters
    twist_cmd.angular.z=0.0; //and stop spinning in place 
    timer=0.0; //reset the timer
    while(timer<time_quarter_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    //Turn ccw 90 degrees and continue moving forward
    twist_cmd.angular.z=fast_yaw_rate; //Turn 90 Degrees ccw fast
    timer=0.0; //reset the timer
    while(timer<time_1_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    //Stop turning and move forward 2 meters
    twist_cmd.angular.z=0.0; //and stop spinning in place 
    timer=0.0; //reset the timer
    while(timer<time_2_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    //Turn ccw 45 degrees and continue moving forward
    twist_cmd.angular.z=-yaw_rate; //Turn 45 Degrees cw 
    timer=0.0; //reset the timer
    while(timer<time_1_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    //Turn ccw 45 degrees and continue moving forward
    twist_cmd.angular.z=yaw_rate; //Turn 45 Degrees ccw 
    timer=0.0; //reset the timer
    while(timer<time_1_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    //Stop turning and move forward 3 meters
    twist_cmd.angular.z=0.0; //and stop spinning in place 
    timer=0.0; //reset the timer
    while(timer<time_3_sec) {
          twist_commander.publish(twist_cmd);
          timer+=sample_dt;
          loop_timer.sleep();
          }
    //halt the motion
    twist_cmd.angular.z=0.0; 
    twist_cmd.linear.x=0.0; 
    for (int i=0;i<10;i++) {
      twist_commander.publish(twist_cmd);
      loop_timer.sleep();
    }               
    //done commanding the robot; node runs to completion
}

