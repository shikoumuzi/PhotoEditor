#ifndef __COORDINATES_H__
#define __COORDINATES_H__

namespace PhotoEdit
{
	class Image;

	class Coordinates
	{
	public:
		static Coordinates null;
	public:
		Coordinates();
		Coordinates(Image* parent, int row, int col);
		Coordinates(Image& parent, int row, int col);
		~Coordinates();
	public:
		void operator=(Coordinates&);
	public:
		int row;
		int col;
		Image* parent;
	};


}
#endif // !__COORDINATES_H__
