#pragma once

#if defined(_MSC_VER) && defined(__cpp_lib_experimental_erase_if)

#include <experimental/map>

#else

namespace std
{
	namespace experimental
	{
		template<class Key, class T, class Compare, class Alloc, class Pred>
		void erase_if(std::map<Key, T, Compare, Alloc>& c, Pred pred)
		{
			for(auto i = c.begin(), last = c.end(); i != last; )
			{
				if(pred(*i))
				{
					i = c.erase(i);
				}
				else
				{
					++i;
				}
			}
		}
	}
}

#endif
