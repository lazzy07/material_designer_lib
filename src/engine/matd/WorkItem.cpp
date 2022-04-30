#include "WorkItem.hpp"
#include "../../core/EngineManager.hpp"
#include <memory>
#include "../vendor/opencl/CLWorkItem.hpp"
#include "../vendor/opencl/CLKernel.hpp"

namespace MATD {
  WorkItem::WorkItem(Kernel* kernel, MATD::GRAPH::ShaderNode* node): m_Kernel(kernel), m_ShaderNode(node) {
    
  }

  WorkItem* WorkItem::CreateWorkItem(Kernel* kernel)
  {
	  switch (CORE::SUPPORTED_ENGINES engine = CORE::EngineManager::GetSelectedEngine()) {
    case CORE::SUPPORTED_ENGINES::CUDA:
      MATD_CORE_ASSERT(false, "WORKITEM::CUDA is not supported yet");
      break;
    case CORE::SUPPORTED_ENGINES::OPEN_CL:
      return new ENGINE::OPENCL::WorkItem((ENGINE::OPENCL::Kernel*)kernel);
      break;
    }
    MATD_CORE_ASSERT(false, "WORKITEM::Un-identified WorkItem type selected");
    return nullptr;
  }


	void WorkItem::SetArgument(size_t index, DTYPES::Argument* argument)
	{
		m_Arguments.insert(std::pair(index, argument));
	}
}
