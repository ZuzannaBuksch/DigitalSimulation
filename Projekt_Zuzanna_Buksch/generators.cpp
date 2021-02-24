#include "generators.h"

#include <iostream>
#include <fstream>

Generators::Generators(int kernel) : kernel_(kernel)
{
}

Generators::~Generators()
{
}

double Generators::Rnd()
{
	int h = floor(kernel_ / kQ);
	kernel_ = kA * (kernel_ - kQ * h) - kR * h;
	if (kernel_ < 0)
		kernel_ = kernel_ + static_cast<int>(kM);
	return kernel_ / kM; 
}

int Generators::Rnd(double min, double max)
{
	return Rnd() * (max - min) + min;
}

int Generators::RndExp(double lambda)
{
	auto k = Rnd();

	return -(1.0/lambda)*log(k);
}

int Generators::RndZeroOne(double p)
{
	auto k = Rnd();

	std::ofstream save_generator_ter("GeneratorTer.txt", std::ios_base::app);
	save_generator_ter << "k = " + std::to_string(k) << std::endl;
	save_generator_ter.close();

	if (k < p)
		return 1;
	else
		return 0;

}

int Generators::GetKernel()
{
  return kernel_;
}
