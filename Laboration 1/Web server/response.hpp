#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "field.hpp"
#include "status.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

class Header
{
  public:
	Header(const StatusLine status, const std::vector<Field> fields) : status {status}, fields {fields} {};

	friend std::ostream& operator<<(std::ostream& stream, const Header& header)
	{
		stream << header.status;

		for (const auto& field : header.fields)
		{
			stream << field;
		}

		stream << "\r\n";

		return stream;
	};

  protected:
	StatusLine status;
	std::vector<Field> fields;
};

class Response
{
  public:
	Response(const Header header, const std::vector<char> body = {}) : header {header}, body {body} {};

	friend std::ostream& operator<<(std::ostream& stream, const Response& response)
	{
		stream << response.header;

		for (const auto character : response.body)
		{
			stream << character;
		}

		return stream;
	};

  protected:
	Header header;
	std::vector<char> body;
};

#endif