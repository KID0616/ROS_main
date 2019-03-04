// ros/ros.h　ROSに関する基本的なAPIのためのヘッダ
#include "ros/ros.h"

// geometry_msgs/Twist.h　ヘッダファイル
#include <geometry_msgs/Twist.h>

//geometry_msgs/PoseWithCovariance.h ヘッダファイル
#include <geometry_msgs/PoseWithCovariance.h>

// Subscribeする対象のトピックが更新されたら呼び出されるコールバック関数
// 引数にはトピックにPublishされるメッセージの型と同じ型を定義する
void chatterCallback(const geometry_msgs::PoseWithCovariance pose)
{
    printf("x:%f  y:%f  z:%f\n",pose.pose.position.x , pose.pose.position.y, pose.pose.position.z );
    printf("x:%f  y:%f  z:%f  w:%f\n",pose.pose.orientation.x , pose.pose.orientation.y, pose.pose.orientation.z, pose.pose.orientation.w );
}




int main(int argc, char **argv)
{
  // 初期化のためのAPI
  // このノードは"master"という名前であるという意味
  ros::init(argc, argv, "master");

  // ノードハンドラの宣言
  ros::NodeHandle nh;

  //Publisherとしての定義
  // n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  // geometry_msgs::Twist型のメッセージを/cmd_velというトピックへ配信する
  //"1000"はトピックキューの最大値
  // ros::Publisher twist_pub = nh.advertise<geometry_msgs::Twist>("Twist/data", 1000);

  ros::Publisher twist_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

  //1秒間に1つのメッセージをPublishする
  ros::Rate loop_rate(10);

  //geometry_msgs::Twist型のオブジェクトを定義
  geometry_msgs::Twist twist;

  //初期値の定義
  twist.linear.x = 0.0;
  twist.linear.y = 0.0;
  twist.linear.z = 0.0;
  twist.angular.x = 0.0;
  twist.angular.y = 0.0;
  twist.angular.z = 1.0;

  //ここからSubscriberの定義
  
  // Subscriberとして/aruco_single/poseというトピックがSubscribeし、トピックが更新されたときは
  // chatterCallbackという名前のコールバック関数を実行する
  ros::Subscriber sub = nh.subscribe("/aruco_single/pose", 1000, chatterCallback);
  
  int count = 0;
  while (ros::ok())//ノードが実行中は基本的にros::ok()=1
  {
  //twist.linear.x = count;
  //twist.angular.z = count;
    twist_pub.publish(twist);//PublishのAPI
    //printf("a = %f b = %f \n",twist.linear.x  , twist.angular.z );
    printf("繰り返し:%d",count);
    // トピック更新の待ちうけを行うAPI
    ros::spin();
    ros::spinOnce();
    loop_rate.sleep();
    count++;
  }
  return 0;
}
