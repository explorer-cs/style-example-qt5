/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "data.h"

#include <QtCore/QRandomGenerator>
#include <QtDataVisualization/QScatterDataProxy>
#include <QtDataVisualization/Q3DScene>
#include <QtDataVisualization/Q3DCamera>
#include <QtDataVisualization/QScatter3DSeries>
#include <QtDataVisualization/Q3DTheme>

#include <QImage>
#include <QColor>
#include <QRgb>

#include <QMessageBox>

#include <QDebug>

#include <eigen3/Eigen/Geometry>

using namespace QtDataVisualization;
using namespace Eigen;

//const int itemCount = 500;

/// modify from qt's offical example

Data::Data(Q3DScatter *scatter)
    : m_graph(scatter),
      //! [1]
      m_inputHandler(new AxesInputHandler(scatter)),
      //! [1]
      m_autoAdjust(false)
{
    m_graph->activeTheme()->setType(Q3DTheme::ThemePrimaryColors);
    m_graph->activeTheme()->setLabelBorderEnabled(true);
    m_graph->activeTheme()->setLabelBackgroundColor(QColor(QRgb(0x151550)));
    m_graph->activeTheme()->setLabelTextColor(Qt::lightGray);
    m_graph->activeTheme()->setFont(QFont("Arial Black", 30));
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetIsometricRight);

    m_graph->axisX()->setRange(0, 1);
    m_graph->axisY()->setRange(0, 1);
    m_graph->axisZ()->setRange(0, 1);

    //! [0]
    // Give ownership of the handler to the graph and make it the active handler
    m_graph->setActiveInputHandler(m_inputHandler);
    //! [0]

    //! [2]
    // Give our axes to the input handler
    m_inputHandler->setAxes(m_graph->axisX(), m_graph->axisZ(), m_graph->axisY());
    //! [2]

    return;
    addData();
}

Data::~Data()
{
    delete m_graph;
}

void Data::setImage(const QImage &img, int &alpha_pixel, double &stddev)
{
    QScatterDataArray *dataArray = new QScatterDataArray;
    QList<QVector3D> list;
    QVector<std::vector<float>> stdlist;

    alpha_pixel = 0;

    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
            QColor color = img.pixelColor(i, j);
            if (color.alpha() == 0) {
                alpha_pixel++;
                continue;
            }

            float r = color.redF();
            float g = color.greenF();
            float b = color.blueF();

            list<<QVector3D(r, g, b);
            QVector<float> v;
            v<<r<<g<<b;
            std::vector<float> stdv = v.toStdVector();
            stdlist<<stdv;
        }
    }
    dataArray->resize(list.count());

    if (dataArray->count() == 0)
        return;

    QScatterDataItem *dataPtr = &dataArray->first();
    for (auto point : list) {
        dataPtr->setPosition(point);
        dataPtr++;
    }

    m_graph->seriesList().at(0)->dataProxy()->resetArray(dataArray);

    std::vector<std::vector<float>> vec;
    vec = stdlist.toStdVector();

    const int rows{ stdlist.count() }, cols{ 3 };

    std::vector<float> vec_;
    for (int i = 0; i < rows; ++i) {
        vec_.insert(vec_.begin() + i * cols, vec[i].begin(), vec[i].end());
    }
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> m(vec_.data(), 1, rows * cols);


    Eigen::MatrixXf mean = m.rowwise().mean(); //<==> m.rowwise().sum() / m.cols();
    float mean_ = mean(0, 0);
    Eigen::MatrixXf sqsum = (m * m.transpose()).rowwise().sum();
    float sqsum_ = sqsum(0, 0);
    float scale = 1. / (rows*cols);
    float variance_ = sqsum_ * scale - mean_ * mean_;
    float stddev_ = std::sqrt(variance_);

    stddev = stddev_;
    qDebug()<<"均值："<<mean_<<"均值平方："<<mean_*mean_<<"平方和："<<sqsum_<<"方差："<<variance_<<"标准差："<<stddev_;
}

void Data::toggleRanges()
{
    if (!m_autoAdjust) {
        m_graph->axisX()->setAutoAdjustRange(true);
        m_graph->axisZ()->setAutoAdjustRange(true);
        m_graph->axisY()->setAutoAdjustRange(true);
        m_inputHandler->setDragSpeedModifier(1.5f);
        m_autoAdjust = true;
    } else {
        m_graph->axisX()->setRange(0, 1);
        m_graph->axisY()->setRange(0, 1);
        m_graph->axisZ()->setRange(0, 1);
        m_inputHandler->setDragSpeedModifier(15.0f);
        m_autoAdjust = false;
    }
}

void Data::addData()
{
    return;

//    QScatter3DSeries *series = new QScatter3DSeries;
//    series->setMesh(QAbstract3DSeries::MeshCube);
//    series->setMeshSmooth(true);
//    m_graph->addSeries(series);

//    QScatter3DSeries *series2 = new QScatter3DSeries;
//    series2->setMesh(QAbstract3DSeries::MeshMinimal);
//    series2->setMeshSmooth(true);
//    m_graph->addSeries(series2);

//    QScatter3DSeries *series3 = new QScatter3DSeries;
//    series3->setMesh(QAbstract3DSeries::MeshSphere);
//    series3->setMeshSmooth(true);
//    m_graph->addSeries(series3);

//    QScatter3DSeries *series4 = new QScatter3DSeries;
//    series4->setMesh(QAbstract3DSeries::MeshBevelCube);
//    series4->setMeshSmooth(true);
//    m_graph->addSeries(series4);

//    QScatter3DSeries *series5 = new QScatter3DSeries;
//    series5->setMesh(QAbstract3DSeries::MeshSphere);
//    m_graph->addSeries(series5);

//    QScatterDataArray *dataArray = new QScatterDataArray;
//    dataArray->resize(itemCount);
//    QScatterDataItem *ptrToDataArray = &dataArray->first();
//    for (int i = 0; i < itemCount; i++) {
//        ptrToDataArray->setPosition(randVector());
//        ptrToDataArray++;
//    }
//    QScatterDataArray *dataArray2 = new QScatterDataArray;
//    dataArray2->resize(itemCount);
//    ptrToDataArray = &dataArray2->first();
//    for (int i = 0; i < itemCount; i++) {
//        ptrToDataArray->setPosition(randVector());
//        ptrToDataArray++;
//    }
//    QScatterDataArray *dataArray3 = new QScatterDataArray;
//    dataArray3->resize(itemCount);
//    ptrToDataArray = &dataArray3->first();
//    for (int i = 0; i < itemCount; i++) {
//        ptrToDataArray->setPosition(randVector());
//        ptrToDataArray++;
//    }
//    QScatterDataArray *dataArray4 = new QScatterDataArray;
//    dataArray4->resize(itemCount);
//    ptrToDataArray = &dataArray4->first();
//    for (int i = 0; i < itemCount; i++) {
//        ptrToDataArray->setPosition(randVector());
//        ptrToDataArray++;
//    }
//    QScatterDataArray *dataArray5 = new QScatterDataArray;
//    dataArray5->resize(itemCount);
//    ptrToDataArray = &dataArray5->first();
//    for (int i = 0; i < itemCount; i++) {
//        ptrToDataArray->setPosition(randVector());
//        ptrToDataArray++;
//    }

//    m_graph->seriesList().at(0)->dataProxy()->resetArray(dataArray);
//    m_graph->seriesList().at(1)->dataProxy()->resetArray(dataArray2);
//    m_graph->seriesList().at(2)->dataProxy()->resetArray(dataArray3);
//    m_graph->seriesList().at(3)->dataProxy()->resetArray(dataArray4);
//    m_graph->seriesList().at(4)->dataProxy()->resetArray(dataArray5);
}

QVector3D Data::randVector()
{
    return QVector3D(
                (float)(QRandomGenerator::global()->bounded(100)) / 2.0f -
                (float)(QRandomGenerator::global()->bounded(100)) / 2.0f,
                (float)(QRandomGenerator::global()->bounded(100)) / 2.0f -
                (float)(QRandomGenerator::global()->bounded(100)) / 2.0f,
                (float)(QRandomGenerator::global()->bounded(100)) / 2.0f -
                (float)(QRandomGenerator::global()->bounded(100)) / 2.0f);
}
