#include "HexCoord.h"
#include <cmath>

HexCoord::HexCoord(int q_, int r_, int s_) : q(q_), r(r_), s(s_)
{

}

HexCoord::~HexCoord()
= default;

HexCoord HexCoord::hexAdd(const HexCoord& a, const HexCoord& b) {
	return {a.getQ() + b.getQ(), a.getR() + b.getR(), a.getS() + b.getS()};
}

HexCoord HexCoord::hexSubtract(const HexCoord& a, const HexCoord& b) {
	return {a.getQ() - b.getQ(), a.getR() - b.getR(), a.getS() - b.getS()};
}


int HexCoord::hexLength(const HexCoord& hex) {
	return int((abs(hex.getQ()) + abs(hex.getR()) + abs(hex.getS())) / 2);
}

int HexCoord::hexDistance(const HexCoord& a, const HexCoord& b) {
	//return a.s;
	return hexLength(hexSubtract(a, b));
}

int HexCoord::getQ() const
{
	return q;
}

int HexCoord::getR() const
{
	return r;
}

int HexCoord::getS() const
{
	return s;
}
