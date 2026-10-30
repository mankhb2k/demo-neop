# Ghi chú Qt Multimedia

## Module chính

Trong Qt 6, **Qt Multimedia** là module cung cấp API C++ và QML cho phát audio/video, thiết bị media, camera và ghi hình.

### Phát media

Các lớp thường dùng cho video editor/player:

| Chức năng | C++ | QML |
| --- | --- | --- |
| Phát audio/video | `QMediaPlayer` | `MediaPlayer` |
| Đầu ra âm thanh | `QAudioOutput` | `AudioOutput` |
| Hiển thị video | `QVideoSink`, `QVideoWidget` | `VideoOutput` |
| Đọc frame video riêng lẻ | `QVideoSink` | — |

`QMediaPlayer` điều khiển phát media. `QAudioOutput` kết nối âm thanh ra loa/tai nghe. `VideoOutput` hoặc `QVideoSink` nhận video để hiển thị hoặc xử lý frame.

### Âm thanh mức thấp

- `QAudioSink`: phát dữ liệu âm thanh thô.
- `QAudioSource`: thu dữ liệu âm thanh từ thiết bị.
- `QAudioDecoder`: giải mã audio vào bộ nhớ để xử lý.

### Camera và ghi hình

- `QCamera`: truy cập camera.
- `QMediaCaptureSession`: kết nối camera, input/output và recorder.
- `QMediaRecorder`: ghi audio/video.
- `QImageCapture`: chụp ảnh tĩnh từ camera.

### Các module liên quan

- **Qt Multimedia Widgets**: API media cho giao diện Qt Widgets; không cần thiết nếu UI dùng QML.
- **Qt Spatial Audio**: API âm thanh không gian 3D; chưa cần cho editor cơ bản.
- **Qt Quick**: module UI/scene graph dùng với QML; là module riêng, không thuộc Qt Multimedia.

## Dùng trong editor này

Giai đoạn player một video:

- C++ tạo và điều khiển `QMediaPlayer` cùng `QAudioOutput`.
- QML cung cấp `VideoOutput` và phần giao diện.
- Qt Multimedia/backend giải mã và phát media; chưa cần gọi trực tiếp FFmpeg API nếu chỉ cần phát thông thường.

Khi cần lấy frame để xử lý timeline/compositing, có thể dùng `QVideoSink` hoặc chuyển sang pipeline FFmpeg trực tiếp tùy mức kiểm soát cần thiết.

## CMake / QML

Liên kết Qt Multimedia trong CMake:

```cmake
find_package(Qt6 REQUIRED COMPONENTS Multimedia Quick)
target_link_libraries(my_app PRIVATE Qt6::Multimedia Qt6::Quick)
```

Import QML:

```qml
import QtMultimedia
```

## Backend và định dạng

Qt Multimedia dùng backend nền tảng để phát media. Theo tài liệu Qt 6.12, FFmpeg backend là mặc định trên desktop, trong đó có macOS; AVFoundation cũng có backend native trên macOS/iOS. Codec/container hỗ trợ có thể phụ thuộc backend và cấu hình của máy. MP4 và MOV là container; codec bên trong file cũng quyết định khả năng phát.

### Backend theo nền tảng

- **FFmpeg**: backend mặc định của Qt Multimedia trên desktop.
- **AVFoundation (`darwin`)**: backend native của Apple cho macOS/iOS.
- **Windows Media Foundation (`windows`)**: backend native trên Windows. Qt đánh dấu backend này deprecated từ Qt 6.10 và dự kiến loại bỏ trong major version tiếp theo.

Có thể chọn backend bằng biến môi trường `QT_MEDIA_BACKEND`. Thay đổi biến này chỉ có hiệu lực khi khởi chạy tiến trình mới.

## Ghi nhận thử seek

### macOS — 2026-10-30

- App Qt Multimedia được chạy với `QT_MEDIA_BACKEND=darwin` để chọn AVFoundation.
- Khi scrub nhanh trên cùng app/video, người dùng nhận thấy frame theo thanh seek mượt hơn rõ rệt và tốc độ gần ngang player của Apple.
- Trước khi đổi backend, frame không theo kịp khi kéo nhanh.
- Đây là đánh giá cảm nhận, chưa có benchmark thời gian hoặc kiểm thử nhiều file. Kết quả gợi ý backend là yếu tố chính trong khác biệt seek của cấu hình này.

### Quy trình so sánh trên Windows

Dùng cùng một bản app, cùng file video và cùng thao tác seek để so sánh hai backend. Đóng app giữa các lần chạy để biến môi trường được nạp lại.

Trong PowerShell, chạy một lần với FFmpeg:

```powershell
$env:QT_MEDIA_BACKEND = "ffmpeg"
.\appEditorCore.exe
```

Đóng app hoàn toàn, rồi chạy lần nữa với Windows Media Foundation:

```powershell
$env:QT_MEDIA_BACKEND = "windows"
.\appEditorCore.exe
```

Trong Qt Creator, cũng có thể đặt `QT_MEDIA_BACKEND` trong Run Environment của cấu hình chạy; đổi giá trị và khởi chạy lại giữa mỗi lượt thử.

Ghi nhận cho từng backend:

- Frame có theo kịp khi kéo thanh seek nhanh không.
- Mất bao lâu để frame ổn định sau khi thả thanh.
- Có giật, đứng hình, lỗi phát hoặc mất tiếng không.
- Tên codec, độ phân giải và frame rate của file thử.

Nếu backend `windows` không khởi chạy hoặc không phát file, kiểm tra Qt Multimedia backend plugin có trong bộ Qt/build đó và ghi lại log. Kết quả Windows hiện chưa được thử. Vì Windows Media Foundation backend đã deprecated từ Qt 6.10, xem lượt thử này là so sánh kỹ thuật; không nên phụ thuộc vào nó cho kế hoạch dài hạn.

## Tài liệu tham khảo

- [Qt Multimedia](https://doc.qt.io/qt-6/qtmultimedia-index.html)
- [Multimedia Overview](https://doc.qt.io/qt-6/multimediaoverview.html)
- [Video Overview](https://doc.qt.io/qt-6/videooverview.html)
- [Qt Multimedia backend notes](https://doc.qt.io/qt-6/qtmultimedia-index.html#target-platform-and-backend-notes)
