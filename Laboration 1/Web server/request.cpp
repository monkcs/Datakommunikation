#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

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

class Status
{
  public:
	Status(const unsigned int code) : code {code}, response {parse(code)} {};

	constexpr auto operator==(const Status& other) const { return this->code == other.code; };
	constexpr auto operator!=(const Status& other) const { return !operator==(other); };

	friend std::ostream& operator<<(std::ostream& stream, const Status& status)
	{
		stream << status.response;
		return stream;
	};

  protected:
	unsigned int code;
	std::string response;

	static std::string parse(const unsigned int code)
	{
		switch (code)
		{
			case 100: return "100 Continue";
			case 101: return "101 Switching Protocols";
			case 102: return "102 Processing";
			case 103: return "103 Early Hints";

			case 200: return "200 OK";
			case 201: return "201 Created";
			case 202: return "202 Accepted";
			case 203: return "203 Non-Authoritative Information";
			case 204: return "204 No Content";
			case 205: return "205 Reset Content";
			case 206: return "206 Partial Content";
			case 207: return "207 Multi-Status";
			case 208: return "208 Already Reported";
			case 226: return "226 IM Used";

			case 300: return "300 Multiple Choices";
			case 301: return "301 Moved Permanently";
			case 302: return "302 Found";
			case 303: return "303 See Other";
			case 304: return "304 Not Modified";
			case 305: return "305 Use Proxy";
			case 306: return "306 Switch Proxy";
			case 307: return "307 Temporary Redirect";
			case 308: return "308 Permanent Redirect";

			case 400: return "400 Bad Request";
			case 401: return "401 Unauthorized";
			case 402: return "402 Payment Required";
			case 403: return "403 Forbidden";
			case 404: return "404 Not Found";
			case 405: return "405 Method Not Allowed";
			case 406: return "406 Not Acceptable";
			case 407: return "407 Proxy Authentication Required";
			case 408: return "408 Request Timeout";
			case 409: return "409 Conflict";
			case 410: return "410 Gone";
			case 411: return "411 Length Required";
			case 412: return "412 Precondition Failed";
			case 413: return "413 Payload Too Large";
			case 414: return "414 URI Too Long";
			case 415: return "415 Unsupported Media Type";
			case 416: return "416 Range Not Satisfiable";
			case 417: return "417 Expectation Failed";
			case 418: return "418 I'm a teapot";
			case 421: return "421 Misdirected Request ";
			case 422: return "422 Unprocessable Entity";
			case 423: return "423 Locked";
			case 424: return "424 Failed Dependency";
			case 425: return "425 Too Early";
			case 426: return "426 Upgrade Required";
			case 428: return "428 Precondition Required";
			case 429: return "429 Too Many Requests";
			case 431: return "431 Request Header Fields Too Large ";
			case 451: return "451 Unavailable For Legal Reasons ";

			case 500: return "500 Internal Server Error";
			case 501: return "501 Not Implemented";
			case 502: return "502 Bad Gateway";
			case 503: return "503 Service Unavailable";
			case 504: return "504 Gateway Timeout";
			case 505: return "505 HTTP Version Not Supported";
			case 506: return "506 Variant Also Negotiates";
			case 507: return "507 Insufficient Storage";
			case 508: return "508 Loop Detected";
			case 510: return "510 Not Extended";
			case 511: return "511 Network Authentication Required";

			default: throw std::invalid_argument {"Invalid HTTP status code: " + std::to_string(code)};
		}
	}
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

class StatusLine
{
  public:
	StatusLine(const Protocol protocol, const Status status) : protocol {protocol}, status {status} {};

	friend std::ostream& operator<<(std::ostream& stream, const StatusLine& statusline)
	{
		stream << statusline.protocol << ' ' << statusline.status << "\r\n";
		return stream;
	};

  protected:
	Protocol protocol;
	Status status;
};

enum class FieldName
{
	AccessControlAllowOrigin,
	AccessControlAllowCredentials,
	AccessControlExposeHeaders,
	AccessControlMaxAge,
	AccessControlAllowMethods,
	AccessControlAllowHeaders,
	AcceptPatch,
	AcceptRanges,
	Age,
	Allow,
	AltSvc,
	CacheControl,
	Connection,
	ContentDisposition,
	ContentEncoding,
	ContentLanguage,
	ContentLength,
	ContentLocation,
	ContentMD5,
	ContentRange,
	ContentType,
	Date,
	DeltaBase,
	ETag,
	Expires,
	IM,
	LastModified,
	Link,
	Location,
	P3P,
	Pragma,
	ProxyAuthenticate,
	PublicKeyPins,
	RetryAfter,
	Server,
	SetCookie,
	StrictTransportSecurity,
	Trailer,
	TransferEncoding,
	Tk,
	Upgrade,
	Vary,
	Via,
	Warning,
	WWWAuthenticate,
	XFrameOptions
};

class Field
{
  public:
	Field(const FieldName name, const std::string value) : name {parse(name)}, value {value} {};

	friend std::ostream& operator<<(std::ostream& stream, const Field& field)
	{
		stream << field.name << ": " << field.value << "\r\n";
		return stream;
	};

  protected:
	std::string name;
	std::string value;

	static std::string parse(const FieldName name)
	{
		switch (name)
		{
			case FieldName::AccessControlAllowOrigin: return "Access-Control-Allow-Origin";
			case FieldName::AccessControlAllowCredentials: return "Access-Control-Allow-Credentials";
			case FieldName::AccessControlExposeHeaders: return "Access-Control-Expose-Headers";
			case FieldName::AccessControlMaxAge: return "Access-Control-Max-Age";
			case FieldName::AccessControlAllowMethods: return "Access-Control-Allow-Methods";
			case FieldName::AccessControlAllowHeaders: return "Access-Control-Allow-Headers";
			case FieldName::AcceptPatch: return "Accept-Patch";
			case FieldName::AcceptRanges: return "Accept-Ranges";
			case FieldName::Age: return "Age";
			case FieldName::Allow: return "Allow";
			case FieldName::AltSvc: return "Alt-Svc";
			case FieldName::CacheControl: return "Cache-Control";
			case FieldName::Connection: return "Connection";
			case FieldName::ContentDisposition: return "Content-Disposition";
			case FieldName::ContentEncoding: return "Content-Encoding";
			case FieldName::ContentLanguage: return "Content-Language";
			case FieldName::ContentLength: return "Content-Length";
			case FieldName::ContentLocation: return "Content-Location";
			case FieldName::ContentMD5: return "Content-MD5";
			case FieldName::ContentRange: return "Content-Range";
			case FieldName::ContentType: return "Content-Type";
			case FieldName::Date: return "Date";
			case FieldName::DeltaBase: return "Delta-Base";
			case FieldName::ETag: return "ETag";
			case FieldName::Expires: return "Expires";
			case FieldName::IM: return "IM";
			case FieldName::LastModified: return "Last-Modified";
			case FieldName::Link: return "Link";
			case FieldName::Location: return "Location";
			case FieldName::P3P: return "P3P";
			case FieldName::Pragma: return "Pragma";
			case FieldName::ProxyAuthenticate: return "Proxy-Authenticate";
			case FieldName::PublicKeyPins: return "Public-Key-Pins";
			case FieldName::RetryAfter: return "Retry-After";
			case FieldName::Server: return "Server";
			case FieldName::SetCookie: return "Set-Cookie";
			case FieldName::StrictTransportSecurity: return "Strict-Transport-Security";
			case FieldName::Trailer: return "Trailer";
			case FieldName::TransferEncoding: return "Transfer-Encoding";
			case FieldName::Tk: return "Tk";
			case FieldName::Upgrade: return "Upgrade";
			case FieldName::Vary: return "Vary";
			case FieldName::Via: return "Via";
			case FieldName::Warning: return "Warning";
			case FieldName::WWWAuthenticate: return "WWW-Authenticate";
			case FieldName::XFrameOptions: return "X-Frame-Options";

			default: throw std::invalid_argument {"Invalid HTTP Header field-name: " + std::to_string(static_cast<int>(name))};
		}
	}
};

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
	Response(const Header header) : header {header} {};

	friend std::ostream& operator<<(std::ostream& stream, const Response& response)
	{
		stream << response.header;
		stream << "\r\n\r\n";

		return stream;
	};

  protected:
	Header header;
};

int main()
{
	try
	{
		const std::vector<Field> fields {Field {FieldName::Connection, "close"}};

		const auto header = Header {StatusLine {Protocol {Version::HTTP1}, Status {404}}, fields};

		std::cout << header;
	}
	catch (const std::runtime_error&)
	{
	}
}

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