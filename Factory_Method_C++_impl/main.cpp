#include <iostream>
#include <vector>
enum ObjectID {
    RectangleID = 0,
    SquareID = 1,
    CircleID = 2,
    Dot_ID,
};

class IBaseShape {
public:
    ~IBaseShape();
    virtual void printInfo() = 0;
    static IBaseShape* createObject(ObjectID id);
};

class Rectangle:public IBaseShape {
public:
    void printInfo() override {std::cout << "Rectangle" << std::endl;}
};
class Square:public IBaseShape {
public:
    void printInfo() override {std::cout << "Square" << std::endl;}
};
class Circle:public IBaseShape {
public:
    void printInfo() override {std::cout << "Circle" << std::endl;}
};
class Dot:public IBaseShape {
public:
    void printInfo() override {std::cout << "Dot" << std::endl;}
};
IBaseShape* IBaseShape::createObject(ObjectID id) {
    IBaseShape* shape = nullptr;
    switch(id) {
        case RectangleID: shape = new Rectangle; break;
        case SquareID: shape = new Square; break;
        case CircleID: shape = new Circle; break;
        case Dot_ID: shape = new Dot; break;
        default:return shape;
    }
    return shape;
}
int main() {
    std::vector<IBaseShape*> shapesVec;
    shapesVec.push_back(IBaseShape::createObject(RectangleID));
    shapesVec.push_back(IBaseShape::createObject(SquareID));
    shapesVec.push_back(IBaseShape::createObject(CircleID));
    shapesVec.push_back(IBaseShape::createObject(Dot_ID));
    shapesVec.push_back(IBaseShape::createObject(Dot_ID));
    shapesVec.push_back(IBaseShape::createObject(CircleID));
    shapesVec.push_back(IBaseShape::createObject(SquareID));
    shapesVec.push_back(IBaseShape::createObject(RectangleID));
    for(IBaseShape *shape: shapesVec) {
        shape->printInfo();
    }
    return 0;
}
