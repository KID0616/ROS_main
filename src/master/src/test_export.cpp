// ros/ros.h　ROSに関する基本的なAPIのためのヘッダ
#include "ros/ros.h"
// comp_tutrial/adder.h　adder.msgから生成されたメッセージを定義しているヘッダ
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv)
{
  // 初期化のためのAPI
  // このノードは"para_in"という名前であるという意味
  ros::init(argc, argv, "master");

  // ノードハンドラの宣言
  ros::NodeHandle nh;

  //Publisherとしての定義
  // n.advertise<comp_tutorial::adder>("para_input", 1000);
  // comp_tutorial::adder型のメッセージをpara_inputというトピックへ配信する
  //"1000"はトピックキューの最大値
  // ros::Publisher twist_pub = nh.advertise<geometry_msgs::Twist>("Twist/data", 1000);

  ros::Publisher twist_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

  //1秒間に1つのメッセージをPublishする
  ros::Rate loop_rate(1);

  //comp_tutrial::adder型のオブジェクトを定義
  //adder.msgで定義したa,bはメンバ変数としてアクセスできる
  geometry_msgs::Twist twist;
  twist.linear.x = 0.0;
  twist.linear.y = 0.0;
  twist.linear.z = 0.0;
  twist.angular.x = 0.0;
  twist.angular.y = 0.0;
  twist.angular.z = 1.0;

  int count = 0;
  while (ros::ok())//ノードが実行中は基本的にros::ok()=1
  {
//    twist.linear.x = count;
  //  twist.angular.z = count;
    twist_pub.publish(twist);//PublishのAPI
    printf("a = %f b = %f \n",twist.linear.x  , twist.angular.z );
    ros::spinOnce();
    loop_rate.sleep();
    count++;
  }
  return 0;
}
