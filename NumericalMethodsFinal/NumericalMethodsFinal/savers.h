#pragma once

#ifndef _INC_SAVERS
#define _INC_SAVERS

#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "Structs.h"

extern componentPathRegistry componentPaths;

namespace savers
{
	template<typename T>
	void saveComponent(T const& obj, std::string _fileName, componentType_e _componentType )
	{
		
		//std::string filePath = getenv("USERPROFILE");
		//filePath += "\\Documents\\" + _fileName + ".txt";
		std::string filePath = componentPaths.registeredComponents[_componentType] + "/" + _fileName + ".txt";
		std::ofstream outfile;

		// open file in write mode, overwriting if file exists.
		//Note: this could lead to loss of data and should be dealt with.
		outfile.open(filePath.c_str(), std::ios::out | std::ios::trunc);

		if (outfile.is_open())
		{
			std::cout << "Writing to file:" << std::endl;
			outfile << obj;
			outfile.close();
		}//if (outfile.is_open())

		std::cout << "Sucsess writing data to:" << std::endl << filePath << std::endl << std::endl;
	}


	template<typename T, typename A>
	void outputData(std::vector<std::vector<T, A> > const& vec, std::string _fileName)
	{
		std::string filePath = componentPaths.registeredComponents[COMPONENT_RESULTS] + "/" + _fileName + ".txt";
		std::ofstream outfile;
		//std::string filePath = getenv("USERPROFILE");
		//filePath += "\\Documents\\" + _fileName + ".csv";

		// open file in write mode, overwriting if file exists.
		//Note: this could lead to loss of data and should be dealt with.
		outfile.open(filePath.c_str(), std::ios::out | std::ios::trunc);

		if (outfile.is_open())
		{
			std::cout << "Writing to file:" << std::endl;

			// write each line to the output file as column vectors
			// this is clunky, since it assumes that no vector has fewer elements than the first
			for (int i = 0; i < vec[0].size(); ++i)
			{
				for (int j = 0; j < vec.size(); ++j)
				{
					outfile << vec[j][i];
					if (j < vec.size() - 1)
						outfile << ',';
				}
				outfile << std::endl;
			}
			outfile << std::endl;
			outfile.close();
		}//if (outfile.is_open())

		std::cout << "Sucsess writing data to:" << std::endl << filePath << std::endl << std::endl;
	}
}

#endif