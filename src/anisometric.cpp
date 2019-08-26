/********************************************************************************************/
/* 		Anisometric Diffusion using Perona Malik Model CPP file                     */
/*                                Coding : Kirankumar Adam                                  */
/********************************************************************************************/

#include "anisometric.hpp"

PM_Diffusion::PM_Diffusion(Mat &src)
{
	iterations = 15;
	kappa = 30;
	delta_t = 0.25;
	this->src = src;

}

PM_Diffusion::PM_Diffusion(int iterations, double kappa, double delta_t, Mat &src)
{
	this->iterations = iterations;
	this->kappa = kappa;
	this->delta_t = delta_t;
	this->src = src;
}


Mat PM_Diffusion::flux(Mat& kernel)
{
	Mat nabla;
	filter2D(src, nabla, -1, kernel);
	
	Mat c = nabla/kappa;
	c = c.mul(c);
	c = 1.0/(1.0 + c);

	//c = c.mul(nabla);

	return c;
}



Mat PM_Diffusion::diffusion()
{
	double d = 1; // difference to adjacent pixel
	double dd = sqrt(2); // difference to diagonal pixel
	
	for (int i = 0; i < iterations; i++) 
	{
		// Calculate flux for east side
		Mat kernel = (Mat_<double>(3,3)<<0,0,0,1,-1,0,0,0,0);
		Mat phi_e = flux(kernel) * (1.0/(d*d));
		
		// Calculate flux for west side
		kernel = (Mat_<double>(3,3)<<0,0,0,0,-1,1,0,0,0);
		Mat phi_w = flux(kernel)*(1.0/(d*d));

		// Calculate flux for north side
		kernel = (Mat_<double>(3,3)<<0,1,0,0,-1,0,0,0,0);
		Mat phi_n = flux(kernel)*(1.0/(d*d));
		
		// Calculate flux for south side
		kernel = (Mat_<double>(3,3)<<0,0,0,0,-1,0,0,1,0);
		Mat phi_s = flux(kernel)*(1.0/(d*d));
		
		// Calculate flux for north east side
		kernel = (Mat_<double>(3,3)<<0,0,1,0,-1,0,0,0,0);
		Mat phi_ne = flux(kernel)*(1.0/(dd*dd));

		// Calculate flux for north west side
		kernel = (Mat_<double>(3,3)<<1,0,0,0,-1,0,0,0,0);
		Mat phi_nw = flux(kernel)*(1.0/(dd*dd));
		
		// Calculate flux for south east side
		kernel = (Mat_<double>(3,3)<<0,0,0,0,-1,0,1,0,0);
		Mat phi_se = flux(kernel)*(1.0/(dd*dd));
		
		// Calculate flux for south west side
		kernel = (Mat_<double>(3,3)<<0,0,0,0,-1,0,0,0,1);
		Mat phi_sw = flux(kernel)*(1.0/(dd*dd));

	
		// Calculating diffused image
		src = src + delta_t * (phi_e + phi_w + phi_n + phi_s + phi_ne + phi_nw + phi_se + phi_sw);
	}

	return src;
}

