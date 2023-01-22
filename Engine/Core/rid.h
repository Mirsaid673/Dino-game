#pragma once

#include <cstdint>

struct RID
{
private:
    uint32_t id;

public:
    static const uint32_t invalid = UINT32_MAX;

    RID() : id(invalid) {}
    RID(uint32_t ID) : id(ID) {}

    bool isValid() const { return id != invalid; }

    void setID(uint32_t ID) { id = ID; }
    uint32_t getID() const { return id; }

    operator uint32_t() const { return id; }
};