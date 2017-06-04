cmake_minimum_required(VERSION 3.5)

project(player)

set(CMAKE_AUTOMOC on)
set(CMAKE_INCLUDE_CURRENT_DIR on)

find_package(Qt5 REQUIRED Widgets)
find_package(Qt5 REQUIRED Multimedia)
find_package(Qt5 REQUIRED MultimediaWidgets)
#include_directories(/home/gnenux/Qt5.5.0/5.5/gcc_64/include/QtWidgets)
include_directories(/usr/include)
#include_directories(/home/gnenux/Qt5.5.0/5.5/gcc_64/include)

set(IMG saber.jpg)
set(STYLE horizontalSlider.css)



set(SOURCES_FILES main.cpp player.h player.cpp about.cpp about.h Ui.cpp Ui.h volumebutton.h volumebutton.cpp positionSlider.h positionSlider.cpp ListViewItemDelegate.cpp ListViewItemDelegate.h LyricView.cpp LyricView.h LyricViewItemDelegate.cpp LyricViewItemDelegate.h)

add_executable(player ${SOURCES_FILES} ${IMG} ${STYLE})
#link_directories(/home/gnenux/Qt5.5.0/5.5/gcc_64/plugins/audio/)
link_libraries(/home/gnenux/Qt5.5.0/5.5/gcc_64/plugins/audio/libqtaudio_alsa.so)
link_libraries(/home/gnenux/Qt5.5.0/5.5/gcc_64/plugins/audio/libqtmedia_pulse.so)
link_libraries(/home/gnenux/Qt5.5.0/5.5/gcc_64/plugins/mediaservice/libqtmedia_audioengine.so)
target_link_libraries(player Qt5::Widgets)
target_link_libraries(player Qt5::Multimedia)
target_link_libraries(player Qt5::MultimediaWidgets)
#target_link_libraries(player qtmedia_pulse.so)
#target_link_libraries(player qtaudio_alsa.so)