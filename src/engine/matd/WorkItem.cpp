#include "WorkItem.hpp"
#include "../../core/EngineManager.hpp"
#include <memory>
#include "../vendor/opencl/CLWorkItem.hpp"

namespace MATD {
  namespace ENGINE {
    Ref<WorkItem> WorkItem::CreateWorkItem(Ref<Kernel> kernel)
    {
      CORE::SUPPORTED_ENGINES engine = CORE::EngineManager::GetSelectedEngine();

      switch (engine) {
      case CORE::SUPPORTED_ENGINES::CUDA:
        MATD_CORE_ASSERT(false, "WORKITEM:: CUDA is not supported yet");
        break;
      case CORE::SUPPORTED_ENGINES::OPEN_CL:
        return std::make_shared<OPENCL::WorkItem>(kernel);
        break;
      }
      MATD_CORE_ASSERT(false, "Un-identified WorkItem type selected");
      return nullptr;
    }

		void WorkItem::SetArgument(ENGINE::Argument* argument)
		{
			m_Arguments.insert(std::pair<std::string, ENGINE::Argument*>(argument->GetID(), argument));
		}
  }
}
