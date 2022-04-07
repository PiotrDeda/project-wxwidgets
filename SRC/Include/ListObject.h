#pragma once

#include <wx/stattext.h>

/**
 * @brief Struktura reprezentująca element listy brył do wyświetlenia.
 */
struct ListObject {
	ListObject(unsigned i, wxStaticText* st) : id(i), staticText(st) {}
	unsigned id;
	wxStaticText* staticText;
};