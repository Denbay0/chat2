#include "hash_table.h"
#include <vector>
#include "user.h"

class Chat {
private:
    HashTable userTable;
    std::vector<User*> users;

public:
    Chat();
    ~Chat();

    void registerUser(const std::string& login, const std::string& password, const std::string& name);
    User* login(const std::string& login, const std::string& password);
    void sendMessage(User& sender, User& recipient, const std::string& message);
    void sendMessageToAll(User& sender, const std::string& message);
    std::vector<User*>& getUsers();
};
