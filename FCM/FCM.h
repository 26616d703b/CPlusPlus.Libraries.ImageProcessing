#pragma once

/**
*	Ce programme...
*
*	@author		Amine MAYOUF && Zekeriya ERDOGAN
*	@date		21/11/2016
*	@since		0.1
*/

#include "StdAfx.h"

#include "Utility.h"


namespace ImageProcessing
{
	inline namespace Segmentation
	{
		class FCM
		{
		public:

			std::vector<ClusterPoint> points;
			std::vector<ClusterCentroid> centroids;

			double_t **U;

			bool isConverged = false;
			cv::Mat image;
			cv::Mat processedImage;

			double_t m;
			double_t e;
			double_t Jm;

			FCM() = delete;
			FCM(const cv::Mat &p_image, const std::vector<ClusterPoint> &p_points, 
				const std::vector<ClusterCentroid> &p_centroids, 
				double_t p_m, double_t p_e);

			~FCM();

			double_t FCM::ObjectiveFunction();

			void FCM::UpdateCentroids();

			void FCM::UpdateMembership();

			void FCM::UpdateImage();
		};
	}
}
