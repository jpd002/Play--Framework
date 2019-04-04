#pragma once

#define FRAMEWORK_MAYBE_UNUSED
#if defined(__has_cpp_attribute)
	#if __has_cpp_attribute(maybe_unused)
		#undef FRAMEWORK_MAYBE_UNUSED
		#define FRAMEWORK_MAYBE_UNUSED [[maybe_unused]]
	#endif
#endif
