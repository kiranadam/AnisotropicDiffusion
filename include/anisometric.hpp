/********************************************************************************************/
/* 		Anisometric Diffusion using Perona Malik Model Header file                  */
/*                                Coding : Kirankumar Adam                                  */
/********************************************************************************************/

#ifndef anisometric_HPP
#define anisometric_HPP

#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class PM_Diffusion
{
	private:
		int iterations; 	// Number of iterations
		double kappa;  		// Kappa as per paper
		double delta_t;		// delta_t as per paper
		Mat src;                // src image
		
		Mat flux(Mat &kernel);
	
	public:
		PM_Diffusion(Mat &src);
		PM_Diffusion(int iterations, double kappa, double delta_t, Mat &src);
		Mat diffusion();
};

#endif
