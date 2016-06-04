#include"matrix.cc"
#include"rational.h"
#include"imaginary.h"
#include"combi.h"
#include"magic.h"

int main()
{
	Matrix<Ratio> m {{
		{3,0,0},
		{0,3,4},
		{1,2,0}
	}};

	//Matrix<float> fm(3,3);
	//(3*(fm.E())).show();

	m.inverse().show();

	m.surround(1.2).show();
	m.show();

	Matrix<float> m3 {{
		{1},{2},{3}
	}};
	m3 = {{{2},{3},{4}}};
	cout << endl;
	//(3*m*m3).show();
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
	m4 = {{
		{2,3},{3,5}}};
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
	MagicSquare ms(4);
	ms.build();
	Matrix<Root> mi {{
		{3, 2},
		{Ratio(2,3), Root(2,2)}
	}};

	auto aa = mi.inverse();
	auto bb = aa.One()*4;
	bb.show();
	aa.show();
	(aa*mi).show();
	Matrix<Imag> mii {{
		{Imag(1,2), Imag(Root(2,2))},
		{3, 2}
	}};
	auto t = mii.ptr();
	cout << *(t+1) << endl;
	(mii*mii).show();
	mii.inverse().show();
}
