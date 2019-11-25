#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "play_listmodel.h"
#include<QtMultimedia>
#include<QMediaPlaylist>
#include<QFileDialog>
#include<QFileInfo>
#include<QDir>
#include<QMediaMetaData>
#include<QMessageBox>
#include<QPixmap>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
    //:/icons/animated-music-image-0085.gif
    ui->w->setWindowFlags(Qt::FramelessWindowHint);
    int w=ui->w->width();
    int h=ui->w->height();
    QPixmap *pix=new QPixmap(":/icons/big-bouncing-music-speakeranimated-gif.gif");
    ui->w->setPixmap(pix->scaled(w,h,Qt::KeepAspectRatio));
   QMovie *movie = new QMovie(":/icons/big-bouncing-music-speakeranimated-gif.gif");
   ui->w->setMovie (movie);
   movie->start ();
    playlist =new QMediaPlaylist();
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
	player = new QMediaPlayer(this);
    player->setPlaylist(playlist);
    model = new PlaylistModel();
    model->setPlaylist(playlist);


	player->setVolume(ui->volume->value());
	connect(player, &QMediaPlayer::stateChanged, this, &MainWindow::stateChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);
    connect(ui->actionOpen_File,SIGNAL(ui->actionOpen_File->triggered),this,SLOT(on_actionOpen_File_triggered()));
    connect(playlist, SIGNAL(currentIndexChanged(int)), SLOT(playlistPChanged(int)));
    connect(ui->listView,&QListView::currentIndex,this,&MainWindow::Action);


    ui->listView->setModel(model);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionOpen_File_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(
                this,
                QString("Add Tracks"),
                QDir::homePath(),
                QString("Audio Files (*.mp3 *.m3u);;All Files and Folders (*.*)"));

    QString fileName=fileNames[0];
    QFileInfo fileInfo(fileName);
    appendPlayList(fileNames);


	ui->playButton->setEnabled(true);
	ui->playButton->click();

}
void MainWindow::appendPlayList(QStringList fileNames)
{
    foreach(QString fileName,fileNames)
    {
        QUrl url(fileName);
        playlist->addMedia(url);
    }
}
void MainWindow::on_playButton_clicked()
{
	player->play();

}
void MainWindow::Action()
{
    ui->playButton->setEnabled(true);
}
void MainWindow::on_pauseButton_clicked()
{
	player->pause();
}

void MainWindow::on_stopButton_clicked()
{
	player->stop();
}

void MainWindow::stateChanged(QMediaPlayer::State state)
{
	if (state == QMediaPlayer::PlayingState)
	{
        ui->playButton->setEnabled(true);
		ui->pauseButton->setEnabled(true);
		ui->stopButton->setEnabled(true);
	}
	else if (state == QMediaPlayer::PausedState)
	{
		ui->playButton->setEnabled(true);
		ui->pauseButton->setEnabled(false);
		ui->stopButton->setEnabled(true);
	}
	else if (state == QMediaPlayer::StoppedState)
	{
		ui->playButton->setEnabled(true);
		ui->pauseButton->setEnabled(false);
		ui->stopButton->setEnabled(false);
	}
}

void MainWindow::positionChanged(qint64 position)
{
	if (ui->progressbar->maximum() != player->duration())
		ui->progressbar->setMaximum(player->duration());

	ui->progressbar->setValue(position);

	int seconds = (position/1000) % 60;
	int minutes = (position/60000) % 60;
	int hours = (position/3600000) % 24;
	QTime time(hours, minutes,seconds);
	ui->durationDisplay->setText(time.toString());
}

void MainWindow::on_volume_sliderMoved(int position)
{
	player->setVolume(position);
}

void MainWindow::on_progressbar_sliderMoved(int position)
{
	player->setPosition(position);
}

void MainWindow::on_nextButton_clicked()
{
    playlist->next();


}

void MainWindow::on_prevButton_clicked()
{
    playlist->previous();
}

void MainWindow::on_pushButton_2_clicked()
{
    playlist->shuffle();
}

void MainWindow::on_actionAdd_Song_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(
                this,
                QString("Add Tracks"),
                QDir::homePath(),
                QString("Audio Files (*.mp3);;All Files and Folders (*.*)"));

    QString fileName=fileNames[0];
    QFileInfo fileInfo(fileName);
    appendPlayList(fileNames);


}

void MainWindow::on_pushButton_clicked()
{
    //reset
    playlist->clear();
}
void MainWindow::playlistPChanged(int p)
{
    ui->listView->setCurrentIndex(model->index(p,0));
}


void MainWindow::on_label_linkActivated(const QString &link)
{

}

void MainWindow::on_Volume_clicked()
{
    if(player->isMuted())
    {

        QPixmap pixmap("image_path");
        QIcon ButtonIcon(pixmap);

        //ui->volume->setIcon(ButtonIcon);
       // button->setIconSize(pixmap.rect().size());
        //button->setFixedSize(pixmap.rect().size());
    }
}

void MainWindow::on_shuffleButton_clicked()
{
    playlist->shuffle();
}

void MainWindow::on_Search_textChanged(const QString &arg1)
{
    /*
    }*/


}

void MainWindow::on_mute_clicked()
{
    if(player->isMuted())
        player->setMuted(false);
    else
        player->setMuted(true);
}
