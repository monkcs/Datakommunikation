// Server-side Synchronous Chatting Application
// using C++ boost::asio

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

	// Reading username
	string u_name = getData(server_socket);
	// Removing "\n" from the username
	u_name.pop_back();

	// Replying with default mesage to initiate chat
	string response, reply;
	reply = "Hello " + u_name + "!";
	cout << "Server: " << reply << endl;
	sendData(server_socket, reply);

	while (true)
	{
		// Fetching response
		response = getData(server_socket);

		// Popping last character "\n"
		response.pop_back();

		// Validating if the connection has to be closed
		if (response == "exit")
		{
			cout << u_name << " left!" << endl;
			break;
		}
		cout << u_name << ": " << response << endl;

		// Reading new message from input stream
		cout << "Server"
			 << ": ";
		getline(cin, reply);
		sendData(server_socket, reply);

		if (reply == "exit")
			break;
	}
	return 0;
}
