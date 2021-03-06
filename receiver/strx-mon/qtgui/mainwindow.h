/*
 * Copyright (C) 2013 Alexandru Csete, OZ9AEC
 *
 * strx-mon is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * strx-mon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Ice/Ice.h>
#include <QMainWindow>
#include <QString>
#include <QTime>
#include <QTimer>

#include "../common/gnuradio.h"
#include "statistics_client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(Ice::ObjectPrx ice_prx, QString host, QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    GNURadio::ControlPortPrx ctrlport;
    GNURadio::KnobIDList     id_list_all;  // vector<string>
    GNURadio::KnobIDList     id_list_fft;  // FFT only (fast refresh)
    GNURadio::KnobIDList     id_list_read; // FIXME
    GNURadio::KnobIDList     id_list_filt; // Filter parameters
    GNURadio::KnobIDList     id_list_ctl;  // Various control parameters
    GNURadio::KnobIDList     id_list_rf;   // RF control parameters

    QTime  *statTimer;  /*!< Delay timer used when fetching statistics. */
    QTimer *dataTimer;  /*!< Timer used to fetch data from remote receiver. */
    int     cb_counter; /*!< Callback counter. */

    CStatisticsClient *stats;

    void makeParamList(void);
    int  fftRate();

private slots:
    void refresh(void);
    void statsReceived(unsigned int id, float volt, float tx, float gnc, float aau);
    void on_plotter_newDemodFreq(qint64 freq, qint64 delta);
    void on_plotter_newFilterFreq(int low, int high);
    void on_recButton_toggled(bool checked);
    void on_chanButton_clicked(void);
    void on_gainSpin_valueChanged(int gain);
    void on_fftCombo_currentIndexChanged(int index);
};

#endif // MAINWINDOW_H
