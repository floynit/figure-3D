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

}