# 🎮 Bài Tập Lớn C++ PTIT – Game AirPlane

📚 **Môn học:** Ngôn ngữ lập trình C++ – PTIT

👨‍🎓 **Sinh viên thực hiện (D23):**

* Nguyễn Trường Thái
* Dương Xuân Quỳnh
* Nguyễn Tiến Dũng

👨‍🏫 **Giảng viên:** Quản Trọng Thế

<p align="center">
  <img width="700" alt="Menu" src="https://github.com/user-attachments/assets/f740f7bd-ac20-4144-b10f-62d3043708cb" />
</p>

---

## 📑 Giới thiệu

Đây là dự án **Bài Tập Lớn C++** tại PTIT, xây dựng trò chơi **AirPlane – Bắn Máy Bay**.
Trò chơi được lập trình bằng **C++** và sử dụng thư viện **SFML** để xử lý đồ họa và âm thanh.

---

## 🔧 Cài đặt & chạy

Clone repo về máy:

```bash
git clone https://github.com/ThaiNT960/BTL-C--PTIT.git
cd BTL-C--PTIT
```

Mở file **AirPlane.sln** bằng **Visual Studio 2022**, build và chạy để trải nghiệm game.

---

## 🕹 Gameplay

* Người chơi điều khiển máy bay chiến đấu, bắn đạn để tiêu diệt kẻ địch.
* Tính điểm dựa trên số lượng kẻ địch bị hạ.
* **Điều khiển:**

  * `W` : Di chuyển lên
  * `A` : Sang trái
  * `S` : Xuống
  * `D` : Sang phải
  * `SPACE` : Bắn

---

## 📸 Hình ảnh minh họa

<p align="center">
  <img width="700" alt="Menu" src="https://github.com/user-attachments/assets/04fa88c2-7ef6-404b-b208-c18bbaec13f1" />
</p>

<p align="center">
  <img width="700" alt="Menu" src="https://github.com/user-attachments/assets/963f64d6-f9b4-4b8e-a488-2e67f85467e8" />
</p>

<p align="center">
  <img width="700" alt="Gameplay" src="https://github.com/user-attachments/assets/a330ef1a-2793-4932-8b38-80312b697c5a" />
</p>

<p align="center">
  <img width="700" alt="Boss Fight" src="https://github.com/user-attachments/assets/df2ce84e-3764-4af9-b545-d16f4134ed04" />
</p>

---

## 📚 Cài đặt & Học SFML

📺 Video hướng dẫn cài đặt: [Xem tại đây](https://www.youtube.com/watch?v=fOmtYmIAmlU)

📚 Series học SFML:

* [Giới thiệu & cơ bản](https://www.youtube.com/watch?v=mLVPY_B3dRU&list=PLZd7ojlRK0byXW3dd-HnucM34JnCPyNkn)
* [Nâng cao & thực hành](https://www.youtube.com/watch?v=ANjk6LsShRo&list=PLZd7ojlRK0bwrL8060OGurG_kaeJc_QOH)

---

## 🎨 Tài nguyên sử dụng

* 🖼 **Ảnh & Background:** [CraftPix](https://craftpix.net/)
* 💥 **Spritesheet vụ nổ:** [OpenGameArt](https://opengameart.org/)
* 🔤 **Phông chữ:** [1001Fonts – Video Game Fonts](https://www.1001fonts.com/video-game-fonts.html?page=2)
* 🛠 **Chỉnh sửa ảnh:** [Photopea](https://www.photopea.com) hoặc Photoshop
* ✂️ **Cắt spritesheet thành ảnh nhỏ:** [EZGIF Sprite Cutter](https://ezgif.com)

---

## ⚠️ 1 số lỗi mắc phải

* Khi tiêu diệt **Boss**, quên xoá phần *scale* đúng cách → dẫn tới vòng đạn tiếp theo trúng vùng đó sẽ **mất hitbox** , đôi khi dính lỗi bất tử

  * 🔧 **Giải pháp tạm thời:** cần reset hoặc clear scale của Boss sau khi tiêu diệt.
  * 📌 **Kết quả:** game vẫn chạy được, nhưng đôi khi gây lỗi va chạm trong màn tiếp theo.<br>
   **Lười fix =)) ,đã đổi tên airplane thành sky warriors, lúc run bị lỗi nhớ chọn x86 ,do cài sfmlx32**

![Visitors](https://komarev.com/ghpvc/?username=ThaiNT96&repo=BTL-Cpp-PTIT&color=blue&style=flat-square)
