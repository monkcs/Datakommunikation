#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <iostream>
#include <string>

enum class Method
{
	Get,
	Head,
	Post,
	Put,
	Delete,
	Trace,
	Options,
	Connect,
	Patch
};

enum class Version
{
	/* HTTP/1.1 */
	HTTP1,

	/* HTTP/2 */
	HTTP2
};

class Protocol
{
  public:
	Protocol(const Version version = Version::HTTP1) : version {(version == Version::HTTP1) ? "HTTP/1.1" : "HTTP/2.0"} {};

	friend std::ostream& operator<<(std::ostream& stream, const Protocol& protocol)
	{
		stream << protocol.version;
		return stream;
	};

  protected:
	std::string version;
};

#endif