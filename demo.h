#ifndef DEMO_H
#define DEMO_H

#include <string>

class Demo
{
private:
    std::string demoName;
public:
    Demo(std::string name);
    virtual void run() = 0;
};

#endif // DEMO_H
