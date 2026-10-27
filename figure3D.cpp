#include<iostream>
#include<cmath>
#include<map>

namespace figure{
struct Position
{
	int x = 0, y = 0, z = 0;

	friend std::ostream& operator<<(std::ostream& os, const Position& p) {
		return os << "pos(" << p.x << ", " << p.y << ", " << p.z << ")";
	}
	friend std::istream& operator>>(std::istream& is, Position& p) {
		return is >> p.x >> p.y >> p.z;
	}
	friend Position operator+(Position h, const Position& p) {
		h.x += p.x;h.y += p.y;h.z += p.z;
		return h;
	}
	friend Position operator-(Position h, const Position& p) {
		h.x -= p.x;h.y -= p.y;h.z -= p.z;
		return h;
	}
};

struct Point
{
private:
	inline static long id_counter = 1;
	inline static std::map<long, Point*> registry;

	Position position;
	long ID;
public:
	Point() {
		ID = id_counter++;
		registry[ID] = this;
	}

	~Point() {
		registry.erase(ID);
	}

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

	static Point* find(long target_id) {
		auto it = registry.find(target_id);
		if (it != registry.end()) {
			return it->second;
		}
		return nullptr;
	}

	friend std::ostream& operator<<(std::ostream& os, const Point& p) {
		return os << "point(" << p.ID << ", " << p.position << ")";
	}
	friend std::istream& operator>>(std::istream& is, Point& p) {
		return is >> p.position;
	}
};

class Line
{
private:
	Point* p1 = nullptr;
	Point* p2 = nullptr;

public:

	Line() = default;

	Line(Point* a, Point* b) : p1(a), p2(b) {}

	double getLength() const {
		if (!p1 || !p2) {
			return 0.0;
		}

		double dx = p2->getX() - p1->getX();
		double dy = p2->getY() - p1->getY();
		double dz = p2->getZ() - p1->getZ();

		return std::sqrt(dx * dx + dy * dy + dz * dz);
	}

	friend std::istream& operator>>(std::istream& is, Line& line) {
		long id1 = 0, id2 = 0;
		is >> id1 >> id2;

		line.p1 = Point::find(id1);line.p2 = Point::find(id2);
		if (!line.p1 || !line.p2) {
			std::clog << "[Warning]: One of the line points was not found in the registry!\n";
		}
		return is;
	}
};

}

int main(void)
{
	figure::Point point1;
	figure::Point point2;
	figure::Point point3;
	std::cin >> point1 >> point2 >> point3;
	std::cout << point1 << point2 << point3;
	
	return 0;
}