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
        Point(int new_x, int new_y, int new_z) : Point() {
            position.x = new_x;position.y = new_y; position.z = new_z;
        }

        Point(int new_x, int new_y) : Point(new_x, new_y, 0) {}
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

        long getId1() const { return id1; }
        long getId2() const { return id2; }

        double getLength() const;

        friend std::istream& operator>>(std::istream& is, Line& line);
        friend std::ostream& operator<<(std::ostream& os, const Line& line);
    };

    class Polygon {
    private:
        inline static long id_counter = 1;
        inline static std::map<long, Polygon*> registry;

        long polID;
        long id1 = 0;
        long id2 = 0;
        long id3 = 0;

    public:
        Polygon();
        ~Polygon();
        Polygon(long a_id, long b_id, long c_id) : Polygon() {
            id1 = a_id;
            id2 = b_id;
            id3 = c_id;
        }

        static Polygon* find(long target_id);

        long getPolId() const { return polID; }
        long getId1() const { return id1; }
        long getId2() const { return id2; }
        long getId3() const { return id3; }

        friend std::istream& operator>>(std::istream& is, Polygon& pol);
        friend std::ostream& operator<<(std::ostream& os, const Polygon& pol);

    };

}

#endif