//
//  main.cpp
//  observer-pattern
//

#include <iostream>
#include <vector>
#include <algorithm>

class Subscriber {
public:
    virtual void notify(const std::string & publisherName, const std::string & message) = 0;
    virtual std::string getName() = 0;
};

class Publisher {
public:
    virtual void subscribe(Subscriber *subscriber) = 0;
    virtual void unsubscribe(Subscriber *subscriber) = 0;
    virtual void publish(const std::string & message) = 0;
};

class ChatGroup : public Publisher {
    std::string groupName;
    std::vector<Subscriber*> subscribers;
public:
    ChatGroup(const std::string & name) : groupName(name) {};
    void subscribe(Subscriber *subscriber) override {
        this->subscribers.push_back(subscriber);
    };
    void unsubscribe(Subscriber *subscriber) override {
        subscribers.erase(std::remove_if(subscribers.begin(), subscribers.end(), [subscriber](Subscriber *s) { return s->getName() == subscriber->getName(); }), subscribers.end());
    };
    void publish(const std::string & message) override {
        for (auto subscriber : subscribers) {
            subscriber->notify(groupName, message);
        }
    };
};

class ChatUser : public Subscriber {
    std::string userName;
public:
    ChatUser(const std::string & userName) : userName(userName) {};
    void notify(const std::string & publisherName, const std::string & message) override {
        std::cout << userName << " received a new message from " << publisherName << ": " << message << "\n";
    }
    std::string getName() override { return userName; };
};

int main(int argc, const char * argv[]) {
    ChatUser *user1 = new ChatUser("Jim");
    ChatUser *user2 = new ChatUser("Barb");
    ChatUser *user3 = new ChatUser("Hannah");
    
    ChatGroup *group1 = new ChatGroup("Gardening group");
    ChatGroup *group2 = new ChatGroup("Dog-lovers group");
    
    group1->subscribe(user1);
    group1->subscribe(user2);
    
    group2->subscribe(user2);
    group2->subscribe(user3);
    
    group1->publish("Special sale on gardening supplies!");
    group2->publish("It's national dog day everyone!");
    
    delete user1;
    delete user2;
    delete user3;
    delete group1;
    delete group2;
    
    return 0;
}
