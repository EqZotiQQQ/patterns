#include <iostream>
#include <vector>

class IBaseShape {
public:
    ~IBaseShape();
    virtual void printInfo() = 0;
};

class Rectangle:public IBaseShape {
public:
    void printInfo() override {std::cout << "Rectangle" << std::endl;}
};
class Square: public IBaseShape {
public:
    void printInfo() override {std::cout << "Square" << std::endl;}
};
class Circle: public IBaseShape {
public:
    void printInfo() override {std::cout << "Circle" << std::endl;}
};
class Dot: public IBaseShape {
public:
    void printInfo() override {std::cout << "Dot" << std::endl;}
};

class Factory {
public:
    virtual IBaseShape* createObject() = 0;
    ~Factory();
};
class RectangleFactory: public Factory {
public:
    IBaseShape * createObject() override {
        return new Rectangle;
    }
};
class SquareFactory: public Factory {
public:
    IBaseShape * createObject() override {
        return new Square;
    }
};
class CircleFactory: public Factory {
public:
    IBaseShape * createObject() override {
        return new Circle;
    }
};
class DotFactory: public Factory {
public:
    IBaseShape * createObject() override {
        return new Dot;
    }
};

int main() {
    std::vector<IBaseShape*> shapesVec;
    RectangleFactory* rf = new RectangleFactory;
    SquareFactory* sf = new SquareFactory;
    CircleFactory* cf = new CircleFactory;
    DotFactory* df = new DotFactory;
    shapesVec.push_back(rf->createObject());
    shapesVec.push_back(sf->createObject());
    shapesVec.push_back(cf->createObject());
    shapesVec.push_back(df->createObject());
    shapesVec.push_back(df->createObject());
    shapesVec.push_back(cf->createObject());
    shapesVec.push_back(sf->createObject());
    shapesVec.push_back(rf->createObject());

    for(IBaseShape *shape: shapesVec) {
        shape->printInfo();
    }
    return 0;
}
