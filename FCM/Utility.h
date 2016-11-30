#pragma once

#include "StdAfx.h"

#include "Utility.h"

#include "ClusterPoint.h"
#include "ClusterCentroid.h"

namespace ImageProcessing
{
	class Utility
	{
	public:
		Utility() = delete;
		~Utility() = delete;

		/*
		@argument		'p_point' représente les valeurs RGB d'un point donné
		'p_centroid' ...

		@description	Cette fonction calcule la distace euclidienne entre un point de l'image
		et un centroid donné.
		*/
		static double_t EuclideanDistance(const ClusterPoint& p_point, const ClusterCentroid& p_centroid);

		static std::vector<std::string> Split(const std::string &p_str, char p_delimiter);
	};
}
