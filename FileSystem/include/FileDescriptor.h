#include <string>

//d -rwx user - rwx group - rwx other
const int permissions_size = 10;

class FileDescriptor {
public:
    std::string name;
    int id;
    std::string type;
    std::string location;
    bool permissions[permissions_size];
    int size;
    std::string username;
    //Time
};
