#include "playback.h"

#include <QFileInfo>

#include <algorithm>

// Playback is the media-control layer between the QML controls and Qt
// Multimedia. QML requests an operation; this class updates QMediaPlayer.
// QMediaPlayer sends decoded video to the QVideoSink owned by VideoOutput,
// and decoded audio to QAudioOutput.
Playback::Playback(QObject *parent)
    : QObject(parent)
{
    m_player.setAudioOutput(&m_audioOutput);

    connect(&m_player, &QMediaPlayer::playbackStateChanged, this, [this] {
        emit playingChanged();
        refreshStatusText();
    });
    connect(&m_player, &QMediaPlayer::positionChanged, this, [this] {
        emit positionChanged();
    });
    connect(&m_player, &QMediaPlayer::durationChanged, this, [this] {
        emit durationChanged();
    });
    connect(&m_player, &QMediaPlayer::seekableChanged,
            this, &Playback::seekableChanged);
    connect(&m_player, &QMediaPlayer::mediaStatusChanged, this, [this] {
        refreshStatusText();
    });
    connect(&m_player, &QMediaPlayer::errorOccurred, this,
            [this](QMediaPlayer::Error, const QString &message) {
                m_errorMessage = message;
                emit errorMessageChanged();
                refreshStatusText();
            });
    connect(&m_audioOutput, &QAudioOutput::volumeChanged, this, [this] {
        emit volumeChanged();
    });
    connect(&m_audioOutput, &QAudioOutput::mutedChanged, this, [this] {
        emit mutedChanged();
    });
}

bool Playback::hasSource() const
{
    return m_source.isValid();
}

QString Playback::sourceName() const
{
    if (!m_source.isValid())
        return {};

    if (m_source.isLocalFile())
        return QFileInfo(m_source.toLocalFile()).fileName();

    return m_source.fileName().isEmpty() ? m_source.toString() : m_source.fileName();
}

bool Playback::playing() const
{
    return m_player.playbackState() == QMediaPlayer::PlayingState;
}

bool Playback::seekable() const
{
    return m_player.isSeekable();
}

qint64 Playback::position() const
{
    return m_player.position();
}

qint64 Playback::duration() const
{
    return m_player.duration();
}

qreal Playback::volume() const
{
    return m_audioOutput.volume();
}

bool Playback::muted() const
{
    return m_audioOutput.isMuted();
}

QString Playback::statusText() const
{
    return m_statusText;
}

QString Playback::errorMessage() const
{
    return m_errorMessage;
}

void Playback::openFile(const QUrl &url)
{
    if (!url.isValid())
        return;

    m_player.stop();
    m_source = url;
    m_errorMessage.clear();
    emit sourceChanged();
    emit errorMessageChanged();

    m_player.setSource(m_source);
    refreshStatusText();
}

void Playback::setVideoSink(QVideoSink *sink)
{
    if (m_videoSink == sink)
        return;

    m_videoSink = sink;
    m_player.setVideoSink(m_videoSink);
}

void Playback::togglePlayback()
{
    if (!hasSource())
        return;

    if (playing())
        m_player.pause();
    else
        m_player.play();
}

void Playback::stop()
{
    m_player.stop();
}

void Playback::seekTo(qint64 position)
{
    if (!m_player.isSeekable() || m_player.duration() <= 0)
        return;

    const qint64 boundedPosition = std::clamp(position, qint64(0), m_player.duration());
    m_player.setPosition(boundedPosition);
}

void Playback::setVolume(qreal volume)
{
    const qreal boundedVolume = std::clamp(volume, qreal(0.0), qreal(1.0));
    m_audioOutput.setVolume(static_cast<float>(boundedVolume));
}

void Playback::setMuted(bool muted)
{
    m_audioOutput.setMuted(muted);
}

void Playback::refreshStatusText()
{
    QString newStatus;

    if (!m_errorMessage.isEmpty()) {
        newStatus = m_errorMessage;
    } else if (!hasSource()) {
        newStatus = QStringLiteral("Open a video to begin");
    } else if (m_player.playbackState() == QMediaPlayer::PlayingState) {
        newStatus = QStringLiteral("Playing");
    } else if (m_player.playbackState() == QMediaPlayer::PausedState) {
        newStatus = QStringLiteral("Paused");
    } else {
        switch (m_player.mediaStatus()) {
        case QMediaPlayer::LoadingMedia:
            newStatus = QStringLiteral("Loading video…");
            break;
        case QMediaPlayer::StalledMedia:
            newStatus = QStringLiteral("Waiting for media…");
            break;
        case QMediaPlayer::BufferingMedia:
            newStatus = QStringLiteral("Buffering…");
            break;
        case QMediaPlayer::EndOfMedia:
            newStatus = QStringLiteral("Playback finished");
            break;
        case QMediaPlayer::InvalidMedia:
            newStatus = QStringLiteral("Unsupported or invalid media");
            break;
        default:
            newStatus = QStringLiteral("Ready");
            break;
        }
    }

    if (m_statusText == newStatus)
        return;

    m_statusText = newStatus;
    emit statusTextChanged();
}
