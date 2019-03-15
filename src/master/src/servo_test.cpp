// ros/ros.h　ROSに関する基本的なAPIのためのヘッダ
#include "ros/ros.h"
#include <iostream>
#include <wiringPi/wiringPi.h>


int main(int argc, char **argv)
{
    // 初期化のためのAPI
    // このノードは"para_in"という名前であるという意味
    ros::init(argc, argv, "para_in");

    // ノードハンドラの宣言
    ros::NodeHandle n;


    //1秒間に1つのメッセージをPublishする
    ros::Rate loop_rate(1);

    if (wiringPiSetupGpio() == -1) {
        std::cout << "cannot setup gpio." << std::endl;
    return 1;
    }

    pinMode(18, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(400);
    pwmSetRange(1024);

    while (ros::ok())//ノードが実行中は基本的にros::ok()=1
    {
        ros::spinOnce();
        int num;
        std::cin >> num;

        if (num == -1) {
            break;
        }

        pwmWrite(18, num);
        loop_rate.sleep();
    }
  return 0;
}