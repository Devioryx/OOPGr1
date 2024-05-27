#include <iostream>
#include <string>
#include <vector>

using namespace std;
// Shte ima sus sigurnost template i diamanten problem na kontrolnoto po praktikuma
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

enum class ComponentType
{
    RAM,
    CPU
};

class Component
{
public:
    Component(const std::string& label) : label(label) {}
    virtual ~Component() = default;

    virtual double price() const = 0;
    virtual void output(std::ostream& out) const
    {
        out << label << std::endl;
        out << price() << std::endl;
    };

private:
    const std::string label;
};

class CPU: public Component
{
public:
    CPU(const std::string& label, const unsigned short cores, const unsigned clockSpeed)
    : Component(label), cores(cores), clockSpeed(clockSpeed) {
        if(cores < 1 || cores > 8)
            throw std::invalid_argument("CPU: Invalid Core Count!");
    }

    virtual double price() const override {
        return cores * 29.99;
    }

    virtual void output(std::ostream& out) const override
    {
        Component::output(out);
        std::cout << cores << std::endl;
        std::cout << clockSpeed << std::endl;
    }

private:
    const unsigned short cores;
    const unsigned short clockSpeed;
};

class RAM: public Component
{
public:
    RAM(const std::string& label, const unsigned short capacity)
    : Component(label), capacity(capacity){
        if(capacity < 1 || capacity > 10'000)
            throw std::invalid_argument("CPU: Invalid Core Count!");
    }

    virtual double price() const override {
        return 89.99 * capacity;
    }

    virtual void output(std::ostream& out) const override
    {
        Component::output(out);
        std::cout << capacity << std::endl;
    }

private:
    const unsigned short capacity;
};

Component* create_component()
{
    std::string type;

    cin >> type;

    try
    {
        if(type == "CPU")
        {
            std::string label;
            unsigned short cores;
            unsigned short clockSpeed;

            cin>>label;
            cin>>cores;
            cin>>clockSpeed;

            return new CPU(label, cores, clockSpeed);
        }

        else if (type == "RAM")
        {
            std::string label;
            unsigned short capacity;

            cin >> label;
            cin >> capacity;

            return new RAM(label, capacity);
        }

        return nullptr;
    }
    catch(...)
    {
        return nullptr;
    }
}


class Configuration
{
public:
    ~ Configuration() {
        for (size_t i = 0; i < components.size(); i++)
            delete components[i];  
    }


private:
    Configuration() {};
    std::vector<Component*> components;

    Configuration& operator=(const Configuration& other) = delete;
    Configuration(const Configuration& other) = delete;


    friend Configuration* create_configuration();
};


Configuration* create_configuration()
{
    static Configuration* instance = new Configuration;
    return instance;
}

int main()
{

}