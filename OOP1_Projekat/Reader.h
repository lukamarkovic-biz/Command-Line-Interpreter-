#define reader_h

#include <string>

class Reader {
public:
	//Gets a line from console of max 512 characters
	static std::string getLine();

	//Gets text from console until EOF
	std::string getText();
	
	//Clears fields of reader
	void clear();

protected:
private:

};