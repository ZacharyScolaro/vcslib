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