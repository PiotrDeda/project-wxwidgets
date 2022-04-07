#include "ProjectMainFrame.h"

#define REGISTER(NAME, COMMAND) m_console->registerCommand(Command(#NAME, std::bind(&ProjectMainFrame::COMMAND, this, std::placeholders::_1)));

ProjectMainFrame::ProjectMainFrame(wxWindow* parent) : MainFrame(parent)
{
	m_console = new Console(_consoleOutput);
	m_shapeContainer = new ShapeContainer(_shapeList);

	// Komendy podstawowe
	REGISTER(set_line_color, SetLineColor);
	REGISTER(line, CreateLine);
	REGISTER(box, CreateBox);
	REGISTER(sphere, CreateSphere);
	REGISTER(cone, CreateCone);
	REGISTER(cylinder, CreateCylinder);
	REGISTER(delete, Delete);
	REGISTER(clear_all, ClearAll);
	REGISTER(move, Move);
	REGISTER(rotate, Rotate);
	REGISTER(save, Save);
	REGISTER(load, Load);

	// Komendy rozszerzone
	REGISTER(render_to_file, RenderToFile);
	REGISTER(set_fill_style, SetFillStyle);
	REGISTER(set_fill_color, SetFillColor);
	REGISTER(view, View);
	REGISTER(set_view_range, SetViewRange);
	REGISTER(camera_look_at, CameraLookAt);
	REGISTER(camera_at, CameraAt);
	REGISTER(camera_fov, CameraFov);
	REGISTER(touch, Touch);

	// Komendy debugowania
	REGISTER(debug_scale, DebugScale);
	REGISTER(debug_culling, DebugCulling);
}

#undef REGISTER


void ProjectMainFrame::MainFrameOnClose(wxCloseEvent& event)
{
	Destroy();
}

void ProjectMainFrame::_promptFieldOnTextEnter(wxCommandEvent& event)
{
	m_console->sendCommand((std::string)_promptField->GetValue());
	_promptField->Clear();
}

void ProjectMainFrame::Unimplemented()
{
	m_console->print("Komenda dostepna jest tylko w pelnej wersji programu\nProsimy zakupic pelna wersje na www.wilcze-majty-software.pl", wxYELLOW);
}

// ##############################
// ##### KOMENDY PODSTAWOWE #####
// ##############################

void ProjectMainFrame::SetLineColor(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "triplet" });
	if (args.size() != 1)
	{
		m_console->print("Correct format is \"set_line_color (r,g,b)\"", wxRED);
		return;
	}
	Triplet rgb = std::any_cast<Triplet>(args[0]);

	if (rgb.value1 < 0 || rgb.value1 > 255 || rgb.value2 < 0 || rgb.value2 > 255 || rgb.value3 < 0 || rgb.value3 > 255)
	{
		m_console->print("RGB values need to be between 0 and 255", wxRED);
		return;
	}

	Presentation::setLineColor(wxColor(rgb.value1, rgb.value2, rgb.value3));
	m_console->print("Set line color to (" + std::to_string((unsigned char)rgb.value1) + "," + std::to_string((unsigned char)rgb.value2) + "," + std::to_string((unsigned char)rgb.value3) + ")");

	Draw();
}

void ProjectMainFrame::CreateLine(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "triplet", "triplet" });
	if (args.size() != 2)
	{
		m_console->print("Correct format is \"line (x1,y1,z1) (x2,y2,z2)\"", wxRED);
		return;
	}
	Triplet point1 = std::any_cast<Triplet>(args[0]);
	Triplet point2 = std::any_cast<Triplet>(args[1]);

	Line* line = new Line(m_shapeContainer->getNextId(), point1.value1, point1.value2, point1.value3, point2.value1, point2.value2, point2.value3);
	m_shapeContainer->addShape(line);
	m_console->print("Created line (id " + std::to_string(line->getId()) + ")");

	Draw();
}

void ProjectMainFrame::CreateBox(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "triplet", "triplet" });
	if (args.size() != 2)
	{
		m_console->print("Correct format is \"box (x1,y1,z1) (x2,y2,z2)\"", wxRED);
		return;
	}
	Triplet point1 = std::any_cast<Triplet>(args[0]);
	Triplet point2 = std::any_cast<Triplet>(args[1]);

	Box* box = new Box(m_shapeContainer->getNextId(), point1.value1, point1.value2, point1.value3, point2.value1, point2.value2, point2.value3);
	m_shapeContainer->addShape(box);
	m_console->print("Created box (id " + std::to_string(box->getId()) + ")");

	Draw();
}

void ProjectMainFrame::CreateSphere(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "triplet", "number", "pair" });
	if (args.size() != 3)
	{
		m_console->print("Correct format is \"sphere (x,y,z) r (n,m)\"", wxRED);
		return;
	}
	Triplet center = std::any_cast<Triplet>(args[0]);
	double radius = std::any_cast<Number>(args[1]).value;
	Pair mesh = std::any_cast<Pair>(args[2]);

	if (radius < 0)
	{
		m_console->print("Radius needs to be a positive value", wxRED);
		return;
	}

	if (mesh.value1 < 0 || mesh.value2 < 0)
	{
		m_console->print("Meridians and parallels need to be positive numbers", wxRED);
		return;
	}

	Sphere* sphere = new Sphere(m_shapeContainer->getNextId(), center.value1, center.value2, center.value3, radius, mesh.value1, mesh.value2);
	m_shapeContainer->addShape(sphere);
	m_console->print("Created sphere (id " + std::to_string(sphere->getId()) + ")");

	Draw();
}

void ProjectMainFrame::CreateCone(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "triplet", "number", "triplet", "number", "number" });
	if (args.size() != 5)
	{
		m_console->print("Correct format is \"cone (x1,y1,z1) r1 (x2,y2,z2) r2 n\"", wxRED);
		return;
	}
	Triplet center1 = std::any_cast<Triplet>(args[0]);
	double radius1 = std::any_cast<Number>(args[1]).value;
	Triplet center2 = std::any_cast<Triplet>(args[2]);
	double radius2 = std::any_cast<Number>(args[3]).value;
	double quads = std::any_cast<Number>(args[4]).value;

	if (radius1 < 0 || radius2 < 0)
	{
		m_console->print("Radii need to be a positive value", wxRED);
		return;
	}

	if (quads < 0)
	{
		m_console->print("n needs to be a positive number", wxRED);
		return;
	}

	Cone* cone = new Cone(m_shapeContainer->getNextId(), center1.value1, center1.value2, center1.value3, radius1, center2.value1, center2.value2, center2.value3, radius2, quads);
	m_shapeContainer->addShape(cone);
	m_console->print("Created cone (id " + std::to_string(cone->getId()) + ")");

	Draw();
}

void ProjectMainFrame::CreateCylinder(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "triplet", "triplet", "number", "number" });
	if (args.size() != 4)
	{
		m_console->print("Correct format is \"cylinder (x1,y1,z1) (x2,y2,z2) r n\"", wxRED);
		return;
	}
	Triplet center1 = std::any_cast<Triplet>(args[0]);
	Triplet center2 = std::any_cast<Triplet>(args[1]);
	double radius = std::any_cast<Number>(args[2]).value;
	double quads = std::any_cast<Number>(args[3]).value;

	if (radius < 0)
	{
		m_console->print("Radius needs to be positive values", wxRED);
		return;
	}

	if (quads < 0)
	{
		m_console->print("n needs to be a positive number", wxRED);
		return;
	}

	Cylinder* cylinder = new Cylinder(m_shapeContainer->getNextId(), center1.value1, center1.value2, center1.value3, center2.value1, center2.value2, center2.value3, radius, quads);
	m_shapeContainer->addShape(cylinder);
	m_console->print("Created cylinder (id " + std::to_string(cylinder->getId()) + ")");

	Draw();
}

void ProjectMainFrame::Delete(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "number" });
	if (args.size() != 1)
	{
		m_console->print("Correct format is \"delete id\"", wxRED);
		return;
	}
	unsigned id = std::any_cast<Number>(args[0]).value;

	if (m_shapeContainer->deleteShape(id))
		m_console->print("Deleted shape (id " + std::to_string(id) + ")");
	else
		m_console->print("Id " + std::to_string(id) + " doesn't exist!");

	Draw();
}

void ProjectMainFrame::ClearAll(std::vector<std::string> arguments)
{
	if (arguments.size() > 1)
		m_console->print("0 arguments expected, got " + std::to_string(arguments.size() - 1) + "! Command will not be executed\nCorrect format is \"clear_all\"", wxRED);

	m_shapeContainer->deleteAllShapes();
	m_console->print("Deleted all shapes");

	Draw();
}

void ProjectMainFrame::Move(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "number", "triplet" });
	if (args.size() != 2)
	{
		m_console->print("Correct format is \"move id (x,y,z)\"", wxRED);
		return;
	}
	unsigned id = std::any_cast<Number>(args[0]).value;
	Triplet vector = std::any_cast<Triplet>(args[1]);

	m_shapeContainer->moveShape(id, vector.value1, vector.value2, vector.value3);
	m_console->print("Moved shape (id " + std::to_string(id) + ")");

	Draw();
}

void ProjectMainFrame::Rotate(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "number", "triplet", "triplet" });
	if (args.size() != 3)
	{
		m_console->print("Correct format is \"rotate id (x,y,z) (a,b,g)\"", wxRED);
		return;
	}
	unsigned id = std::any_cast<Number>(args[0]).value;
	Triplet vector = std::any_cast<Triplet>(args[1]);
	Triplet rotation = std::any_cast<Triplet>(args[2]);

	m_shapeContainer->rotateShape(id, vector.value1, vector.value2, vector.value3, rotation.value1, rotation.value2, rotation.value3);
	m_console->print("Rotated shape (id " + std::to_string(id) + ")");

	Draw();
}

void ProjectMainFrame::Save(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "name" });
	if (args.size() != 1)
	{
		m_console->print("Correct format is \"save name\"", wxRED);
		return;
	}
	std::string filename = std::any_cast<Name>(args[0]).value;

	m_console->print("Saving to file " + filename + "...");
	try
	{
		m_shapeContainer->saveToFile(filename);
	}
	catch (std::runtime_error const& e)
	{
		m_console->print(e.what(), wxRED);
		return;
	}
	m_console->print("Succesfully saved!");

	Draw();
}

void ProjectMainFrame::Load(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "name" });
	if (args.size() != 1)
	{
		m_console->print("Correct format is \"load name\"", wxRED);
		return;
	}
	std::string filename = std::any_cast<Name>(args[0]).value;

	m_console->print("Loading from file " + filename);
	try
	{
		m_shapeContainer->loadFromFile(filename);
	}
	catch (std::runtime_error const& e)
	{
		m_console->print(e.what(), wxRED);
		return;
	}
	catch (...)
	{
		m_console->print("Error loading from file! File may be corrupted or not a data file", wxRED);
		return;
	}
	m_console->print("Succesfully loaded!");

	Draw();
}

// ###############################
// ##### KOMENDY ROZSZERZONE #####
// ###############################

void ProjectMainFrame::RenderToFile(std::vector<std::string> arguments)
{
	Unimplemented();
}

void ProjectMainFrame::SetFillStyle(std::vector<std::string> arguments)
{
	Unimplemented();
}

void ProjectMainFrame::SetFillColor(std::vector<std::string> arguments)
{
	Unimplemented();
}

void ProjectMainFrame::View(std::vector<std::string> arguments)
{
	Unimplemented();
}

void ProjectMainFrame::SetViewRange(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "name", "number" });
	if (args.size() != 2)
	{
		m_console->print("Correct format is \"set_view_range right | front | top r\"", wxRED);
		return;
	}
	std::string mode = std::any_cast<Name>(args[0]).value;
	double range = std::any_cast<Number>(args[1]).value;

	if (mode == "right")
	{
		Presentation::setRightRange(range);
		m_console->print("Set right range to " + std::to_string(range));
	}
	else if (mode == "front")
	{
		Presentation::setFrontRange(range);
		m_console->print("Set front range to " + std::to_string(range));
	}
	else if (mode == "top")
	{
		Presentation::setTopRange(range);
		m_console->print("Set top range to " + std::to_string(range));
	}
	else
	{
		m_console->print("Incorrect argument 1 (\"" + mode + "\"). \"right\", \"front\" or \"top\" expected", wxRED);
		m_console->print("Correct format is \"set_view_range right | front | top r\"", wxRED);
		return;
	}

	Draw();
}

void ProjectMainFrame::CameraLookAt(std::vector<std::string> arguments)
{
	Unimplemented();
}

void ProjectMainFrame::CameraAt(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "triplet" });
	if (args.size() != 1)
	{
		m_console->print("Correct format is \"camera_at (x,y,z)\"", wxRED);
		return;
	}
	Triplet point = std::any_cast<Triplet>(args[0]);

	Presentation::setCamera(point.value1, point.value2, point.value3);
	m_console->print("Kamera ustawiona w pozycji (" + std::to_string(point.value1) + "," + std::to_string(point.value2) + "," + std::to_string(point.value3) + ")");

	Draw();
}

void ProjectMainFrame::CameraFov(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "number" });
	if (args.size() != 1)
	{
		m_console->print("Correct format is \"camera_fov alfa\"", wxRED);
		return;
	}
	double alpha = std::any_cast<Number>(args[0]).value;

	//TODO: wartoœæ w zasiêgu
	Presentation::setFov(alpha);
	m_console->print("FOV ustawiony na " + std::to_string(alpha));

	Draw();
}

void ProjectMainFrame::Touch(std::vector<std::string> arguments)
{
	Unimplemented();
}

// ###############################
// ##### KOMENDY DEBUGOWANIA #####
// ###############################

void ProjectMainFrame::DebugScale(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "number" });
	if (args.size() != 1)
	{
		m_console->print("Correct format is \"debug_scale s\"", wxRED);
		return;
	}
	double scale = std::any_cast<Number>(args[0]).value;

	Presentation::debug_scale = scale;
	m_console->print("Set scale to " + std::to_string(scale), wxYELLOW);

	Draw();
}

void ProjectMainFrame::DebugCulling(std::vector<std::string> arguments)
{
	std::vector<std::any> args = m_console->validateArguments(arguments, { "name" });
	if (args.size() != 1)
	{
		m_console->print("Correct format is \"debug_culling true | false\"", wxRED);
		return;
	}
	std::string value = std::any_cast<Name>(args[0]).value;

	if (value == "true")
		Presentation::debug_enableCulling = true;
	else if (value == "false")
		Presentation::debug_enableCulling = false;
	m_console->print("Set culling to " + value, wxYELLOW);

	Draw();
}

// ##############################
// #####	 RYSOWANIE 		#####
// ##############################

void ProjectMainFrame::Draw()
{
	wxClientDC topDC(_viewTop);
	wxClientDC frontDC(_viewFront);
	wxClientDC rightDC(_viewRight);
	wxClientDC perspectiveDC(_viewPerspective);

	Presentation::drawTop(topDC, m_shapeContainer->getShapes());
	Presentation::drawFront(frontDC, m_shapeContainer->getShapes());
	Presentation::drawRight(rightDC, m_shapeContainer->getShapes());
	Presentation::drawPerspective(perspectiveDC, m_shapeContainer->getShapes());
}

void ProjectMainFrame::MainFrameOnPaint(wxPaintEvent& event)
{
	Draw();
}