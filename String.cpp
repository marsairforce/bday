
#include "String.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <memory.h>


#define INTEGER_LENGTH 20

// Constructors
String::String() : p(String::alloc("",0,0)) {
}


String::String(int n) : p(String::alloc("",0)) {
        char temp[INTEGER_LENGTH];

        sprintf(temp, "%d", n);
        String::assign(p,temp,String::length(temp));
}

String::String(char ch) : p(String::alloc(&ch,1)) {
}

String::String(const char *str) : p(String::alloc(str ? str : "", str ? strlen(str) : 0)) {
}

String::String(const char *str, int n) : p(String::alloc(str ? str : "", str ? n : 0)) {
}

String::String(const String &st) : p(String::alloc(st.p.s,st.p.len,st.p.size)) {
}

// destructor
String::~String() {
        delete p.s;
}

// search function
int String::search(const char * source, int slen, const char *s_str, int sslen) {
  if (sslen==0 && slen!=0) return -1;
   if (sslen==1) {
    const char *loc=source; char search_ch = *s_str;
        while (slen--)
             if ( *loc == search_ch) return loc-source;
             else loc++;
        return -1;
   }

  const char *stop_index=source+(slen-sslen+1); // give up if not found yet
  const char *curr_index=source;            // starting point

  if (stop_index> curr_index) while(curr_index != stop_index) {
     register const char *sp=curr_index;
     register const char *ssp=s_str;
     register const char *ss_end=ssp+sslen;
     while ((ssp != ss_end) && (*sp++ == *ssp++)) ;   // spin over string
     if (*(sp-1)==*(ssp-1)) return curr_index-source; // check for equal
     else ++curr_index;
  }
  return -1;    // not found

}

// compare function
int String::compare(const char *s1, int s1_len, const char *s2,int s2_len) {
        int diff;
        diff=strncmp(s1,s2,s1_len);

        if (diff !=0 || s1_len==s2_len)
                return diff;
        else
                return (s1_len > s2_len) ? 1 : -1;
}

// copy assignment
String & String::operator = (int n) {
        char temp[INTEGER_LENGTH];
        sprintf(temp,"%d",n);
        String::assign(p,temp,String::length(temp));
        return Str();
}

String & String::operator = (char ch) {
        String::assign(p,&ch,1);
        return Str();
}

String & String::operator = (const char *s) {
        if (s == (char *) NULL) String::assign(p,"",0);
        else String::assign(p,s,String::length(s));
        return Str();
}

String & String::operator = (const String &str) {
        if (this==&str) return Str();
        String::assign(p, str.p.s, str.p.len);
        return Str();
}

// append assignment

String & String::operator += (int n) {
        char temp[INTEGER_LENGTH];
        sprintf(temp,"%d",n);
        String::append(p,temp,String::length(temp));
        return Str();
}

String & String::operator += (char ch) {
        String::append(p,&ch,1);
        return Str();
}

String & String::operator += (const char *s) {
        if (s == (char *) NULL)
                String::append(p,"",0);
        else
                String::append(p,s,String::length(s));
        return Str();
}

String & String::operator += (const String &s) {
        String::append(p, s.p.s, s.p.len);
        return Str();
}

// function to concatenate two string types (used by + operator)
void String::concat(StringData &p, const char *s1, int l1, const char *s2, int l2) {
        memcpy(p.s,s1,l1);
        memcpy(p.s+l1,s2,l2);
        p.len=l1+l2;
        p.s[p.len]='\0';
}

// + operator returns a new string that is the concatenation of two values
// (uses inline concat fnction)

String String::operator + (int n) const {
        char s[INTEGER_LENGTH];
        sprintf(s, "%d", n);
        int slen = String::length(s);
        String temp;
        temp.add(int(length()+slen));
        String::concat(temp.p,cptr(),length(),s,slen);
        return temp;
}

String String::operator + (char ch) const {
        String temp;
        temp.add(int(length()+1));
        String::concat(temp.p,cptr(),length(),&ch,1);
        return temp;
}

String String::operator + (const char *s) const {
        int slen;
        String temp;
        if (s == (char *) NULL) {
                temp.add(int(length()+0));
                String::concat(temp.p,cptr(),length(),"",0);
        }
        else {
                slen = String::length(s);
                temp.add(int(length()+slen));
                String::concat(temp.p,cptr(),length(),s,slen);
        }
        return temp;
}

String String::operator + (const String &s) const {
        String temp;
        temp.add(int(length()+s.length()));
        String::concat(temp.p,cptr(),length(),s.cptr(),s.length());
        return temp;
}

// + operator requires the following friend functions

String operator + (int n, String & s1) {
        char s[INTEGER_LENGTH];
        sprintf(s, "%d", n);
        int slen = strlen(s);
        String temp;
        temp.add(slen+s1.length());
        String::concat(temp.p, s, slen, s1.cptr(), s1.length());
        return temp;
}

String operator + (char ch, const String & s1) {
        String temp;
        temp.add(1+s1.length());
        String::concat(temp.p,&ch,1,s1.cptr(),s1.length());
        return temp;
}

String operator + (const char *s, const String &s1) {
        int slen;
        String temp;

        if (s == (char*) NULL) {
                temp.add(0+s1.length());
                String::concat(temp.p, "", 0, s1.cptr(), s1.length());
        }
        else {
                slen = strlen(s);
                temp.add(slen+s1.length());
                String::concat(temp.p, s, slen, s1.cptr(), s1.length());
        }
        return temp;
}

/*
String operator + (const String &s1, const String &s2) {
        String temp;
        temp.add(int(s1.length()+s2.length()));
        String::concat(temp.p,s1.cptr(),s1.length(),s2.cptr(),s2.length());
}
*/
// returns the character in the string indexed by 'i'
char & String::operator [] (int i) {
        if (i < 0 || p.len < i)
                exception("Index out of bounds");
        return p.s[i];
}

// output a string usign ostream
std::ostream & operator << (std::ostream & os, const String &s) {
        os.write(s.cptr(), s.length());
        return os;
}

// input a string (skip white space)
std::istream & operator >> (std::istream &is, String &s) {
        int ch;
        s="";

        while ( ((ch = is.get()) != EOF) && (isspace(ch))) ; // spin
        if (ch != EOF) {
                s += char(ch);
                while( ((ch = is.get()) != EOF) && (!isspace(ch)))
                        s += char(ch);
        }
        return is;
}

// input a string (keep white space)
int getLine(std::istream &is, String &s, char delim, int dropit) {
        int ch;
        // should check for errors on instream here

        s="";

        while ( ((ch = is.get()) != EOF) && (ch != delim))
                s+=char(ch);
        if (ch == delim && !dropit)
                s += delim;
        if (is.eof())
                return -1;
        return s.length();
}

// add to length allocated to a string
String & String::add(int len) {
        if (len >= 0) {
                int newSize = p.len + len;
                if (newSize >= p.size) String::resize(p,newSize);
        }
        return Str();
}

//match and compare functions

int String::match(void * str, int type) {
        if (type==STRING_MATCH_BY_STRING && !strcmp(p.s, ((String*)str)->cptr()) )
                return 1;
        else if (type == STRING_MATCH_BY_CHAR && !strcmp(p.s, (char*)str) )
                return 1;
        return 0;
}

int String::compare(void * obj, int ) {
        String *nc = (String*) obj;
        return strcmp(p.s, nc->cptr() );
}

// String operations

// removes leading and following space characters from a string
void String::trimWhiteSpace() {
        int i = 0;
        for (i=0; i < p.len; i++) {     // skip leading spaces
                if (!isspace(p.s[i])) break;
        }
        int k = 0;
        for (; i < p.len; i++) {        // move stuff in string to front of string
                p.s[i] = p.s[i];
                k++;
        }
        for (i=k-1; i>0; i--) {           // remove spaces following string too
                if (!isspace(p.s[i])) break;
        }
        p.len = i+1;                    // adjust new length of string
        p.s[p.len]='\0';                // tack on the null
}

void String::upperCase() {
        char* temp = p.s;
        for (int i = 0; i < p.len; i++) {
                if (islower(*temp) ) *temp = toupper(*temp);
                temp++;
        }
}

void String::lowerCase() {
        char* temp = p.s;
        for (int i = 0; i < p.len; i++) {
                if (isupper(*temp) ) *temp = tolower( *temp);
                temp++;
        }
}


// change the length of the string by index offset
// (actually truncates the string)
int String::setLength(int n) {
        if (n < p.size) {
                p.len=n;
                p.s[p.len]='\0';
        }
        return p.len;
}

// calculates the size of a new request
// should be passed the size of string to be allocated, not including the NULL
inline int hunk_size(int n) {
        n++; // add one for null character
        return (n/STRING_HUNKSIZE)*STRING_HUNKSIZE+STRING_HUNKSIZE;
}

// allocate space for string
StringData String::alloc(const char *data, int len, int size) {
        StringData temp;

        temp.size = (size== -1) ? hunk_size(len) : hunk_size(size);
        temp.len = len;
        temp.s = new char[temp.size];
        if (temp.s != NULL) {
                if (len) memcpy(temp.s,data,len);
                temp.s[len]='\0';
        }
        return temp;

}

// resize the string
void String::resize(StringData &sd, int newSize) {
        if (newSize >= sd.size) {
                StringData temp = String::alloc(sd.s, sd.len, newSize);
                delete sd.s;
                sd = temp;
        }
}

// assign the string
void String::assign(StringData &sd, const char *data, int len) {
        if (len >= sd.size) {
                delete sd.s;
                sd=String::alloc(data,len);
        }
        else {
                memcpy(sd.s,data,len);
                sd.s[len]='\0';
                sd.len=len;
        }
}

// calculatesthe length of string
int String::length(const char *s) {
        const char *p=s;

        while(*p) p++;
        return int(p-s);
}

// appends a character string to a String
void String::append(StringData &sd, const char *data, int slen) {
        int newSize = sd.len+slen;
        if (newSize >= sd.size)
                String::resize(sd,newSize);
        memcpy(&sd.s[sd.len],data,slen);
        sd.len += slen;
        sd.s[sd.len]='\0';
}

// exception handling
void String::exception(char *message) {
        std::cerr << "String Exception: " << message << "\n" << "\n";
        dump();
        exit (1);
}

// dump string contents (for crash debug)
void String::dump() {
        std::cerr << "\n"
             << "String length: " << p.len  << "\n"
             << "String size  : " << p.size << "\n"
             << "String s     : " << p.s    << "\n";
        for (int i = 0; i < p.len; i++)
                std::cerr << i << " :  " << p.s[i] << " " << (int)p.s[i] << "\n";
}

// verify string contents, call exception if error
void String::verify() {
        if (p.len >= p.size) exception("VERIFY:  length >= size");
        if (p.s[p.len] != '\0') exception("VERIFY:  missing null");
        if (p.s==NULL) exception("VERIFY:  s == NULL");
}

/* End of simple String library */

// stuff from Nid String

// return left stubstring, up to index
String String::left(int index) const {
        if (!cptr())
                return "";
        if (index > length())
                return cptr();


        String tempStr;
        for (int i = 0; i < index; i++)
                tempStr += p.s[i];
        return tempStr;
}

String String::left(const String &s, int index) {
        return s.left(index);
}

String String::right(int index) const {
        if (!cptr())
                return "";
        if (index > length())
                return cptr();

        String tempStr;
        int l = length();
        for (int i = l - index; i < l; i++)
                tempStr += p.s[i];
        return tempStr;
}

String String::right(const String &s, int index) {
        return s.right(index);
}

void String::replaceChar(char find, char replace) {
        if (cptr()) {
                char* temp = p.s;
                while(temp) {
                        if (*temp == find)
                                *temp = replace;
                        temp++;
                }
        }
}

int String::parseInt() {
        return atoi(cptr());
}


char String::charAt(int index) {
	return p.s[index];
}

int String::parseInt(String &s) {
        return atoi(s.cptr());
}

int String::parseInt(const String &s) {
        return atoi(s.cptr());
}

int String::indexOf(const char* c) {
	return String::search(cptr(), length(), c, String::length(c) );
}

int String::indexOf(const String& s) {
	return String::search(cptr(), length(), s.cptr(), s.length() );
}