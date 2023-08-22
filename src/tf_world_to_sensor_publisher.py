#!/usr/bin/env python 

import rospy
import geometry_msgs.msg
import nav_msgs
import tf2_ros
import tf

receive_mocap = False

def main_program():
    """ Main function initializes node and subscribers and starts
        the ROS loop. """
    # rospy.init_node('lidar_sensor_frame_tf_listener')
    # pub_topic = rospy.get_param('topics/mocap')
    # #sub_topic = rospy.get_param('topics/camera_odom_sample')
    # from_frame = 'world'
    # to_frame = 'sensor'
    if receive_mocap == True:
        broadcaster = tf2_ros.StaticTransformBroadcaster()
        static_transformStamped = geometry_msgs.msg.TransformStamped() 
        static_transformStamped.header.stamp = rospy.Time.now()
        static_transformStamped.header.frame_id = "world"
        static_transformStamped.child_frame_id = "os_sensor"

        static_transformStamped.transform.translation.x = sensor_pose.pose.position.x
        static_transformStamped.transform.translation.y = sensor_pose.pose.position.y
        static_transformStamped.transform.translation.z = sensor_pose.pose.position.z

        static_transformStamped.transform.rotation.x = sensor_pose.pose.orientation.x
        static_transformStamped.transform.rotation.y = sensor_pose.pose.orientation.y
        static_transformStamped.transform.rotation.z = sensor_pose.pose.orientation.z
        static_transformStamped.transform.rotation.w = sensor_pose.pose.orientation.w

        broadcaster.sendTransform(static_transformStamped)

    # tfBuffer = tf2_ros.Buffer()
    # tf_listener = tf2_ros.TransformListener(tfBuffer)
    # publisher = rospy.Publisher(
    #     pub_topic, geometry_msgs.msg.PoseStamped, queue_size=10)

    # # Set callback and start spinning
    # r = rospy.Rate(100)
    # while not rospy.is_shutdown():
    #     try:
    #         trans = tfBuffer.lookup_transform(from_frame, to_frame, rospy.Time(0))
    #     except (tf2_ros.LookupException, tf2_ros.ConnectivityException, tf2_ros.ExtrapolationException):
    #         print("fail to lookup transfrom")
    #         r.sleep()
    #         continue

    # # Create and fill pose message for publishing
    #     pose = geometry_msgs.msg.PoseStamped()
    #     pose.header.stamp = rospy.Time(0)
    #     pose.header.frame_id = from_frame
    #     pose.pose.position.x = trans.transform.translation.x
    #     pose.pose.position.y = trans.transform.translation.y
    #     pose.pose.position.z = trans.transform.translation.z
    #     pose.pose.orientation.x = trans.transform.rotation.x
    #     pose.pose.orientation.y = trans.transform.rotation.y
    #     pose.pose.orientation.z = trans.transform.rotation.z
    #     pose.pose.orientation.w = trans.transform.rotation.w
    #     publisher.publish(pose)
    #     r.sleep()


def mocap_listener(data):
    global sensor_pose
    sensor_pose = data.pose
    receive_mocap = True


if __name__ == '__main__':
    rospy.init_node('lidar_sensor_frame_tf_listener')
    main_program()
    mocap_listener = rospy.Subscriber("", geometry_msgs.msg.PoseStamped, mocap_listener)
    rospy.spin()