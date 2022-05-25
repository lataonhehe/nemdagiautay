
# nemdagiautay

    Bài tập môn LTNC - INT2215 1
    Nguyễn Minh Tuấn
    Mã sinh viên: 21020395

## *Mô tả trò chơi*

### *Giới thiệu*

* Ném đá giấu tay là trò chơi đối kháng 1 vs 1 giải trí với âm nhạc và đồ họa bắt mắt, vui nhộn.
### *Hướng dẫn cài đặt*
#### 1.Cài đặt:
* Chương trình sử dụng file project của Code::Blocks.
* Hãy chắc chắn rằng bạn đã tải đầy đủ Code::Blocks, Mingw và các thư viện SDL2, SDL_image, SDL_ttf, SDL_mixer bản tương thích với thiết bị được sử dụng.
* Tải thư mục nemdagiautay.
* Sửa lại đường dẫn vào file SDL:
	* Nếu bạn chưa có sẵn các thư viện liên kết (các file .dll) trong System, hãy lấy chúng từ SDL2/bin và thả vào thư mục nemdagiautay hoặc System32 (với máy 32 bit)/SysWOW64 (với máy 64 bit).
	* Mở nemdagiautay.cbp bằng Code::Blocks, trong Project/Build options/Search directories/Compiler xóa đường dẫn cũ và thay bằng đường dẫn tới thư mục include/SDL2.
					   trong Linkers xóa đường dẫn cũ và thay bằng đường dẫn tới thư mục lib ứng với các thư viện trên.
* Bên cạnh đó, hãy chắc chắn rằng phần Other linker options trong Project/Build options/Linker settings đã ghi đầy đủ:
			-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
			
#### 2. Chạy chương trình:
* Chọn Build/Rebuild trên thanh điều khiển (hoặc ấn Ctrl-F11), nếu không thành công hãy thử khởi động lại Code::Blocks hoặc kiểm tra lại các thao tác.
* Sau khi build thành công thì chương trình có thể chạy.


### *Cách chơi*

#### 1. Luật chơi
* Hai người chơi điều khiển nhân vật của mình để tránh đạn và ném đối thủ.

* Mỗi người chơi có 25 máu, mỗi máu tương ứng với 1 lần dính đạn.

* Người chơi có thể bị mất máu bởi đạn của chính mình.

#### 2. Các phím thao tác
* Hai người chơi sử dụng bàn phím máy tính để điều khiển con rắn của mình.

    | Chức năng  | Player 1 | Player 2|
    | ------------- |:-------------:| --------|
    | Di chuyển sang trái    | A    |← |
    | Di chuyển sang phải    | D    |→ |
    | Di chuyển lên trên     | W    |↑ |
    | Ném                    | T    |M |
* Các thao tác trò chơi
    * Menu: Dùng thao tác chuột để chọn Play, Options.
    * Options: Dùng thao tác chuột để chọn vũ khí cho mỗi nhân vật.


## *Hình ảnh minh họa*

### More
* [Video demo trò chơi](https://youtu.be/qRMOV3hEJ_I)

## *Các kĩ thuật sử dụng*
### SDL
* Sử dụng các kĩ thuật để render hình ảnh, âm thanh.
* Load hình ảnh, âm thanh đơn giản.

### C++
* Sử dụng các kiến thức về: Mảng, Vector, Class, Struct,...
* Sử dụng phân chia file để quản lí.

### Kĩ thuật khác
* Tính toán, căn chỉnh vị trí các đối tượng hiển thị, dùng map thể hiện các vật cản.
* Tính toán fps, tối ưu bộ nhớ và tài nguyên game sử dụng.
* Phân chia file: Logic game ở một file và SDL ở một file.
* Tạo menu cùng các chức năng.
* Tối giản hàm main dễ dọc, dễ hiểu.

## *Nguồn tham khảo*
* Nguồn hình ảnh, âm thanh: Internet, tự thiết kế.
* Thư viện SDL2: [Lazyfoo](https://lazyfoo.net/tutorials/SDL/index.php).
* Phân chia, quản lí file và logic game: Tham khảo Internet, thầy cô và bạn bè.

## *Kết luận*
* Sau quá trình làm game, em rút ra được việc phân chia, quản lí các đối tượng hết sức quan trọng. Việc phân chia tốt sẽ giúp giảm thời gian sửa lỗi và dễ quản lí.

## *Lời cuối*
*Cảm ơn mọi người đã đọc và đánh giá project.*

#### **Mức điểm tự đánh giá: 9,25-9,5.**

