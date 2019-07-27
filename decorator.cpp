#include <iostream>

using namespace std;

// https://sourcemaking.com/design_patterns/decorator/cpp/1

class widget {
public:
    virtual ~widget() {}
    virtual void draw() = 0;
};

class core : public widget {
public:
    void draw() override {
        cout << "Draw: Core";
    }
    ~core() {
        cout << " ~core()";
    }
};

class decor : public widget {
    widget* wrapee_ = nullptr;
public:
    decor(widget* w) : wrapee_{w} {}
    void draw() override {
        wrapee_->draw();
    }
    ~decor() {
        // cout << " ~decor()";
        delete wrapee_;
    }
};

class decorX : public decor {
public:
    decorX(widget* w) : decor(w) {}
    void draw() override {
        decor::draw();
        cout << " X";
    }
    ~decorX() {
        cout << " ~X()";
    }
};

class decorY : public decor {
public:
    decorY(widget* w) : decor(w) {}
    void draw() override {
        decor::draw();
        cout << " Y";
    }
    ~decorY() {
        cout << " ~Y()";
    }
};

template<typename T>
class MixinX : public T {
public:
    void draw() {
        T::draw();
        cout << " X";
    } 
};


template<typename T>
class MixinY : public T {
public:
    void draw() {
        T::draw();
        cout << " Y";
    } 
};


void test_decor() {
    cout << "----" << __func__ << "----" << endl;
    widget* w = nullptr;

    w = new core;
    w->draw();
    cout << "\n";
        
    w = new decorX(w);
    w->draw();
    cout << "\n";
    
    w = new decorY(w);
    w->draw();
    cout << "\n";
    
    delete w;
    cout << "\n";
}

void test_mixin() {
    cout << "----" << __func__ << "----" << endl;
    MixinX<core> mixin_x_core;
    mixin_x_core.draw();
    cout << "\n";

    MixinY<MixinX<core>> mixin_xy_core;
    mixin_xy_core.draw();
    cout << "\n";
}
int main(int argc, char** argv) 
{
    test_decor();
    test_mixin();
    return 0;
}