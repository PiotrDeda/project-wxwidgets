#pragma once

#include <algorithm>
#include <any>
#include <fstream>
#include <sstream>
#include <vector>
#include <wx/textctrl.h>
#include "ListObject.h"
#include "Shape.h"

/**
 * @brief Klasa opisuj�ca kontener na bry�y.
 */
class ShapeContainer
{
protected:
	std::vector<Shape*> m_shapes;
	wxTextCtrl* m_shapeList;
	unsigned m_nextId;

public:
	/**
	 * @brief Konstruktor klasy ShapeContainer.
	 *
	 * @param shapeList Kontrolka w kt�rej wypisywane b�d� bry�y.
	 */
	ShapeContainer(wxTextCtrl* shapeList) : m_shapeList(shapeList), m_nextId(1) {}

	/**
	 * @brief Dodaje bry�� do konteneru.
	 *
	 * @param shape Bry�a.
	 */
	void addShape(Shape* shape);

	/**
	 * @brief Usuwa zadan� bry��.
	 *
	 * @param id Identyfikator bry�y do usuni�cia.
	 *
	 * @return Zwraca true je�li jaka� bry�a zosta�a usuni�ta, w przeciwnym wypadku false.
	 */
	bool deleteShape(unsigned id);

	/**
	 * @brief Usuwa wszystkie bry�y z konteneru.
	 */
	void deleteAllShapes();

	/**
	 * @brief Przesuwa bry�� o wektor [\p x, \p y, \p z].
	 *
	 * @param id Identyfikator bry�y do przesuni�cia.
	 * @param x Warto�� x wektora przesuni�cia.
	 * @param y Warto�� y wektora przesuni�cia.
	 * @param z Warto�� z wektora przesuni�cia.
	 */
	void moveShape(unsigned id, double x, double y, double z);

	/**
	 * @brief Obraca bry�� wok� punktu (\p x, \p y, \p z) o k�t \p a wzd�u� osi X, \p b wzd�u� osi Y i k�t \p g wzd�u� osi Z.
	 *
	 * @param id Identyfikator bry�y do obr�cenia.
	 * @param x Wsp�rz�dna x �rodka obrotu.
	 * @param y Wsp�rz�dna y �rodka obrotu.
	 * @param z Wsp�rz�dna z �rodka obrotu.
	 * @param a K�t obrotu wok� osi X.
	 * @param b K�t obrotu wok� osi Y.
	 * @param g K�t obrotu wok� osi Z.
	 */
	void rotateShape(unsigned id, double x, double y, double z, double a, double b, double g);

	/**
	 * @brief Od�wie�a list� bry�.
	 */
	void refreshList();

	/**
	 * @brief Zapisuje dane bry� i ustawienia do pliku.
	 *
	 * @param filename Nazwa pliku.
	 * @throw std::runtime_error Rzucany je�li zapis pliku si� nie powiedzie.
	 */
	void saveToFile(std::string filename);

	/**
	 * @brief Wczytuje dane bry� i ustawienia z pliku. 
	 *
	 * Wczytuje dane bry� i ustawienia z pliku. Obecne dane zostan� usuni�te.
	 * Weryfikuje poprawno�� sk�adni pliku, ale nie weryfikuje poprawno�ci danych pod k�tem sensowno�ci ich wykorzystania w programie.
	 * 
	 * @param filename Nazwa pliku.
	 * @throw std::runtime_error Rzucany je�li odczyt pliku si� nie powiedzie. Obecne dane nie zostan� wtedy usuni�te.
	 */
	void loadFromFile(std::string filename);

	/**
	 * @brief Przetwarza linijk� pliku wygenerowanego przez aplikacj�. Metoda przeznaczona do u�ytku loadFromFile.
	 *
	 * @param words Linijka podzielona na s�owa.
	 *
	 * @return Kontener zawieraj�cy warto�ci wy�uskane z linijki.
	 */
	std::vector<double> validateWords(std::vector<std::string> words);

	/**
	 * @brief Zwraca kolejn� warto�� identyfikatora, kt�ra ma zosta� przypisana nast�pnej utworzonej bryle.
	 *
	 * @return Identyfikator.
	 */
	unsigned getNextId();

	/**
	 * @brief Zwraca kontener bry�.
	 *
	 * @return Kontener bry�.
	 */
	std::vector<Shape*> getShapes();
};