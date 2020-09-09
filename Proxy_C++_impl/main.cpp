#include <iostream>

#include <memory>


/*
 * Позволяет подставлять вместо реальных объектов специальные объекты-заменители.
 * Эти объекты перехватывают вызовы к оригинальному объекту, позволяя сделать что-то до или после передачи вызова оригиналу.
 * */
class Subject {
public:
    virtual void request() const = 0;
};

class RealSubject: public Subject{
public:
    RealSubject() { std::cout << "real subject created" << std::endl; }
    ~RealSubject() { std::cout << "real subject destroyed" << std::endl; }
    void request() const override {
        std::cout << "RealSubject: Request()" << std::endl;
    }
};

class Proxy: public Subject {
public:
    Proxy(RealSubject* rs):
            real_subject(new RealSubject(*rs)) {}
    ~Proxy() {delete real_subject;}
    void request() const override{
        if (this->checkAccess()) {
            this->real_subject->request();
            this->logAccess();
        }
    }
private:
    bool checkAccess() const {
        std::cout << "Proxy: checking access prior to firing a real request" << std::endl;
        return true;
    }
    void logAccess() const {
        std::cout << "Proxy: Logging the time of request" << std::endl;
    }
    RealSubject* real_subject;
};

void clientCode(Subject& subj) {
    subj.request();
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    RealSubject* rs = new RealSubject;
    clientCode(*rs);
    std::cout << "Client: Executing the same client code with a proxy:" << std::endl;
    Proxy *proxy = new Proxy(rs);
    clientCode(*proxy);
    delete rs;
    delete proxy;
    return 0;
}
