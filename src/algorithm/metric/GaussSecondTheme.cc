#include <algorithm/metric/GaussSecondTheme.h>
#include <util/MathTools.h>

namespace ep {
namespace alg {

GaussSecondTheme::GaussSecondTheme(const geom::GeoEarth &earth)
	: SecondTheme(earth)
{
}

double
GaussSecondTheme::evaluateDistance(
    const geom::GeoCoordinate *coord1, const geom::GeoCoordinate *coord2,
    double &a1, double &a2)
{
    double length2p;
	double Bm, B1, L1, B2, L2;
	double Nm, V2m, m, B, e2m, tm;
	double DltA, Delt_B, Delt_l, Delt_a;
	double s1, s2, DLT_A, Am, A12, A211;
	double tmp;
	// double A212;

    L1 = toRadius(coord1->getLon());
    B1 = toRadius(coord1->getLat());
    L2 = toRadius(coord2->getLon());
    B2 = toRadius(coord2->getLat());

	Bm = (B1 + B2) / 2;
	Nm = a / sqrt(1 - e1 * sin(Bm) * sin(Bm));

	V2m = 1 + e2 * cos(Bm) * cos(Bm);

	m = (L2 - L1) * cos(Bm);

	tm = tan(Bm);
	e2m = V2m - 1;
	B = (B2 - B1);

	tmp = B * B / V2m / V2m * e2m * (-1 + tm * tm - e2m - 4 * tm * tm * e2m) / 8.0;
	Delt_B = 1.0 / 24.0 * m * m * (2 + 3 * tm * tm + 2 * e2m) + tmp;

	Delt_l = m * m * tm * tm / 24.0 - B * B / 24.0 / V2m / V2m * (1 + e2m - 9 * e2m * tm * tm);

	Delt_a = 1 / 12.0 * m * m * V2m + B * B / 24.0 / V2m / V2m * (3 + 8 * e2m + 5 * e2m * e2m);

	s1 = Nm * B * (1 - Delt_B) / V2m;
	s2 = Nm * m * (1 - Delt_l);
	length2p = sqrt(s1 * s1 + s2 * s2);

	if (s1 != 0)
	{
		DltA = m * tm * (1 + Delt_a);
		Am = atan(s2 / s1);
		A12 = Am - 0.5 * DltA;
		A211 = Am + 0.5 * DltA + PI;
		if (B2 < B1)
		{
			A12 = Am - 0.5 * DltA + PI;
			A211 = Am + 0.5 * DltA;
		}
	}
	else
	{
		if (L1 > L2)
		{
			A12 = 1.5 * PI;
			A211 = 0.5 * PI;
		}
		else
		{
			A12 = 0.5 * PI;
			A211 = 1.5 * PI;
		}
	}

	// A212 = Am + 0.5 * DltA - PI;
	if (A211 > 2 * PI)
	{
		A211 = A211 - 2 * PI;
	}
	if (A211 < 0)
	{
		A211 = A211 + 2 * PI;
	}
	if (A12 < 0)
	{
		A12 = A12 + 2 * PI;
	}
	if (A12 > 2 * PI)
	{
		A12 = A12 - 2 * PI;
	}
	a1 = A12 * 180 / PI;
	a2 = A211 * 180 / PI;
	if (length2p > 300000)
	{
		return -length2p;
	}
	else
	{
		return length2p;
	}
}

double
GaussSecondTheme::evaluateDistance(
    const geom::GeoCoordinate *coord1, const geom::GeoCoordinate *coord2)
{
    double a1 = 0, a2 = 0;
    return evaluateDistance(coord1, coord2, a1, a2);
}

} // namespace alg
} // namespace ep