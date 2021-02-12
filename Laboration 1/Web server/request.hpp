#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "protocol.hpp"

#include <algorithm>
#include <filesystem>
#include <ranges>
#include <string>
#include <vector>

class Request
{
  public:
	Request(const std::string request) { parse(request); };

	Method method;
	std::string path;
	Protocol protocol;

  protected:
	void parse(std::string request)
	{
		request.erase(std::remove(request.begin(), request.end(), '\r'), request.end());

		std::vector<std::string> properties {};

		for (auto line : (request | std::ranges::views::split('\n')))
		{
			for (auto word : (line | std::ranges::views::split(' ')))
			{
				std::string command {};
				for (auto character : word)
				{
					command += character;
				}
				properties.emplace_back(command);
			}

			/* Break after first line */
			break;
		}

		if (properties.at(0) == "GET")
		{
			method = Method::Get;
		}
		else
		{
			throw std::runtime_error {"Unsupported request method"};
		}

		if (properties.at(1) == "/")
		{
			path = "index.html";
		}
		else
		{
			path = properties.at(1);
			path.erase(std::remove(path.begin(), path.end(), '/'), path.end());
		}

		if (!std::filesystem::exists(path))
		{
			throw std::runtime_error {"Invalid file path"};
		}

		if (properties.at(2) == "HTTP/1.1")
		{
			protocol = Protocol {Version::HTTP1};
		}
		else
		{
			throw std::runtime_error {"Unsupported http version"};
		}
	};
};

#endif