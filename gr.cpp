#include "stdafx.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

class Graph
{
private:
	bool ** matr;
	unsigned int num_vertices;


	void DFS(unsigned int v, std::vector<bool> & visited, std::ostream & stream)
	{
		visited[v] = true;
		stream << v << " ";
		for (int i = 0; i < num_vertices; ++i) {
			if (matr[v][i] == 1 && !visited[i]) {
				DFS(i, visited, stream);
			}
		}
	}


public:
	Graph()
	{
		matr = nullptr;
		num_vertices = 0;
	}
	~Graph()
	{
		if (matr)
		{
			for (unsigned int i = 0; i < num_vertices; i++)
			{
				delete[] matr[i];
			}
			delete[] matr;
		}
	}


	void DFS(unsigned int v, std::ostream & stream)
	{
		if (v < num_vertices) {
			std::vector<bool> visited(num_vertices);
			DFS(v, visited, stream);
		}
		else {
			std::ostringstream sstream;
			sstream << "graph consist " << num_vertices << " vertecies " << v;
			throw std::out_of_range(sstream.str());
		}
	}


	bool read(std::istream &stream)
	{
		bool success = true;
		if (stream >> num_vertices)
		{
			bool **elements = new bool *[num_vertices];
			for (unsigned int i = 0; success && i < num_vertices; ++i) {
				elements[i] = new bool[num_vertices];
				for (unsigned int j = 0; j < num_vertices; ++j) {
					if (!(stream >> elements[i][j])) {
						success = false;
						break;
					}
					if (elements[i][j] != 1 && elements[i][j] != 0) {
						success = false;
						break;
					}
				}
			}
			if (success)
			{
				matr = new bool *[num_vertices];
				for (unsigned int i = 0; i < num_vertices; i++)
				{
					matr[i] = new bool[num_vertices];
					for (unsigned int j = 0; j < num_vertices; j++)
					{
						matr[i][j]= elements[i][j];
					}
				}
				for (unsigned int i = 0; i < num_vertices; ++i)
				{
					delete[] elements[i];
				}
				delete[] elements;
			}
			else
			{
				success = false;
			}
		}
		else
		{
			success = false;
		}
		return success;
	}
};
int main() {
	std::ifstream fin;
	fin.open("D:\\Visual Studio Projects\\gr.txt");

	Graph gr;
	if(gr.read(fin)) gr.DFS(2, std::cout);
	else std::cout << "error\n";

	return 0;
}
