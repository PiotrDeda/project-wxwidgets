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
 * @brief Klasa opisuj¹ca kontener na bry³y.
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
	 * @param shapeList Kontrolka w której wypisywane bêd¹ bry³y.
	 */
	ShapeContainer(wxTextCtrl* shapeList) : m_shapeList(shapeList), m_nextId(1) {}

	/**
	 * @brief Dodaje bry³ê do konteneru.
	 *
	 * @param shape Bry³a.
	 */
	void addShape(Shape* shape);

	/**
	 * @brief Usuwa zadan¹ bry³ê.
	 *
	 * @param id Identyfikator bry³y do usuniêcia.
	 *
	 * @return Zwraca true jeœli jakaœ bry³a zosta³a usuniêta, w przeciwnym wypadku false.
	 */
	bool deleteShape(unsigned id);

	/**
	 * @brief Usuwa wszystkie bry³y z konteneru.
	 */
	void deleteAllShapes();

	/**
	 * @brief Przesuwa bry³ê o wektor [\p x, \p y, \p z].
	 *
	 * @param id Identyfikator bry³y do przesuniêcia.
	 * @param x Wartoœæ x wektora przesuniêcia.
	 * @param y Wartoœæ y wektora przesuniêcia.
	 * @param z Wartoœæ z wektora przesuniêcia.
	 */
	void moveShape(unsigned id, double x, double y, double z);

	/**
	 * @brief Obraca bry³ê wokó³ punktu (\p x, \p y, \p z) o k¹t \p a wzd³u¿ osi X, \p b wzd³u¿ osi Y i k¹t \p g wzd³u¿ osi Z.
	 *
	 * @param id Identyfikator bry³y do obrócenia.
	 * @param x Wspó³rzêdna x œrodka obrotu.
	 * @param y Wspó³rzêdna y œrodka obrotu.
	 * @param z Wspó³rzêdna z œrodka obrotu.
	 * @param a K¹t obrotu wokó³ osi X.
	 * @param b K¹t obrotu wokó³ osi Y.
	 * @param g K¹t obrotu wokó³ osi Z.
	 */
	void rotateShape(unsigned id, double x, double y, double z, double a, double b, double g);

	/**
	 * @brief Odœwie¿a listê bry³.
	 */
	void refreshList();

	/**
	 * @brief Zapisuje dane bry³ i ustawienia do pliku.
	 *
	 * @param filename Nazwa pliku.
	 * @throw std::runtime_error Rzucany jeœli zapis pliku siê nie powiedzie.
	 */
	void saveToFile(std::string filename);

	/**
	 * @brief Wczytuje dane bry³ i ustawienia z pliku. 
	 *
	 * Wczytuje dane bry³ i ustawienia z pliku. Obecne dane zostan¹ usuniête.
	 * Weryfikuje poprawnoœæ sk³adni pliku, ale nie weryfikuje poprawnoœci danych pod k¹tem sensownoœci ich wykorzystania w programie.
	 * 
	 * @param filename Nazwa pliku.
	 * @throw std::runtime_error Rzucany jeœli odczyt pliku siê nie powiedzie. Obecne dane nie zostan¹ wtedy usuniête.
	 */
	void loadFromFile(std::string filename);

	/**
	 * @brief Przetwarza linijkê pliku wygenerowanego przez aplikacjê. Metoda przeznaczona do u¿ytku loadFromFile.
	 *
	 * @param words Linijka podzielona na s³owa.
	 *
	 * @return Kontener zawieraj¹cy wartoœci wy³uskane z linijki.
	 */
	std::vector<double> validateWords(std::vector<std::string> words);

	/**
	 * @brief Zwraca kolejn¹ wartoœæ identyfikatora, która ma zostaæ przypisana nastêpnej utworzonej bryle.
	 *
	 * @return Identyfikator.
	 */
	unsigned getNextId();

	/**
	 * @brief Zwraca kontener bry³.
	 *
	 * @return Kontener bry³.
	 */
	std::vector<Shape*> getShapes();
};