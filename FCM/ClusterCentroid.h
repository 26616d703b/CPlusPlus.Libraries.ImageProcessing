#pragma once


namespace ImageProcessing
{
	inline namespace Segmentation
	{
		class ClusterCentroid
		{
			/*
			*	Attributes
			*/

		public:

			uint16_t x;
			uint16_t y;

			// Le nombre de pixels dans le nuage
			uint32_t pixelCount;

			double_t rSum;
			double_t gSum;
			double_t bSum;
			double_t membershipSum;

			cv::Vec3b color;
			cv::Vec3b originalColor;

			/*
			*	Methods
			*/
			ClusterCentroid() = default;
			ClusterCentroid(uint16_t p_x, uint16_t p_y, cv::Vec3b p_color);

			~ClusterCentroid() = default;
		};
	}
}
