#include "Console.h"

Console::Console(wxTextCtrl* textCtrl)
{
	_textCtrl = textCtrl;
	_textCtrl->SetBackgroundColour(*wxBLACK);
	_textCtrl->SetDefaultStyle(wxTextAttr(*wxWHITE));
	_stream = new std::ostream(_textCtrl);
}

void Console::registerCommand(Command command)
{
	_commands.push_back(command);
}

void Console::sendCommand(std::string commandText) {
	std::vector<std::string> arguments{ std::istream_iterator<std::string>{std::istringstream(commandText)}, std::istream_iterator<std::string>{} };
	if (arguments.size() <= 0)
		return;
	for (auto i : _commands)
	{
		if (i.name == arguments[0]) {
			i.command(arguments);
			return;
		}
	}
	print("Command \"" + arguments[0] + "\" not found!", wxRED);
}

std::vector<std::any> Console::validateArguments(std::vector<std::string> arguments, std::initializer_list<std::string> argumentTypes)
{
	std::vector<std::any> result;

	if (arguments.size() != argumentTypes.size() + 1)
	{
		print("Incorrect argument amount! " + std::to_string(argumentTypes.size()) + " arguments expected, got " + std::to_string(arguments.size() - 1), wxRED);
		return result;
	}

	int i = 1;
	for each (auto arg in argumentTypes)
	{
		if (arg == "number")
		{
			double val;
			try
			{
				val = std::stof(arguments[i]);
			}
			catch (...)
			{
				print("Incorrect argument " + std::to_string(i) + " (\"" + arguments[i] + "\"). Number expected", wxRED);
				return result;
			}
			result.push_back(Number(val));
		}
		else if (arg == "pair")
		{
			std::string temp = arguments[i];
			std::replace(temp.begin(), temp.end(), '(', ' ');
			std::replace(temp.begin(), temp.end(), ')', ' ');
			std::replace(temp.begin(), temp.end(), ',', ' ');
			std::vector<std::string> vals{ std::istream_iterator<std::string>{std::istringstream(temp)}, std::istream_iterator<std::string>{} };
			double val1, val2;
			try
			{
				val1 = std::stof(vals.at(0));
				val2 = std::stof(vals.at(1));
			}
			catch (...)
			{
				print("Incorrect argument " + std::to_string(i) + " (\"" + arguments[i] + "\"). Pair expected (e.g. \"(1,-2.5)\")", wxRED);
				return result;
			}
			result.push_back(Pair(val1, val2));
		}
		else if (arg == "triplet")
		{
			std::string temp = arguments[i];
			std::replace(temp.begin(), temp.end(), '(', ' ');
			std::replace(temp.begin(), temp.end(), ')', ' ');
			std::replace(temp.begin(), temp.end(), ',', ' ');
			std::vector<std::string> vals{ std::istream_iterator<std::string>{std::istringstream(temp)}, std::istream_iterator<std::string>{} };
			double val1, val2, val3;
			try
			{
				val1 = std::stof(vals.at(0));
				val2 = std::stof(vals.at(1));
				val3 = std::stof(vals.at(2));
			}
			catch (...)
			{
				print("Incorrect argument " + std::to_string(i) + " (\"" + arguments[i] + "\"). Triplet expected (e.g. \"(1,-2.,3.5)\")", wxRED);
				return result;
			}
			result.push_back(Triplet(val1, val2, val3));
		}
		else if (arg == "name")
		{
			result.push_back(Name(arguments[i]));
		}

		i++;
	}

	return result;
}

void Console::print(std::string text, const wxColour* color)
{
	_textCtrl->SetDefaultStyle(wxTextAttr(*color));
	if (!_textCtrl->IsEmpty())
		*_stream << "\n";
	*_stream << text;
	_stream->flush();
	_textCtrl->SetDefaultStyle(wxTextAttr(*wxWHITE));
}
