/*
    Copyright (c) <year> <copyright holders>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef CMDPARSER_H
#define CMDPARSER_H

#include <string>
#include <iostream>
#include <vector>

#define OPTIONS_COUNT 2

enum commands { WIDTH, HEIGHT }; 

struct Token {
	std::string option;
	std::string value;
	int info;
};

class CmdParser
{
  public:
	CmdParser();
	CmdParser(std::string a_args);
	CmdParser(int a_argc, char *a_argv[]);
	~CmdParser(void);
	
  private:
	int GetId(std::string a_cmd);	// int or commands?
	int ParseTokens(std::vector< std::string > a_tokens);
	int InitializeOptions(void);
	int SetOption(int id, std::string a_setting);
	int ToggleOption(int id);
	
	 struct Token options[OPTIONS_COUNT];	// list of options

};

#endif // CMDPARSER_H


/*
This could be renamed to "Settings" or "Options"
- constructor would call InitializeOptions(), which would set default options
- Parse() (?) could take argc and argv, tokenize and call ParseTokens() which would change options
- SetScene() (?) takes a pointer to scene and sets scene's options

Parsing scene-files (somewhere in the future..) doesn't have to have anything to do with this.
This could just tell scene if it needs to parse some filename, given by this
*/