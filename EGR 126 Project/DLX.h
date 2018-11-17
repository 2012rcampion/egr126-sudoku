#pragma once
#include "Board.h"
#include <memory>
#include <string>
#include <list>
#include <map>


class DLX {
private:
	class Node;
	typedef std::shared_ptr<Node> NodePtr;
		
	NodePtr h; // root
	std::list<NodePtr> solution;
	//std::map<NodePtr, std::string> names;
public:
	DLX();
	DLX(Board b);
	std::list<Board> search(int max_results = -1);
private:
	void cover_column(NodePtr& c);
	void uncover_column(NodePtr& c);
	//void print_solution();
	Board get_solution();
	//std::string N(const NodePtr& y);
};

