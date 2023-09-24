#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H


#include <QWidget>
#include <QMediaPlayer>
#include <QAbstractButton>
#include <QGraphicsVideoItem>
#include <QGraphicsView>
#include <QSlider>
#include <QColorDialog>


class overlay;

class videoplayer : public QWidget
{
    Q_OBJECT

public:
    videoplayer(QWidget* parent = nullptr);
    ~videoplayer();
    void play();

    QSize sizeHint() const;

private slots:
    void leftSliderValueChanged(int value);
    void rightSliderValueChanged(int value);

    void showError(QMediaPlayer::Error error);

private :
    QMediaPlayer*  m_mediaPlayer = nullptr;
    QGraphicsVideoItem* m_videoItem = nullptr;
    QGraphicsView* m_view = nullptr;
    QGraphicsScene* m_scene = nullptr;

	/* control sliders */
    QSlider* m_leftSlider = nullptr;
    QSlider* m_rightSlider = nullptr;

	/* functionality to change overlay color */
    QPushButton* m_btn_colorPicker = nullptr;
    overlay* m_overlay = nullptr;

    /* change the overlay color */
    void openColorDialog();

    /* update the color on Pick Color button */
    void updateButtonColor();
};

#endif // VIDEOPLAYER_H
