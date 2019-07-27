#include <iostream>

using namespace std;

// https://sourcemaking.com/design_patterns/decorator/cpp/1
// http://www.thinkbottomup.com.au/site/blog/C%20%20_Mixins_-_Reuse_through_inheritance_is_good
// https://michael-afanasiev.github.io/2016/08/03/Combining-Static-and-Dynamic-Polymorphism-with-C++-Template-Mixins.html

class decor_base {
public:
    virtual ~decor_base() {}
    virtual void draw() = 0;
};

class decor_core : public decor_base {
public:
    void draw() override {
        cout << "Decor Draw: Core";
    }
    ~decor_core() {
        cout << __func__ << "\n";
    }
};

class decor : public decor_base {
    decor_base* wrapee_ = nullptr;
public:
    decor(decor_base* w) : wrapee_{w} {}
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
    decorX(decor_base* w) : decor(w) {}
    void draw() override {
        decor::draw();
        cout << " X";
    }
    ~decorX() {
        cout << __func__ << " ";
    }
};

class decorY : public decor {
public:
    decorY(decor_base* w) : decor(w) {}
    void draw() override {
        decor::draw();
        cout << " Y";
    }
    ~decorY() {
        cout << __func__ << " ";
    }
};

template<typename T>
class mixin_common : public T {
public:
    void draw() {
        this->do_draw();
    }
};

class mixin_core {
public:
    ~mixin_core() {
        cout << __func__ << endl;
    }
    void do_draw() {
        cout << "Mixin Draw: Core";
    }
};

template<typename T>
class mixinX : public T {
public:
    ~mixinX() {
        cout << __func__ << " ";
    }
    void do_draw() {
        T::do_draw();
        cout << " X";
    } 
};

template<typename T>
class mixinY : public T {
public:
    ~mixinY() {
        cout << __func__ << " ";
    }
    void do_draw() {
        T::do_draw();
        cout << " Y";
    } 
};

void test_decor() {
    cout << "------ " << __func__ << " ------" << endl;
    decor_base* w = nullptr;

    w = new decor_core;
    w->draw();
    cout << "\n";
        
    w = new decorX(w);
    w->draw();
    cout << "\n";
    
    w = new decorY(w);
    w->draw();
    cout << "\n";
    
    delete w;
}

void test_mixin() {
    cout << "------ " << __func__ << " ------" << endl;
    mixin_common<mixin_core> mixin_just_core;
    mixin_just_core.draw();
    cout << "\n";
    
    mixin_common<mixinX<mixin_core>> mixin_x_core;
    mixin_x_core.draw();
    cout << "\n";

    mixin_common<mixinY<mixinX<mixin_core>>> mixin_xy_core;
    mixin_xy_core.draw();
    cout << "\n";
/*
    // wrong
    mixinX<core> mixin_x_core;
    mixin_x_core.draw();
    cout << "\n";

    mixinY<mixinX<core>> mixin_xy_core;
    mixin_xy_core.draw();
    cout << "\n";
*/
}

int main(int argc, char** argv) 
{
    test_decor();
    test_mixin();
    return 0;
}