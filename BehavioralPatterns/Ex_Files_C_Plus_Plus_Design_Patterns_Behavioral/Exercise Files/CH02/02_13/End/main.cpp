//
//  main.cpp
//  combined-patterns-1
//

#include <iostream>
#include <vector>
#include <algorithm>

class Subscriber {
public:
    virtual void notify(const std::string & publisherName, const std::string & message) = 0;
    virtual std::string getName() = 0;
};
 
class ChatUser : public Subscriber {
    std::string userName;
public:
    ChatUser(const std::string & userName) : userName(userName) {};
    void notify(const std::string & publisherName, const std::string & message) override {
        std::cout << userName << " received a new message from " << publisherName << ": " << message << "\n";
    }
    std::string getName() override {
        return userName;
    }
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
    ChatGroup(const std::string & groupName) : groupName(groupName) {};
    void subscribe(Subscriber *subscriber) {
        this->subscribers.push_back(subscriber);
    }
    void unsubscribe(Subscriber *subscriber) {
        subscribers.erase(std::remove_if(subscribers.begin(), subscribers.end(), [subscriber](Subscriber *s){ return s->getName() == subscriber->getName(); }), subscribers.end());
    }
    void publish(const std::string & message) {
        for (auto subscriber : subscribers) {
            subscriber->notify(groupName, message);
        }
    }
};

class Handler {
public:
    virtual Handler *setNext(Handler *nextValidator) = 0;
    virtual ~Handler() {};
    virtual std::string handle(ChatGroup *group, const std::string & message) = 0;
};

class BaseHandler : public Handler {
protected:
    Handler *next = nullptr;
public:
    ~BaseHandler() { delete next; };
    Handler *setNext(Handler *nextValidator) override {
        next = nextValidator;
        return nextValidator;
    }
    virtual std::string handle(ChatGroup *group, const std::string & message) override {
        if (this->next) {
            return this->next->handle(group, message);
        }
        return "Success!";
    }
};

class NotEmptyValidator: public BaseHandler {
public:
    std::string handle(ChatGroup *group, const std::string & message) override {
        std::cout << "Checking if empty...\n";
        
        if (message.empty()) {
            return "Please enter a value";
        }
        
        return BaseHandler::handle(group, message);
    }
};

class LengthValidator: public BaseHandler {
    int minLength;
public:
    LengthValidator(int minLength) : minLength(minLength) {};
    std::string handle(ChatGroup *group, const std::string & message) override {
        std::cout << "Checking if length equals" << minLength << "...\n";
        
        if (message.length() < minLength) {
            return "Please enter a value longer than " + std::to_string(minLength);
        }
        
        return BaseHandler::handle(group, message);
    }
};

class PostMessageHandler: public BaseHandler {
public:
    std::string handle(ChatGroup *group, const std::string & message) {
        group->publish(message);
        return "Message Sent!";
    }
};

int main(int argc, const char * argv[]) {
    ChatUser *user1 = new ChatUser("Jim");
    ChatUser *user2 = new ChatUser("Barb");
    ChatUser *user3 = new ChatUser("Hannah");
    
    ChatGroup *group1 = new ChatGroup("Gardening Group");
    ChatGroup *group2 = new ChatGroup("Dog-lovers Group");
    
    group1->subscribe(user1);
    group1->subscribe(user2);
    
    group2->subscribe(user2);
    group2->subscribe(user3);
    
    Handler *sendMessageChain = new BaseHandler;
    
    sendMessageChain
        ->setNext(new NotEmptyValidator)
        ->setNext(new LengthValidator(2))
        ->setNext(new PostMessageHandler);
    
    std::cout << "Sending empty message:\n" << sendMessageChain->handle(group1, "") << "\n\n";
    std::cout << "Sending short message:\n" << sendMessageChain->handle(group1, "H") << "\n\n";
    std::cout << "Sending message to group 1:\n" << sendMessageChain->handle(group1, "Hello everyone in group 1!") << "\n\n";
    std::cout << "Sending message to group 2:\n" << sendMessageChain->handle(group2, "Hello everyone in group 2!") << "\n\n";
    
    delete user1;
    delete user2;
    delete user3;
    delete group1;
    delete group2;
    delete sendMessageChain;
}

