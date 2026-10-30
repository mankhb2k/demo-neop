import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Dialogs
import QtQuick.Layouts
import QtMultimedia

ApplicationWindow {
    id: window

    width: 1100
    height: 720
    minimumWidth: 760
    minimumHeight: 500
    visible: true
    title: playback.hasSource ? playback.sourceName + " — EditorCore" : "EditorCore Player"
    color: "#101114"

    function formatTime(milliseconds) {
        const totalSeconds = Math.floor(milliseconds / 1000)
        const minutes = Math.floor(totalSeconds / 60)
        const seconds = totalSeconds % 60
        return String(minutes).padStart(2, "0") + ":" + String(seconds).padStart(2, "0")
    }

    FileDialog {
        id: openDialog
        title: "Open video"
        nameFilters: ["Video files (*.mp4 *.mov *.m4v *.mkv *.webm *.avi)", "All files (*)"]
        onAccepted: playback.openFile(selectedFile)
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 66
            color: "#181a1f"

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 22
                anchors.rightMargin: 22
                spacing: 16

                Rectangle {
                    Layout.preferredWidth: 34
                    Layout.preferredHeight: 34
                    radius: 10
                    color: "#7c5cff"

                    Text {
                        anchors.centerIn: parent
                        text: "E"
                        color: "white"
                        font.pixelSize: 19
                        font.bold: true
                    }
                }

                ColumnLayout {
                    spacing: 2

                    Text {
                        text: "EDITORCORE"
                        color: "#f3f3f6"
                        font.pixelSize: 14
                        font.bold: true
                        font.letterSpacing: 1.2
                    }

                    Text {
                        text: "VIDEO PLAYER"
                        color: "#868892"
                        font.pixelSize: 10
                        font.letterSpacing: 1.4
                    }
                }

                Item { Layout.fillWidth: true }

                Text {
                    Layout.maximumWidth: 360
                    text: playback.hasSource ? playback.sourceName : "No video loaded"
                    color: playback.hasSource ? "#c9cad0" : "#777982"
                    font.pixelSize: 13
                    elide: Text.ElideMiddle
                }

                Button {
                    text: "＋  Open video"
                    onClicked: openDialog.open()

                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        font.pixelSize: 13
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 8
                        color: parent.down ? "#6245d8" : parent.hovered ? "#795be9" : "#6b4ee0"
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 18
            radius: 12
            color: "#08090b"
            clip: true

            VideoOutput {
                id: videoOutput
                anchors.fill: parent
                fillMode: VideoOutput.PreserveAspectFit

                Component.onCompleted: playback.setVideoSink(videoOutput.videoSink)
                Component.onDestruction: playback.setVideoSink(null)
            }

            Column {
                anchors.centerIn: parent
                spacing: 12
                visible: !playback.hasSource

                Rectangle {
                    width: 68
                    height: 68
                    radius: 34
                    color: "#191b21"
                    border.color: "#292b33"

                    Text {
                        anchors.centerIn: parent
                        text: "▶"
                        color: "#777982"
                        font.pixelSize: 23
                        leftPadding: 4
                    }
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Open a video to start previewing"
                    color: "#c6c7cd"
                    font.pixelSize: 15
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "MP4 · MOV · MKV · WEBM"
                    color: "#70727c"
                    font.pixelSize: 11
                    font.letterSpacing: 1.2
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 96
            color: "#181a1f"

            ColumnLayout {
                anchors.fill: parent
                anchors.leftMargin: 22
                anchors.rightMargin: 22
                anchors.topMargin: 5
                anchors.bottomMargin: 5
                spacing: 0

                Slider {
                    id: seekSlider
                    Layout.fillWidth: true
                    Layout.preferredHeight: 22
                    from: 0
                    to: Math.max(1, playback.duration)
                    enabled: playback.hasSource && playback.seekable && playback.duration > 0
                    onMoved: playback.seekTo(Math.round(value))

                    Binding {
                        target: seekSlider
                        property: "value"
                        value: playback.position
                        when: !seekSlider.pressed
                    }

                    background: Rectangle {
                        x: seekSlider.leftPadding
                        y: seekSlider.topPadding + seekSlider.availableHeight / 2 - height / 2
                        width: seekSlider.availableWidth
                        height: 4
                        radius: 2
                        color: seekSlider.enabled ? "#373941" : "#292b31"

                        Rectangle {
                            width: seekSlider.visualPosition * parent.width
                            height: parent.height
                            radius: parent.radius
                            color: seekSlider.enabled ? "#8064f5" : "#55515f"
                        }
                    }

                    handle: Rectangle {
                        x: seekSlider.leftPadding
                           + seekSlider.visualPosition * (seekSlider.availableWidth - width)
                        y: seekSlider.topPadding + seekSlider.availableHeight / 2 - height / 2
                        width: 12
                        height: 12
                        radius: 6
                        color: seekSlider.pressed ? "#ffffff" : "#d9d2ff"
                        border.color: "#8064f5"
                        border.width: 2
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    spacing: 16

                    Button {
                        text: playback.playing ? "❚❚" : "▶"
                        enabled: playback.hasSource
                        onClicked: playback.togglePlayback()

                        contentItem: Text {
                            text: parent.text
                            color: parent.enabled ? "white" : "#777982"
                            font.pixelSize: 18
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        background: Rectangle {
                            implicitWidth: 44
                            implicitHeight: 40
                            radius: 9
                            color: parent.down ? "#6245d8" : parent.hovered ? "#795be9" : "#6b4ee0"
                        }
                    }

                    Button {
                        text: "■"
                        enabled: playback.hasSource
                        onClicked: playback.stop()

                        contentItem: Text {
                            text: parent.text
                            color: parent.enabled ? "#d4d5da" : "#777982"
                            font.pixelSize: 14
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        background: Rectangle {
                            implicitWidth: 40
                            implicitHeight: 40
                            radius: 9
                            color: parent.hovered ? "#2b2d34" : "#22242a"
                        }
                    }

                    Text {
                        text: window.formatTime(playback.position) + " / "
                              + window.formatTime(playback.duration)
                        color: "#c1c2c8"
                        font.pixelSize: 12
                        font.family: "monospace"
                    }

                    Item { Layout.fillWidth: true }

                    Text {
                        Layout.maximumWidth: 300
                        text: playback.statusText
                        color: playback.errorMessage.length > 0 ? "#ff8585" : "#8d9099"
                        font.pixelSize: 12
                        elide: Text.ElideRight
                    }

                    Button {
                        text: playback.muted ? "Muted" : "Sound"
                        onClicked: playback.muted = !playback.muted

                        contentItem: Text {
                            text: parent.text
                            color: "#c9cad0"
                            font.pixelSize: 12
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        background: Rectangle {
                            implicitWidth: 58
                            implicitHeight: 36
                            radius: 8
                            color: parent.hovered ? "#2b2d34" : "#22242a"
                        }
                    }

                    Slider {
                        id: volumeSlider
                        Layout.preferredWidth: 118
                        from: 0
                        to: 1
                        value: playback.volume
                        onMoved: playback.setVolume(value)
                    }
                }
            }
        }
    }
}
