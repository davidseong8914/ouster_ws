#!/usr/bin/env python

import rospy
import geometry_msgs.msg
import nav_msgs.msg

def callback(data):
    """Listens to a transform between from_frame and to_frame and publishes it
       as a odom with a zero covariance."""
    global pub

    # Create and fill odom message for publishing
    odom = nav_msgs.msg.Odometry()
    odom.header.stamp = rospy.Time(0)
    odom.pose.pose = data.pose

    pub.publish(odom)

def main_program():
    global pub
    rospy.init_node('pose_to_odom_publisher')
    rospy.Subscriber('/mocap_node/t265_pose_frame_pose', geometry_msgs.msg.PoseStamped, callback)
    pub = rospy.Publisher('/t265/odom/sample', nav_msgs.msg.Odometry, queue_size=1)
    rospy.Timer(rospy.Duration(0.01), callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        main_program()
    except rospy.ROSInterruptException:
        pass
