#include "ShapeContainer.h"

void ShapeContainer::addShape(Shape* shape) {
	m_shapes.push_back(shape);
	refreshList();
}

bool ShapeContainer::deleteShape(unsigned id)
{
	bool removed = false;
	for (auto i : m_shapes)
		if (i->getId() == id)
			removed = true;

	m_shapes.erase(std::remove_if(m_shapes.begin(), m_shapes.end(), [id](Shape* shape) { return shape->getId() == id; }), m_shapes.end());
	refreshList();
	
	if (removed)
		return true;
	return false;
}

void ShapeContainer::deleteAllShapes()
{
	m_shapes.clear();
	m_nextId = 1;
	refreshList();
}

void ShapeContainer::moveShape(unsigned id, double x, double y, double z)
{
	for (auto shape : m_shapes)
		if (shape->getId() == id)
			shape->move(x, y, z);
	refreshList();
}

void ShapeContainer::rotateShape(unsigned id, double x, double y, double z, double a, double b, double g)
{
	for (auto shape : m_shapes)
		if (shape->getId() == id)
			shape->rotate(x, y, z, a, b, g);
	refreshList();
}

void ShapeContainer::refreshList()
{
	m_shapeList->SetValue("");
	for (auto shape : m_shapes)
		std::ostream(m_shapeList) << shape->toString() << "\n";
}

void ShapeContainer::saveToFile(std::string filename)
{
	std::ofstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("Error saving to file! Application may not have required permissions or file name contains special characters");

	file << "id " << m_nextId << "\n";
	file << "line_color " << Presentation::getLineColor().Red() << " " << Presentation::getLineColor().Green() << " " << Presentation::getLineColor().Blue() << "\n";
	file << "range_top " << Presentation::getTopRange() << "\n";
	file << "range_front " << Presentation::getFrontRange() << "\n";
	file << "range_right " << Presentation::getRightRange() << "\n";
	file << "camera " << Presentation::getCameraX() << " " << Presentation::getCameraY() << " " << Presentation::getCameraZ() << "\n";
	file << "fov " << Presentation::getFov() << "\n";
	for (auto shape : m_shapes)
	{
		file << shape->toString() << "\n";
		file << shape->getData().size() << "\n";
		for (const auto& i : shape->getData())
			file << i.begin.x << "\n" << i.begin.y << "\n" << i.begin.z << "\n" << i.end.x << "\n" << i.end.y << "\n" << i.end.z << "\n";
	}

	file.close();
}

void ShapeContainer::loadFromFile(std::string filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("Error loading from file! File does not exist or application doesn't have required permissions");

	std::vector<Shape*> temp;
	std::string line;
	while (std::getline(file, line))
	{
		std::vector<std::string> words{ std::istream_iterator<std::string>{std::istringstream(line)}, std::istream_iterator<std::string>{} };
		Shape* newShape;

		if (words[1] == "line")
		{
			std::vector<double> v = validateWords(words);
			newShape = new Line(v[0], v[1], v[2], v[3], v[4], v[5], v[6]);
		}
		else if (words[1] == "box")
		{
			std::vector<double> v = validateWords(words);
			newShape = new Box(v[0], v[1], v[2], v[3], v[4], v[5], v[6]);
		}
		else if (words[1] == "sphere")
		{
			std::vector<double> v = validateWords(words);
			newShape = new Sphere(v[0], v[1], v[2], v[3], v[4], v[5], v[6]);
		}
		else if (words[1] == "cone")
		{
			std::vector<double> v = validateWords(words);
			newShape = new Cone(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9]);
		}
		else if (words[1] == "cylinder")
		{
			std::vector<double> v = validateWords(words);
			newShape = new Cylinder(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);
		}
		else if (words[0] == "id")
		{
			m_nextId = std::stof(words[1]);
			continue;
		}
		else if (words[0] == "line_color")
		{
			Presentation::setLineColor(wxColor(words[1][0], words[2][0], words[3][0]));
			continue;
		}
		else if (words[0] == "range_top")
		{
			Presentation::setTopRange(std::stof(words[1]));
			continue;
		}
		else if (words[0] == "range_front")
		{
			Presentation::setFrontRange(std::stof(words[1]));
			continue;
		}
		else if (words[0] == "range_right")
		{
			Presentation::setRightRange(std::stof(words[1]));
			continue;
		}
		else if (words[0] == "camera")
		{
			Presentation::setCamera(std::stof(words[1]), std::stof(words[2]), std::stof(words[3]));
			continue;
		}
		else if (words[0] == "fov")
		{
			Presentation::setFov(std::stof(words[1]));
			continue;
		}
		else
		{
			throw std::runtime_error("Error loading from file! File may be corrupted or not a data file");
		}

		std::getline(file, line);
		int n = std::stof(line);
		std::vector<Segment>* data = newShape->getDataPtr();
		data->clear();
		double v[6];
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				std::getline(file, line);
				v[j] = std::stof(line);
			}
			data->push_back(Segment(Point(v[0], v[1], v[2]), Point(v[3], v[4], v[5])));
		}

		temp.push_back(newShape);
	}

	file.close();
	m_shapes = temp;
	refreshList();
}

std::vector<double> ShapeContainer::validateWords(std::vector<std::string> words)
{
	std::vector<double> v;
	v.push_back(std::stof(words[0]));
	if (words[1] == "line" || words[1] == "box")
	{
		std::string temp = words[2] + words[3];
		std::replace(temp.begin(), temp.end(), '(', ' ');
		std::replace(temp.begin(), temp.end(), ')', ' ');
		std::replace(temp.begin(), temp.end(), ',', ' ');
		std::vector<std::string> vals{ std::istream_iterator<std::string>{std::istringstream(temp)}, std::istream_iterator<std::string>{} };
		for (int i = 0; i < 6; i++)
			v.push_back(std::stof(vals[i]));
	}
	else if (words[1] == "sphere")
	{
		std::string temp = words[2] + words[3] + words[4];
		std::replace(temp.begin(), temp.end(), '(', ' ');
		std::replace(temp.begin(), temp.end(), ')', ' ');
		std::replace(temp.begin(), temp.end(), ',', ' ');
		std::vector<std::string> vals{ std::istream_iterator<std::string>{std::istringstream(temp)}, std::istream_iterator<std::string>{} };
		for (int i = 0; i < 6; i++)
			v.push_back(std::stof(vals[i]));
	}
	else if (words[1] == "cone")
	{
		std::string temp = words[2] + words[3] + words[4] + words[5] + " " + words[6];
		std::replace(temp.begin(), temp.end(), '(', ' ');
		std::replace(temp.begin(), temp.end(), ')', ' ');
		std::replace(temp.begin(), temp.end(), ',', ' ');
		std::vector<std::string> vals{ std::istream_iterator<std::string>{std::istringstream(temp)}, std::istream_iterator<std::string>{} };
		for (int i = 0; i < 9; i++)
			v.push_back(std::stof(vals[i]));
	}
	else if (words[1] == "cylinder")
	{
		std::string temp = words[2] + words[3] + words[4] + " " + words[5];
		std::replace(temp.begin(), temp.end(), '(', ' ');
		std::replace(temp.begin(), temp.end(), ')', ' ');
		std::replace(temp.begin(), temp.end(), ',', ' ');
		std::vector<std::string> vals{ std::istream_iterator<std::string>{std::istringstream(temp)}, std::istream_iterator<std::string>{} };
		for (int i = 0; i < 8; i++)
			v.push_back(std::stof(vals[i]));
	}

	return v;
}

unsigned ShapeContainer::getNextId()
{
	m_nextId++;
	return m_nextId - 1;
}

std::vector<Shape*> ShapeContainer::getShapes() {
	return m_shapes;
}
