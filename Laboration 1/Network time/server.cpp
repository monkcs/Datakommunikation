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
		connection {connect()}, server {.sin_family {AF_INET}, .sin_port {htons(port)}, .sin_addr {.s_addr {INADDR_ANY}}}
	{
		if (bind(connection, &reinterpret_cast<sockaddr&>(server), sizeof(server)) < 0)
		{
			throw std::runtime_error {"Bind to port failed. Privileged access required"};
		}
	};

	~TimeProtocol()
	{
		close(connection);
	};

	void serve()
	{
		while (true)
		{
			socklen_t lenght = sizeof(server);

			if (recvfrom(connection, nullptr, 0, MSG_WAITALL, &reinterpret_cast<sockaddr&>(server), &lenght) < 0)
			{
				throw std::runtime_error {"Bind to socket failed"};
			}

			const std::array<uint8_t, 4> buffer {time()};
			sendto(connection, &buffer.front(), buffer.size(), MSG_CONFIRM, &reinterpret_cast<sockaddr&>(server), lenght);
		}
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

	std::array<uint8_t, 4> time() const
	{
		/* Add constant of seconds to make time start from year 1900 */
		const uint32_t time = std::time(nullptr) + 2208988800;

		return {static_cast<uint8_t>(time >> 24), static_cast<uint8_t>(time >> 16), static_cast<uint8_t>(time >> 8),
				static_cast<uint8_t>(time)};
	}
};

int main(const int count, char const* const arguments[])
{
	const uint16_t port = (count > 1) ? std::stoul(arguments[1]) : 37;

	TimeProtocol connection {port};
	connection.serve();
}
