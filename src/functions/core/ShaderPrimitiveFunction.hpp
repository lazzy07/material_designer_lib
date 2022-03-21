#pragma once
#include "ShaderFunction.hpp"

namespace MATD {
	namespace FUNC {
		class ShaderPrimitiveFunction : public ShaderFunction {
		public:
			ShaderPrimitiveFunction(MATD::GRAPH::Node* node);
			~ShaderPrimitiveFunction();

			virtual void Calculate() = 0;
			virtual void SetSocketArguments() = 0;
		};
	}
}