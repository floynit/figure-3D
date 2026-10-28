#include<iostream>
#include<memory>
#include<cmath>
#include<map>
namespace figure {
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
			h.x += p.x; h.y += p.y; h.z += p.z;
			return h;
		}
		friend Position operator-(Position h, const Position& p) {
			h.x -= p.x; h.y -= p.y; h.z -= p.z;
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
		long id1 = 0;
		long id2 = 0;

	public:
		Line() = default;
		Line(long a_id, long b_id) : id1(a_id), id2(b_id) {}

		double getLength() const {
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

		friend std::istream& operator>>(std::istream& is, Line& line) {
			is >> line.id1 >> line.id2;

			if (!Point::find(line.id1) || !Point::find(line.id2)) {
				std::clog << "[Warning]: One of the line points was not found in the registry!\n";
			}
			return is;
		}

		friend std::ostream& operator<<(std::ostream& os, const Line& line) {
			Point* s1 = Point::find(line.id1);
			Point* s2 = Point::find(line.id2);

			os << "Line[";
			if (s1) os << *s1; else os << "deleted/not found";
			os << " <-> ";
			if (s2) os << *s2; else os << "deleted/not found";
			os << "] (length: " << line.getLength() << ")";
			return os;
		}
	};
}