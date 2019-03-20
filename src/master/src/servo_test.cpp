// ros/ros.h　ROSに関する基本的なAPIのためのヘッダ
#include "ros/ros.h"
#include <iostream>
#include "pigpiod_if2.h"

#define servo_num 4
#define MOTOR_FREQ 50
#define RANGE 1024


int main(int argc, char **argv)
{
    // 初期化のためのAPI
    // このノードは"para_in"という名前であるという意味
    ros::init(argc, argv, "servo_test");

    // ノードハンドラの宣言
    ros::NodeHandle n;
    int num = 125;
    int pi;

    pi = pigpio_start(0, 0);

    set_mode(pi,servo_num , PI_OUTPUT);
    //pwmSetMode(PWM_MODE_MS);
    set_PWM_frequency(pi,servo_num,MOTOR_FREQ); // 周波数指定
    set_PWM_range(pi, servo_num, RANGE);

    while (ros::ok())//ノードが実行中は基本的にros::ok()=1
    {

        if (num == 1000) {
            num = 25;
        }
        printf("%d\n",num);
        num++;
        set_PWM_dutycycle(pi,servo_num,num);
        //gpio_write(pi,servo_num,0);
        sleep(1);
        gpio_write(pi,servo_num,1);
        //sleep(0.5);
        //gpio_write(pi,servo_num,0);
    }
  printf("end");
  pigpio_stop(pi);
  return 0;
}