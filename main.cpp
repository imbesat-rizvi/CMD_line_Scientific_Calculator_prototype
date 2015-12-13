#include "Calculator.h"

using namespace std;

void print_complex(complex<long double>);

int main(int argc, char **argv)
{
	Calculator Calc;
	complex<long double> calculated_result;

	if(argc !=2)
		printf("Please provide only one command line argument.\n");

	calculated_result = Calc.calculate(argv[1]);
	print_complex(calculated_result);
	return 0;
}

void print_complex(complex<long double> z)
{
	char sign;
	long double tol = 1e-15;

	if(fabsl(z.imag()) < tol)
			z = complex<long double>(z.real(),0);

	if(!z.imag())
		printf("%Lf\n",z.real());
	else if(!z.real())
	{
		if(z.imag() < 0)
		{	
			sign = '-';
			printf("%ci%Lf\n",sign,fabsl(z.imag()));
		}
		else
			printf("i%Lf\n",z.imag());
	}
	else
	{
		if(z.imag() < 0)
		{
			sign = '-';
			printf("%Lf %c i%Lf\n",z.real(),sign,fabsl(z.imag()));
		}
		else
			printf("%Lf + i%Lf\n",z.real(),fabsl(z.imag()));
	}
	return;
}
