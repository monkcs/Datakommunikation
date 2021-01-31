#include <array>
#include <chrono>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <vector>

class TimeProtocol
{
  public:
	TimeProtocol(const std::uint16_t port = 37) :
		connection {connect()}, server {.sin_family {AF_INET}, .sin_port {htons(port)}, .sin_addr {.s_addr {INADDR_ANY}}} {};

	~TimeProtocol()
	{
		close(connection);
	};

	auto time()
	{
		transmit();

		std::array<uint8_t, 4> buffer {};
		socklen_t lenght = sizeof(server);

		recvfrom(connection, &buffer.front(), buffer.size(), MSG_WAITALL, &reinterpret_cast<sockaddr&>(server), &lenght);

		const auto raw = static_cast<uint32_t>(buffer[0] << 24 | (buffer[1] << 16) | (buffer[2] << 8) | (buffer[3]));

		/* Subtract constant of seconds to make time start from year 1900 */
		return static_cast<std::time_t>(raw - 2208988800);
	}

  protected:
	int connection;
	sockaddr_in server;

	int connect() const
	{
		if (const auto connection = socket(AF_INET, SOCK_DGRAM, 0); connection >= 0)
		{
			return connection;
		}
		else
		{
			throw std::runtime_error {"Socket creation failed"};
		}
	}

	/* Transmit empty UDP datagram to wake server */
	void transmit() const
	{
		if (sendto(connection, nullptr, 0, MSG_CONFIRM, &reinterpret_cast<const sockaddr&>(server), sizeof(server)) != 0)
		{
			throw std::runtime_error {"Error sending request to server"};
		}
	}
};

int main(const int count, char const* const arguments[])
{
	const uint16_t port = (count > 1) ? std::stoul(arguments[1]) : 37;

	TimeProtocol connection {port};

	const auto time = connection.time();
	std::cout << std::asctime(std::localtime(&time));
}
