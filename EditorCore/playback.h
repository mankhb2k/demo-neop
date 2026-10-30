#pragma once

#include <QAudioOutput>
#include <QMediaPlayer>
#include <QObject>
#include <QUrl>
#include <QVideoSink>

// Owns media playback, including source loading, transport controls, seeking,
// and audio output. The QML layer uses this object as its playback API.
class Playback final : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool hasSource READ hasSource NOTIFY sourceChanged)
    Q_PROPERTY(QString sourceName READ sourceName NOTIFY sourceChanged)
    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged)
    Q_PROPERTY(bool seekable READ seekable NOTIFY seekableChanged)
    Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(qreal volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(bool muted READ muted WRITE setMuted NOTIFY mutedChanged)
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged)

public:
    explicit Playback(QObject *parent = nullptr);

    bool hasSource() const;
    QString sourceName() const;
    bool playing() const;
    bool seekable() const;
    qint64 position() const;
    qint64 duration() const;
    qreal volume() const;
    bool muted() const;
    QString statusText() const;
    QString errorMessage() const;

    Q_INVOKABLE void openFile(const QUrl &url);
    Q_INVOKABLE void setVideoSink(QVideoSink *sink);
    Q_INVOKABLE void togglePlayback();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void seekTo(qint64 position);
    Q_INVOKABLE void setVolume(qreal volume);
    Q_INVOKABLE void setMuted(bool muted);

signals:
    void sourceChanged();
    void playingChanged();
    void seekableChanged();
    void positionChanged();
    void durationChanged();
    void volumeChanged();
    void mutedChanged();
    void statusTextChanged();
    void errorMessageChanged();

private:
    void refreshStatusText();

    // Keep the player declared after its output so it is destroyed first.
    QAudioOutput m_audioOutput;
    QMediaPlayer m_player;
    QUrl m_source;
    QVideoSink *m_videoSink = nullptr;
    QString m_errorMessage;
    QString m_statusText = QStringLiteral("Open a video to begin");
};
