#include "response.hpp"

#include <boost/asio.hpp>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

class Server
{
  public:
	Server() {};

	void run()
	{
		const auto fields = std::vector<Field> {Field {FieldName::Connection, "close"}};

		std::string path {};
		if (path == "valid")	// test case
		{
			const auto header = Header {StatusLine {Protocol {Version::HTTP1}, Status {200}}, fields};
			const auto response = Response {header, std::vector<char> {'h', 'e', 'j'}};
		}
		else
		{
			const auto header = Header {StatusLine {Protocol {Version::HTTP1}, Status {404}}, fields};
			const auto response = Response {header};
		}
	};
};

int main() { }