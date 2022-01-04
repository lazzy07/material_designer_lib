#pragma once
#include "../core/Node.hpp"

namespace MATD{
  namespace GRAPH{
    class ShaderNode : public Node{
    public:
      ShaderNode(JSON JSONObj);
      ~ShaderNode();

      virtual void Update(JSON JSONObj) override;
    };
  }
}