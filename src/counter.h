#pragma once

class Counter {
public:
    int Increment() { return ++value_; }
    int Value() const { return value_; }
    void Reset() { value_ = 0; }

private:
    int value_ = 0;
};
