#include"matrix.cc"
#include"rational.h"
#include"combi.h"
#include"magic.h"

int main()
{
	Matrix<float> m {{
		{3,0,0},
		{0,3,4},
		{1,2,0}
	}};
	m.surround(1.2).show();
	m.show();

	Matrix<float> m3 {{
		{1},{2},{3}
	}};
	cout << endl;
	(3*m*m3).show();
	cout << endl;
	Matrix<char> m2 {{
		{67, 68,69}
	}};
	m2.show();
	auto a = m2.surround('$');
	a.show();
	a(0,0) = 'r';
	a.show();
	cout << a(2,1) << endl;

	Matrix<float> m4 {{
		{0.2,3},
		{2,8}
	}};
	m4.show();
	auto k = m4.inverse();
	(k*m4).show();
	auto s = m.inverse();
	(s*m).show();

	Matrix<Ratio> mr {{
		{2,3},
			{Ratio(1,2), 0}
	}};
	Matrix<Ratio> mr2 {{
		{2,3},
			{Ratio(1,2), 0}
	}};
	(mr+mr2*mr).surround('#').show();
	cout << "4P3 = " << nHr(4,3).count() <<endl;
	m.E().show();
	unsigned char cc = 67;
	cout << cc << endl;
	MagicSquare ms(3);
	ms.partial_nPr();
}
