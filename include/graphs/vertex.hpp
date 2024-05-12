#pragma once

class Vertex {
public:

    int id;
    int o;

    explicit Vertex(int o, int id = -1) {
        this->id = id;
        this->o = o;
    }

    Vertex(const Vertex& other) {
        this->id = other.id;
        this->o = other.o;
    }

    static Vertex* build(int o, bool reset = false) {
        static int id = 0;
        reset ? id = 0 : id = id;
        auto* v = new Vertex(o, id);
        id++;
        return v;
    }

    bool operator==(const Vertex& other) const {
        return this->id == other.id;
    }

    bool operator!=(const Vertex& other) const {
        return this->id != other.id;
    }

    bool operator<(const Vertex& other) const {
        return this->id < other.id;
    }

    bool operator==(const Vertex* other) const {
        return this->id == other->id;
    }


    bool operator<(const Vertex* other) const {
        return this->id < other->id;
    }

    bool operator>(const Vertex& other) const {
        return this->id > other.id;
    }
};