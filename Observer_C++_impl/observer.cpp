#include <iostream>
#include <list>
#include <string>
#include <memory>

class ISubscriber {
public:
    virtual      ~ISubscriber() {};
    virtual void update(const std::string &message_for_subscribers) = 0;
};

class IPublisher {
public:
    virtual      ~IPublisher() {};
    virtual void attach(ISubscriber* subscriber) = 0;
    virtual void detach(ISubscriber* subscriber) = 0;
    virtual void notify() = 0;
};

class Publisher : public IPublisher {
public:
    virtual ~Publisher() {
        std::cout << "publisher free" << std::endl;
    }

    void attach(ISubscriber* subscriber) override {
        std::cout << subscriber << " attached to publisher " << this << std::endl;
        m_subscribers.push_back(subscriber);
    }

    void detach(ISubscriber* subscriber) override {
        std::cout << subscriber << " detached from publisher " << this << std::endl;
        m_subscribers.remove(subscriber);
    }

    void notify() override {
        std::cout << "Publisher did new entry" << std::endl;
        for (auto iter = m_subscribers.begin(); iter != m_subscribers.end(); iter++) {
            (*iter)->update(m_message);
        }
    }

    void create_message(const std::string& msg) {
        m_message = msg;
        notify();
    }

    int obs_cnt() {
        return m_subscribers.size();
    }

private:
    std::list<ISubscriber*> m_subscribers;
    std::string             m_message;
};

class Subscriber : public ISubscriber {
public:
    Subscriber(Publisher& publisher) :
        m_publisher(publisher) {
        this->m_publisher.attach(this);
        std::cout << "Observer attached to Subject. Total number of observers is " << ++Subscriber::m_id << std::endl;
        this->m_number = Subscriber::m_id;
    }
    virtual ~Subscriber() {
        std::cout << "observer rip" << std::endl;
    }
    void update(const std::string& message_for_subscribers) override {
        std::cout << "on message update: " << message_for_subscribers << std::endl;
        m_msg_from_publisher = message_for_subscribers;
    }
    void unsubscribe() {
        std::cout << "Observer detached from Subject. Total number of observers is " << --Subscriber::m_id << std::endl;
        m_publisher.detach(this);
    }

private:
    std::string m_msg_from_publisher;
    Publisher&  m_publisher;
    static int  m_id;
    int         m_number;
};

int Subscriber::m_id = 0;

void processing() {
    Publisher* publisher = new Publisher;
    Subscriber* subscriber1 = new Subscriber(*publisher);
    Subscriber* subscriber2 = new Subscriber(*publisher);
    Subscriber* subscriber3 = new Subscriber(*publisher);
    publisher->create_message("Hello!");
    subscriber1->unsubscribe();
    publisher->create_message("Bye!");

    delete subscriber1;
    delete subscriber2;
    delete subscriber3;
    delete publisher;
}

int main() {
    std::cout << "main - start" << std::endl;
    processing();
    std::cout << "main - end" << std::endl;
    return 0;
}