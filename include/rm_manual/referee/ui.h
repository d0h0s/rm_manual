//
// Created by peter on 2021/5/24.
//

#ifndef RM_MANUAL_REFEREE_UI_H_
#define RM_MANUAL_REFEREE_UI_H_

#include "rm_manual/referee/referee.h"
#include "rm_manual/referee/graph.h"
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <rm_common/ori_tool.h>

namespace rm_manual {
class UiBase {
 public:
  explicit UiBase(ros::NodeHandle &nh, Referee &referee) : referee_(referee) {}
  virtual void display() {
    for (int i = 0; i < (int) graph_vector_.size(); i++)
      referee_.sendUi(graph_vector_[i]->getConfig(), graph_vector_[i]->getContent());
  }
 protected:
  std::vector<GraphBase *> graph_vector_;
  Referee &referee_;
};

class UiTitle : public UiBase {
 public:
  explicit UiTitle(ros::NodeHandle &nh, Referee &referee) : UiBase(nh, referee) {
    XmlRpc::XmlRpcValue title_config;
    if (!nh.getParam("title", title_config)) {
      ROS_ERROR("Title no defined (namespace %s)", nh.getNamespace().c_str());
      return;
    }
    for (int i = 0; i < (int) title_config.size(); ++i) graph_vector_.push_back(new UnChangeGraph(title_config[i]));
  }
};

} // namespace rm_manual
#endif //RM_MANUAL_REFEREE_UI_H_
