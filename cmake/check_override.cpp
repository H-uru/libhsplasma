struct A {
    virtual void fun() = 0;
};
struct B : public A {
    void fun() override { }
};
struct C : public A {
    void fun() final { }
};

int main(int, char **) {
    B b;
    b.fun();
    C c;
    c.fun();

    return 0;
}
