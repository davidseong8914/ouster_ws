// Generated by gencpp from file ouster_ros/GetMetadata.msg
// DO NOT EDIT!


#ifndef OUSTER_ROS_MESSAGE_GETMETADATA_H
#define OUSTER_ROS_MESSAGE_GETMETADATA_H

#include <ros/service_traits.h>


#include <ouster_ros/GetMetadataRequest.h>
#include <ouster_ros/GetMetadataResponse.h>


namespace ouster_ros
{

struct GetMetadata
{

typedef GetMetadataRequest Request;
typedef GetMetadataResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct GetMetadata
} // namespace ouster_ros


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::ouster_ros::GetMetadata > {
  static const char* value()
  {
    return "d37888e5a47bef783c189dec5351027e";
  }

  static const char* value(const ::ouster_ros::GetMetadata&) { return value(); }
};

template<>
struct DataType< ::ouster_ros::GetMetadata > {
  static const char* value()
  {
    return "ouster_ros/GetMetadata";
  }

  static const char* value(const ::ouster_ros::GetMetadata&) { return value(); }
};


// service_traits::MD5Sum< ::ouster_ros::GetMetadataRequest> should match
// service_traits::MD5Sum< ::ouster_ros::GetMetadata >
template<>
struct MD5Sum< ::ouster_ros::GetMetadataRequest>
{
  static const char* value()
  {
    return MD5Sum< ::ouster_ros::GetMetadata >::value();
  }
  static const char* value(const ::ouster_ros::GetMetadataRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::ouster_ros::GetMetadataRequest> should match
// service_traits::DataType< ::ouster_ros::GetMetadata >
template<>
struct DataType< ::ouster_ros::GetMetadataRequest>
{
  static const char* value()
  {
    return DataType< ::ouster_ros::GetMetadata >::value();
  }
  static const char* value(const ::ouster_ros::GetMetadataRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::ouster_ros::GetMetadataResponse> should match
// service_traits::MD5Sum< ::ouster_ros::GetMetadata >
template<>
struct MD5Sum< ::ouster_ros::GetMetadataResponse>
{
  static const char* value()
  {
    return MD5Sum< ::ouster_ros::GetMetadata >::value();
  }
  static const char* value(const ::ouster_ros::GetMetadataResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::ouster_ros::GetMetadataResponse> should match
// service_traits::DataType< ::ouster_ros::GetMetadata >
template<>
struct DataType< ::ouster_ros::GetMetadataResponse>
{
  static const char* value()
  {
    return DataType< ::ouster_ros::GetMetadata >::value();
  }
  static const char* value(const ::ouster_ros::GetMetadataResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // OUSTER_ROS_MESSAGE_GETMETADATA_H