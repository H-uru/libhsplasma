struct A {
    virtual void fun() = 0;
};
struct B : public A {
    void fun() override { }
    virtual void funner() final { }
};

int main(int, char **) {
    B b;
    b.fun();
    b.funner();

    return 0;
}
