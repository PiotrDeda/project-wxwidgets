#include "Shape.h"

/* ------------ Shape ----------- */

// Przesuwa poczatek i koniec kazdego segmentu o zadane przez argumenty wywolania wartosci
void Shape::move(double x, double y, double z) {
	for (auto& elem : m_data) {
		elem.begin.x += x;
		elem.begin.y += y;
		elem.begin.z += z;

		elem.end.x += x;
		elem.end.y += y;
		elem.end.z += z;
	}
}

void Shape::rotate(double x, double y, double z, double a, double b, double g) {
	a *= M_PI / 180;
	b *= M_PI / 180;
	g *= M_PI / 180;

	move(-x, -y, -z);

	for (auto& elem : m_data) {
		double obeginx = elem.begin.x;
		double obeginy = elem.begin.y;
		double obeginz = elem.begin.z;
		double oendx = elem.end.x;
		double oendy = elem.end.y;
		double oendz = elem.end.z;

		// Rotacja wokol z:
		elem.begin.x = obeginx * cos(g) - obeginy * sin(g);
		elem.begin.y = obeginx * sin(g) + obeginy * cos(g);
		elem.end.x = oendx * cos(g) - oendy * sin(g);
		elem.end.y = oendx * sin(g) + oendy * cos(g);

		obeginx = elem.begin.x;
		obeginy = elem.begin.y;
		obeginz = elem.begin.z;
		oendx = elem.end.x;
		oendy = elem.end.y;
		oendz = elem.end.z;

		// Rotacja wokol y:
		elem.begin.x = obeginx * cos(b) + obeginz * sin(b);
		elem.begin.z = -obeginx * sin(b) + obeginz * cos(b);
		elem.end.x = oendx * cos(b) + oendz * sin(b);
		elem.end.z = -oendx * sin(b) + oendz * cos(b);

		obeginx = elem.begin.x;
		obeginy = elem.begin.y;
		obeginz = elem.begin.z;
		oendx = elem.end.x;
		oendy = elem.end.y;
		oendz = elem.end.z;

		// Rotacja wokol x:
		elem.begin.y = obeginy * cos(a) - obeginz * sin(a);
		elem.begin.z = obeginy * sin(a) + obeginz * cos(a);
		elem.end.y = oendy * cos(a) - oendz * sin(a);
		elem.end.z = oendy * sin(a) + oendz * cos(a);
	}

	move(x, y, z);
}

std::vector<Segment> Shape::findCircle(double r)
{
	std::vector<Segment> segments;

	double x = 0, y = r;

	double prevx1 = y, prevy1 = x;
	double prevx2 = -y, prevy2 = x;
	double prevx3 = y, prevy3 = -x;
	double prevx4 = -y, prevy4 = -x;
	double prevx5 = x, prevy5 = y;
	double prevx6 = -x, prevy6 = y;
	double prevx7 = x, prevy7 = -y;
	double prevx8 = -x, prevy8 = -y;

	double d = 1.2 - r;
	while (true)
	{
		x++;
		if (d < 0)
			d += 2 * x + 1;
		else
		{
			d += 2 * x - 2 * y + 1;
			y--;
		}

		if (y < x)
			break;

		segments.push_back(Segment(Point(prevx1, prevy1, 0), Point(y, x, 0)));
		segments.push_back(Segment(Point(prevx2, prevy2, 0), Point(-y, x, 0)));
		segments.push_back(Segment(Point(prevx3, prevy3, 0), Point(y, -x, 0)));
		segments.push_back(Segment(Point(prevx4, prevy4, 0), Point(-y, -x, 0)));
		segments.push_back(Segment(Point(prevx5, prevy5, 0), Point(x, y, 0)));
		segments.push_back(Segment(Point(prevx6, prevy6, 0), Point(-x, y, 0)));
		segments.push_back(Segment(Point(prevx7, prevy7, 0), Point(x, -y, 0)));
		segments.push_back(Segment(Point(prevx8, prevy8, 0), Point(-x, -y, 0)));
		prevx1 = y, prevy1 = x;
		prevx2 = -y, prevy2 = x;
		prevx3 = y, prevy3 = -x;
		prevx4 = -y, prevy4 = -x;
		prevx5 = x, prevy5 = y;
		prevx6 = -x, prevy6 = y;
		prevx7 = x, prevy7 = -y;
		prevx8 = -x, prevy8 = -y;
	}

	segments.push_back(Segment(Point(prevx5, prevy5, 0), Point(x, y, 0)));
	segments.push_back(Segment(Point(prevx6, prevy6, 0), Point(-x, y, 0)));
	segments.push_back(Segment(Point(prevx7, prevy7, 0), Point(x, -y, 0)));
	segments.push_back(Segment(Point(prevx8, prevy8, 0), Point(-x, -y, 0)));

	return segments;
}

/* ------------ Line ----------- */

Line::Line(unsigned id, double x1, double y1, double z1, double x2, double y2, double z2) : Shape(id)
{
	m_data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2)));
}

std::string Line::toString()
{
	std::ostringstream os;
	os << m_id << " line (" << m_data[0].begin.x << "," << m_data[0].begin.y << "," << m_data[0].begin.z << ") (" << m_data[0].end.x << "," << m_data[0].end.y << "," << m_data[0].end.z << ")";
	return os.str();
}

/* ------------ Box ----------- */

Box::Box(unsigned id, double x1, double y1, double z1, double x2, double y2, double z2) : Shape(id)
{
	Point point1 = Point(x1, y1, z1);
	Point point2 = Point(x2, y2, z2);

	//odcinki wychodzace z punktu 1
	m_data.push_back(Segment(point1, Point(point1.x, point1.y, point2.z)));
	m_data.push_back(Segment(point1, Point(point1.x, point2.y, point1.z)));
	m_data.push_back(Segment(point1, Point(point2.x, point1.y, point1.z)));

	//odcinki wychodzace z punktu 2
	m_data.push_back(Segment(point2, Point(point2.x, point2.y, point1.z)));
	m_data.push_back(Segment(point2, Point(point1.x, point2.y, point2.z)));
	m_data.push_back(Segment(point2, Point(point2.x, point1.y, point2.z)));

	//krawedzie poziome
	m_data.push_back(Segment(Point(point2.x, point1.y, point2.z), Point(point2.x, point1.y, point1.z)));
	m_data.push_back(Segment(Point(point1.x, point2.y, point1.z), Point(point1.x, point2.y, point2.z)));
	m_data.push_back(Segment(Point(point1.x, point2.y, point1.z), Point(point2.x, point2.y, point1.z)));
	m_data.push_back(Segment(Point(point1.x, point1.y, point2.z), Point(point2.x, point1.y, point2.z)));

	//krawedzie pionowe
	m_data.push_back(Segment(Point(point1.x, point1.y, point2.z), Point(point1.x, point2.y, point2.z)));
	m_data.push_back(Segment(Point(point2.x, point2.y, point1.z), Point(point2.x, point1.y, point1.z)));

}

std::string Box::toString()
{
	std::ostringstream os;
	os << m_id << " box (" << m_data[0].begin.x << "," << m_data[0].begin.y << "," << m_data[0].begin.z << ") (" << m_data[3].begin.x << "," << m_data[3].begin.y << "," << m_data[3].begin.z << ")";
	return os.str();
}

/* ------------ Sphere ----------- */

Sphere::Sphere(unsigned id, double x, double y, double z, double r, double M, double N) :
	Shape(id), m_center(0, 0, 0), m_radius(r), m_meridians(M), m_parallels(N)
{
	std::vector< std::vector<Point>* > nodes;

	Point up(0, r, 0);
	Point down(0, -r, 0);
	int M1 = M + 2;
	for (int m = 0; m < M1; m++)
	{

		for (double n = 0; n < N; n++)
		{
			nodes.push_back(new std::vector<Point>);
			if (m == 0) {
				(nodes[0])->push_back(up);
			}
			else if (m == M1 - 1) {
				(nodes[M1 - 1])->push_back(down);
			}
			else {
				double x0 = r * sin(M_PI * m / M1) * cos(2.0 * M_PI * n / N);
				double y0 = r * cos(M_PI * m / M1);
				double z0 = r * sin(M_PI * m / M1) * sin(2.0 * M_PI * n / N);

				(nodes[m])->push_back(Point(x0, y0, z0));
			}

		}
	}

	for (int m = 1; m < M1; m++)
	{
		for (int n = 0; n < N; n++)
		{
			m_data.push_back(Segment((*(nodes[m - 1]))[n], (*(nodes[m]))[n]));
		}

		for (int n = 1; n < N; n++)
		{
			m_data.push_back(Segment((*(nodes[m]))[n - 1], (*(nodes[m]))[n]));

		}
		m_data.push_back(Segment((*(nodes[m]))[N - 1], (*(nodes[m]))[0]));
	}

	for (auto& elem : nodes) {
		delete elem;
	}

	move(x, y, z);
}

void Sphere::move(double x, double y, double z)
{
	Shape::move(x, y, z); std::vector<Point> points;
	m_center.x += x;
	m_center.y += y;
	m_center.z += z;
}

void Sphere::rotate(double x, double y, double z, double a, double b, double g)
{
	Shape::rotate(x, y, z, a, b, g);

	a *= M_PI / 180;
	b *= M_PI / 180;
	g *= M_PI / 180;

	m_center.x -= x;
	m_center.y -= y;
	m_center.z -= z;

	double obeginx = m_center.x;
	double obeginy = m_center.y;
	double obeginz = m_center.z;

	// Rotacja wokol z:
	m_center.x = obeginx * cos(g) - obeginy * sin(g);
	m_center.y = obeginx * sin(g) + obeginy * cos(g);

	obeginx = m_center.x;
	obeginy = m_center.y;
	obeginz = m_center.z;

	// Rotacja wokol y:
	m_center.x = obeginx * cos(b) + obeginz * sin(b);
	m_center.z = -obeginx * sin(b) + obeginz * cos(b);

	obeginx = m_center.x;
	obeginy = m_center.y;
	obeginz = m_center.z;

	// Rotacja wokol x:
	m_center.y = obeginy * cos(a) - obeginz * sin(a);
	m_center.z = obeginy * sin(a) + obeginz * cos(a);

	m_center.x += x;
	m_center.y += y;
	m_center.z += z;
}

std::string Sphere::toString()
{
	std::ostringstream os;
	os << m_id << " sphere (" << m_center.x << "," << m_center.y << "," << m_center.z << ") " << m_radius << " (" << m_meridians << "," << m_parallels << ")";
	return os.str();
}

/* ------------ Cone ----------- */

Cone::Cone(unsigned id, double x1, double y1, double z1, double r1, double x2, double y2, double z2, double r2, double n)
	: Shape(id), m_center1(x1, y1, z1), m_radius1(r1), m_center2(x2, y2, z2), m_radius2(r2), m_quads(n)
{
	std::vector<Segment> points1 = findCircle(n);
	std::vector<Segment> points2 = findCircle(n);

	double f1 = r1 / n;
	double f2 = r2 / n;
	double py, pz;
	for (auto& p : points1) {
		py = p.begin.y, pz = p.begin.z;
		p.begin.x = (p.begin.x * f1) + x1;
		p.begin.y = (pz * f1) + y1;
		p.begin.z = (py * f1) + z1;
		py = p.end.y, pz = p.end.z;
		p.end.x = (p.end.x * f1) + x1;
		p.end.y = (pz * f1) + y1;
		p.end.z = (py * f1) + z1;
	}

	for (auto& p : points2) {
		py = p.begin.y, pz = p.begin.z;
		p.begin.x = (p.begin.x * f2) + x2;
		p.begin.y = (pz * f2) + y2;
		p.begin.z = (py * f2) + z2;
		py = p.end.y, pz = p.end.z;
		p.end.x = (p.end.x * f2) + x2;
		p.end.y = (pz * f2) + y2;
		p.end.z = (py * f2) + z2;
	}

	for (auto& p : points1)
		m_data.push_back(p);
	for (auto& p : points2)
		m_data.push_back(p);

	for (int i = 0; i < points1.size(); i++) {
		m_data.push_back(Segment(points1[i].begin, points2[i].begin));
	}
}

void Cone::move(double x, double y, double z)
{
	Shape::move(x, y, z); std::vector<Point> points;
	m_center1.x += x;
	m_center1.y += y;
	m_center1.z += z;
	m_center2.x += x;
	m_center2.y += y;
	m_center2.z += z;
}

void Cone::rotate(double x, double y, double z, double a, double b, double g)
{
	Shape::rotate(x, y, z, a, b, g);

	a *= M_PI / 180;
	b *= M_PI / 180;
	g *= M_PI / 180;

	m_center1.x -= x;
	m_center1.y -= y;
	m_center1.z -= z;
	m_center2.x -= x;
	m_center2.y -= y;
	m_center2.z -= z;

	double obeginx = m_center1.x;
	double obeginy = m_center1.y;
	double obeginz = m_center1.z;
	double oendx = m_center2.x;
	double oendy = m_center2.y;
	double oendz = m_center2.z;

	// Rotacja wokol z:
	m_center1.x = obeginx * cos(g) - obeginy * sin(g);
	m_center1.y = obeginx * sin(g) + obeginy * cos(g);
	m_center2.x = oendx * cos(g) - oendy * sin(g);
	m_center2.y = oendx * sin(g) + oendy * cos(g);

	obeginx = m_center1.x;
	obeginy = m_center1.y;
	obeginz = m_center1.z;
	oendx = m_center2.x;
	oendy = m_center2.y;
	oendz = m_center2.z;

	// Rotacja wokol y:
	m_center1.x = obeginx * cos(b) + obeginz * sin(b);
	m_center1.z = -obeginx * sin(b) + obeginz * cos(b);
	m_center2.x = oendx * cos(b) + oendz * sin(b);
	m_center2.z = -oendx * sin(b) + oendz * cos(b);

	obeginx = m_center1.x;
	obeginy = m_center1.y;
	obeginz = m_center1.z;
	oendx = m_center2.x;
	oendy = m_center2.y;
	oendz = m_center2.z;

	// Rotacja wokol x:
	m_center1.y = obeginy * cos(a) - obeginz * sin(a);
	m_center1.z = obeginy * sin(a) + obeginz * cos(a);
	m_center2.y = oendy * cos(a) - oendz * sin(a);
	m_center2.z = oendy * sin(a) + oendz * cos(a);

	m_center1.x += x;
	m_center1.y += y;
	m_center1.z += z;
	m_center2.x += x;
	m_center2.y += y;
	m_center2.z += z;
}

std::string Cone::toString()
{
	std::ostringstream os;
	os << m_id << " cone (" << m_center1.x << "," << m_center1.y << "," << m_center1.z << ") " << m_radius1 << " (" << m_center2.x << "," << m_center2.y << "," << m_center2.z << ") " << m_radius2 << " " << m_quads;
	return os.str();
}

/* ------------ Cylinder ----------- */

Cylinder::Cylinder(unsigned id, double x1, double y1, double z1, double x2, double y2, double z2, double r, double n)
	: Shape(id), m_center1(x1, y1, z1), m_radius(r), m_center2(x2, y2, z2), m_quads(n)
{
	std::vector<Segment> points1 = findCircle(n);
	std::vector<Segment> points2 = findCircle(n);

	double f = r / n;
	double py, pz;
	for (auto& p : points1) {
		py = p.begin.y, pz = p.begin.z;
		p.begin.x = (p.begin.x * f) + x1;
		p.begin.y = (pz * f) + y1;
		p.begin.z = (py * f) + z1;
		py = p.end.y, pz = p.end.z;
		p.end.x = (p.end.x * f) + x1;
		p.end.y = (pz * f) + y1;
		p.end.z = (py * f) + z1;
	}

	for (auto& p : points2) {
		py = p.begin.y, pz = p.begin.z;
		p.begin.x = (p.begin.x * f) + x2;
		p.begin.y = (pz * f) + y2;
		p.begin.z = (py * f) + z2;
		py = p.end.y, pz = p.end.z;
		p.end.x = (p.end.x * f) + x2;
		p.end.y = (pz * f) + y2;
		p.end.z = (py * f) + z2;
	}

	for (auto& p : points1)
		m_data.push_back(p);
	for (auto& p : points2)
		m_data.push_back(p);

	for (int i = 0; i < points1.size(); i++) {
		m_data.push_back(Segment(points1[i].begin, points2[i].begin));
	}
}

void Cylinder::move(double x, double y, double z)
{
	Shape::move(x, y, z); std::vector<Point> points;
	m_center1.x += x;
	m_center1.y += y;
	m_center1.z += z;
	m_center2.x += x;
	m_center2.y += y;
	m_center2.z += z;
}

void Cylinder::rotate(double x, double y, double z, double a, double b, double g)
{
	Shape::rotate(x, y, z, a, b, g);

	a *= M_PI / 180;
	b *= M_PI / 180;
	g *= M_PI / 180;

	m_center1.x -= x;
	m_center1.y -= y;
	m_center1.z -= z;
	m_center2.x -= x;
	m_center2.y -= y;
	m_center2.z -= z;

	double obeginx = m_center1.x;
	double obeginy = m_center1.y;
	double obeginz = m_center1.z;
	double oendx = m_center2.x;
	double oendy = m_center2.y;
	double oendz = m_center2.z;

	// Rotacja wokol z:
	m_center1.x = obeginx * cos(g) - obeginy * sin(g);
	m_center1.y = obeginx * sin(g) + obeginy * cos(g);
	m_center2.x = oendx * cos(g) - oendy * sin(g);
	m_center2.y = oendx * sin(g) + oendy * cos(g);

	obeginx = m_center1.x;
	obeginy = m_center1.y;
	obeginz = m_center1.z;
	oendx = m_center2.x;
	oendy = m_center2.y;
	oendz = m_center2.z;

	// Rotacja wokol y:
	m_center1.x = obeginx * cos(b) + obeginz * sin(b);
	m_center1.z = -obeginx * sin(b) + obeginz * cos(b);
	m_center2.x = oendx * cos(b) + oendz * sin(b);
	m_center2.z = -oendx * sin(b) + oendz * cos(b);

	obeginx = m_center1.x;
	obeginy = m_center1.y;
	obeginz = m_center1.z;
	oendx = m_center2.x;
	oendy = m_center2.y;
	oendz = m_center2.z;

	// Rotacja wokol x:
	m_center1.y = obeginy * cos(a) - obeginz * sin(a);
	m_center1.z = obeginy * sin(a) + obeginz * cos(a);
	m_center2.y = oendy * cos(a) - oendz * sin(a);
	m_center2.z = oendy * sin(a) + oendz * cos(a);

	m_center1.x += x;
	m_center1.y += y;
	m_center1.z += z;
	m_center2.x += x;
	m_center2.y += y;
	m_center2.z += z;
}

std::string Cylinder::toString()
{
	std::ostringstream os;
	os << m_id << " cylinder (" << m_center1.x << "," << m_center1.y << "," << m_center1.z << ") (" << m_center2.x << "," << m_center2.y << "," << m_center2.z << ") " << m_radius << " " << m_quads;
	return os.str();
}
