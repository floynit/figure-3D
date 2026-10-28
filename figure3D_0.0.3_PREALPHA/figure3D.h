#pragma once
#ifndef FIGURE3D_H
#define FIGURE3D_H
#include <iostream>
#include <map>
#include <cmath>

namespace figure {

    struct Position {
        int x = 0, y = 0, z = 0;

        friend std::ostream& operator<<(std::ostream& os, const Position& p) {
            return os << "pos(" << p.x << ", " << p.y << ", " << p.z << ")";
        }
        friend std::istream& operator>>(std::istream& is, Position& p) {
            return is >> p.x >> p.y >> p.z;
        }
        friend Position operator+(Position h, const Position& p) {
            h.x += p.x; h.y += p.y; h.z += p.z;
            return h;
        }
        friend Position operator-(Position h, const Position& p) {
            h.x -= p.x; h.y -= p.y; h.z -= p.z;
            return h;
        }
    };

    struct Point {
    private:
        inline static long id_counter = 1;
        inline static std::map<long, Point*> registry;

        Position position;
        long ID;

    public:
        Point();
        ~Point();

        Point(const Point&) = delete;
        Point& operator=(const Point&) = delete;
        Point(Point&&) = delete;
        Point& operator=(Point&&) = delete;

        long getId() const { return ID; }
        int getX() const { return position.x; }
        int getY() const { return position.y; }
        int getZ() const { return position.z; }

        void setCoordinates(int new_x, int new_y, int new_z) {
            position.x = new_x;
            position.y = new_y;
            position.z = new_z;
        }

        static Point* find(long target_id);

        friend std::ostream& operator<<(std::ostream& os, const Point& p) {
            return os << "point(" << p.ID << ", " << p.position << ")";
        }
        friend std::istream& operator>>(std::istream& is, Point& p) {
            return is >> p.position;
        }
    };

    class Line {
    private:
        long id1 = 0;
        long id2 = 0;

    public:
        Line() = default;
        Line(long a_id, long b_id) : id1(a_id), id2(b_id) {}

        double getLength() const;

        friend std::istream& operator>>(std::istream& is, Line& line);
        friend std::ostream& operator<<(std::ostream& os, const Line& line);
    };

}

#endif