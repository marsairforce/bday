/*+****************************************************************************

       Class: RStringParser

 Description: This class provides string parsing functionality.

              Any operations performed using the RString member
              functions that reduce the string length, may cause
              the parsing to start over at the beginning.

   Example:

      RString *prov = new RString(" A B C \" B \"\"A B C D E \" F G H");
      RStringParser *provparse = new RStringParser(*prov);
      RString ans;
      ans = provparse->getNextToken(" ","\"");
      while (ans != "") {
        cout << ans << "\n";
        ans = provparse->getNextToken(" ","\"");
      }
      cout << "\n";

   Output:

      ****************************************
      A
      B
      C
      " B "
      "A B C D E "
      F
      G
      H
      ****************************************

   Example:

      RString *tokens = new RString("PM A01 PE 1 PI 1");
      cout << *tokens << "\n";
      RStringParser *parse = new RStringParser(*tokens);
      RString aa;
      aa = parse->getNextToken(" \t");
      while (aa != "") {
        cout << aa << "\n";
        aa = parse->getNextToken(" \t");
      }
      aa = parse->getRemainderFromWord("PE");
      cout << aa << "\n";
      aa = parse->getRemainderFromChar("EA");
      cout << aa << "\n";

      parse->setToBeginning();
      aa = parse->getNextToken(" \t");
      cout << aa << "\n";
      aa = parse->getNextToken(" \t");
      cout << aa << "\n";
      parse->scanForwardToChar("EA");
      aa =  parse->getRemainder();
      cout << aa << "\n";
      parse->scanForwardToWord("PE");
      aa =  parse->getRemainder();
      cout << aa << "\n";
      cout << "End\n";

   Output:
      ****************************************
      PM A01 PE 1 PI 1
      PM
      A01
      PE
      1
      PI
      1
      PE 1 PI 1
      A01 PE 1 PI 1
      PM
      A01
      E 1 PI 1

      End
      ****************************************

****************************************************************************-*/
#ifndef STRINGPARSER_H
#define STRINGPARSER_H

// includes from this library package
#include "Types.h"
#include "String.h"


class StringParser : public String {
        String * sptr;
        int current;

public:
        StringParser();
        StringParser(char * str);
        StringParser(String & str);

        virtual ~StringParser();

        // assignment operators

        StringParser & operator = (int);
        StringParser & operator = (char);
        StringParser & operator = (const char *);
        StringParser & operator = (const String &);
        StringParser & operator = (const StringParser &);

        StringParser & operator += (int);
        StringParser & operator += (char);
        StringParser & operator += (const char *);
        StringParser & operator += (const String &);
        StringParser & operator += (const StringParser &);

        // functions to update the current pointer
        void setToBegnning() {current = 0; }
        void scanForwardToChar(char *);
        void scanForwardToChar(String &);

        void scanForwardToWord(char *);
        void scanForwardToWord(String &);

        String & getNextTokenAfterDelimiter(char * delimiter);
        String & getNextTokenAfterDelimiter(String & delimiter);

        String & getNextToken(char * delimiter, Boolean munchflag = False);
        String & getNextToken(String& delimiter, Boolean munchflag = False);

        String & getNextToken(char * delimiter, char* subdelimiter, Boolean munchflag = False);
        String & getNextToken(String & delimiter, String& subdelimiter, Boolean munchflag = False);

        // functions that do not update the current pointer
        String & getRemainder();
        String & getRemainderFromChar(char* target);
        String & getRemainderFromChar(String& target);

        String & getRemainderFromWord(char* target);
        String & getRemainderFromWord(String & target);
};

#endif