#pragma once

class CRefCounter
{
public:
    CRefCounter() : i_count(0) {}

    int iAdd() { return ++i_count; }
    int iDec() { return --i_count; }
    int iGet() const { return i_count; }

private:
    int i_count;
};
