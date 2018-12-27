#include <stdio.h>
#include "StringParser.h"
#include <stdio.h>
#include <string.h>
#include "Debug.h"
#include "StringParser.h"

#define INTEGER_LENGTH 20

StringParser::StringParser() : String() {
        current = 0;
        sptr = NULL;
}

StringParser::StringParser(char *str) : String(str) {
        current = 0;
        sptr = NULL;
}

StringParser::StringParser(String &str) : String(str) {
        current = 0;
        sptr = NULL;
}

StringParser::~StringParser() {
        if (sptr != NULL) {
                delete sptr;
                sptr = NULL;
        }
}

StringParser & StringParser::operator = (int n) {
        current = 0;
        char temp[INTEGER_LENGTH];
        sprintf(temp,"%d",n);
        String::assign(p,temp,String::length(temp));
        return *this;
}

StringParser & StringParser::operator = (char ch) {
        current = 0;
        String::assign(p,&ch,1);
        return *this;
}

StringParser & StringParser::operator = (const char *s) {
        current = 0;
        if (s == (char *) NULL)
                String::assign(p,"",0);
        else
                String::assign(p,s,String::length(s));
        return *this;
}

StringParser & StringParser::operator = (const String &str) {
        current = 0;
        String::assign(p,str.cptr(),str.length());
        return *this;
}


StringParser & StringParser::operator = (const StringParser &str) {
        current = 0;
        if (this==&str) return *this;
        String::assign(p,str.p.s,str.p.len);
        return *this;
}

StringParser & StringParser::operator += (int n) {
        char temp[INTEGER_LENGTH];
        sprintf(temp,"%d",n);
        String::append(p,temp,String::length(temp));
        return *this;
}

StringParser & StringParser::operator += (char ch) {
        String::append(p,&ch,1);
        return *this;
}

StringParser & StringParser::operator += (const char *s) {
        if (s == (char *) NULL)
                String::append(p,"",0);
        else
                String::append(p,s,String::length(s));
        return *this;
}

StringParser & StringParser::operator += (const String &str) {
        String::append(p,str.cptr(),str.length());
        return *this;
}


StringParser & StringParser::operator += (const StringParser &str) {
        String::append(p,str.p.s,str.p.len);
        return *this;
}


String & StringParser::getNextToken(String & delimiters, Boolean munchflag) {
        return getNextToken(delimiters.cptr(),munchflag);
}

String & StringParser::getNextToken(char* delimiters, Boolean munchFlag) {
        Enter("StringParser::getNextToken");
        int i, j, flag;
        int delimiters_len = strlen(delimiters);

        if (sptr != NULL) {
                delete sptr;
                sptr = NULL;
        }

        // Skip all delimiters starting at current
        for (i=current; i<length(); i++) {
                flag=0;
                for (j=0; j<delimiters_len; j++) {
                        if (p.s[i] == delimiters[j]) flag=1;
                }
                if (!flag)
                        break;
        }
        current = i;

        sptr = new String("");
        for (i=current; i<length(); i++) {
                flag=0;
                for (j=0; j<delimiters_len; j++) {
                        if (p.s[i] == delimiters[j]) flag=1;
                }
                if (flag)
                        break;
                *sptr += p.s[i];
        }
        current = i;

        // Skip all delimiters after token
        if (munchFlag) {
                for (i=current; i<length(); i++) {
                        flag=0;
                        for (j=0; j<delimiters_len; j++) {
                                if (p.s[i] == delimiters[j]) flag=1;
                        }
                        if (!flag) break;
                }
                current = i;
        }
        NLeave( *sptr );
}

String & StringParser::getNextToken(char *delimiters, char *subdelimiter, Boolean munchflag) {
        String temp(delimiters);
        String temp1(subdelimiter);
        return getNextToken(temp,temp1,munchflag);
}

String & StringParser::getNextToken(String& delimiter, String& subdelimiter, Boolean munchFlag) {
        Enter("StringParser::getNextSubToken");
        int i, j, flag;
        String temp, alldelimiter;

        if (sptr != NULL) {
                delete sptr;
                sptr = NULL;
        }

        // Skip all delimiter starting at current
        for (i=current; i<length(); i++) {
                flag=0;
                for (j=0; j<delimiter.length(); j++) {
                        if (p.s[i] == delimiter[j]) flag=1;
                }
                if (!flag) break;
        }
        current = i;

        flag = 0;
        for (i=0; i<subdelimiter.length(); i++) {
                if (p.s[current] == subdelimiter[i])
                        flag = 1; // 1st char is a subdelim
        }
        if (flag) {
                temp = p.s[current];   // Add beginning delimiter
                temp += getNextToken(subdelimiter);
                temp += p.s[current];  // Add the end delimiter to the token.
                *sptr = temp;
                if (current != length())
                        current++; // May add 1 to skip the found del
                }
                else {
                        alldelimiter = delimiter + subdelimiter;
                        temp  = getNextToken(alldelimiter);
                        *sptr = temp;
                }

                if (munchFlag) {
                        // Skip all delimiter after token
                        for (i=current; i<length(); i++) {
                                flag=0;
                                for (j=0; j<delimiter.length(); j++) {
                                        if (p.s[i] == delimiter[j])
                                                flag=1;
                                }
                                if (!flag)
                                        break;
                        }
                        current = i;
                }
        NLeave( *sptr );
}

String & StringParser::getNextTokenAfterDelimiter(String &delimiters) {
        return(getNextTokenAfterDelimiter(delimiters.cptr()));
}

String & StringParser::getNextTokenAfterDelimiter(char *delimiters) {
        Enter("StringParser::getNextTokenAfterDelimiter");
        int i, j, flag;
        int delimiters_len = strlen(delimiters);

        if (sptr != NULL) {
                delete sptr;
                sptr = NULL;
        }

        // Skip only the first delimiter starting at current
        flag=0;
        for (j=0; j<delimiters_len; j++) {
                if (p.s[current] == delimiters[j])
                        flag=1;
        }
        if (flag)
                current++;

        sptr = new String("");
        for (i=current; i<length(); i++) {
                flag=0;
                for (j=0; j<delimiters_len; j++) {
                        if (p.s[i] == delimiters[j])
                                flag=1;
                }
        if (flag)
                break;
                *sptr += p.s[i];
        }
        current = i;
        NLeave( *sptr );
}

void StringParser::scanForwardToChar(String& target) {
        scanForwardToChar(target.cptr());
}

void StringParser::scanForwardToChar(char * target) {
        Enter("StringParser::scanForwardToChar");
        int i, j, flag;
        int target_len = strlen(target);

        for (i=current; i<length(); i++) {
                flag=0;
                for (j=0; j<target_len; j++) {
                        if (p.s[i] == target[j])
                                flag=1;
                }
                if (flag)
                        break;
        }
        current = i;
        VLeave();
}

void StringParser::scanForwardToWord(char *target) {
        String temp(target);
        scanForwardToWord(temp);
}

void StringParser::scanForwardToWord(String &target) {
        Enter("StringParser::scanForwardToWord");
        int i, j;
        String temp;

        int offset_length = length() - target.length() + 1;

        // Could be much more efficient using strncmp
        for (i=current; i<offset_length; i++) {
                temp = "";
                for (j=0; j<target.length(); j++) {
                        temp += p.s[i+j];
                }
                if (temp == target)
                        break;
        }
        if (i < offset_length)
                current = i;
        else
                current = length();
}

String & StringParser::getRemainder() {
        Enter("StringParser::getRemainder");
        if (sptr != NULL) {
                delete sptr;
                sptr = NULL;
        }

        sptr = new String("");
        *sptr = cptr() + current;
        NLeave( *sptr );
}

String & StringParser::getRemainderFromChar(String &target) {
        return(getRemainderFromChar(target.cptr()));
}

String & StringParser::getRemainderFromChar(char *target) {
        Enter("StringParser::getRemainderFromChar");
        int i, j, flag;
        int target_len = strlen(target);

        if (sptr != NULL) {
                delete sptr;
                sptr = NULL;
        }

        sptr = new String("");
        for (i=0; i<length(); i++) {
                flag=0;
                for (j=0; j<target_len; j++) {
                        if (p.s[i] == target[j]) flag=1;
                }
                if (flag)
                        break;
                }
        *sptr = cptr() + i;
        NLeave( *sptr );
}

String & StringParser::getRemainderFromWord(char *target) {
        String temp(target);
        return getRemainderFromWord(temp);
}

String & StringParser::getRemainderFromWord(String &target) {
        Enter("StringParser::getRemainderFromWord");
        int i, j;
        String temp;

        if (sptr != NULL) {
                delete sptr;
                sptr = NULL;
        }

        int offset_length = length() - target.length() + 1;

        sptr = new String("");
        for (i=0; i<offset_length; i++) {
                temp = "";
                for (j=0; j<target.length(); j++) {
                        temp += p.s[i+j];
                }
                if (temp == target)
                        break;
        }
        if (i < offset_length)
                *sptr = cptr() + i;
        NLeave( *sptr );
}
