// Server-side Synchronous Chatting Application
// using C++ boost::asio

#include "response.hpp"

#include <boost/asio.hpp>
#include <iostream>
using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

// Driver program for receiving data from buffer
string getData(tcp::socket& socket)
{
	boost::asio::streambuf buf;
	boost::asio::read_until(socket, buf, "\n");
	string data = buffer_cast<const char*>(buf.data());
	return data;
}

// Driver program to send data
void sendData(tcp::socket& socket, const string& message) { write(socket, buffer(message + "\n")); }

int main(int argc, char* argv[])
{
	io_service io_service;

	// Listening for any new incomming connection
	// at port 9999 with IPv4 protocol
	tcp::acceptor acceptor_server(io_service, tcp::endpoint(tcp::v4(), 9999));

	// Creating socket object
	tcp::socket server_socket(io_service);

	// waiting for connection
	acceptor_server.accept(server_socket);

	// Replying with default mesage to initiate chat
	string response, reply;

	while (true)
	{
		response = getData(server_socket);

		const auto fields = std::vector<Field> {Field {FieldName::Connection, "close"}};
		const auto header = Header {StatusLine {Protocol {Version::HTTP1}, Status {200}}, fields};
		const auto response = Response {header, std::vector<char> {'h', 'e', 'j'}};

		std::ostringstream stream;
		stream << response;
		reply = stream.str();	 //"HTTP/1.1 200 OK\r\nConnection: close\r\n\r\nhello\r\n\r\n";
		sendData(server_socket, reply);
		continue;
		// Fetching response
	}
	return 0;
}
