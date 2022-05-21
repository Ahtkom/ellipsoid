#include <algorithm/metric/BesselSecondTheme.h>
#include <util/MathTools.h>

namespace ep {
namespace alg {

BesselSecondTheme::BesselSecondTheme(const geom::GeoEarth &earth)
	: SecondTheme(earth)
{
}

double
BesselSecondTheme::evaluateDistance(
    const geom::GeoCoordinate *coord1, const geom::GeoCoordinate *coord2,
    double &a1, double &a2)
{
    double L1 = toRadius(coord1->getLon());
    double B1 = toRadius(coord1->getLat());
    double L2 = toRadius(coord2->getLon());
    double B2 = toRadius(coord2->getLat());

    double W1 = sqrt(1 - e1 * sin(B1) * sin(B1));
	double W2 = sqrt(1 - e1 * sin(B2) * sin(B2));
	double sinu1 = sin(B1) * sqrt(1 - e1) / W1;
	double sinu2 = sin(B2) * sqrt(1 - e1) / W2;
	double cosu1 = cos(B1) / W1;
	double cosu2 = cos(B2) / W2;
	double L = L2 - L1;
	double A1 = sinu1 * sinu2;
	double A2 = cosu1 * cosu2;
	double b1 = cosu1 * sinu2;
	double b2 = sinu1 * cosu2;

    //用迭代法计算大地方位角、球面长度以及经差
	double dlta = 0;
	double lmd = 0;
	double p, q;
	double sgm, cossgm, sinsgm;
	double sinA0, cosAo_2;
	double x;
	double alf, bta;
	double ismall = 0;

	//迭代计算大地方位角
	do
	{
		lmd = L + dlta;
		p = cosu2 * sin(lmd);
		q = b1 - b2 * cos(lmd);

		a1 = atan(p / q);
		if (p > 0)
		{
			if (q > 0)
				a1 = fabs(a1);
			else
				a1 = PI - fabs(a1);
		}
		else
		{
			if (q < 0)
				a1 = PI + fabs(a1);
			else
				a1 = PI * 2 - fabs(a1);
		}

		sinsgm = p * sin(a1) + q * cos(a1);
		cossgm = A1 + A2 * cos(lmd); // cossgm不能为0
		sgm = atan(sinsgm / cossgm);
		if (cossgm > 0)
			sgm = fabs(sgm);
		else
			sgm = PI - fabs(sgm);

		sinA0 = cosu1 * sin(a1);
		cosAo_2 = 1 - sinA0 * sinA0;
		x = 2 * A1 - (1 - sinA0 * sinA0) * cos(sgm);

		alf = (e1 / 2 + e1 * e1 / 8 + e1 * e1 * e1 / 16) - (e1 * e1 / 16 + e1 * e1 * e1 / 16) * cosAo_2 + (3 * e1 * e1 * e1 / 128) * cosAo_2 * cosAo_2;

		bta = 2 * ((e1 * e1 / 32 + e1 * e1 * e1 / 32) * cosAo_2 - (e1 * e1 * e1 / 64) * cosAo_2 * cosAo_2) / cosAo_2;

		//改正值
		double temp = dlta; //上一次的改正值
		dlta = (alf * sgm - bta * x * sin(sgm)) * sinA0;

		//两次dlta做差
		ismall = fabs(dlta - temp);
	} while (ismall > 0.0000000001);

	// sgm = 1.572478980;
	//计算系数A、B"、C"以及S
	double S;
	if (B1 == 0 && B2 == 0)
	{
		S = fabs(L) * a;
	}
	else
	{
		double k2 = e2 * cosAo_2;
		double k4 = k2 * k2;
		double k6 = k2 * k2 * k2;
		double A = b * (1 + k2 / 4 - 3 * k4 / 64 + 5 * k6 / 256);
		double B = 2 * b * (k2 / 8 - k4 / 32 + 15 * k6 / 1024) / cosAo_2; // cosAo_2不能为0
		double C = 2 * b * (k4 / 128 - 3 * k6 / 512) / (cosAo_2 * cosAo_2);
		double y = (cosAo_2 * cosAo_2 - 2 * x * x) * cos(sgm);
		S = A * sgm + (B * x + C * y) * sin(sgm);
	}

	//计算反方位角
	p = -(cosu1 * sin(lmd));
	q = -(b1 * cos(lmd) - b2);
	a2 = atan(p / q);
	if (p > 0)
	{
		if (q > 0)
			a2 = fabs(a2);
		else
			a2 = PI - fabs(a2);
	}
	else
	{
		if (q < 0)
			a2 = PI + fabs(a2);
		else
			a2 = PI * 2 - fabs(a2);
	}

	a1 = toDegree(a1);
	B1 = toDegree(B1);
	L1 = toDegree(L1);
	a2 = toDegree(a2);
	B2 = toDegree(B2);
	L2 = toDegree(L2);

	if (S > 300000)
	{
		return S;
	}
	else
	{
		return -S;
	}
}

double
BesselSecondTheme::evaluateDistance(
    const geom::GeoCoordinate *coord1, const geom::GeoCoordinate *coord2)
{
    double a1 = 0, a2 = 0;
    return evaluateDistance(coord1, coord2, a1, a2);
}

} // namespace alg
} // namespace ep