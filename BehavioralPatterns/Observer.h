#pragma once
#include <iostream>
#include <vector>

class Subscriber {
public:
    virtual void notify(const std::string& publisherName, const std::string& message) = 0;
    virtual std::string getName() = 0;
};

class Publisher {
public:
    virtual void subscribe(Subscriber* subscriber) = 0;
    virtual void unsubscribe(Subscriber* subscriber) = 0;
    virtual void publish(const std::string& message) = 0;
};

class ChatGroup : public Publisher {
    std::string groupName;
    std::vector<Subscriber*> subscribers;
public:
    ChatGroup(const std::string& name) : groupName(name) {};
    void subscribe(Subscriber* subscriber) override {
        this->subscribers.push_back(subscriber);
    };
    void unsubscribe(Subscriber* subscriber) override {
        subscribers.erase(std::remove_if(subscribers.begin(), subscribers.end(), [subscriber](Subscriber* s) { return s->getName() == subscriber->getName(); }), subscribers.end());
    };
    void publish(const std::string& message) override {
        for (auto subscriber : subscribers) {
            subscriber->notify(groupName, message);
        }
    };
};

class ChatUser : public Subscriber {
    std::string userName;
public:
    ChatUser(const std::string& userName) : userName(userName) {};
    void notify(const std::string& publisherName, const std::string& message) override {
        std::cout << userName << " received a new message from " << publisherName << ": " << message << "\n";
    }
    std::string getName() override { return userName; };
};


