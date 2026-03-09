#ifndef PUNKT_HPP
#define PUNKT_HPP

class punkt{

private:

double x, y;

public:

punkt();
punkt(double x, double y);

double getX() const;
double getY() const;

void setX(const double x_);
void setY(const double y_);

};

#endif