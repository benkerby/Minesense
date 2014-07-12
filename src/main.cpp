#include <vector>
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
	std::vector< std::string > arguments(argv, argv + argc);
	for (const auto& arg : arguments)
	{
		std::cout << arg << std::endl;
	}
	std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}
