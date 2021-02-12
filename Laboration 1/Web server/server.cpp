#include "request.hpp"
#include "response.hpp"

#include <boost/asio.hpp>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

class Server
{
  public:
	Server(const uint16_t port) : port {port} {};

	void run() const
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::acceptor acceptor_server(io_service,
													   boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));

		while (true)
		{
			boost::asio::ip::tcp::socket server_socket(io_service);

			// waiting for connection
			acceptor_server.accept(server_socket);

			try
			{
				const Request request {receive(server_socket)};

				send(server_socket, handle(request));
			}
			catch (const std::runtime_error&)
			{
				send(server_socket, error());
			}

			server_socket.close();
		}
	}

	std::string handle(const Request request) const
	{
		const auto fields = std::vector<Field> {Field {FieldName::Connection, "close"}};

		const auto header = Header {StatusLine {Protocol {Version::HTTP1}, Status {200}}, fields};
		const auto response = Response {header, getFile(request.path)};

		std::ostringstream stream;
		stream << response;
		return stream.str();
	};

	std::string error() const
	{
		const auto fields = std::vector<Field> {Field {FieldName::Connection, "close"}};

		const auto header = Header {StatusLine {Protocol {Version::HTTP1}, Status {404}}, fields};
		const auto response = Response {header, Status {404}};

		std::ostringstream stream;
		stream << response;
		return stream.str();
	}

	std::string getFile(std::string filename) const
	{
		std::string text_line;	  // the current line read from the file
		std::string output = "";
		std::ifstream html_file(filename);

		while (std::getline(html_file, text_line))
		{
			output += text_line + "\n";	   // take the current line and appends it to the end of output getline removes the "\n"
										   // so I add it to the end of every line so the fromating of the text remains the same
		}

		return output;
	};

  protected:
	uint16_t port;

	std::string receive(boost::asio::ip::tcp::socket& socket) const
	{
		boost::asio::streambuf buffert;
		boost::asio::read_until(socket, buffert, "\n");
		return boost::asio::buffer_cast<const char*>(buffert.data());
	}

	void send(boost::asio::ip::tcp::socket& socket, const std::string& message) const
	{
		write(socket, boost::asio::buffer(message));
	}
};

int main(const int count, char const* const arguments[])
{
	const uint16_t port = (count > 1) ? std::stoul(arguments[1]) : 80;

	Server server {port};
	server.run();
}