#include "KernelGraph.hpp"
#include "../core/MaterialGraph.hpp"
#include "../data_graph/DataNode.hpp"
#include "../shader_graph/ShaderNode.hpp"
#include <algorithm>

MATD::GRAPH::KernelGraph::KernelGraph(MATD::GRAPH::MaterialGraph* graph,const MATD::JSON& JSONObj) : MATD::GRAPH::Graph(graph, JSONObj)
{
	this->Init(JSONObj);
	MATD_CORE_TRACE("MATD::GRAPH KernelGraph created ID: {} MatGraphID: {}", this->GetID(), this->GetMaterialGraph()->GetID());
}

MATD::GRAPH::KernelGraph::~KernelGraph()
{
}


std::string MATD::GRAPH::KernelGraph::GetKernelName()
{
	std::string id = this->GetID();
	id.erase(std::remove(id.begin(), id.end(), '-'), id.end());
	return id;
}

void MATD::GRAPH::KernelGraph::CreateNode(MATD::JSON JSONObj)
{
}

void MATD::GRAPH::KernelGraph::Update(MATD::JSON JSONObj)
{
	MATD_CORE_TRACE("Kernel update {}", JSONObj);
	std::string type = JSONObj["type"].get<std::string>();
	std::string update = JSONObj["update"].get<std::string>();

	if (type == "kernel") {
		m_KernelSource = update;
	}
	else if (type == "functions") {
		m_FunctionsSource = update;
	}
	else {
		MATD_CORE_ERROR("Unknown update type in Kernel: {}", this->GetID());
	}
}

void MATD::GRAPH::KernelGraph::Init(const MATD::JSON& JSONObj)
{
	this->SetID(JSONObj["id"].get<std::string>());
	m_KernelSource = JSONObj["data"]["kernel"].get<std::string>();
	m_KernelSource = JSONObj["data"]["functions"].get<std::string>();
}

void MATD::GRAPH::KernelGraph::Compile()
{
	InitKernel();
	auto kernel = MATD::Kernel::CreateKernelFromSource(this->GetID(), m_ShaderSource);
	m_EngineKernel.reset(kernel);
}

void MATD::GRAPH::KernelGraph::InitKernel()
{
	m_ShaderSource = "";

	std::string structs = R""""(
typedef float Number1;
typedef float ColorVec1;

struct ColorVec3 {
	float r;
	float g;
	float b;
};

struct Number2 {
	float x;
	float y;
};

struct Lut1Elem {
	ColorVec1 color;
	int pos;
};

struct Lut3Elem {
	struct ColorVec3 color;
	int pos;
};


)"""";

	m_ShaderSource += structs;
	m_ShaderSource += m_FunctionsSource;

	m_ShaderSource += "\n\n";

	m_ShaderSource += "__kernel void ";
	m_ShaderSource += ("kernel_" + this->GetKernelName() + "(") ;

	//add kernel parameters
	{
		auto materialGraph = this->GetMaterialGraph();
		auto shaderGraph = materialGraph->GetGraph(GRAPH_TYPE::SHADER_GRAPH);

		//data parameters
		{
			auto dataGraph = materialGraph->GetGraph(GRAPH_TYPE::DATA_GRAPH);
			auto dataOutputNodes = dataGraph->GetOutputNodes();

			size_t index = 0;
			std::string argList = "";
			for (auto node : dataOutputNodes) {
				auto outSocket = node->GetOutputSocket("out");
				auto arg = outSocket->GetArgument();


				auto argName = node->GetFunction()->get()->GetArgument("id")->GetData<std::string>();
				
				argList += index > 0 ? "," : "";

				switch (arg->GetDataType())
				{
				case MATD::DATA_TYPES::NUMBER1:
					index += 1;
					argList += "Number1 " + *argName;
					break;
				case MATD::DATA_TYPES::NUMBER2:
					index += 1;
					argList += "Number2 " + *argName;
					break;
				case MATD::DATA_TYPES::STRING:
					break;
				case MATD::DATA_TYPES::BOOLEAN:
					index += 1;
					argList += "float " + *argName;
					break;
				case MATD::DATA_TYPES::COLORVEC1:
					index += 1;
					argList += "ColorVec1 " + *argName;
					break;
				case MATD::DATA_TYPES::COLORVEC3:
					index += 1;
					argList += "ColorVec3 " + *argName;
					break;
				case MATD::DATA_TYPES::LUT1:
					index += 2;
					argList += "Lut1Elem* " + *argName;
					argList += ", int " + *argName + "_size";
					break;
				case MATD::DATA_TYPES::LUT3:
					index += 2;
					argList += "Lut1Elem* " + *argName;
					argList += ", int " + *argName + "_size";
					break;
				default:
					break;
				}
			}

			m_ShaderSource += argList + "){\n\n";
			m_ShaderSource += m_KernelSource;
			m_ShaderSource += "\n\n};";
		}
	}

	MATD_CORE_TRACE("Kernel: \n" + m_ShaderSource);
}

void MATD::GRAPH::KernelGraph::SetOutputs()
{
}

void MATD::GRAPH::KernelGraph::SubmitToQueue(Ref<MATD::Queue> queue)
{
}

