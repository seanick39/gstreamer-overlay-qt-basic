#include "videoplayer.h"

#include <QtWidgets>
#include "overlay.h"


videoplayer::videoplayer(QWidget* parent)
    :QWidget(parent)
{
    // set up player with scene and view
    m_mediaPlayer = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    const QRect screenGeo = QApplication::desktop()->screenGeometry(this);

    // overlay possible with QGraphicsItems, so use QGraphicsVideoItem instead of QVideoWidget
    m_videoItem = new QGraphicsVideoItem;
    m_videoItem->setSize(QSizeF(screenGeo.width() / 3, screenGeo.height() / 3));
    m_mediaPlayer->setAudioRole(QAudio::VideoRole);
    m_videoItem->setPos(0, 0);
    m_scene = new QGraphicsScene(this);
    m_view = new QGraphicsView(m_scene);

    m_scene->addItem(m_videoItem);


    m_overlay = new overlay(m_videoItem->size().rwidth(), m_videoItem->size().rheight(), QColorConstants::Gray);
    m_overlay->setPos(0, 0);
    m_scene->addItem(m_overlay);

    auto* controlLayout = new QHBoxLayout;
    controlLayout->setContentsMargins(0, 0, 0, 0);

    auto* xlayout = new QHBoxLayout;
    m_leftSlider = new QSlider(this);

	// turn the sliders up to 100 to synchronize with the state of the overlay at height 0
    m_leftSlider->setValue(100);
    m_rightSlider = new QSlider(this);
    m_rightSlider->setValue(100);
    xlayout->addWidget(m_leftSlider);
    xlayout->addWidget(m_view);
    xlayout->addWidget(m_rightSlider);

    QBoxLayout* layout = new QVBoxLayout(this);

    m_btn_colorPicker = new QPushButton("Pick color", this);
    m_btn_colorPicker->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_btn_colorPicker->setMaximumSize(150, 40);
    updateButtonColor();
    layout->addWidget(m_btn_colorPicker);
    layout->addLayout(xlayout);
    layout->addLayout(controlLayout);

    // need Qt's VideoSurface for gstreamer
    m_mediaPlayer->setVideoOutput(m_videoItem->videoSurface());

    // connecting signals and slots to handle overlay heights
    connect(m_leftSlider, &QSlider::valueChanged, this, &videoplayer::leftSliderValueChanged);
    connect(m_rightSlider, &QSlider::valueChanged, this, &videoplayer::rightSliderValueChanged);

    connect(m_btn_colorPicker, &QPushButton::clicked, this, &videoplayer::openColorDialog);
	
	// handle error if backend isn't available
    connect(m_mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &videoplayer::showError);

    // m_mediaPlayer->setMedia(QUrl("gst-pipeline: tcpclientsrc host=127.0.0.1 port=5000 ! decodebin ! videoconvert ! qtvideosink"));
    m_mediaPlayer->setMedia(QUrl("gst-pipeline: tcpclientsrc host=127.0.0.1 port=5000 ! decodebin ! videoconvert ! qtvideosink"));
    m_videoItem->show();
}

videoplayer::~videoplayer(){}

QSize videoplayer::sizeHint() const
{
    return (m_videoItem->size() * qreal(3) / qreal(2)).toSize();
}


void videoplayer::leftSliderValueChanged(int value)
{
    m_overlay->setLeftHeight(m_videoItem->size().height() * (100-value) / 100);
}

void videoplayer::rightSliderValueChanged(int value)
{
    m_overlay->setRightHeight(m_videoItem->size().height() * (100-value) / 100);
}


void videoplayer::updateButtonColor()
{
    auto pixmap = QPixmap(80, 80);
    pixmap.fill(m_overlay->color());
    m_btn_colorPicker->setIcon(pixmap);
}

void videoplayer::play()
{
    m_mediaPlayer->play();
}


void videoplayer::openColorDialog()
{
    auto color = QColorDialog::getColor(m_overlay->color(), this);
    m_overlay->changeColor(color);
    updateButtonColor();
}

void videoplayer::showError(QMediaPlayer::Error)
{
    QMessageBox::critical(this, tr("Error"), m_mediaPlayer->errorString());
    close();
}

