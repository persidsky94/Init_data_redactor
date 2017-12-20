#ifndef POLYGONPARAMS_H
#define POLYGONPARAMS_H

#include <QString>

struct polygonParams
{
	QString name;
	double density;
	// x,y - top left bounding rect coordinates
//    double speed_c;
	double x;
	double y;
};
#endif // POLYGONPARAMS_H
