#include <iostream>
#include <string>
#include <vector>
#include "Chat.h"

void Chat::start() {
    isChatWork_ = true;
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const {
    for (auto& user : users_) {
        if (login == user.getUserLogin())
            return std::make_shared<User>(user);
    }

    return nullptr;
}

std::shared_ptr<User> Chat::getUserByName(const std::string& name) const {
    for (auto& user : users_) {
        if (name == user.getUserName())
            return std::make_shared<User>(user);
    }

    return nullptr;
}

void Chat::login() {
    std::string login, password;
    char operation;

    do {
        std::cout << "login: ";
        std::cin >> login;
        std::cout << "password: ";
        std::cin >> password;

        currentUser_ = getUserByLogin(login);

        if (currentUser_ == nullptr || (password != currentUser_->getUserPassword())) {

            currentUser_ = nullptr;

            std::cout << "login failed..." << std::endl;
            std::cout << "(0)exit or (any key)repeat: ";
            std::cin >> operation;

            if (operation == "0")
                break;
        }
    } while (!currentUser_);
}

void Chat::signUp() {
    std::string login, password, name;

    std::cout << "login: ";
    std::cin >> login;
    std::cout << "password: ";
    std::cin >> password;
    std::cout << "name: ";
    std::cin >> name;

    if (getUserByLogin(login) || login == "all") {
        throw UserLoginExp();
    }

    if (getUserByName(name) || name == "all") {
        throw UserNameExp();
    }
