#include "toinitdataconverter.h"
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QLabel>
#include <QDialog>
#include <QVBoxLayout>

ToInitDataConverter::ToInitDataConverter(SceneItemContainer *container, GridScene *scene, QObject *parent) : QObject(parent)
{
    _sceneContainer = container;
    _scene = scene;
}

bool ToInitDataConverter::convertToInitData()
{
    if(!_scene || !_sceneContainer)
        return false;

    QDialog dialog;
    QVBoxLayout layout(&dialog);
    QLabel label("Converting model data to init data..."); //doesn't work!?
    layout.addWidget(&label);
    dialog.show();
    dialog.raise();
    dialog.activateWindow();

    if (!createSourcesIndexFile(*(_sceneContainer->getSceneSources())))
        return false;
    if (!createSourcesBinFile(*(_sceneContainer->getSceneSources())))
        return false;

    if (!createRecieversIndexFile(*(_sceneContainer->getSceneRecievers())))
        return false;

    if (!createBulkBinFile(_scene, *(_sceneContainer->getScenePolygons())))
        return false;
    if (!createRhoXBinFile(_scene, *(_sceneContainer->getScenePolygons())))
        return false;
    if (!createRhoYBinFile(_scene, *(_sceneContainer->getScenePolygons())))
        return false;

    if (!createEmptyFile())
            return false;
    if (!createConfigFile())
        return false;

    return true;
}

bool ToInitDataConverter::createSourcesIndexFile(std::vector<SourceItem *> sources)
{
    auto sourcesIndexFilename = _pathToCalcDir + QString("/") + _sourcesIndexFileName;
    QFile::remove(sourcesIndexFilename);
    QFile file(sourcesIndexFilename);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    for (auto source : sources)
    {
        QPoint sourceCoord = QPoint(source->getParams().x, source->getParams().y);
        auto mappedSource = mapToSceneNode(sourceCoord, _scene);
        if (!mappedSource)
            continue;
        //0 precision because solver's parser expects int?
        out << QString::number(mappedSource->rx(), 'f', 0) + QString(" ") + QString::number(mappedSource->ry(), 'f', 0) + QString(" 0") << endl;
        delete mappedSource;
    }
    return true;
}

bool ToInitDataConverter::createSourcesBinFile(std::vector<SourceItem *> sources)
{
    auto sourcesBinFilename = _pathToCalcDir + QString("/") + _sourcesBinFileName;
    QFile::remove(sourcesBinFilename);
    QFile file(sourcesBinFilename);
    file.open(QIODevice::WriteOnly);
//    QDataStream out(&file);
//    out.setByteOrder(QDataStream::LittleEndian);
    int counter = 0;
    QString pathToRickerScript = QString("/home/pers/code/cfgexec/python/tools/ricker_impulse.py");
    QString begin = QString ("-0.3");
    QString end = QString ("0.07");
    QString num = QString::number(_scene->getParams().time_steps);// + QString(" ");
    QString freq = QString("50");
    for (auto source : sources)
    {
        QPoint sourceCoord = QPoint(source->getParams().x, source->getParams().y);
        auto mappedSource = mapToSceneNode(sourceCoord, _scene);
        if (!mappedSource)
            continue;
        ++counter;
        QProcess p;
        QString params;
        QString filename = _pathToCalcDir + QString("/") + QString("src_u") + QString::number(counter) + QString(".bin");
        params = pathToRickerScript + begin + end + num + freq + filename;
        QStringList par;
        par << pathToRickerScript << begin << end << num << freq << filename;
        p.start("python", par);
        p.waitForFinished(-1);
        QString output(p.readAllStandardOutput());
        output += QString(" ");
    }


    auto concatScriptFileName = _pathToCalcDir + QString("/") + _concatScriptName;
    QFile::remove(concatScriptFileName);
    QFile scriptFile(concatScriptFileName);
    scriptFile.open(QIODevice::WriteOnly);
    QTextStream scriptStream(&scriptFile);

    scriptStream << QString("import numpy as np; np.vstack((");
    int counter2 = 0;
    while (counter2 < counter)
    {
        ++counter2;
        scriptStream << (QString("np.fromfile(\'") + _pathToCalcDir + QString("/src_u") + QString::number(counter2) + QString(".bin\', dtype=\'<f8\')"));
        if (counter2 < counter)
            scriptStream << QString(", ");
    }
    scriptStream << QString(")).T.astype(\'<f8\').tofile(\'") + _pathToCalcDir + QString("/") + _sourcesBinFileName + QString("\')");
    scriptFile.close();

    QProcess p;
    QStringList params;
    params << concatScriptFileName;
    p.start("python", params);
    p.waitForFinished(-1);
    return true;
}

bool ToInitDataConverter::createRecieversIndexFile(std::vector<RecieverGroup *> recievers)
{
    auto recieversIndexFilename = _pathToCalcDir + QString("/") + _recieversIndexFileName;
    QFile::remove(recieversIndexFilename);
    QFile file(recieversIndexFilename);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    for (auto reciever : recievers)
    {
        printRecieversToTextStream(reciever, out);
    }
    return true;
}

void ToInitDataConverter::printRecieversToTextStream(RecieverGroup *reciever, QTextStream& stream)
{
    auto params = reciever->getParams();
    auto currentX = params.firstx;
    for (int i=0; i<params.recieversNumber; ++i, currentX += params.deltax)
    {
        auto rcvPoint = mapToSceneNode(QPoint(currentX, params.y), _scene);
        if (!rcvPoint)
            continue;
        stream << QString::number(rcvPoint->rx(), 'f', 0) + QString(" ") + QString::number(rcvPoint->ry(), 'f', 0) + QString(" 0") << endl;
    }
}

QPoint *ToInitDataConverter::mapToSceneNode(QPoint point, GridScene *scene)
{
    auto params = scene->getParams();
    auto xIndex = (int)(point.rx() / params.space_step_x);
    if (xIndex < 0 || xIndex >= params.nodes_x)
        return NULL;
    auto yIndex = (int)(point.ry() / params.space_step_y);
    if (yIndex < 0 || yIndex >= params.nodes_y)
        return NULL;
    auto returnPoint = new QPoint(xIndex, yIndex);
    return returnPoint;
}

bool ToInitDataConverter::createBulkBinFile(GridScene *scene, std::vector<PolygonItem *> polygons)
{
    auto sourcesBinFilename = _pathToCalcDir + QString("/") + _bulkBinFileName;//QString("test_qt.bin");
    QFile::remove(sourcesBinFilename);
    QFile file(sourcesBinFilename);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out.setByteOrder(QDataStream::LittleEndian);

    auto params = scene->getParams();

    for (int i=0; i<params.nodes_y; ++i)
    {
        for (int j=0; j<params.nodes_x; ++j)
        {
            auto speed = speedInPoint(QPoint(params.space_step_x*j, params.space_step_y*i));
            out << (double)(speed*speed);
        }
    }
    return true;
}

bool ToInitDataConverter::createRhoXBinFile(GridScene *scene, std::vector<PolygonItem *> polygons)
{
    auto sourcesBinFilename = _pathToCalcDir + QString("/") + _rhoXBinFileName;//QString("test_qt.bin");
    QFile::remove(sourcesBinFilename);
    QFile file(sourcesBinFilename);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out.setByteOrder(QDataStream::LittleEndian);

    auto params = scene->getParams();

    for (int i=0; i<params.nodes_y; ++i)
    {
        for (int j=0; j<params.nodes_x; ++j)
        {
            auto density = densityInPoint(QPoint(params.space_step_x*(0.5+j), params.space_step_y*i));
            out << (double)density;
        }
    }
    return true;
}

bool ToInitDataConverter::createRhoYBinFile(GridScene *scene, std::vector<PolygonItem *> polygons)
{
    auto sourcesBinFilename = _pathToCalcDir + QString("/") + _rhoYBinFileName;
    QFile::remove(sourcesBinFilename);
    QFile file(sourcesBinFilename);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out.setByteOrder(QDataStream::LittleEndian);

    auto params = scene->getParams();

    for (int i=0; i<params.nodes_y; ++i)
    {
        for (int j=0; j<params.nodes_x; ++j)
        {
            auto density = densityInPoint(QPoint(params.space_step_x*j, params.space_step_y*(0.5 +i)));
            out << (double)density;
        }
    }
    return true;
}

double ToInitDataConverter::densityInPoint(QPoint point)
{
    double density = _scene->getParams().density;
    auto polygons = *(_sceneContainer->getScenePolygons());
    for (auto polygon: polygons)
    {
        if (polygon->isInsidePolygon(point))
            density = polygon->getParams().density;
    }
    return density;
}

double ToInitDataConverter::speedInPoint(QPoint point)
{
    double speed = _scene->getParams().speed_c;
    auto polygons = *(_sceneContainer->getScenePolygons());
    for (auto polygon: polygons)
    {
     //   if (polygon->isInsidePolygon(point))
         //   speed = polygon->getParams().;
    }
    return speed;
}

bool ToInitDataConverter::createEmptyFile()
{
    auto emptyFileName = _pathToCalcDir + QString("/") + _empty;
    QFile::remove(emptyFileName);
    QFile file(emptyFileName);
    file.open(QIODevice::WriteOnly);
    return true;
}

bool ToInitDataConverter::createConfigFile()
{
    auto configFileName = _pathToCalcDir + QString("/") + _configFileName;
    QFile::remove(configFileName);
    QFile file(configFileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    if (!_scene)
        return false;
    auto sceneParams = _scene->getParams();
    out << "{" << endl;
    out << "order: 2" << endl;
    out << "nodes: [ " << sceneParams.nodes_x << ", " << sceneParams.nodes_y << " ]" << endl;
    out << "space_step: [ " << QString::number(sceneParams.space_step_x, 'f', 8) << ", " << QString::number(sceneParams.space_step_y, 'f', 8) << " ]" << endl;
    out << "time_steps: " << sceneParams.time_steps << endl;
    out << "time_step: " << QString::number(sceneParams.time_step, 'f', 8) << endl;
    out << "material: {" << endl;
    out << "\trho_x : " << _rhoXBinFileName << endl;
    out << "\trho_y : " << _rhoYBinFileName << endl;
    out << "\tbulk : " << _bulkBinFileName << endl;
    out << "}" << endl;
    out << "pml:" << endl;
    out << "\t{" << endl;
    out << "\tlength: " << sceneParams.pml_length << endl;
    out << "\tmax_value: " << sceneParams.pml_maxvalue << endl;
    out << "\t}" << endl;
    out << "sources:" << endl;
    out << "\t{" << endl;
    out << "\t\tpressure: {" << endl;
    out << "\t\t\tindices: " << _sourcesIndexFileName << endl;
    out << "\t\t\tpath: " << _sourcesBinFileName << endl;
    out << "\t\t}" << endl;
    out << "\t\tacceleration: {" << endl;
    out << "\t\t\tx: {" << endl;
    out << "\t\t\t\tindices: " << _empty << endl;
    out << "\t\t\t\tpath: " << _empty << endl;
    out << "\t\t\t}" << endl;
    out << "\t\t\ty: {" << endl;
    out << "\t\t\t\tindices: " << _empty << endl;
    out << "\t\t\t\tpath: " << _empty << endl;
    out << "\t\t\t}" << endl;
    out << "\t\t}" << endl;
    out << "\t}" << endl;
    out << "receivers:" << endl;
    out << "\t{" << endl;
    out << "\t\tpressure: {" << endl;
    out << "\t\t\tindices: " << _recieversIndexFileName << endl;
    out << "\t\t\tpath: " << _recieversBinFileName << endl;
    out << "\t\t}" << endl;
    out << "\t\tacceleration: {" << endl;
    out << "\t\t\tx: {" << endl;
    out << "\t\t\t\tindices: " << _empty << endl;
    out << "\t\t\t\tpath: " << _empty << endl;
    out << "\t\t\t}" << endl;
    out << "\t\t\ty: {" << endl;
    out << "\t\t\t\tindices: " << _empty << endl;
    out << "\t\t\t\tpath: " << _empty << endl;
    out << "\t\t\t}" << endl;
    out << "\t\t}" << endl;
    out << "\t}" << endl;
    out << "wavefields:" << endl;
    out << "\t{" << endl;
    out << "\tpressure: wf_a_*.bin" << endl;
    out << "\tacceleration: {" << endl;
    out << "\t\tx: wf_px_*.bin" << endl;
    out << "\t\ty: wf_py_*.bin" << endl;
    out << "\t\t}" << endl;
    out << "\t save_step: " << sceneParams.save_step << endl;
    out << "\t}" << endl;
    out << "}" << endl;

    return true;
}
