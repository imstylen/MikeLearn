#include "MikeLearn.h"
//#include <iostream>
//#include <Eigen/Dense>
//
//using namespace  Eigen;
//
//void test(std::vector<float> xArr)
//{
//	std::cout << xArr.size();
//	std::cout << std::endl;
//}
//
//void fit(std::vector<float> xArr, int nI)
//{
//	
//	int nRows = xArr.size()/nI;
//	
//	std::cout << nRows << std::endl;
//	std::cout << nI << std::endl;
//
//
//	try
//	{
//		auto m = Map<Matrix<float, Dynamic, Dynamic,RowMajor> >(xArr.data(),nRows,nI);
//		auto n = m * m.transpose();
//		std::cout << "Matrix m: \n";
//		std::cout << n << std::endl;
//	}
//	catch (std::exception& e)
//	{
//		std::cout << "Error!!! \n";
//		std::cout << e.what() << '\n';
//	}
//
//
//}
