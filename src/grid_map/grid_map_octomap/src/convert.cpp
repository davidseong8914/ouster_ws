#include <filters/filter_chain.h>
#include <grid_map_msgs/GridMap.h>
#include <octomap/math/Utils.h>
#include <octomap/octomap.h>

#include <Eigen/Core>
#include <fstream>
#include <grid_map_core/GridMap.hpp>
#include <grid_map_cv/InpaintFilter.hpp>
#include <grid_map_cv/grid_map_cv.hpp>
#include <grid_map_filters/MeanInRadiusFilter.hpp>
#include <grid_map_filters/NormalVectorsFilter.hpp>
#include <grid_map_octomap/GridMapOctomapConverter.hpp>
#include <grid_map_ros/grid_map_ros.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include "ros/ros.h"
#include "std_msgs/String.h"

using namespace grid_map;

int main(int argc, char **argv) {
  ros::init(argc, argv, "octomap_to_gridmap_converter");
  ros::NodeHandle n;

  ros::Publisher grid_map_pub =
      n.advertise<grid_map_msgs::GridMap>("grid_map_publisher", 1);

  ros::Rate loop_rate(1);

  octomap::OcTree octomap("/home/rml/test_octomap.bt");

  // Convert to grid map.
  GridMap gridMap;
  gridMap.setTimestamp(0.0);
  gridMap.setFrameId("map");
  bool res =
      GridMapOctomapConverter::fromOctomap(octomap, "elevation", gridMap);

  if (true) {
    ROS_INFO_STREAM("convert successfully " << res);
    ROS_INFO("Created map with size %f x %f m (%i x %i cells).",
             gridMap.getLength().x(), gridMap.getLength().y(),
             gridMap.getSize()(0), gridMap.getSize()(1));
  }

  //   std::ofstream file(std::string("/home/rml/test_octomap.csv").c_str());
  //   if (file.is_open()) {
  //     file << gridMap.get("elevation") << '\n';
  //     // file << "m" << '\n' <<  colm(matrix) << '\n';
  //   }

  // Filter chain
  filters::FilterChain<GridMap> filterChain_("grid_map::GridMap");
  std::string filterChainParametersName_;
  n.param("filter_chain_parameter_name", filterChainParametersName_,
          std::string("grid_map_filters"));
  filterChain_.configure(filterChainParametersName_, n);

  GridMap filteredMap;
  if (!filterChain_.update(gridMap, filteredMap)) {
    ROS_ERROR("Could not update the grid map filter chain!");
    return 0;
  }
  ROS_INFO("Finish filtering");
  //   grid_map::InpaintFilter<grid_map::GridMap> inpaint_filter;
  //   grid_map::MeanInRadiusFilter<grid_map::GridMap> mean_in_radius_filter;
  //   grid_map::NormalVectorsFilter<grid_map::GridMap> normal_vectors_filter,
  //   smooth_normal_vectors_filter;

  // Get submap
  float maxX = 2.5;
  float minX = -2.5;
  float maxY = 2.5;
  float minY = -2.5;
  bool isSuccess;
  Length length(maxX - minX, maxY - minY);
  Position position(0.0, 0.0);
  GridMap subMap = filteredMap.GridMap::getSubmap(position, length, isSuccess);

  // Change resolution from 0.02 to 0.1
  GridMap modifiedMap;
  GridMapCvProcessing::changeResolution(subMap, modifiedMap, 0.1);

  // Save map to csv
  std::ofstream file(std::string("/home/rml/submap.csv").c_str());
  if (file.is_open()) {
    Eigen::MatrixXf output = modifiedMap.get("z_smooth");
    std::cout << output.rows() << " and " << output.cols() << std::endl;
    for (int i = 0; i < output.rows(); ++i) {
      for (int j = 0; j < output.cols(); ++j) {
        // Write the matrix element to the file
        file << output(i, j);

        // // Add a comma between elements (except for the last element in a
        // row)
        if (j < output.cols() - 1) {
          file << " ";
        }
      }
      // Start a new line after each row
      file << std::endl;
    }
    file.close();
    ROS_INFO("submap saved");
  }

  ROS_INFO("Created map with size %f x %f m (%i x %i cells).",
           modifiedMap.getLength().x(), modifiedMap.getLength().y(),
           modifiedMap.getSize()(0), modifiedMap.getSize()(1));

  grid_map_msgs::GridMap message;
  GridMapRosConverter::toMessage(modifiedMap, message);
  grid_map_pub.publish(message);
  while (ros::ok()) {
    grid_map_pub.publish(message);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}