#pragma once

#define FRAMEWORK_NODISCARD
#if defined(__has_cpp_attribute)
	#if __has_cpp_attribute(nodiscard)
		#undef FRAMEWORK_NODISCARD
		#define FRAMEWORK_NODISCARD [[nodiscard]]
	#endif
#endif