#pragma once

#ifndef _INC_UTILITYFUNCTIONS
#define _INC_UTILITYFUNCTIONS

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <climits>

// for some reason including this fucks up some stuff.
//#include <Windows.h>

typedef enum {
	LOWER_BOUND,
	UPPER_BOUND
}boundType;

namespace util
{
	bool yesNo(std::string promptText);

	//gets input from cin and will loop until the input is of the specified type, rejecting invalid inputs.
	template <typename T>
	T getSanitizedInput()
	{
		T terminalInput;
		bool failedInput = true;

		do
		{
			std::cin >> terminalInput;

			if (std::cin.fail())
				std::cin.clear();

			std::cin.ignore(255, '\n');			// clear out any additional input from the stream until the end of the line

			if (std::cin.gcount() > 1)								// if the ignore cleared out more than one character, assume that bad data was passed to the input stream
			{
				std::cout << "Error: invalid data entered." << std::endl;
				std::cout << "Re-enter value as (" << typeid(T).name() << "): ";
			}
			else
				failedInput = false;

		} while (failedInput);

		return terminalInput;
	}

	template <typename T>
	T getSanitizedInput(double lBound, double uBound)
	{
		T terminalInput;
		bool failedInput = true;

		do
		{
			std::cin >> terminalInput;

			
			if (std::cin.fail())
				std::cin.clear();
			
			std::cin.ignore(255, '\n');	

			if (std::cin.gcount() > 1)
			{
				std::cout << "Error: invalid data entered." << std::endl;
				std::cout << "Re-enter value as (" << typeid(T).name() << ")";
				std::cout << " between ( " << lBound << " , " << uBound << " ): ";
			}
			else
			{
				if (terminalInput <= uBound && terminalInput >= lBound)
					failedInput = false;
				else
				{
					std::cout << "Error: data entered outside of given bounds." << std::endl;
					std::cout << "Re-enter a value between ( " << lBound << " , " << uBound << " ): ";
				}
			}
		} while (failedInput);

		return terminalInput;
	}

	template <typename T>
	T getSanitizedInput(double bound, boundType boundTyp)
	{
		T terminalInput;
		bool failedInput = true;

		do
		{
			std::cin >> terminalInput;

			if (std::cin.fail())
				std::cin.clear();

			std::cin.ignore(255, '\n');

			if (std::cin.gcount() > 1)
			{
				std::cout << "Error: invalid data entered." << std::endl;
				std::cout << "Re-enter value as (" << typeid(T).name() << ")";

				if (boundTyp == UPPER_BOUND)
					std::cout << " smaller than " << bound << ": ";
				else
					std::cout << " larger than " << bound << ": ";
			}
			else
			{
				if ((terminalInput <= bound && boundTyp == UPPER_BOUND) || (terminalInput >= bound && boundTyp == LOWER_BOUND))
					failedInput = false;
				else
				{
					std::cout << "Error: data entered outside of given bound." << std::endl;
					if (boundTyp == UPPER_BOUND)
						std::cout << "Re-enter a value smaller than " << bound << ": ";
					else
						std::cout << "Re-enter a value larger than " << bound << ": ";
				}
			}
		} while (failedInput);

		return terminalInput;
	}

	//make another getSanitizedInput function that takes two parameter types, one being the type of data you want back and the other being the stream object
	template <typename T>
	T getSanitizedInput(T in)
	{
		T extractedValue;
		bool failedInput = true;

		do
		{
			in >> extractedValue;

			if (in.fail())
			{
				in.clear();
				failedInput = false;
			}
				

				

		} while (failedInput);

		return terminalInput;
	}
} // namespace util

#endif