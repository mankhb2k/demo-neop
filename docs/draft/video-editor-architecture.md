# Kiến trúc đề xuất cho video editor C++/QML

## Mục tiêu

Xây dựng ứng dụng biên tập video trên desktop, dùng QML cho giao diện, C++ cho lõi xử lý, FFmpeg cho media I/O và Skia (nếu chọn) cho compositing/paint 2D.

## Sơ đồ tổng thể

```text
QML UI
  │ lệnh/trạng thái qua QObject và QAbstractListModel
  ▼
C++ Editor Core
  ├── Project & Timeline Engine
  ├── Playback / Seek / Frame Cache
  ├── Render Graph / Compositor
  ├── Audio Engine
  └── Export Controller
       │
       ├── FFmpeg: đọc, giải mã, chuyển đổi, trộn, mã hóa
       └── Renderer: Skia hoặc Qt Quick/QRhi
                    │
                    └── Preview texture hiển thị trong QML
```

## Engine có thể dùng sẵn

### Qt Quick / QML

- Dùng QML cho giao diện và Qt Quick cho scene graph của UI.
- Dùng `QObject` và `QAbstractListModel` làm ranh giới giữa QML và trạng thái C++.
- Một item C++ tùy chỉnh có thể đưa nội dung preview vào scene QML.
- Có thể dùng `QQuickRhiItem` khi cần render nội dung vào texture offscreen rồi ghép cùng scene Qt Quick.

### FFmpeg

- `libavformat`: đọc container và demux stream.
- `libavcodec`: giải mã và mã hóa audio/video.
- `libswscale`: chuyển đổi pixel format và scale video khi cần.
- `libswresample`: chuyển đổi sample format, sample rate và layout âm thanh.
- `libavfilter`: dùng filter graph có sẵn khi phù hợp.

### Renderer: chọn một đường chính

- **Qt Quick / QRhi:** phù hợp khi muốn tích hợp trực tiếp với Qt Quick và GPU.
- **Skia:** phù hợp khi cần canvas 2D, paint, text hoặc compositing bằng Skia; cần viết cầu nối C++ để đưa kết quả render vào QML.

Không nên để Qt Quick và Skia cùng quản lý việc vẽ một lớp nội dung. Giữ Qt Quick làm UI; chọn một backend rõ ràng cho nội dung preview/compositing.

## Engine C++ cần tự xây

1. **Project / Timeline Engine**
   - Tracks, clips, trim, split, transition, keyframe và effect parameters.
   - Undo/redo và lưu/mở project.
   - Dùng frame index hoặc timestamp có timebase rõ ràng; tránh dùng `float` cho thời gian timeline.

2. **Playback Engine**
   - Quản lý thời điểm hiện tại của timeline và playback clock.
   - Seek đến frame cần giải mã, điều phối decode queue và đồng bộ video/audio.
   - Quản lý cache frame và chính sách bỏ frame khi playback bị trễ.

3. **Render Graph / Compositor**
   - Xác định clip nào hiện tại đang hoạt động, thứ tự ghép, transform, opacity, text và effects.
   - Nhận frame đã decode từ FFmpeg và tạo nội dung preview.
   - Dùng cùng project model cho preview và export để giảm sai khác kết quả.

4. **Audio Engine**
   - Trộn các audio track, volume, fade và đồng bộ với playback clock.
   - Dùng FFmpeg để decode/resample; nối output với Qt hoặc API âm thanh của hệ điều hành để phát.

5. **Export Controller**
   - Đọc project theo timeline, lấy frame/audio tại các thời điểm cần render.
   - Chuyển nội dung sang FFmpeg encoder/muxer để tạo file đầu ra.
   - Cung cấp progress, cancel và báo lỗi cho UI.

6. **Media / Cache Engine**
   - Đọc metadata, tạo thumbnail/waveform và quản lý cache.
   - Có thể bổ sung proxy media khi tối ưu playback độ phân giải cao.

## Luồng preview

1. QML gửi lệnh play, pause hoặc seek tới Playback Engine.
2. Playback Engine xác định thời điểm timeline và yêu cầu FFmpeg giải mã frame tương ứng.
3. Frame được chuyển đổi sang định dạng renderer cần, nếu cần.
4. Render Graph ghép các clip và effects tại thời điểm đó.
5. Renderer cung cấp texture/frame cho item preview trong QML.
6. Audio Engine phát âm thanh theo cùng playback clock.

## Luồng export

1. Export Controller đọc project và duyệt timeline theo thời gian/frame.
2. FFmpeg giải mã nguồn; Render Graph tạo frame tổng hợp theo project.
3. Audio Engine tạo audio tổng hợp.
4. FFmpeg encode và mux audio/video thành file đầu ra.

Nếu dùng Skia cho preview nhưng FFmpeg filter graph riêng cho export, một số effect có thể cho kết quả khác nhau. Nên định nghĩa effect trong Render Graph của ứng dụng rồi cung cấp backend preview/export tương ứng.

## Thứ tự triển khai MVP

1. Import một video và đọc metadata.
2. Play/pause/seek và hiển thị preview.
3. Timeline một track với trim/split.
4. Thêm audio track và đồng bộ playback.
5. Thêm nhiều track, transform và một số effects cơ bản.
6. Export file video.

Nên bắt đầu với CPU frame path đơn giản để xác nhận pipeline. Sau đó tối ưu bằng texture/GPU path nếu hiệu năng yêu cầu.

## Tài liệu tham khảo

- [Qt Quick Scene Graph](https://doc.qt.io/qt-6/qtquick-visualcanvas-scenegraph.html)
- [QQuickRhiItem](https://doc.qt.io/qt-6/qquickrhiitem.html)
- [FFmpeg Documentation](https://ffmpeg.org/documentation.html)
- [Building Skia](https://skia.org/docs/user/build/)
