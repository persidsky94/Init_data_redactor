#ifndef TOINITDATACONVERTER_H
#define TOINITDATACONVERTER_H

#include <QObject>
#include <QString>
#include "gridscene.h"
#include "sourceitem.h"
#include "recievergroup.h"
#include "polygonitem.h"
#include "sceneitemcontainer.h"

class ToInitDataConverter : public QObject
{
	Q_OBJECT
public:
    explicit ToInitDataConverter(SceneItemContainer *container, GridScene *scene, QObject *parent = nullptr);

    bool convertToInitData();

    QString _pathToCalcDir = QString("/home/pers/code/calc_acoustic2d");

private:
    const QString _configFileName = QString("config.hrdata");
    const QString _bulkBinFileName = QString("bulk.bin");
    const QString _rhoXBinFileName = QString("rho_x.bin");
    const QString _rhoYBinFileName = QString("rho_y.bin");
    const QString _sourcesIndexFileName = QString("src_u_ind.txt");
    const QString _sourcesBinFileName = QString("src_u.bin");
    const QString _recieversIndexFileName = QString("recv_u_ind.txt");
    const QString _recieversBinFileName = QString("recv_u.bin");
    const QString _empty = QString("empty");
    const QString _concatScriptName = QString("concat_script.py");


    SceneItemContainer *_sceneContainer = NULL;
    GridScene *_scene = NULL;


    bool createConfigFile();
    bool createSourcesIndexFile(std::vector<SourceItem *> sources);
    bool createSourcesBinFile(std::vector<SourceItem *> sources);
    bool createRecieversIndexFile(std::vector<RecieverGroup *> recievers);
    bool createBulkBinFile(GridScene *scene, std::vector<PolygonItem *> polygons);
    bool createRhoXBinFile(GridScene *scene, std::vector<PolygonItem *> polygons);
    bool createRhoYBinFile(GridScene *scene, std::vector<PolygonItem *> polygons);

    bool createEmptyFile();

    void printRecieversToTextStream(RecieverGroup *reciever, QTextStream& stream);
    double densityInPoint(QPoint point);
    double speedInPoint(QPoint point);
    QPoint *mapToSceneNode(QPoint point, GridScene *scene);
};

#endif // TOINITDATACONVERTER_H
