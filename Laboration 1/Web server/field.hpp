#ifndef FIELD_HPP
#define FIELD_HPP

#include <iostream>
#include <string>

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

#endif