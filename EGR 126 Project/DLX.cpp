#include "DLX.h"
#include <iostream>
#include <algorithm>
//#include <sstream>

class DLX::Node {
public:
	typedef size_t size_type;
private:
	NodePtr left, right, up, down, column;
	size_type size;

	Node() {};

public:
	static NodePtr make_node() {
		NodePtr n{ new Node };
		R(n) = n;
		L(n) = n;
		U(n) = n;
		D(n) = n;
		return n;
	}

	friend NodePtr& L(const NodePtr& x) { return x->left; }
	friend NodePtr& R(const NodePtr& x) { return x->right; }
	friend NodePtr& U(const NodePtr& x) { return x->up; }
	friend NodePtr& D(const NodePtr& x) { return x->down; }
	friend NodePtr& C(const NodePtr& x) { return x->column; }
	friend size_type& S(const NodePtr& y) { return y->size; }

	void set_row_col_num(int row, int col, int num) {
		size = (row << 8) + (col << 4) + (num << 0);
	}

	int get_row() {
		return (size >> 8) & 0xF;
	}
	int get_col() {
		return (size >> 4) & 0xF;
	}
	int get_num() {
		return (size >> 0) & 0xF;
	}

	friend void connect_left_right(NodePtr& l, NodePtr& r) {
		R(l) = r;
		L(r) = l;
	}
	friend void connect_up_down(NodePtr& u, NodePtr& d) {
		U(d) = u;
		D(u) = d;
	}

	friend void insert_right(NodePtr& l, NodePtr& r) {
		L(r) = l;
		R(r) = R(l);
		R(L(r)) = r;
		L(R(r)) = r;
	}
	friend void insert_left(NodePtr& r, NodePtr& l) {
		R(l) = r;
		L(l) = L(r);
		R(L(l)) = l;
		L(R(l)) = l;
	}
	friend void insert_down(NodePtr& u, NodePtr& d) {
		U(d) = u;
		D(d) = D(u);
		D(U(d)) = d;
		U(D(d)) = d;
	}
	friend void insert_up(NodePtr& d, NodePtr& u) {
		D(u) = d;
		U(u) = U(d);
		D(U(u)) = u;
		U(D(u)) = u;
	}
};

DLX::DLX() : h(Node::make_node()) {}

DLX::DLX(Board b) : DLX{} {
	std::array<std::array<NodePtr, Board::size>, Board::size>row_col;
	std::array<std::array<NodePtr, Board::size>, Board::size>row_num;
	std::array<std::array<NodePtr, Board::size>, Board::size>col_num;
	std::array<std::array<NodePtr, Board::size>, Board::size>box_num;

	for(int row = 0; row < Board::size; ++row) {
		for(int col = 0; col < Board::size; ++col) {
			NodePtr y = Node::make_node();
			row_col[row][col] = y;
			/*std::ostringstream name;
			name << "R" << (row + 1) << "C" << (col + 1);
			names.emplace(y, name.str());*/
			insert_left(h, y);
		}
	}
	for(int row = 0; row < Board::size; ++row) {
		for(int num = 0; num < Board::size; ++num) {
			NodePtr y = Node::make_node();
			row_num[row][num] = y;
			/*std::ostringstream name;
			name << "R" << (row + 1) << "#" << (num + 1);
			names.emplace(y, name.str());*/
			insert_left(h, y);
		}
	}
	for(int col = 0; col < Board::size; ++col) {
		for(int num = 0; num < Board::size; ++num) {
			NodePtr y = Node::make_node();
			col_num[col][num] = y;
			/*std::ostringstream name;
			name << "C" << (col + 1) << "#" << (num + 1);
			names.emplace(y, name.str());*/
			insert_left(h, y);
		}
	}
	for(int box = 0; box < Board::size; ++box) {
		for(int num = 0; num < Board::size; ++num) {
			NodePtr y = Node::make_node();
			box_num[box][num] = y;
			/*std::ostringstream name;
			name << "B" << (box + 1) << "#" << (num + 1);
			names.emplace(y, name.str());*/
			insert_left(h, y);
		}
	}

	for(int row = 0; row < Board::size; ++row) {
		for(int col = 0; col < Board::size; ++col) {
			int box = Board::index_to_box_number(Board::row_col_to_index(row, col)).first;
			int clue = b.get(row, col) - 1;
			for(int num = 0; num < Board::size; ++num) {
				NodePtr rc = Node::make_node();
				NodePtr rn = Node::make_node();
				NodePtr cn = Node::make_node();
				NodePtr bn = Node::make_node();
				rc->set_row_col_num(row, col, num);
				rn->set_row_col_num(row, col, num);
				cn->set_row_col_num(row, col, num);
				bn->set_row_col_num(row, col, num);
				C(rc) = row_col[row][col];
				C(rn) = row_num[row][num];
				C(cn) = col_num[col][num];
				C(bn) = box_num[box][num];
				insert_right(rc, rn);
				insert_right(rn, cn);
				insert_right(cn, bn);
				insert_up(C(rc), rc);
				insert_up(C(rn), rn);
				insert_up(C(cn), cn);
				insert_up(C(bn), bn);
				if(num == clue) solution.push_back(rc);
			}
		}
	}

	for(int row = 0; row < Board::size; ++row) {
		for(int col = 0; col < Board::size; ++col) {
			int box = Board::index_to_box_number(Board::row_col_to_index(row, col)).first;
			int num = b.get(row, col) - 1;
			if(num < 0) continue;
			cover_column(row_col[row][col]);
			cover_column(row_num[row][num]);
			cover_column(col_num[col][num]);
			cover_column(box_num[box][num]);
		}
	}
}

std::list<Board> DLX::search(int max_results) {
	std::list<Board> solutions{};
	if(R(h) == h) {
		//print_solution();
		//return true;
		solutions.push_back(get_solution());
		return solutions;
	}
	NodePtr c = R(h);
	for(NodePtr ci = R(c); ci != h; ci = R(ci)) {
		if(S(ci) < S(c)) {
			c = ci;
		}
	}
	int remaining = max_results;
	cover_column(c);
	for(NodePtr r = D(c); r != c && remaining; r = D(r)) {
		solution.push_back(r);
		for(NodePtr j = R(r); j != r; j = R(j)) {
			cover_column(C(j));
		}
		auto s = search(remaining);
		remaining -= s.size();
		solutions.splice(solutions.end(), s);
		for(NodePtr j = L(r); j != r; j = L(j)) {
			uncover_column(C(j));
		}
		solution.pop_back();
	}
	uncover_column(c);
	return solutions;
}

void DLX::cover_column(NodePtr& c) {
	L(R(c)) = L(c);
	R(L(c)) = R(c);
	for(auto i = D(c); i != c; i = D(i)) {
		for(auto j = R(i); j != i; j = R(j)) {
			U(D(j)) = U(j);
			D(U(j)) = D(j);
			--S(C(j));
		}
	}
}

void DLX::uncover_column(NodePtr& c) {
	for(auto i = U(c); i != c; i = U(i)) {
		for(auto j = L(i); j != i; j = L(j)) {
			++S(C(j));
			U(D(j)) = j;
			D(U(j)) = j;
		}
	}
	L(R(c)) = c;
	R(L(c)) = c;
}

Board DLX::get_solution() {
	Board b;
	for(auto o : solution) {
		int row = o->get_row();
		int col = o->get_col();
		int num = o->get_num();
		b.set(row, col, num + 1);
	}
	return b;
}

/*
std::string DLX::N(const NodePtr& y) {
	return names.at(y);
}
*/