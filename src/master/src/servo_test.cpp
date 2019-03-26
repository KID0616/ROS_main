// ros/ros.h　ROSに関する基本的なAPIのためのヘッダ
#include "ros/ros.h"
#include <iostream>
#include "pigpiod_if2.h"
#include "master/deg.h"

#define servo_num 4
#define MOTOR_FREQ 50
#define RANGE 1024

int deg = 90;

void chatterCallback(const master::deg msg)
{
    deg = msg.deg ;
    printf("deg:%d \n",deg);
}

int main(int argc, char **argv)
{
    // 初期化のためのAPI
    // このノードは"para_in"という名前であるという意味
    ros::init(argc, argv, "servo_test");

    // ノードハンドラの宣言
    ros::NodeHandle n;
    int num = 75;
    int pi;
    int deg = 90;

    pi = pigpio_start(0, 0);
 
    set_mode(pi,servo_num , PI_OUTPUT);
    //pwmSetMode(PWM_MODE_MS);
    set_PWM_frequency(pi,servo_num,MOTOR_FREQ); // 周波数指定
    set_PWM_range(pi, servo_num, RANGE);

    while (ros::ok())//ノードが実行中は基本的にros::ok()=1
    {

        ros::Subscriber sub = n.subscribe("servo_input", 1000, chatterCallback);

        num = (deg/180) * 100 +25 ;
        //printf("%d\n",deg);
        //num=75 90deg 25:0deg 125:180deg
        set_PWM_dutycycle(pi,servo_num,num);
        //gpio_write(pi,servo_num,0);
        sleep(1);
        gpio_write(pi,servo_num,1);
        //sleep(0.5);
        //gpio_write(pi,servo_num,0);
        ros::spin();
    }
  printf("end");
  pigpio_stop(pi);
  return 0;
}