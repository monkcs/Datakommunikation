#include <boost/asio.hpp>
#include <filesystem>
#include <iostream>
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

/*

class Request
{
  protected:
	void parse(const std::string& request);

	Method method;
	std::filesystem::path path;
	Protocol protocol;
	std::string host;
};*/