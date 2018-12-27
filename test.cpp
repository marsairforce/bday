#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class myRecord {
public:
        double num;
        char x[1024];
        char character;
};

void main(void) {
        fstream Object("user.dat",ios::binary|ios::out);
        myRecord record;
        record.num = 3.1459;
        strcpy(record.x, "Test string");
        record.character = '@';

        Object.write(reinterpret_cast<char *>(&record), sizeof(myRecord));
        Object.close();
        Object.open("user.dat", ios::binary | ios::in);
        Object.read(reinterpret_cast<char *>(&record),sizeof(myRecord));
        Object.close();
}