#include "chat.h"
#include <iostream>
#include <functional>

Chat::Chat() : userTable(100) {}

Chat::~Chat() {
    for (auto user : users) {
        delete user;
    }
}

void Chat::registerUser(const std::string& login, const std::string& password, const std::string& name) {
    size_t hash = std::hash<std::string>{}(password);
    if (!userTable.insert(login, hash)) {
        throw std::runtime_error("User with this login already exists.");
    }
    users.push_back(new User(login, password, name));
}

User* Chat::login(const std::string& login, const std::string& password) {
    auto hashOpt = userTable.find(login);
    if (!hashOpt.has_value()) {
        return nullptr; // Пользователь не найден
    }

    size_t hash = std::hash<std::string>{}(password);
    if (hashOpt.value() == hash) {
        for (auto user : users) {
            if (user->getLogin() == login) {
                return user;
            }
        }
    }
    return nullptr; // Неправильный пароль
}

void Chat::sendMessage(User& sender, User& recipient, const std::string& message) {
    recipient.receiveMessage(sender.getName(), message);
}

void Chat::sendMessageToAll(User& sender, const std::string& message) {
    for (const auto& user : users) {
        if (user != &sender) {
            user->receiveMessage(sender.getName(), message);
        }
    }
}

std::vector<User*>& Chat::getUsers() {
    return users;
}
