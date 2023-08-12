// Assumes Origin is Top Left

template <typename T> class BoundingBox {
private:
	T left;
	T right;
	T top;
	T bottom;

public:
	T X;
	T Y;
	BoundingBox(T x, T y, T left, T right, T top, T bottom);
	bool Intersects(const BoundingBox& bb);
};

template <typename T> BoundingBox<T>::BoundingBox(T x, T y, T left, T right, T top, T bottom) :
	left(left),
	right(right),
	top(top),
	bottom(bottom),
	X(x),
	Y(y)
{
}

template <typename T> bool BoundingBox<T>::Intersects(const BoundingBox& bb) {
	return !((X + right) <= (bb.X + bb.left)
		|| (X + left) >= (bb.X + bb.right)
		|| (Y + top) >= (bb.Y + bb.bottom)
		|| (Y + bottom) <= (bb.Y + bb.top)
		);
}
