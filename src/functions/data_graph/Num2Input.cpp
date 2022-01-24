#include "Num2Input.hpp"
#include "../../core/UUIDGenerator.hpp"
#include "../../graphs/core/OutputSocket.hpp"

MATD::FUNC::DATA::INPUT::Num2Input::Num2Input(MATD::GRAPH::Node* node) : DataPrimitiveFunction(node)
{
	MATD_CORE_TRACE("MATD::FUNC Num2Input function created");
}

void MATD::FUNC::DATA::INPUT::Num2Input::Calculate()
{
}

void MATD::FUNC::DATA::INPUT::Num2Input::SetSocketArguments()
{
	auto node = this->GetNode();

	{
		node->SetOutputSocket("out", std::make_shared<MATD::GRAPH::OutputSocket>("out", node));
	}
}
