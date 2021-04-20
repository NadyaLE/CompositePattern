#include <algorithm>
#include <iostream>
#include <list>
#include <string>
using namespace std;

class Component {
protected:
    Component* parent_;
public:
    virtual ~Component() {}
    void SetParent(Component* parent) {
        this->parent_ = parent;
    }
    Component* GetParent() const {
        return this->parent_;
    }
    
    virtual void Add(Component* component) {}
    virtual void Remove(Component* component) {}
 
    virtual bool IsComposite() const {
        return false;
    }
    
    virtual string Operation() const = 0;
};

class Leaf : public Component {
    string name_;
    public:
        Leaf(string name) {
            name_ = name;
    }
    string Operation() const override {
        return name_;
    }
};

class Composite : public Component {
   
protected:
    list<Component*> children_;

public:
   
    void Add(Component* component) override {
        this->children_.push_back(component);
        component->SetParent(this);
    }
    
    void Remove(Component* component) override {
        children_.remove(component);
        component->SetParent(nullptr);
    }
    bool IsComposite() const override {
        return true;
    }
    
    string Operation() const override {
        string result;
        for (const Component* c : children_) {
            if (c == children_.back()) {
                result += c->Operation();
            }
            else {
                result += c->Operation() + "+";
            }
        }
        return "1/(" + result + ")";
    }
};

void ClientCode(Component* component) {
    cout << "RESULT: " << component->Operation();   
}


void ClientCode2(Component* component1, Component* component2) {
    cout << "RESULT: (" << component1->Operation() << "+" << component2->Operation() << ")";   
}


int main() {
    Component* tree1 = new Composite;
    Component* leaf_3 = new Leaf("3");
    Component* leaf_4 = new Leaf("4");
    Component* leaf_5 = new Leaf("5");
    Component* leaf_6 = new Leaf("6");
    Component* leaf_7 = new Leaf("7");
    tree1->Add(leaf_3);
    tree1->Add(leaf_4);
    tree1->Add(leaf_5);
    Component* tree2 = new Composite;
    tree2->Add(leaf_7);
    tree2->Add(tree1);
    Component* tree3 = new Composite;
    tree3->Add(leaf_6);
    tree3->Add(tree2);
    Component* tree4 = new Composite;
    tree4->Add(leaf_6);
    tree4->Add(tree3);
    Component* tree5 = new Composite;
    tree5->Add(leaf_6);
    tree5->Add(tree4);
    cout << "Client: Now I've got a composite tree:\n";
    ClientCode2(leaf_6, tree5);
    cout << "\n";
    delete tree1;
    delete tree2;
    delete tree3;
    delete tree4;
    delete tree5;
    delete leaf_3;
    delete leaf_4;
    delete leaf_5;
    delete leaf_7;

    return 0;
}