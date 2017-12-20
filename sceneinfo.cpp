#include "sceneinfo.h"
#include "ui_sceneinfo.h"

SceneInfo::SceneInfo(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SceneInfo)
{
	ui->setupUi(this);
}

SceneInfo::~SceneInfo()
{
	delete ui;
}

void SceneInfo::initWithParams(sceneParams params)
{
	ui->nameLine->setText(params.name);
    ui->nodesXBox->setValue(params.nodes_x);
    ui->nodesYBox->setValue(params.nodes_y);
    ui->spaceStepXBox->setValue(params.space_step_x);
    ui->spaceStepYBox->setValue(params.space_step_y);
    ui->timeStepsBox->setValue(params.time_steps);
    ui->timeStepBox->setValue(params.time_step);
    ui->saveStepBox->setValue(params.save_step);
    ui->densityBox->setValue(params.density);
    ui->speedCBox->setValue(params.speed_c);
    ui->pmlLengthBox->setValue(params.pml_length);
    ui->pmlMaxValueBox->setValue(params.pml_maxvalue);
}

sceneParams SceneInfo::constructParams()
{
	sceneParams params;
	params.name = ui->nameLine->text();
    params.nodes_x = ui->nodesXBox->value();
    params.nodes_y = ui->nodesYBox->value();
    params.space_step_x = ui->spaceStepXBox->value();
    params.space_step_y = ui->spaceStepYBox->value();
    params.time_steps = ui->timeStepsBox->value();
    params.time_step = ui->timeStepBox->value();
    params.save_step = ui->saveStepBox->value();
    params.density = ui->densityBox->value();
    params.speed_c = ui->speedCBox->value();
    params.pml_length = ui->pmlLengthBox->value();
    params.pml_maxvalue = ui->pmlMaxValueBox->value();

    return params;
}
