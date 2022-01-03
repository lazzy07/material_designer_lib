#pragma once
#include "Node.hpp"

namespace MATD{
  namespace GRAPH{
    class DataNode : public Node{
    public:
      DataNode(JSON JSONObj);
      ~DataNode();

      virtual void Update(JSON JSONObj) override;
    };
  }
}