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

#include "CmdParser.h"

CmdParser::CmdParser() // empty constructor
{
// 	 InitializeOptions(); // this is how every constructor should begin
}

CmdParser::CmdParser(int a_argc, char* a_argv[]) //constructor, commnads given as main() gets them
{
	 InitializeOptions(); // this is how every constructor should begin
	 
	 // for each token in argv, we put it into a string-vector
	 // then give the vector to ParseTokens()

	
	std::vector<std::string> list;
	for (int i = 1; i < a_argc; ++i)	// put all given tokens from char-list to vector ( would list or something be better?)
	{					// skip index i=0, the programs name
		 list.push_back(a_argv[i]);
	}
	
	ParseTokens(list);
}

CmdParser::CmdParser(std::string a_args) //constructor, commands given as a string
{
// 	 InitializeOptions(); // this is how every constructor should begin
// 	 FIXME: like above, tokenize a_args into a string-vector

	 // for each token in argv, we put it into a string-vector
	 // then give the vector to ParseTokens()

	
// 	std::vector<std::string> list;
// 	for (int i = 1; i < a_argc; ++i)	// put all given tokens from char-list to vector ( would list or something be better?)
// 	{					// skip index i=0, the programs name
// 		 list.push_back(a_argv[i]);
// 	}
// 	
// 	ParseTokens(list);

}

int CmdParser::InitializeOptions(void )
{					// initializes the list of known options
			    // options[] is type "struct Token", and private member
			    // info: 
			    // 		0: standalone
			    //		1: needs one more token

	std::cout << "int CmdParser::InitializeOptions() begins" << std::endl;

	 options[0].option = "--width";
	 options[0].info = 1;
	 options[1].option = "--height";
	 options[1].info = 1;
}


int CmdParser::ParseTokens(std::vector< std::string > a_tokens)
{
	std::cout << "int CmdParser::ParseTokens() begins" << std::endl;
	// for all tokens in a_tokens check if it matches with our options, using GetId ( -1 == doesn't match)
	// if it matches and the option in question needs additional info, we check if next token is what it wants
	// if it is, we give those to another funktion to be evaluated
	// if it doesn't, we discard the first command 
	// then we do this all again for next tokens

	int id;
	std::string token;
	for (unsigned int i = 0; i < a_tokens.size(); ++i)
	{
		token = a_tokens[i];
		std::cout << "Token " << i << std::endl;
		if ((id = GetId(token)) != -1)
		{
			if (options[id].info == 1 && i+1 < a_tokens.size()) // two-part command, needs two tokens (like --width 700)
			{
				SetOption(id,a_tokens[++i]); // FIXME: this doesn't check for next token's validity before moving on
			}
			else if (options[id].info == 0) // one-part command, (like --help)
			{
				ToggleOption(id);
			}
		}
		else		// if token didn't match database, tell it to customer and continue
		{
		  std::cout << "Given command was not recognised: " << token << std::endl;
		}
	}
}

int CmdParser::SetOption(int id, std::string a_setting)
{	
	// FIXME: sanity check?
	options[id].value = a_setting;
}

int CmdParser::ToggleOption(int id)
{
 // FIXME: make this do something
}


int CmdParser::GetId(std::string a_cmd)
{			// we check the given command against our list of options, and return enumerated id if we get a match

	 
	 for (int i = 0; i < OPTIONS_COUNT; ++i)
	 {
	   if (a_cmd == options[i].option)
	     return i;			// this doesn't actually do anything with the enumerate-thing
					// is it bad? not sure. enumerate might help some things, but it would need more code
	 }
	 return -1;			// invalid cmd, returns 
	 
}

CmdParser::~CmdParser(void ) // this is a stupid destructor
{			     // it doesn't destrcut anything, but prints some info
  std::cout << "CmdParser quitting. Parsed today:" << std::endl;
  
  for (int i = 0; i < OPTIONS_COUNT; ++i)
	  std::cout << options[i].option << " : " << options[i].value << std::endl;

}
