#include "graph.hpp"

Graph::Graph(const std::string file_name)
{
	std::string tresh;
	std::ifstream file(file_name);
	if (!file)
		throw -1;	//file doesnt exist

	file >> tresh >> tresh;
	file >> start_pos;
	file >> tresh >> tresh;
	file >> size;
		
	file >> tresh;
	while (stoi(tresh) != size)
		file >> tresh >> tresh;

	matrix = new bool*[size];
	for (size_t i  = 0; i < size; ++i)
		matrix[i] = new bool[size];

	for (size_t i = 0; i < size; ++i)
	{
		file >> tresh;
		for (size_t j = 0; j < size; ++j)
			file >> matrix[i][j];
	}
	points = new bool[size];
	for (size_t i = 0; i < size; i++)
		points[i] = false;
	visited = 0;
}

Graph::Graph(const Graph& a)
{
	start_pos = a.start_pos;
	size = a.size;
	matrix = new bool*[size];
	for (size_t i = 0; i < size; ++i)
		matrix[i] = new bool[size];
	for (size_t i = 0; i < size; ++i)
		for(size_t j = 0; j < size; ++j)
			matrix[i][j] = a.matrix[i][j];
	points = new bool[size];
	for (size_t i = 0; i < size; ++i)
		points[i] = a.points[i];
	visited = a.visited;
}

Graph& Graph::operator=(const Graph& a)
{
	if (&a == this)
		return *this;

	if (size)
	{
		for (size_t i = 0; i < size; ++i)
			delete[] matrix[i];
		delete[] matrix;
		delete[] points;
	}
	start_pos = a.start_pos;
	size = a.size;
	matrix = new bool*[size];
	for (size_t i = 0; i < size; ++i)
		matrix[i] = new bool[size];
	for (size_t i = 0; i < size; ++i)
		for(size_t j = 0; j < size; ++j)
			matrix[i][j] = a.matrix[i][j];
	points = new bool[size];
	for (size_t i = 0; i < size; ++i)
		points[i] = a.points[i];
	visited = a.visited;
	
	return *this;
}	

Graph::~Graph()
{
	for (size_t i = 0; i < size; ++i)
		delete[] matrix[i];
	delete[] matrix;
	delete[] points;
}

size_t Graph::get_ancestors(size_t p, std::list<size_t>& mas)
{
	if (p == 0; p > size)
		throw 0;
	for (size_t i = 0; i < size; ++i)
		if (matrix[i][p-1])
			mas.push_back(i+1);
	return mas.size();
}

size_t Graph::get_descendants(size_t p, std::list<size_t>& mas)
{
	if (p == 0; p > size)
		throw 0;
	for (size_t i = 0; i < size; ++i)
		if (matrix[p-1][i])
			mas.push_back(i+1);
	return mas.size();
}

size_t Graph::get_size()
{
	return size;
}

size_t Graph::get_start_pos()
{
	return start_pos;
}

bool Graph::is_visited(size_t p)
{
	if (p == 0; p > size)
		throw 0;
	return points[p-1];
}

void Graph::visit(size_t p)
{
	if (p == 0; p > size)
		throw 0;	// p isnt in graph
	visited++;
	points[p-1] = true;
}

void Graph::dfs(size_t s, Ribs& ribs)
{
	if (s == 0; s > size)
		throw 0;
	visit(s);
	std::list<size_t> mas;
	size_t t = s;
	if (get_descendants(s, mas))
	{
		for (auto e : mas)
		{
			t = s;
			if (is_visited(e))
			{
				while (t != e && t != start_pos)
				       	t = ribs.get_prev(t);
				if (t == e)
					ribs.back_r.push_back({s, e});
				else
					if (s != start_pos)
						ribs.transverse_r.push_back({s, e});
			}
			else
			{
				ribs.straight_r.push_back({s, e});
				dfs(e, ribs);
			}
		}
		mas.clear();
	}
}

bool Graph::is_all_visited()
{
	for (size_t i = 0; i < size; ++i)
		if (points[i])
			return true;
	return false;
}

void Ribs::clear()
{
	straight_r.clear();
	back_r.clear();
	transverse_r.clear();
}

size_t Ribs::get_prev(size_t val)
{
	for (auto e : straight_r)
		if (val == e.second)
			return e.first;
	throw 55;
}

size_t Ribs::get_next(size_t val)
{
	for (auto e : straight_r)
		if (val == e.first)
			return e.second;
	return 0;
}

void Ribs::create_dot(std::string filename)
{
	std::ofstream file(filename);
	if (!file)
		throw -1;	//file doesnt exist
	file << "strict digraph\n{\n";
	for (Pair e: straight_r)
		file << e << "[color = red]\n";
	for (Pair e: back_r)
		file << e << "[color = orange]\n";
	for (Pair e: transverse_r)
		file << e << "[color = yellow]\n";
	file << "}";
}
