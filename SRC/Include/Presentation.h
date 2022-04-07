#pragma once

#include <wx/wx.h>
#include "Segment.h"
#include "Shape.h"

class Shape;

/**
 * @brief Klasa wirtualna reprezentująca kształt, jej potomkami są konkretne bryły.
 */
class Presentation
{
protected:
	static wxColor m_lineColor, m_fillingColor;
	static double m_topRange, m_frontRange, m_rightRange;
	static double m_topScale, m_frontScale, m_rightScale;
	static double m_cameraX, m_cameraY, m_cameraZ;
	static double m_fov;

public:
	static double debug_scale;
	static bool debug_enableCulling;

	/**
	 * @brief Rysuje widok z góry, widoczne osie to X i Z, kamera przesuwa się wzdłuż osi Y.
	 *
	 * @param DC Wskaźnik na powierzchnię po której będą rysowane bryły.
	 * @param shapes Kontener brył do narysowania.
	 */
	static void drawTop(wxClientDC& DC, std::vector<Shape*> shapes);

	/**
	 * @brief Rysuje widok od przodu, widoczne osie to X i Y, kamera przesuwa się wzdłuż osi Z.
	 *
	 * @param DC Wskaźnik na powierzchnię po której będą rysowane bryły.
	 * @param shapes Kontener brył do narysowania.
	 */
	static void drawFront(wxClientDC& DC, std::vector<Shape*> shapes);

	/**
	 * @brief Rysuje widok z prawej strony, widoczne osie to Y i Z, kamera przesuwa się wzdłuż osi X.
	 *
	 * @param DC Wskaźnik na powierzchnię po której będą rysowane bryły.
	 * @param shapes Kontener brył do narysowania.
	 */
	static void drawRight(wxClientDC& DC, std::vector<Shape*> shapes);

	/**
	 * @brief Rysuje widok perspektywiczny.
	 *
	 * @param DC Wskaźnik na powierzchnię po której będą rysowane bryły.
	 * @param shapes Kontener brył do narysowania.
	 */
	static void drawPerspective(wxClientDC& DC, std::vector<Shape*> shapes);

	/**
	 * @brief Zmienia kolor linii.
	 *
	 * @param color Kolor linii.
	 */
	static void setLineColor(wxColor color) { m_lineColor = color; }

	/**
	 * @brief Zmienia kolor wypełnienia (niezaimplementowana).
	 *
	 * @param color Kolor wypełnienia.
	 */
	static void setFillingColor(wxColor color) { m_fillingColor = color; }

	/**
	 * @brief Ustawia punkt z którego patrzy się górna kamera na (0, \p range, 0).
	 *
	 * @param range Współrzędna y punktu.
	 */
	static void setTopRange(double range) { m_topRange = range; m_topScale = 1 / range; }

	/**
	 * @brief Ustawia punkt z którego patrzy się przednia kamera na (0,0,\p range).
	 *
	 * @param range Współrzędna z punktu.
	 */
	static void setFrontRange(double range) { m_frontRange = range; m_frontScale = 1 / range; }

	/**
	 * @brief Ustawia punkt z którego patrzy się prawa kamera na (\p range,0,0).
	 *
	 * @param range Współrzędna x punktu
	 */
	static void setRightRange(double range) { m_rightRange = range; m_rightScale = 1 / range; }

	/**
	 * @brief Ustawia położenie kamery perspektywicznej.
	 *
	 * @param x Współrzędna x.
	 * @param y Współrzędna y.
	 * @param z Współrzędna z.
	 */
	static void setCamera(double x, double y, double z) { m_cameraX = x; m_cameraY = y; m_cameraZ = z; }

	/**
	 * @brief Ustawia pole widzenia kamery perspektywicznej.
	 *
	 * @param fov Pole widzenia.
	 */
	static void setFov(double fov) { m_fov = fov; }
	
	/**
	 * @brief Zwraca kolor linii.
	 *
	 * @return Kolor linii.
	 */
	static wxColor getLineColor() { return m_lineColor; }

	/**
	 * @brief Zwraca kolor wypełnienia (niezaimplementowana).
	 *
	 * @return Kolor wypełnienia.
	 */
	static wxColor getFillingColor() { return m_fillingColor; }

	/**
	 * @brief Zwraca punkt patrzenia górnej kamery.
	 *
	 * @return Punkt patrzenia górnej kamery.
	 */
	static double getTopRange() { return m_topRange; }

	/**
	 * @brief Zwraca punkt patrzenia przedniej kamery.
	 *
	 * @return Punkt patrzenia przedniej kamery.
	 */
	static double getFrontRange() { return m_frontRange; }

	/**
	 * @brief Zwraca punkt patrzenia prawej kamery.
	 *
	 * @return Punkt patrzenia prawej kamery.
	 */
	static double getRightRange() { return m_rightRange; }

	/**
	 * @brief Zwraca współrzędną x kamery perspektywicznej.
	 *
	 * @return Współrzędna x.
	 */
	static double getCameraX() { return m_cameraX; }

	/**
	 * @brief Zwraca współrzędną y kamery perspektywicznej.
	 *
	 * @return Współrzędna y.
	 */
	static double getCameraY() { return m_cameraY; }

	/**
	 * @brief Zwraca współrzędną z kamery perspektywicznej.
	 *
	 * @return Współrzędna z.
	 */
	static double getCameraZ() { return m_cameraZ; }

	/**
	 * @brief Zwraca pole widzenia kamery perspektywicznej.
	 *
	 * @return Pole widzenia.
	 */
	static double getFov() { return m_fov; }
};