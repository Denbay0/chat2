#include "user.h"
#include <iostream>

User::User(std::string l, std::string p, std::string n) : login(l), password(p), name(n) {}

std::string User::getLogin() const {
    return login;
}

std::string User::getPassword() const {
    return password;
}

std::string User::getName() const {
    return name;
}

void User::receiveMessage(const std::string& sender, const std::string& message) {
    messages.push_back(std::make_pair(sender, message)); // Сохранение сообщения в массив пользователя
}

void User::viewMessages() const {
    for (const auto& message : messages) {
        std::cout << message.first << ": " << message.second << std::endl;
    }
}