#pragma once
#include <iostream>
#include <fstream>


class graph {
	struct vertex {
	public:
		int number;
		vertex(int num) {
			number = num;
		};
	};

public:
	int n;
	int** adjancency_matrix;
	bool is_created = false;
	graph();
	graph(char* url);
	~graph();

	bool check_creation();
	int weight(vertex vi, vertex vj);
	bool is_edge(vertex vi, vertex vj);
	void print_adjancency_matrix();
	void print_adjancency_list(vertex v);
	void print_list_of_edges();
	void print_list_of_edges(vertex v);
	bool is_directed();
}