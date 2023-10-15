#pragma once
class HexCoord
{
private:
	const int q, r, s;

public:
	//Constructors / destructors
	HexCoord(int q_, int r_, int s_);
	virtual ~HexCoord();

    /*
     * Adding two hex coordinates
     */
	static HexCoord hexAdd(const HexCoord& a, const HexCoord& b);

    /*
     * Subtracting two hex coordinates
     *
     * @param a first hexCoord
     * @param b second hexCoord
     * @return difference between two hexes on the hex grid plane
     *
     */
	static HexCoord hexSubtract(const HexCoord& a, const HexCoord& b);

	static int hexLength(const HexCoord& hex);

    /*
     * Getting distance between two hexes
     *
     * @param a first hexCoord
     * @param b second hexCoord
     * @return distance between two hexes on the hex grid plane
     */
	static int hexDistance(const HexCoord& a, const HexCoord& b);

	//getters
	[[nodiscard]] int getQ() const;
	[[nodiscard]] int getR() const;
	[[nodiscard]] int getS() const;
};


