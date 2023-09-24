#include <QApplication>
#include "videoplayer.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("gstreamer-player-backend");

    videoplayer player;

    player.show();
    player.play();
    return app.exec();
}
