#include "figure3D.h"

namespace figure {

    Point::Point() {
        ID = id_counter++;
        registry[ID] = this;
    }

    Point::~Point() {
        registry.erase(ID);
    }

    Point* Point::find(long target_id) {
        auto it = registry.find(target_id);
        if (it != registry.end()) {
            return it->second;
        }
        return nullptr;
    }

    double Line::getLength() const {
        Point* s1 = Point::find(id1);
        Point* s2 = Point::find(id2);

        if (!s1 || !s2) {
            return 0.0;
        }

        double dx = s2->getX() - s1->getX();
        double dy = s2->getY() - s1->getY();
        double dz = s2->getZ() - s1->getZ();

        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    Polygon::Polygon() {
        polID = id_counter++;
        registry[polID] = this;
    }

    Polygon::~Polygon() {
        registry.erase(polID);;
    }

    Polygon* Polygon::find(long target_id) {
        auto it = registry.find(target_id);
        if (it != registry.end()) {
            return it->second;
        }
        return nullptr;
    }

    std::istream& operator>>(std::istream& is, Line& line) {
        is >> line.id1 >> line.id2;

        if (!Point::find(line.id1) || !Point::find(line.id2)) {
            std::clog << "[Warning]: One of the line points was not found in the registry!\n";
        }
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const Line& line) {
        Point* s1 = Point::find(line.id1);
        Point* s2 = Point::find(line.id2);

        os << "Line[";
        if (s1) os << *s1; else os << "deleted/not found";
        os << " <-> ";
        if (s2) os << *s2; else os << "deleted/not found";
        os << "] (length: " << line.getLength() << ")";
        return os;
    }

    std::istream& operator>>(std::istream& is, Polygon& pol) {
        is >> pol.id1 >> pol.id2 >> pol.id3;
        if (!Point::find(pol.id1) || !Point::find(pol.id2) || !Point::find(pol.id3)) {
            std::clog << "[Warning]: One of the polygon points was not found in the registry!\n";
        }
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const Polygon& pol) {
        Point* s1 = Point::find(pol.id1);
        Point* s2 = Point::find(pol.id2);
        Point* s3 = Point::find(pol.id3);

        os << "Poligon[";
        if (s1) os << *s1; else os << "deleted/not found";
        os << " <-> ";
        if (s2) os << *s2; else os << "deleted/not found";
        os << " <-> ";
        if (s3) os << *s3; else os << "deleted/not found";
        os << "]";
        return os;
    }
}