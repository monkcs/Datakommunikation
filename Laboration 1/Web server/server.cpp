#include "response.hpp"

#include <boost/asio.hpp>
#include <filesystem>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>
#include <fstream>

class Server
{
  public:
	Server() {};

	void run()
	{
		const auto fields = std::vector<Field> {Field {FieldName::Connection, "close"}};

		std::string path {};
		if (path == "valid")	// test case
		{
			const auto header = Header {StatusLine {Protocol {Version::HTTP1}, Status {200}}, fields};
			const auto response = Response {header, std::vector<char> {'h', 'e', 'j'}};
		}
		else
		{
			const auto header = Header {StatusLine {Protocol {Version::HTTP1}, Status {404}}, fields};
			const auto response = Response {header};
		}
	};

	//reading html file test
	void html_test(){
		std::cout << getHTML("website - Copy.html");
	};

	private:
		std::string getHTML(std::string filename){
			std::string text_line; //the current line read from the file
			std::string output = "";
			std::ifstream html_file(filename); 

			while(std::getline(html_file, text_line)){
				output += text_line + "\n"; //take the current line and appends it to the end of output getline removes the "\n" so I add it to the end of every line so the fromating of the text remains the same
			}
			return output;
		};
};

<<<<<<< Updated upstream
int main()
{
	Server t;
	t.run();
=======
int main() { 
	Server server{};
	server.html_test();
>>>>>>> Stashed changes
}