#pragma once
#include <map>
#include <string>
#include "../../core/Core.hpp"
#include "../../core/JSONParser.hpp"
#include "../../types/matd/MatdDataTypes.hpp"
#include "Argument.hpp"

namespace MATD{
  namespace GRAPH {
    class Node;
  }

  namespace FUNC{
    class Function{
    public:
			static Ref<FUNC::Function> FunctionFactory(MATD::GRAPH::Node* node, const std::string& initialID, MATD::JSON JSONObj);

      Function(MATD::GRAPH::Node* node);
      ~Function();

      virtual void Init(MATD::JSON JSONObj) = 0;
      virtual void Calculate() = 0;
      virtual void Update() = 0;

      virtual void OnComplete() = 0;

      inline GRAPH::Node* GetNode() { return m_Node; };
      inline std::map<std::string, Ref<MATD::FUNC::Argument>>* GetArguments() { return &m_Arguments; };
      inline Ref<MATD::FUNC::Argument> GetArgument(const std::string& id) { return m_Arguments[id]; };
      void SetArgument(Ref<Argument> arg);
    private:
      MATD::GRAPH::Node* m_Node;
      std::map<std::string, Ref<MATD::FUNC::Argument>> m_Arguments;
    };
  }
}