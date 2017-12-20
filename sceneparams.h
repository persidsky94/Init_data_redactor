#ifndef SCENEPARAMS_H
#define SCENEPARAMS_H

#include <QString>

struct sceneParams
{
	QString name;
    int nodes_x;
    int nodes_y;
    double space_step_x;
    double space_step_y;
    int time_steps;
    double time_step;
    int save_step;
    double density;
    double speed_c;
    int pml_length;
    double pml_maxvalue;
};

#endif // SCENEPARAMS_H
