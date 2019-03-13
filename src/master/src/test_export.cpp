// ros/ros.h　ROSに関する基本的なAPIのためのヘッダ
#include "ros/ros.h"

// geometry_msgs/Twist.h　ヘッダファイル
#include <geometry_msgs/Twist.h>

//geometry_msgs/PoseWithCovariance.h ヘッダファイル
#include <geometry_msgs/PoseStamped.h>

#include<cmath>

#define x_d 0.40  //目標位置
#define K_p 0.5  //目標ゲイン
#define K_i 0.0  //目標ゲイン
#define K_d 0.2  //目標ゲイン
#define K_phi 0.8

geometry_msgs::Twist twist;

//誤差の積分
double e_i = 0.0;
double e_I = 0.0;

int t = 0;   // Δt
int t_n_1 = 0; // 前回のナノ秒
int t_s_1 = 0; // 前回の秒

// Subscribeする対象のトピックが更新されたら呼び出されるコールバック関数
// 引数にはトピックにPublishされるメッセージの型と同じ型を定義する
void chatterCallback(const geometry_msgs::PoseStamped pose )
{

    double e = 0.0;  //z位置誤差
    double e_d = 0.0;  //微分誤差
    double a_x = 0.0; //加速度
    double a_phi = 0.0; //角加速度
    double v = 0.0;
    double w = 0.0;
    int t_s = 0;  // 秒の変化
    int t_n = 0;  //　ナノ秒の変化

    //時間変化の計算
    t_s = pose.header.stamp.sec - t_s_1;
    t_n = pose.header.stamp.nsec - t_n_1;

    //時間変化tの計算（ミリ秒）
    if(pose.header.seq ==1){
      t = pose.header.stamp.nsec / 1000000;
    }


    else if (t_s <= 1){
      t = t_s*1000 + t_n / 1000000;
      //printf("t_s = %d  t_n = %d\n",t_s,t_n);
    }

    //位置誤差の計算
    e = x_d - pose.pose.position.z;
    e_i = e_i + e * t;
    e_d = (e - e_I) / t;

    //twist.linear.x = -1 *( K_p * e + K_i * e_i - K_d * e_d ) ;
    //twist.angular.z = -1 * K_phi * atan2(pose.pose.position.x , pose.pose.position.z);
    a_x = -1 *( K_p * e + K_i * e_i + K_d * e_d ) ;
    a_phi = -1 * K_phi * atan2(pose.pose.position.x , pose.pose.position.z);

    v += a_x*t;
    w += a_phi * t;
    twist.linear.x = v;
    twist.angular.z = w;

    printf("a = %f b = %f \n",twist.linear.x  , twist.angular.z );
    printf("time is %d\n",t);


    //グローバル変数を更新
    t_n_1 = pose.header.stamp.nsec;
    t_s_1 = pose.header.stamp.sec;
    e_I = e;
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
  ros::Rate loop_rate(15);

  //geometry_msgs::Twist型のオブジェクトを定義

  //初期値の定義
  twist.linear.x = 0.0;  //直進方向に寄与するのはこの部分だけ
  twist.linear.y = 0.0;
  twist.linear.z = 0.0;
  twist.angular.x = 0.0;
  twist.angular.y = 0.0;
  twist.angular.z = 0.0;  //回転に寄与するのはこの部分だけ

  //ここからSubscriberの定義
  
  // Subscriberとして/aruco_single/poseというトピックがSubscribeし、トピックが更新されたときは
  // chatterCallbackという名前のコールバック関数を実行する
  ros::Subscriber sub = nh.subscribe("/aruco_single/pose", 1000, chatterCallback);
  
  int count = 0;
  while (ros::ok())//ノードが実行中は基本的にros::ok()=1
  {
    // トピック更新の待ちうけを行うAPI
    ros::spinOnce();
    twist_pub.publish(twist);//PublishのAPI
    //printf("time is %d\n",t);
    //printf("a = %f b = %f \n",twist.linear.x  , twist.angular.z );
    //printf("time is \n");
    twist.linear.x = 0.0;
    twist.angular.z = 0.0;
    loop_rate.sleep();
    //printf("time is %d\n",t);
    count++;
  }
  return 0;
}
