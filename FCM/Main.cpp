#include "StdAfx.h"

#include "FCM.h"


using namespace ImageProcessing;


int main(int argc, char **argv)
{
	argc = 4;

	if (argc < 4)
	{
		std::cerr << "Paramètres insuffisants..." << std::endl;

		return EXIT_FAILURE;
	}	

	argv[0] = "../luffy.jpg";
	// C
	argv[1] = "3";
	// m
	argv[2] = "2";
	// e
	argv[3] = "0.3";

	cv::Mat in = cv::imread(argv[0]);

	if (!in.data)
	{
		std::cerr << "Aucune image ne correspond au chemin spécifié..." << std::endl;
		return EXIT_FAILURE;
	}
	else
	{
		cv::namedWindow("In", CV_WINDOW_AUTOSIZE);
		cv::namedWindow("Out", CV_WINDOW_AUTOSIZE);

		for (auto i = 0; i < std::stoi(argv[1]); ++i)
		{
			cv::namedWindow("Membership_to_centroid_" + std::to_string(i), CV_WINDOW_AUTOSIZE);
		}

		std::vector<ClusterPoint> points(in.rows * in.cols);
		std::vector<ClusterCentroid> centroids(std::stoi(argv[1]));

		auto k = 0;

		for (auto i = 0; i < in.rows; ++i)
		{
			for (auto j = 0; j < in.cols; ++j)
			{
				points[k] = ClusterPoint(i, j, in.at<cv::Vec3b>(i, j));
				++k;
			}
		}

		std::cout << "Génération aléatoire des coordonnées des des centroides." << std::endl;
		// Générer aléatoirement la position des centroides
		std::srand(std::time(0));

		int n1;
		int n2;

		for (auto j = 0; j < centroids.size(); ++j) 
		{
			n1 = std::rand() % (in.rows + 1);
			n2 = std::rand() % (in.cols + 1);

			centroids[j] = ClusterCentroid(n1, n2, in.at<cv::Vec3b>(n1, n2));
		}

		FCM fcm(in, points, centroids, std::stoi(argv[2]), std::stoi(argv[3]));

		double_t Jnew;

		double_t top;
		double_t sumTerms;

		do
		{
			fcm.Jm = fcm.ObjectiveFunction();
			fcm.UpdateCentroids();

			for (auto j = 0; j < centroids.size(); ++j)
			{
				for (auto i = 0; i < points.size(); ++i)
				{
					top = Utility::EuclideanDistance(points[i], centroids[j]);

					if (top < 1.0)
						top = fcm.e;

					// sumTerms is the sum of distances from this data point to all clusters.
					sumTerms = 0.0;

					for (auto jk = 0; jk < centroids.size(); ++jk)
					{
						sumTerms += top / Utility::EuclideanDistance(points[i], centroids[jk]);

					}
					// Then the membership value can be calculated as...
					fcm.U[i][j] = (double)(1.0 / std::pow(sumTerms, (2 / (fcm.m - 1))));
				}
			};

			fcm.UpdateMembership();
			
			Jnew = fcm.ObjectiveFunction();

		} while (std::abs(fcm.Jm - Jnew) < fcm.e);

		cv::imshow("In", fcm.image);
		cv::imshow("Out", fcm.processedImage);

		std::vector<cv::Mat> membershipImages(centroids.size());
		cv::Mat m;

		for (auto j = 0; j < centroids.size(); ++j) 
		{
			m = fcm.image.clone();

			cv::cvtColor(m, m, CV_RGB2GRAY);

			for (auto i = 0; i < points.size(); ++i)
			{
				m.at<char>(points[i].x, points[i].y) = fcm.U[i][j] * 255;
			}

			cv::applyColorMap(m, m, cv::COLORMAP_JET);

			membershipImages[j] = m;

			cv::imshow("Membership_to_centroid_" + std::to_string(j), membershipImages[j]);
		}

		// Out
		cv::imwrite("luffy_segmented.jpg", fcm.processedImage);

		cv::waitKey(0);
	}

	system("pause");

	return EXIT_SUCCESS;
}
