#include "Presentation.h"

double Presentation::debug_scale = 10;
bool Presentation::debug_enableCulling = false;
wxColor Presentation::m_lineColor = *wxBLACK;
wxColor Presentation::m_fillingColor = *wxWHITE;
double Presentation::m_topRange = 1;
double Presentation::m_frontRange = 1;
double Presentation::m_rightRange = 1;
double Presentation::m_topScale = 1;
double Presentation::m_frontScale = 1;
double Presentation::m_rightScale = 1;
double Presentation::m_cameraX = 1;
double Presentation::m_cameraY = 1;
double Presentation::m_cameraZ = 1;
double Presentation::m_fov = 90;

void Presentation::drawTop(wxClientDC& DC, std::vector<Shape*> shapes)
{
	wxCoord w, h;
	DC.Clear();
	DC.GetSize(&w, &h);
	DC.SetDeviceOrigin(w / 2, h / 2);
	DC.SetAxisOrientation(true, false);
	DC.SetPen(wxPen(m_lineColor, 3));

	for (auto shape : shapes)
		for (auto& line : shape->getData())
			if (debug_enableCulling && line.begin.y > m_topRange && line.end.y > m_topRange)
				continue;
			else
				DC.DrawLine(wxPoint(debug_scale * m_topScale * line.begin.x, debug_scale * m_topScale * line.begin.z), wxPoint(debug_scale * m_topScale * line.end.x, debug_scale * m_topScale * line.end.z));
}

void Presentation::drawFront(wxClientDC& DC, std::vector<Shape*> shapes)
{
	wxCoord w, h;
	DC.Clear();
	DC.GetSize(&w, &h);
	DC.SetDeviceOrigin(w / 2, h / 2);
	DC.SetAxisOrientation(true, true);
	DC.SetPen(wxPen(m_lineColor, 3));

	for (auto shape : shapes)
		for (auto& line : shape->getData())
			if (debug_enableCulling && line.begin.z > m_frontRange && line.end.z > m_frontRange)
				continue;
			else
				DC.DrawLine(wxPoint(debug_scale * m_frontScale * line.begin.x, debug_scale * m_frontScale * line.begin.y), wxPoint(debug_scale * m_frontScale * line.end.x, debug_scale * m_frontScale * line.end.y));
}

void Presentation::drawRight(wxClientDC& DC, std::vector<Shape*> shapes)
{
	wxCoord w, h;
	DC.Clear();
	DC.GetSize(&w, &h);
	DC.SetDeviceOrigin(w / 2, h / 2);
	DC.SetAxisOrientation(false, true);
	DC.SetPen(wxPen(m_lineColor, 3));

	for (auto shape : shapes)
		for (auto& line : shape->getData())
			if (debug_enableCulling && line.begin.x > m_rightRange && line.end.x > m_rightRange)
				continue;
			else
				DC.DrawLine(wxPoint(debug_scale * m_frontScale * line.begin.z, debug_scale * m_frontScale * line.begin.y), wxPoint(debug_scale * m_frontScale * line.end.z, debug_scale * m_frontScale * line.end.y));
}

void Presentation::drawPerspective(wxClientDC& DC, std::vector<Shape*> shapes)
{
	wxCoord w, h;
	DC.Clear();
	DC.GetSize(&w, &h);
	DC.SetDeviceOrigin(w / 2, h / 2);
	DC.SetAxisOrientation(true, true);
	DC.SetPen(wxPen(m_lineColor, 3));

	double f1, f2, beginx, beginy, endx, endy;
	for (auto shape : shapes)
		for (auto& line : shape->getData())
		{
			if (debug_enableCulling && line.begin.z > m_cameraZ && line.end.z > m_cameraZ)
				continue;
			f1 = m_fov / (-debug_scale * m_cameraZ + line.begin.z);
			f2 = m_fov / (-debug_scale * m_cameraZ + line.end.z);
			beginx = line.begin.x * f1 - debug_scale * m_cameraX;
			beginy = line.begin.y * f1 - debug_scale * m_cameraY;
			endx = line.end.x * f2 - debug_scale * m_cameraX;
			endy = line.end.y * f2 - debug_scale * m_cameraY;
			DC.DrawLine(wxPoint(beginx, beginy), wxPoint(endx, endy));
		}
}
