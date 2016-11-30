#include "StdAfx.h"

#include "ClusterPoint.h"


namespace ImageProcessing
{
	inline namespace Segmentation
	{
		ClusterPoint::ClusterPoint(uint16_t p_x, uint16_t p_y, cv::Vec3b p_color)
			: x(p_x), y(p_y), color(p_color), clusterIndex(-1)
		{}
	}
}
