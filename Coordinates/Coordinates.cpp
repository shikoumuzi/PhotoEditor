#include"Coordinates.h"

namespace PhotoEdit
{
	Coordinates::Coordinates() :parent(nullptr), row(-1), col(-1) {}
	Coordinates::Coordinates(Image* parent, int row, int col) :parent(parent), row(row), col(col) {}
	Coordinates::Coordinates(Image& parent, int row, int col) :Coordinates(&parent, row, col) {}
	Coordinates::~Coordinates()
	{
		this->parent = nullptr;
	}

	void Coordinates::operator=(Coordinates& that)
	{
		this->row = that.row;
		this->col = that.col;
		this->parent = that.parent;
	}
}