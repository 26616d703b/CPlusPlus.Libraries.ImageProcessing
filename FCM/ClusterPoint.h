#pragma once

#include "StdAfx.h"


namespace ImageProcessing
{
	inline namespace Segmentation
	{
		class ClusterPoint
		{
		public:
			uint16_t x;
			uint16_t y;

			cv::Vec3b color;
			cv::Vec3b originalColor;

			double clusterIndex;

			ClusterPoint() = default;
			ClusterPoint(uint16_t p_x, uint16_t p_y, cv::Vec3b p_color);

			~ClusterPoint() = default;
		};
	}
}
