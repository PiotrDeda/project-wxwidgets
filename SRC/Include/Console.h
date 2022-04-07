#pragma once

#include <algorithm>
#include <any>
#include <iostream>
#include <sstream>
#include <vector>
#include <wx/textctrl.h>
#include "ArgumentTypes.h"
#include "Command.h"

/**
 * @brief Klasa reprezentująca konsolę.
 */
class Console
{
protected:
	wxTextCtrl* _textCtrl;
	std::ostream* _stream;
	std::vector<Command> _commands;

public:
	/**
	 * @brief Konstruktor konsoli.
	 *
	 * @param textCtrl Kontrolka w której będzie wypisywany tekst wysyłany przez konsolę.
	 *  Powinna posiadać styl wxTE_MULTILINE, wxTE_READONLY i wxTE_RICH lub wxTE_RICH2 (do obsługi kolorowego tekstu).
	 *  Kolor jej tła będzie automatycznie zmieniony na czarny.
	 */
	Console(wxTextCtrl* textCtrl);

	/**
	 * @brief Dodaje komendę do obsługi przez konsolę.
	 *
	 * @param command Dodawana komenda. Zobacz Command::Command.
	 */
	void registerCommand(Command command);

	/**
	 * @brief Wysyła komendę do konsoli. 
	 * 
	 * Metoda wysyłająca komendę do konsoli. Komenda powinna zostać pobrana samodzielnie przez aplikację i wysłana w formie tekstowej tą metodą.
	 * 
	 * @param commandText Tekst wysyłanej komendy. Powinien być całą wysyłaną komendą w formie czystego tekstu zawierającego zarówno nazwę jak i argumenty komendy.
	 */
	void sendCommand(std::string commandText);

	/**
	 * @brief Sprawdza poprawność wpisanej komendy.
	 *
	 * Metoda sprawdzająca poprawność argumentów. Powinna być wywoływana na początku wywoływanej funkcji.
	 * 
	 * @param arguments Lista argumentów do weryfikacji. Powinien być tutaj bezpośrednio przekazany argument wywoływanej funkcji (porównaj Command::Command).
	 * @param argumentTypes Rodzaje argumentów przyjmowanych przez funkcję.
	 * Każdy element listy reprezentuje jeden argument i przyjmuje wartość "number" (Number), "pair" (Pair), "triplet" (Tripler) lub "name" (Name).
	 *
	 * @return Zwraca wektor łańcuch znaków taki, że każdy element jest argumentem wyłuskanym z tekstu, w formie Number, Pair, Triplet lub Name (analogicznie do parametru argumentTypes).
	 */
	std::vector<std::any> validateArguments(std::vector<std::string> arguments, std::initializer_list<std::string> argumentTypes);

	/**
	 * @brief Drukuje tekst w kontrolce tekstu.
	 *
	 * @param text Tekst do wydrukowania.
	 * @param color Kolor drukowanego tekstu, domyślnie biały.
	 */
	void print(std::string text, const wxColour* color = wxWHITE);
};