#include "stdafx.h"

#include "Utility.h"

namespace ImageProcessing
{
	double_t Utility::EuclideanDistance(const ClusterPoint& p_point, const ClusterCentroid& p_centroid)
	{

		return std::sqrt(std::pow(p_point.color[0] - p_centroid.color[0], 2.0)
			+ std::pow(p_point.color[1] - p_centroid.color[1], 2.0)
			+ std::pow(p_point.color[2] - p_centroid.color[2], 2.0));
	}

	std::vector<std::string> Utility::Split(const std::string & p_str, char p_delimiter)
	{
		auto l = 0;
		std::vector<std::string> result;

		for (auto i = 0; i < p_str.size(); ++i)
		{
			if (p_str[i] == p_delimiter) 
			{
				result.push_back(p_str.substr(l, i));
				l = i;
			}
		}

		return result;
	}
}
