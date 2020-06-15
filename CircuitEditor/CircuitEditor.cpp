#pragma warning(disable:4996)

#include"QbitWrapper.h"
//#include"GnuGraph.h"
#include<chrono>
#include <string>
#include"Frame.h"

//inline void pressEnter(void)
//{
//	cout << "Press ENTER to continue . . ." << '\n';
//	cin.get();
//}
//
//void test1()
//{
//	GnuGraph graph;
//	string output = graph.plot("1 1\n2 4\n3 9\n4 16\n5 25\n6 36\n7 49\n8 64\n9 81\n10 100\n");
//	cout << "Test1:\n" << output << '\n';
//	//pressEnter();
//}
//
//void test2()
//{
//	GnuGraph graph;
//
//	vector<double> x, y;
//	for (size_t i = 0; i < 200; ++i)
//	{
//		x.push_back(double(i));
//		y.push_back(sqrt(x[i]));
//	}
//
//	string output = graph.plot(x, y, "y = sqrt(x)");
//	//string output = graph.animate(x, y);
//	cout << "Test2:\n" << output << '\n';
//	//pressEnter();
//}

//void test3()
//{
//	GnuGraph graph;
//
//	vector<vector<double>> vec;
//	vec.push_back({ 1.0, 1.0, 1.0 });
//	vec.push_back({ 2.0, 2.0, 2.0 });
//	vec.push_back({ 3.0, 4.0, 4.0 });
//	vec.push_back({ 4.0, 8.0, 8.0 });
//	vec.push_back({ 5.0, 16.0, 16.0 });
//	vec.push_back({ 5.0, 32.0, 32.0 });
//	cout << "Test3:\n" << graph.plotLine3D(vec, "test3") << '\n';
//	pressEnter();
//}

//void test4()
//{
//	GnuGraph graph;
//
//	vector<double> x0, y0, x1, y1;
//	for (size_t i = 0; i < 200; ++i)
//	{
//		x0.push_back(double(i));
//		y0.push_back(sqrt(x0[i]));
//
//		x1.push_back(double(i));
//		y1.push_back(pow(x1[i], 1.0 / 3.0));
//	}
//
//	graph.addPlot(x0, y0, "y = sqrt(x)");
//	graph.addPlot(x1, y1, "y = x^(1/3)");
//	string output = graph.plot();
//	cout << "Test4:\n" << output << '\n';
//	//pressEnter();
//}

//void test5()
//{
//	GnuGraph graph;
//
//	vector<vector<double>> vec;
//	vec.push_back({ 1.0, 1.0, 1.0 });
//	vec.push_back({ 2.0, 2.0, 2.0 });
//	vec.push_back({ 3.0, 4.0, 4.0 });
//	vec.push_back({ 4.0, 8.0, 8.0 });
//	vec.push_back({ 5.0, 16.0, 16.0 });
//	vec.push_back({ 5.0, 32.0, 32.0 });
//
//	graph.addLine3D(vec, "test5");
//
//	const vector<double> start{ 1.0, 1.0, 1.0 };
//	const vector<double> direction{ 1.0, 0.0, 0.0 };
//
//	graph.addVector3D(start, direction);
//
//	cout << "Test5:\n" << graph.plot3D() << '\n';
//	pressEnter();
//}

//void test6()
//{
//	GnuGraph graph;
//
//	const size_t n = 200;
//	vector<vector<double>> vec(n);
//	for (size_t i = 0; i < n; ++i)
//	{
//		vec[i] = { cos(i / 20.0), sin(i / 30.0), cos(i / 50.0) };
//	}
//
//	graph.addLine3D(vec, "test6");
//	cout << graph.plot3D() << '\n';
//	pressEnter();
//}

//int main(int argc, char* argv[])
//{
//	test1();
//	test2();
//	//test3();
//	test4();
//	//test5();
//	//test6();
//
//	return 0;
//}

std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
void StartLog()
{
	std::cout << "CircuitEditor started" << std::endl;
	std::cout << "Default datatype: " << sizeof(_Type) << std::endl;
	std::cout << "MAX_BIT_SIZE: " << std::to_string(MAX_BIT_SIZE) << std::endl;
	std::cout << "THREADS_NUMBER: " << std::to_string(THREADS_NUMBER) << std::endl;
	std::cout << "USE_THREADS: " << (USE_THREADS ? "true" : "false") << std::endl;
	std::cout << "CIRCUIT_LOGS: " << (CIRCUIT_LOGS ? "true" : "false") << std::endl;
	std::cout << "CheckThreadDelay: " << CheckThreadDelay << std::endl;
	std::cout << "----------" << std::endl;
}

void EndLog()
{
	long long mills = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
	std::cout << "The circuit has been created in " << mills << "ms" << std::endl;
}

Circuit* InitQuantumRegister(unsigned int reg)
{
	std::cout << "Creating circuit of " << reg << " quantum registers...";
	Circuit* c = new Circuit(reg);
	std::cout << "Done" << std::endl;

	return c;
}

int main()
{
	StartLog();

	//Algorithm - the only editable part
	{
		Circuit* c = InitQuantumRegister(3);
		CX(c, 0, 1);
		H(c, 2);
		H(c, 1);
		Y(c, 1);
		
		//X(c, 1);
		//CX(c, 0, 1);
		//CX(c, 1, 2);
		//CX(c, 0, 2);
		//Swap(c, 1, 2);
		//
		//Optimize(c);
		
		Info(c, true, true);
	}

	EndLog();

	//Stop
	std::cout << "Press a key then ENTER to exit..." << std::endl;
	char a;
	std::cin >> a;

	return 0;
}