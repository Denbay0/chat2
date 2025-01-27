#pragma once
#include <string>
#include <vector>

class User {
private:
    std::string login;
    std::string password;
    std::string name;
    std::vector<std::pair<std::string, std::string>> messages; // Пары (отправитель, сообщение)
public:
    User(std::string l, std::string p, std::string n);

    std::string getLogin() const;
    std::string getPassword() const;
    std::string getName() const;

    void receiveMessage(const std::string& sender, const std::string& message);
    void viewMessages() const;
};