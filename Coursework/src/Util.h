#pragma once
#include <vector>

namespace Util {


	std::vector<std::string> split(const std::string& str, const std::string& delim)
	{
		std::vector<std::string> strs;
		size_t last = 0;
		size_t next = 0;
		while ((next = str.find(delim, last)) != std::string::npos)
		{
			strs.push_back(str.substr(last, next - last));
			last = next + delim.size();
		}
		if (last < str.size())
			strs.push_back(str.substr(last));
		return strs;
	}






}
