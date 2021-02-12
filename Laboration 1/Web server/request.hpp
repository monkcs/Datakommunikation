
#include <filesystem>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

/*
int main()
{
	try
	{
		const std::vector<Field> fields {Field {FieldName::Connection, "close"}};

		const auto header = Header {StatusLine {Protocol {Version::HTTP1}, Status {200}}, fields};

		std::cout << header;
	}
	catch (const std::runtime_error&)
	{
	}
}
*/

class Request
{
  protected:
	void parse(const std::string& request)
	{
		for (const auto word : "GET / HTTP/1.1" | std::ranges::views::split("\n\r"))
		{
			for (auto c : t)
			{
				std::cout << c;
			}
			std::cout << "\n";
		}
	};

	//	Method method;
	//	std::filesystem::path path;
	//	Protocol protocol;
	//	std::string host;
};