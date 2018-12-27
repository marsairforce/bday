#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <string>


#define STRING_HUNKSIZE 16
#define STRING_MATCH_BY_STRING 0
#define STRING_MATCH_BY_CHAR   1

typedef struct {
  int   len;                            // length of string (not including null)
  int   size;                           // allocated size of string
  char  *s;                             // pointer to data};
} StringData ;

class String {
private:
        void exception(char* message); // Causes process to exit.

protected:

public:
        StringData p;                   // The actual string

        // utility functions
        static StringData alloc(const char* data, int len, int size=-1);
        static void resize(StringData &sd, int newSize);
        static void assign(StringData &sd, const char *data, int len);
        static int length(const char *s);
        static int search(const char *s,int slen,const char *s_str,int sslen);
        static int compare(const char *s1,int s1_len,const char *s2,int s2_len);
        static void append(StringData &sd, const char *data, int slen);
        static void concat(StringData &p,const char *s1, int l1,
                                          const char *s2, int l2);

        // constructors
        String();
        String(int);
        String(char);
        String(const char *);
        String(const char *, int);
        String(const String &);

        virtual ~String();

        // copy assignment
        String & operator = (int);
        String & operator = (char);
        String & operator = (const char *);
        String & operator = (const String &);

        // append assignment
        String & operator += (int);
        String & operator += (char);
        String & operator += (const char *);
        String & operator += (const String &);

        // + operator returns a new string that is the concatenation of 2 values
        String operator + (int n) const;
        String operator + (char) const;
        String operator + (const char *) const;
        String operator + (const String &) const;
        friend String operator + (int, const String &);
        friend String operator + (char, const String &);
        friend String operator + (const char *, const String &);
//        friend String operator + (const String &, const String &);


        // output a string, input a string (skip white space),
        // getline inputs a string maintaining whitespace

        friend std::ostream & operator << (std::ostream &os, const String &);
        friend std::istream & operator >> (std::istream &is, String &);
        int getLine(std::istream &, String &, char delim='\n',int dropit=1);

        // String operations
        char& operator [] (int);
        String & add(int);
        void trimWhiteSpace();
        void upperCase();
        void lowerCase();

        int match( void* str, int type=STRING_MATCH_BY_STRING);
        int compare( void* obj, int );

        virtual String &Str()         { return *this; }

        int length() const            { return p.len; }
        int setLength(int);
        int size();

        operator const char *() const { return p.s; }
        char * cptr() const           { return p.s; }

        int enpty() const             { return length()==0; }
        int operator !() const        { return length()==0; }

        operator void *() const       { return (void *) length(); }


        // utility functions
        void dump();
        void verify();


// relational stuff
// (define these as global operators, to allow two arguments !)

// < comparison

        friend inline int operator < (const String &s1, char c) {
                return String::compare(s1.cptr(),s1.length(),&c,1)<0;
        }

        friend inline int operator < (const String &s1, const char *c) {
                return String::compare(s1.cptr(),s1.length(),c,String::length(c))<0;
        }

        friend inline int operator < (char c, const String &s1) {
                return String::compare(&c,1,s1.cptr(),s1.length())<0;
        }

        friend inline int operator < (const char *c,const String &s1) {
                return String::compare(c,String::length(c),s1.cptr(),s1.length())<0;
        }

        friend inline int operator < (const String &s1,const String &s2) {
                return String::compare(s1.cptr(),s1.length(),s2.cptr(),s2.length())<0;
        }

        // <= comparison
        friend inline int operator <= (const String &s1,char c) {
                return String::compare(s1.cptr(),s1.length(),&c,1)<=0;
        }

        friend inline int operator <= (const String &s1,const char *c) {
                return String::compare(s1.cptr(),s1.length(),c,String::length(c))<=0;
        }

        friend inline int operator <= (char c, const String &s1) {
                return String::compare(&c,1,s1.cptr(),s1.length())<=0;
        }

        friend inline int operator <= (const char *c,const String &s1) {
                return String::compare(c,String::length(c),s1.cptr(),s1.length())<=0;
        }

        friend inline int operator <= (const String &s1,const String &s2) {
                return String::compare(s1.cptr(),s1.length(),s2.cptr(),s2.length())<=0;
        }

        // == comparison
        friend inline int operator == (const String &s1,char c) {
                return String::compare(s1.cptr(),s1.length(),&c,1)==0;
        }

        friend inline int operator == (const String &s1,const char *c) {
                return String::compare(s1.cptr(),s1.length(),c,String::length(c))==0;
        }

        friend inline int operator == (char c, const String &s1) {
                return String::compare(&c,1,s1.cptr(),s1.length())==0;
        }

        friend inline int operator == (const char *c,const String &s1) {
                return String::compare(c,String::length(c),s1.cptr(),s1.length())==0;
        }

        friend inline int operator == (const String &s1,const String &s2) {
                return String::compare(s1.cptr(),s1.length(),s2.cptr(),s2.length())==0;
        }

        // != comparison
        friend inline int operator != (const String &s1,char c) {
                return String::compare(s1.cptr(),s1.length(),&c,1)!=0;
        }

        friend inline int operator != (const String &s1,const char *c) {
                return String::compare(s1.cptr(),s1.length(),c,String::length(c))!=0;
        }

        friend inline int operator != (char c, const String &s1) {
                return String::compare(&c,1,s1.cptr(),s1.length())!=0;
        }

        friend inline int operator != (const char *c,const String &s1) {
                return String::compare(c,String::length(c),s1.cptr(),s1.length())!=0;
        }

        friend inline int operator != (const String &s1,const String &s2) {
                return String::compare(s1.cptr(),s1.length(),s2.cptr(),s2.length())!=0;
        }

        // > comparison
        friend inline int operator > (const String &s1,char c) {
                return String::compare(s1.cptr(),s1.length(),&c,1)>0;
        }

        friend inline int operator > (const String &s1,const char *c) {
                return String::compare(s1.cptr(),s1.length(),c,String::length(c))>0;
        }

        friend inline int operator > (char c, const String &s1) {
                return String::compare(&c,1,s1.cptr(),s1.length())>0;
        }

        friend inline int operator > (const char *c,const String &s1) {
                return String::compare(c,String::length(c),s1.cptr(),s1.length())>0;
        }

        friend inline int operator > (const String &s1,const String &s2) {
                return String::compare(s1.cptr(),s1.length(),s2.cptr(),s2.length())>0;
        }
        // >= comparison
        friend inline int operator >= (const String &s1,char c) {
                return String::compare(s1.cptr(),s1.length(),&c,1)>=0;
        }

        friend inline int operator >= (const String &s1,const char *c) {
                return String::compare(s1.cptr(),s1.length(),c,String::length(c))>=0;
        }

        friend inline int operator >= (char c, const String &s1) {
                return String::compare(&c,1,s1.cptr(),s1.length())>=0;
        }

        friend inline int operator >= (const char *c,const String &s1) {
                return String::compare(c,String::length(c),s1.cptr(),s1.length())>=0;
        }

        friend inline int operator >= (const String &s1,const String &s2) {
                return String::compare(s1.cptr(),s1.length(),s2.cptr(),s2.length())>=0;
        }


        // stuff from NidString
        String left(int) const;
        static String left(const String &s, int);

        String right(int) const;
        static String right(const String &s, int);

        void replaceChar(char find, char replace);


        // extra stuff
        int parseInt();

        static int parseInt(String &s);
        static int parseInt(const String &s);

        char charAt(int);

        int indexOf(const char *);
        int indexOf(const String &s);

};



#endif
