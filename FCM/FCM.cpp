#include "StdAfx.h"
#include "FCM.h"

namespace ImageProcessing
{
	inline namespace Segmentation
	{
		FCM::FCM(const cv::Mat & p_image,
			const std::vector<ClusterPoint>& p_points,
			const std::vector<ClusterCentroid>& p_centroids,
			double_t p_m, double_t p_e) 
			: image(p_image), processedImage(p_image.clone()), points(p_points), centroids(p_centroids), m(p_m), e(p_e)
		{
			// Initialisation de la matrice des degrés d'appartenance
			U = new double_t*[p_points.size()];

			double_t difference;

			for (auto i = 0; i < p_points.size(); ++i)
			{
				U[i] = new double_t[p_centroids.size()];

				for (auto j = 0; j < p_centroids.size(); ++j)
				{

					difference = std::sqrt(std::pow(Utility::EuclideanDistance(points[i], centroids[j]), 2.0));

					U[i][j] = (difference == 0) ? p_e : difference;
				}
			}

			UpdateMembership();
		}

		FCM::~FCM()
		{
			// Libérer p'espace reservé à la matrice
			for (size_t i = 0; i < points.size(); ++i) {

				free(U[i]);
			}

			free(U);
		}

		double_t FCM::ObjectiveFunction()
		{
			for (auto i = 0; i < points.size(); ++i)
			{
				for (auto j = 0; j < centroids.size(); j++)
				{
					Jm += std::pow(U[i][j], m) * std::pow(Utility::EuclideanDistance(points[i], centroids[j]), 2.0);
				}
			}

			return Jm;
		}

		void FCM::UpdateCentroids()
		{
			double_t p;

			for (auto j = 0; j < centroids.size(); ++j)
			{
				p = 0.0;
				centroids[j].pixelCount = 1;
				centroids[j].rSum = 0;
				centroids[j].gSum = 0;
				centroids[j].bSum = 0;
				centroids[j].membershipSum = 0;

				for (auto i = 0; i < points.size(); ++i)
				{
					p = std::pow(U[i][j], m);

					centroids[j].rSum += p * points[i].color[0];
					centroids[j].gSum += p * points[i].color[1];
					centroids[j].bSum += p * points[i].color[2];
					centroids[j].membershipSum += p;

					if (U[i][j] == points[i].clusterIndex)
					{
						centroids[j].pixelCount += 1;
					}
				}

				centroids[j].color[0] = centroids[j].rSum / centroids[j].membershipSum;
				centroids[j].color[1] = centroids[j].gSum / centroids[j].membershipSum;
				centroids[j].color[2] = centroids[j].bSum / centroids[j].membershipSum;
			}

			UpdateImage();
		}

		void FCM::UpdateMembership()
		{
			double_t max;
			double_t min;
			double_t sum;

			double_t newMax;

			for (auto i = 0; i < points.size(); ++i)
			{
				max = 0.0;
				min = 0.0;
				sum = 0.0;

				newMax = 0;

				//Normalize the entries
				for (auto j = 0; j < centroids.size(); ++j)
				{
					max = U[i][j] > max ? U[i][j] : max;
					min = U[i][j] < min ? U[i][j] : min;
				}
				//Sets the values to the normalized values between 0 and 1
				for (auto j = 0; j < centroids.size(); ++j)
				{
					U[i][j] = (U[i][j] - min) / (max - min);
					sum += U[i][j];
				}
				//Makes it so that the sum of all values is 1 
				for (auto j = 0; j < centroids.size(); ++j)
				{
					U[i][j] = U[i][j] / sum;

					if (std::isnan(U[i][j]))
					{
						U[i][j] = 0.0;
					}

					newMax = U[i][j] > newMax ? U[i][j] : newMax;
				}

				// ClusterIndex is used to store the strongest membership value to a cluster, used for defuzzification
				points[i].clusterIndex = newMax;
			};
		}
	}

			
	void FCM::UpdateImage()
	{
		for (auto i = 0; i < points.size(); ++i)
		{
			for (auto j = 0; j < centroids.size(); ++j)
			{
				if (U[i][j] == points[i].clusterIndex)
				{
					processedImage.at<cv::Vec3b>(points[i].x, points[i].y) = centroids[j].color;
				}
			}
		}
	}
}
