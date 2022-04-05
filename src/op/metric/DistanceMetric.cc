#include <op/metric/DistanceMetric.h>
#include <algorithm/alg.h>
#include <geom/GeoFactory.h>
#include <geom/GeoCoordinate.h>
#include <geom/GeoCoordinateSequence.h>
#include <geom/GeoPoint.h>
#include <geom/GeoLineSegment.h>
#include <geom/GeoLineString.h>
#include <geom/GeoLinearRing.h>
#include <geom/GeoPolygon.h>
#include <geom/GeoMultiLineString.h>
#include <geom/GeoMultiPolygon.h>

#include <math.h>
#include <iostream>

namespace ep {
namespace op {

DistanceMetric::DistanceMetric(const geom::GeoEarth &earth)
    : BaseMetric(earth)
{
}

double
DistanceMetric::evaluateDistance(const geom::GeoGeometry *g1, const geom::GeoGeometry *g2)
{
	if (g1->getGeometryType() == "POINT") {
        if (g2->getGeometryType() == "POINT") {
            return distancePoints(
				static_cast<const geom::GeoPoint *>(g1),
				static_cast<const geom::GeoPoint *>(g2));
		}
	}
	return -1.0;
	// if (g1->getGeometryType() == "POINT") {
    //     if (g2->getGeometryType() == "POINT") {
    //         return distancePoints(
	// 			static_cast<const geom::GeoPoint *>(g1),
	// 			static_cast<const geom::GeoPoint *>(g2));
    //     } else if (g2->getGeometryType() == "LINESTRING" ||
	// 			g2->getGeometryType() == "LINEARRING") {
	// 		return distancePointToLineString(
	// 			static_cast<const geom::GeoPoint *>(g1),
	// 			static_cast<const geom::GeoLineString *>(g2));
	// 	} else if (g2->getGeometryType() == "POLYGON") {
	// 		return distancePointToPolygon(
	// 			static_cast<const geom::GeoPoint *>(g1),
	// 			static_cast<const geom::GeoPolygon *>(g2));
	// 	} else if (g2->getGeometryType() == "MULTILINESTRING") {
	// 		return distancePointToMultiLineString(
	// 			static_cast<const geom::GeoPoint *>(g1),
	// 			static_cast<const geom::GeoMultiLineString *>(g2));
	// 	} else if (g2->getGeometryType() == "MULTIPolygon") {
	// 		return distancePointToMultiPolygon(
	// 			static_cast<const geom::GeoPoint *>(g1),
	// 			static_cast<const geom::GeoMultiPolygon *>(g2));
	// 	}
    // } else if (g1->getGeometryType() == "LINESTRING") {
	// 	if (g2->getGeometryType() == "LINESTRING" ||
	// 			g2->getGeometryType() == "LINEARRING") {
	// 		return distanceLineStrings(
	// 			static_cast<const geom::GeoLineString *>(g1),
	// 			static_cast<const geom::GeoLineString *>(g2));
	// 	} else if (g2->getGeometryType() == "POLYGON") {
	// 		return distanceLineStringToPolygon(
	// 			static_cast<const geom::GeoLineString *>(g1),
	// 			static_cast<const geom::GeoPolygon *>(g2));
	// 	} else if (g2->getGeometryType() == "MULTILINESTRING") {
	// 		return distanceLineStringToMultiLineString(
	// 			static_cast<const geom::GeoLineString *>(g1),
	// 			static_cast<const geom::GeoMultiLineString *>(g2));
	// 	} else if (g2->getGeometryType() == "MULTIPOLYGON") {
	// 		return distanceLineStringToMultiPolygon(
	// 			static_cast<const geom::GeoLineString *>(g1),
	// 			static_cast<const geom::GeoMultiPolygon *>(g2));
	// 	}
	// } else if (g1->getGeometryType() == "POLYGON") {
	// 	if (g2->getGeometryType() == "POLYGON") {
	// 		return distancePolygons(
	// 			static_cast<const geom::GeoPolygon *>(g1),
	// 			static_cast<const geom::GeoPolygon *>(g2));
	// 	} else if (g2->getGeometryType() == "MULTILINESTRING") {
	// 		return distancePolygonToMultiLineString(
	// 			static_cast<const geom::GeoPolygon *>(g1),
	// 			static_cast<const geom::GeoMultiLineString *>(g2));
	// 	} else if (g2->getGeometryType() == "MULTIPOLYGON") {
	// 		return distancePolygonToMultiPolygon(
	// 			static_cast<const geom::GeoPolygon *>(g1),
	// 			static_cast<const geom::GeoMultiPolygon *>(g2));
	// 	}
	// } else if (g1->getGeometryType() == "MULTILINESTRING") {
	// 	if (g2->getGeometryType() == "MULTILINESTRING") {
	// 		return distanceMultiLineStrings(
	// 			static_cast<const geom::GeoMultiLineString *>(g1),
	// 			static_cast<const geom::GeoMultiLineString *>(g2));
	// 	} else if (g2->getGeometryType() == "MULTIPOLYGON") {
	// 		return distanceMultiLineStringToMultiPolygon(
	// 			static_cast<const geom::GeoMultiLineString *>(g1),
	// 			static_cast<const geom::GeoMultiPolygon *>(g2));
	// 	}
	// } else if (g1->getGeometryType() == "MULTIPOLYGON") {
	// 	if (g2->getGeometryType() == "MULTIPOLYGON") {
	// 		return distanceMultiPolygons(
	// 			static_cast<const geom::GeoMultiPolygon *>(g1),
	// 			static_cast<const geom::GeoMultiPolygon *>(g2));
	// 	}
	// }
    // return evaluateDistance(g2, g1);
}


double
DistanceMetric::distancePoints
 (const geom::GeoPoint *pt1, const geom::GeoPoint *pt2)
{
    return distanceCoordinates(pt1->getCoordinate(), pt2->getCoordinate());
}

double
DistanceMetric::distancePointToLineString
 (const geom::GeoPoint *pt, const geom::GeoLineString *ls)
{
}

double
DistanceMetric::distanceCoordinateToTwoCoordinates(
	const geom::GeoCoordinate *coord,
	const geom::GeoCoordinate *coord1,
	const geom::GeoCoordinate *coord2)
{
	double A01, A10, A12, A21, A20, A02;
	double len01 = SecondTheme(coord, coord1, A01, A10);
	double len02 = SecondTheme(coord, coord2, A12, A21);
	double len12 = SecondTheme(coord1, coord2, A20, A02);

}


double
DistanceMetric::distanceCoordinates
 (const geom::GeoCoordinate *coord1, const geom::GeoCoordinate *coord2)
{
	double a1, a2;
	double res =  SecondTheme(coord1, coord2, a1, a2);

#ifdef ELLIPSOID_DEBUG
	std::cout << "DistanceMetric::distanceCoordinates\n"
			  << a1 << " " << a2 << std::endl;
#endif

	return res;
}

geom::GeoCoordinate
DistanceMetric::FirstTheme(const geom::GeoCoordinate *coord1, double dist, double a1, double &a2)
{
	if (dist > 300000) {
		return Bessel_FirstTheme(coord1, dist, a1, a2);
	} else {
		return Gauss_FirstTheme(coord1, dist, a1, a2);
	}
}

double
DistanceMetric::SecondTheme(
	const geom::GeoCoordinate *coord1,
	const geom::GeoCoordinate *coord2,
	double &a1,
	double &a2)
{
	static bool LongOrShort = false; // 先验值，判断先做长距离还是先做短距离 false为短
	double s;
	if (LongOrShort) {
		s = Bessel_SecondTheme(coord1, coord2, a1, a2);
		if (s < 0) {
			s = Gauss_SecondTheme(coord1, coord2, a1, a2);
			LongOrShort = !LongOrShort;
		}
	} else {
		s = Gauss_SecondTheme(coord1, coord2, a1, a2);
		if (s < 0) {
			s = Bessel_SecondTheme(coord1, coord2, a1, a2);
			LongOrShort = !LongOrShort;
		}
	}
	return s;
}

geom::GeoCoordinate
DistanceMetric::Bessel_FirstTheme
 (const geom::GeoCoordinate *coord1, double dist, double a1, double &a2)
{
	double L1 = coord1->getLon();
	double B1 = coord1->getLat();


	double B2, L2;

	// double b = ParmaB;
	// double e1 = EE1;
	// double e2 = EE2;

	if ((B1 >= -EPSILON) && (B1 <= EPSILON))
	{
		B1 = 0.0000000001;
	}

	B1 = B1 * PI / 180;
	L1 = L1 * PI / 180;
	a1 = a1 * PI / 180;

	//计算起点的规划纬度
	double W1 = sqrt(1 - e1 * sin(B1) * sin(B1));
	double sinu1 = sin(B1) * sqrt(1 - e1) / W1;
	double cosu1 = cos(B1) / W1;

	//计算辅助函数值
	// double test1 = sin(a1);
	// double test2 = cos(a1);
	double sinAo = cosu1 * sin(a1);
	double cota1 = cosu1 * cos(a1) / sinu1; // sinu1不能为0
	double sin2sgm1 = 2 * cota1 / (cota1 * cota1 + 1);
	double cos2sgm1 = (cota1 * cota1 - 1) / (cota1 * cota1 + 1);
	double cosAo_2 = 1 - sinAo * sinAo;
	double k2 = e2 * cosAo_2;
	double k4 = k2 * k2;
	double k6 = k2 * k2 * k2;

	//计算系数A、B、C以及alf、beita
	double A = b * (1 + k2 / 4 - 3 * k4 / 64 + 5 * k6 / 256);
	double B = b * (k2 / 8 - k4 / 32 + 15 * k6 / 1024);
	double C = b * (k4 / 128 - 3 * k6 / 512);
	double alf = (e1 / 2 + e1 * e1 / 8 + e1 * e1 * e1 / 16) - (e1 * e1 / 16 + e1 * e1 * e1 / 16) * cosAo_2 + (3 * e1 * e1 * e1 / 128) * cosAo_2 * cosAo_2;
	double bta = (e1 * e1 / 32 + e1 * e1 * e1 / 32) * cosAo_2 - (e1 * e1 * e1 / 64) * cosAo_2 * cosAo_2;

	//计算球面长度
	double sgm0 = (dist - (B + C * cos2sgm1) * sin2sgm1) / A;
	double sin2sgm1_sgm0 = sin2sgm1 * cos(2 * sgm0) + cos2sgm1 * sin(2 * sgm0);
	double cos2sgm1_sgm0 = cos2sgm1 * cos(2 * sgm0) - sin2sgm1 * sin(2 * sgm0);
	double sgm = sgm0 + (B + 5 * C * cos2sgm1_sgm0) * sin2sgm1_sgm0 / A;

	//计算经差改正数
	double dlta = (alf * sgm + bta * (sin2sgm1_sgm0 - sin2sgm1)) * sinAo;

	//计算终点大地坐标以及大地方位角
	double sinu2 = sinu1 * cos(sgm) + cosu1 * cos(a1) * sin(sgm);
	B2 = atan(sinu2 / (sqrt(1 - e1) * sqrt(1 - sinu2 * sinu2)));

	double lmd = atan(sin(a1) * sin(sgm) / (cosu1 * cos(sgm) - sinu1 * sin(sgm) * cos(a1)));
	if (sin(a1) > 0)
	{
		if (tan(lmd) > 0)
			lmd = fabs(lmd);
		else
			lmd = PI - fabs(lmd);
	}
	else
	{
		if (tan(lmd) < 0)
			lmd = -fabs(lmd);
		else
			lmd = fabs(lmd) - PI;
	}

	L2 = L1 + lmd - dlta;
	if (((a1 >= -EPSILON) && (a1 <= EPSILON)) || (((a1 - PI) >= -EPSILON) && ((a1 - PI) <= EPSILON)))
	{
		L2 = L1;
	}

	if (L2 > PI)
		L2 = L2 - 2 * PI;
	if (L2 < -PI)
		L2 = L2 + 2 * PI;

	a2 = atan(cosu1 * sin(a1) / (cosu1 * cos(sgm) * cos(a1) - sinu1 * sin(sgm)));
	if (sin(a1) < 0)
	{
		if (tan(a2) > 0)
			a2 = fabs(a2);
		else
			a2 = PI - fabs(a2);
	}
	else
	{
		if (tan(a2) > 0)
			a2 = PI + fabs(a2);
		else
			a2 = PI * 2 - fabs(a2);
	}

	// a2 = a2 + PI;
	// if (a2 > 2 * PI)
	//{
	//	a2 = a2 - 2 * PI;
	// }

	B2 = B2 * 180 / PI;
	L2 = L2 * 180 / PI;
	a2 = a2 * 180 / PI;
	
	return {L2, B2};
}

geom::GeoCoordinate
DistanceMetric::Gauss_FirstTheme
 (const geom::GeoCoordinate *coord1, double dist, double a1, double &a2)
{
	double Bm, B1, L1, B2, L2;
	double Nm, V2m, m, e2m, tm;
	double Delt_B, DltA, Delt_l, Delt_a, l;
	double s1, s2, DLT_A, Am, A211;
	double A212, tmp;

	// double a = ParmaA;
	// double b = ParmaB;
	double B = 0;
	// double e1 = EE1;
	// double e2 = EE2;

	L1 = coord1->getLon() * PI / 180.0;
	B1 = coord1->getLat() * PI / 180.0;
	a1 = a1 * PI / 180.0;

	Bm = B1;
	Am = a1;
	Nm = a / sqrt(1 - e1 * sin(Bm) * sin(Bm));

	V2m = 1 + e2 * cos(Bm) * cos(Bm);

	l = dist * sin(a1) / (Nm * cos(Bm));

	m = l * cos(Bm);

	tm = tan(Bm);
	e2m = V2m - 1;

	tmp = B * B / V2m / V2m * e2m * (-1 + tm * tm - e2m - 4 * tm * tm * e2m) / 8.0;
	Delt_B = 1.0 / 24.0 * m * m * (2 + 3 * tm * tm + 2 * e2m) + tmp;

	Delt_l = m * m * tm * tm / 24.0 - B * B / 24.0 / V2m / V2m * (1 + e2m - 9 * e2m * tm * tm);

	Delt_a = 1.0 / 12.0 * m * m * V2m + B * B / 24 / V2m / V2m * (3 + 8 * e2m + 5 * e2m * e2m);

	B = dist / Nm * cos(Am) * V2m * (1 + Delt_B);
	l = dist / Nm * sin(Am) / cos(Bm) * (1 + Delt_l);

	DltA = dist / Nm * sin(Am) * tm * (1 + Delt_l + Delt_a);

	double BB2, ll2, AA21;

	BB2 = B1 + B;
	ll2 = L1 + l;
	AA21 = a1 + DltA + PI;

	bool loopit, btrue, ltrue, Dltatrue;
	double Eps0;
	loopit = true;
	Eps0 = 0.00000000005;

	double b0, l0, dltA0;
	b0 = B;
	l0 = l;
	dltA0 = DltA;

	while (loopit)
	{
		Bm = B1 + 0.5 * B;
		Am = a1 + 0.5 * DltA;
		btrue = true;
		ltrue = true;
		Dltatrue = true;
		Nm = a / sqrt(1 - e1 * sin(Bm) * sin(Bm));

		V2m = 1 + e2 * cos(Bm) * cos(Bm);

		m = l * cos(Bm);

		tm = tan(Bm);
		e2m = V2m - 1;
		tmp = B * B / V2m / V2m * e2m * (-1 + tm * tm - e2m - 4 * tm * tm * e2m) / 8.0;
		Delt_B = 1.0 / 24.0 * m * m * (2 + 3 * tm * tm + 2 * e2m) + tmp;
		Delt_l = m * m * tm * tm / 24.0 - B * B / 24.0 / V2m / V2m * (1 + e2m - 9 * e2m * tm * tm);
		Delt_a = 1 / 12.0 * m * m * V2m + B * B / 24.0 / V2m / V2m * (3 + 8 * e2m + 5 * e2m * e2m);

		B = dist / Nm * cos(Am) * V2m * (1 + Delt_B);
		l = dist / Nm * sin(Am) / cos(Bm) * (1 + Delt_l);
		DltA = dist / Nm * sin(Am) * tm * (1 + Delt_l + Delt_a);

		if ((fabs(B - b0) > Eps0) || (fabs(l - l0) > Eps0) || (fabs(dltA0 - DltA) > Eps0))
		{
			b0 = B;
			l0 = l;
			dltA0 = DltA;
			loopit = true;
		}
		else
		{
			loopit = false;
		}
	}

	BB2 = B1 + B;
	ll2 = L1 + l;
	AA21 = a1 + DltA + PI;

	if (AA21 > 2 * PI)
	{
		AA21 = AA21 - 2 * PI;
	}
	if (AA21 < 0)
	{
		AA21 = AA21 + 2 * PI;
	}

	a2 = AA21 * 180 / PI;
	return {ll2 * 180 / PI, BB2 * 180 / PI};
	// j2 = ll2 * 180 / PI;
	// w2 = BB2 * 180 / PI;
}

double
DistanceMetric::Bessel_SecondTheme(
	const geom::GeoCoordinate *coord1,
	const geom::GeoCoordinate *coord2,
	double &a1,
	double &a2)
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
DistanceMetric::Gauss_SecondTheme(
	const geom::GeoCoordinate *coord1,
	const geom::GeoCoordinate *coord2,
	double &a1,
	double &a2)
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


} // namespace op
} // namespace ep