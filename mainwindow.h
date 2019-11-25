#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QTime>
#include "play_listmodel.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_actionOpen_File_triggered();

	void on_playButton_clicked();
	void on_pauseButton_clicked();
	void on_stopButton_clicked();

	void stateChanged(QMediaPlayer::State state);
	void positionChanged(qint64 position);

	void on_volume_sliderMoved(int position);
	void on_progressbar_sliderMoved(int position);
    void appendPlayList(QStringList fileNames);
    void on_nextButton_clicked();

    void on_prevButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionAdd_Song_triggered();

    void on_pushButton_clicked();
    void playlistPChanged(int p);
    void Action();
    void on_label_linkActivated(const QString &link);

    void on_Volume_clicked();

    void on_shuffleButton_clicked();

    void on_Search_textChanged(const QString &arg1);

    void on_mute_clicked();

private:
	Ui::MainWindow *ui;

	QMediaPlayer* player;
    QMediaPlaylist* playlist;
    PlaylistModel * model;


};

#endif // MAINWINDOW_H
