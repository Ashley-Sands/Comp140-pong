#pragma once
class Color
{
public:
	Color();
	Color(int r, int g, int b);
	Color(int r, int g, int b, int a);
	~Color();

	int red;
	int green;
	int blue;
	int alpha;
};

