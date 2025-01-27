#include <iostream>
#include <string>
#include "chat.h"

int main() {
    Chat chat;

    std::cout << "Welcome to the Chat Application!" << std::endl;

    int choice = 0;
    User* currentUser = nullptr;

    do {
        std::cout << "Choose an option:" << std::endl;
        if (currentUser == nullptr) {
            std::cout << "1. Register" << std::endl;
            std::cout << "2. Log in" << std::endl;
            std::cout << "3. Exit" << std::endl;
        }
        else {
            std::cout << "4. Send a message" << std::endl;
            std::cout << "5. Send a message to all" << std::endl;
            std::cout << "6. View my messages" << std::endl;
            std::cout << "7. Log out" << std::endl;
        }
        std::cout << "Your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string login, password, name;
            std::cout << "Enter login: ";
            std::cin >> login;
            std::cout << "Enter password: ";
            std::cin >> password;
            std::cout << "Enter name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            chat.registerUser(login, password, name);
            std::cout << "User registered successfully!" << std::endl;
            break;
        }
        case 2: {
            std::string login, password;
            std::cout << "Enter login: ";
            std::cin >> login;
            std::cout << "Enter password: ";
            std::cin >> password;
            currentUser = chat.login(login, password);
            if (currentUser != nullptr) {
                std::cout << "Welcome back, " << currentUser->getName() << "!" << std::endl;
            }
            else {
                std::cout << "Failed to log in. Incorrect username or password." << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "Exiting..." << std::endl;
            break;
        }
        case 4: {
            if (currentUser != nullptr) {
                std::string recipientLogin, message;
                std::cout << "Enter recipient's login: ";
                std::cin >> recipientLogin;
                User* recipient = nullptr;
                for (auto user : chat.getUsers()) {
                    if (user->getLogin() == recipientLogin) {
                        recipient = user;
                        break;
                    }
                }
                if (recipient != nullptr) {
                    std::cin.ignore();
                    std::cout << "Enter your message: ";
                    std::getline(std::cin, message);
                    chat.sendMessage(*currentUser, *recipient, message);
                    std::cout << "Message sent successfully." << std::endl;
                }
                else {
                    std::cout << "Recipient not found." << std::endl;
                }
            }
            else {
                std::cout << "You need to log in first." << std::endl;
            }
            break;
        }
        case 5: {
            if (currentUser != nullptr) {
                std::string message;
                std::cin.ignore();
                std::cout << "Enter your message to all users: ";
                std::getline(std::cin, message);
                chat.sendMessageToAll(*currentUser, message);
                std::cout << "Message sent to all users." << std::endl;
            }
            else {
                std::cout << "You need to log in first." << std::endl;
            }
            break;
        }
        case 6: {
            if (currentUser != nullptr) {
                currentUser->viewMessages();
            }
            else {
                std::cout << "You need to log in first." << std::endl;
            }
            break;
        }
        case 7: {
            if (currentUser != nullptr) {
                currentUser = nullptr;
                std::cout << "Logged out successfully." << std::endl;
            }
            else {
                std::cout << "You are not logged in." << std::endl;
            }
            break;
        }
        default: {
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
            break;
        }
        }
    } while (choice != 3);

    return 0;
}