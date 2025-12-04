#define echo.h

#include "./ModelReader.h"
#include <vector>


class Echo : public ModelCommand {
public:
	//Prints the arg to the output stream
	virtual void process(std::string arg);
protected:

private:
};