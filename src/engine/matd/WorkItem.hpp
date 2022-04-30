#pragma once
#include "../../core/Core.hpp"
#include "../../types/matd/Argument.hpp"
#include "../../graphs/shader_graph/ShaderNode.hpp"
#include "Kernel.hpp"
#include "Queue.hpp"
#include <map>

namespace MATD {
	class WorkItem {
	public:
		WorkItem(Kernel* kernel, MATD::GRAPH::ShaderNode* node = nullptr);

		void SetArgument(size_t index, DTYPES::Argument* argument);
		virtual void SetOutput(size_t index, DTYPES::Argument* argument) = 0;

		[[nodiscard]] Kernel* GetKernel() const { return m_Kernel; }
		[[nodiscard]] std::map<size_t, DTYPES::Argument*>& GetArguments() { return m_Arguments; }

		virtual void AddToQueue(MATD::Queue* queue) = 0;
		virtual void OnComplete() = 0;

		GRAPH::ShaderNode* GetShaderNode() const { return m_ShaderNode; }

		[[nodiscard]] DTYPES::Argument* GetOutput() const { return m_Output; }
		void SetOutputItem(DTYPES::Argument* arg) { m_Output = arg; }
		static WorkItem* CreateWorkItem(Kernel* kernel);
	private:
		Kernel* m_Kernel;
		GRAPH::ShaderNode* m_ShaderNode;

		DTYPES::Argument* m_Output = nullptr;
		std::map<size_t, DTYPES::Argument*> m_Arguments;
	};
}