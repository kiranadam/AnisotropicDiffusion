/********************************************************************************************/
/* 		Anisometric Diffusion using Perona Malik Model Main file                    */
/*                             Coding : Kirankumar Adam                                     */
/********************************************************************************************/

#include "anisometric.hpp"

int main(int argc, char **argv) 
{
	Mat input = imread("taj-rgb-noise.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input",input);

	Mat out = input.clone();
	out.convertTo(out, CV_32FC1);

	PM_Diffusion pm(out);

	out = pm.diffusion();
	double min;
	double max;
	minMaxIdx(out, &min, &max);

	out.convertTo(out, CV_8UC1, 255 / (max - min), -min);
	imshow("Diffuesed Image", out);
	waitKey(0);

	return 0;
}
