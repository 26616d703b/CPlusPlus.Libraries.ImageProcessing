#include "stdafx.h"
#include "ClusterCentroid.h"

namespace ImageProcessing
{
	inline namespace Segmentation
	{
		ClusterCentroid::ClusterCentroid(uint16_t p_x, uint16_t p_y, cv::Vec3b p_color)
			: x(p_x), y(p_x), pixelCount(0), rSum(0), gSum(0), bSum(0), membershipSum(0),
			color(p_color), originalColor(p_color)
		{
		}
	}
}
