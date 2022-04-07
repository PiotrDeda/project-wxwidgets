#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <wx/wx.h>
#include "Presentation.h"
#include "Project.h"
#include "Segment.h"

/**
 * @brief Klasa wirtualna reprezentująca bryłę, przechowuje jej identyfikator i segmenty.
 */
class Shape
{
protected:
	unsigned m_id;
	std::vector<Segment> m_data;
public:
	/**
	 * @brief Konstruktor przypisujący identyfikator do bryły.
	 *
	 * @param id Identyfikator.
	 */
	Shape(unsigned id) : m_id(id) {}

	/**
	 * @brief Zwraca identyfikator bryły.
	 *
	 * @return Identyfikator.
	 */
	unsigned getId() { return m_id; }

	/**
	 * @brief Przesuwa bryłę o wektor [\p x, \p y, \p z].
	 *
	 * @param x Wartość x wektora przesunięcia.
	 * @param y Wartość y wektora przesunięcia.
	 * @param z Wartość z wektora przesunięcia.
	 */
	virtual void move(double x, double y, double z);

	/**
	 * @brief Obraca bryłę wokół punktu (\p x, \p y, \p z) o kąt \p a wzdłuż osi X, \p b wzdłuż osi Y i kąt \p g wzdłuż osi Z.
	 *
	 * @param x Współrzędna x środka obrotu.
	 * @param y Współrzędna y środka obrotu.
	 * @param z Współrzędna z środka obrotu.
	 * @param a Kąt obrotu wokół osi X.
	 * @param b Kąt obrotu wokół osi Y.
	 * @param g Kąt obrotu wokół osi Z.
	 */
	virtual void rotate(double x, double y, double z, double a, double b, double g);

	/**
	 * @brief Zwraca kontener segmentów.
	 *
	 * @return Kontener segmentów.
	 */
	std::vector<Segment> getData() { return m_data; }

	/**
	 * @brief Zwraca wskaźnik na wektor segmentów.
	 *
	 * @return Wskaźnik na wektor segmentów.
	 */
	std::vector<Segment>* getDataPtr() { return &m_data; }

	/**
	 * @brief Zwraca podstawowe informacje o bryle w formacie odpowiednim do wyświetlania na liście brył.
	 *
	 * @return Łańcuch znaków z informacjami o bryle.
	 */
	virtual std::string toString() { return std::to_string(m_id) + " unknown shape"; }

	/**
	 * @brief Funkcja realizująca \p <midpoint circle algorithm>.
	 *
	 * @param r Promień tworzonego okręgu.
	 *
	 * @return Segmenty utworzonego okręgu.
	 */
	static std::vector<Segment> findCircle(double r);
};

class Line : public Shape
{
public:
	/**
	 * @brief Tworzy odcinek.
	 *
	 * @param id Identyfikator.
	 * @param x1 Współrzędna x pierwszego końca.
	 * @param y1 Współrzędna y pierwszego końca.
	 * @param z1 Współrzędna z pierwszego końca.
	 * @param x2 Współrzędna x drugiego końca.
	 * @param y2 Współrzędna y drugiego końca.
	 * @param z2 Współrzędna z drugiego końca.
	 */
	Line(unsigned id, double x1, double y1, double z1, double x2, double y2, double z2);

	/**
	 * @brief zwraca informacje o obiekcie w formie std::string.
	 *
	 * @return String z informacjami.
	 */
	std::string toString() override;
};

class Box : public Shape
{
public:
	/**
	 * @brief Tworzy sześcian.
	 *
	 * @param id Identyfikator.
	 * @param x1 Współrzędna x pierwszego narożnika.
	 * @param y1 Współrzędna y pierwszego narożnika.
	 * @param z1 Współrzędna z pierwszego narożnika.
	 * @param x2 Współrzędna x drugiego narożnika.
	 * @param y2 Współrzędna y drugiego narożnika.
	 * @param z2 Współrzędna z drugiego narożnika.
	 */
	Box(unsigned id, double x1, double y1, double z1, double x2, double y2, double z2);

	/**
	 * @brief zwraca informacje o obiekcie w formie std::string.
	 *
	 * @return String z informacjami.
	 */
	std::string toString() override;
};

class Sphere : public Shape
{
protected:
	Point m_center;
	double m_radius;
	double m_meridians;
	double m_parallels;

public:
	/**
	 * @brief Tworzy sferę.
	 *
	 * @param id Identyfikator.
	 * @param x Współrzędna x środka.
	 * @param y Współrzędna y środka.
	 * @param z Współrzędna z środka.
	 * @param r Promień.
	 * @param m Ilość południków.
	 * @param n Ilość równoleżników.
	 */
	Sphere(unsigned id, double x, double y, double z, double r, double m, double n); 

	void move(double x, double y, double z) override;
	void rotate(double x, double y, double z, double a, double b, double g) override;

	/**
	 * @brief zwraca informacje o obiekcie w formie std::string.
	 *
	 * @return String z informacjami.
	 */
	std::string toString() override;
};

class Cone : public Shape
{
protected:
	Point m_center1;
	double m_radius1;
	Point m_center2;
	double m_radius2;
	double m_quads;
public:
	/**
	 * @brief Tworzy (ścięty) stożek.
	 *
	 * @param id Identyfikator.
	 * @param x1 Współrzędna x pierwszej podstawy.
	 * @param y1 Współrzędna y pierwszej podstawy.
	 * @param z1 Współrzędna z pierwszej podstawy.
	 * @param r1 Promień dolnej podstawy.
	 * @param x2 Współrzędna x drugiej podstawy.
	 * @param y2 Współrzędna y drugiej podstawy.
	 * @param z2 Współrzędna z drugiej podstawy.
	 * @param r2 Promień górnej podstawy.
	 * @param n "Promień" do użycia w algorytmie generowania okręgu w podstawie.
	 */
	Cone(unsigned id, double x1, double y1, double z1, double r1, double x2, double y2, double z2, double r2, double n);
	void move(double x, double y, double z) override;
	void rotate(double x, double y, double z, double a, double b, double g) override;
	std::string toString() override;
};

class Cylinder : public Shape
{
protected:
	Point m_center1;
	Point m_center2;
	double m_radius;
	double m_quads;
public:
	/**
	 * @brief Tworzy cylinder.
	 *
	 * @param id Identyfikator.
	 * @param x1 Współrzędna x pierwszej podstawy.
	 * @param y1 Współrzędna y pierwszej podstawy.
	 * @param z1 Współrzędna z pierwszej podstawy.
	 * @param x2 Współrzędna x drugiej podstawy.
	 * @param y2 Współrzędna y drugiej podstawy.
	 * @param z2 Współrzędna z drugiej podstawy.
	 * @param r Promień podstaw.
	 * @param n "Promień" do użycia w algorytmie generowania okręgu w podstawie.
	 */
	Cylinder(unsigned id, double x1, double y1, double z1, double x2, double y2, double z2, double r, double n);
	void move(double x, double y, double z) override;
	void rotate(double x, double y, double z, double a, double b, double g) override;
	std::string toString() override;
};


