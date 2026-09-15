# BÁO CÁO BÀI TẬP VỀ NHÀ CHƯƠNG 04 — CÁC MÔ HÌNH THUẬT TOÁN
**Học phần:** Cấu trúc Dữ liệu và Giải thuật (Mã học phần: INT1306)  
**Học viện:** Học viện Công nghệ Bưu chính Viễn thông (PTIT)

---

## 👨‍🎓 THÔNG TIN SINH VIÊN
- **Họ và tên:** Huỳnh Nguyễn Tiến Anh
- **Mã số sinh viên (MSSV):** N24DCDT001
- **Lớp sinh hoạt:** D24CQDT01-N
- **Nhóm học phần:** Nhóm 01
- **Repository GitHub:** [https://github.com/anhtienhao66a-dotcom/tuan05.git](https://github.com/anhtienhao66a-dotcom/tuan05.git)

---

## 📁 CẤU TRÚC THƯ MỤC MÃ NGUỒN

Repository được tổ chức chuẩn hóa theo các phần của bài tập, gồm đầy đủ cả **3 ngôn ngữ: Python, C++, Julia** cùng các chương trình kiểm chứng độc lập:

```text
.
├── README.md                     # Hướng dẫn chi tiết biên dịch và chạy từng ngôn ngữ
├── Phan_2/                       # Phần 2: Bài toán cái túi 0/1 theo 7 bước chuẩn
│   ├── cai_tui.py                # Cài đặt bằng Python (in bảng f, giá trị max, truy vết)
│   ├── cai_tui.cpp               # Cài đặt bằng C++
│   └── cai_tui.jl                # Cài đặt bằng Julia (chỉ số đánh từ 1)
└── Phan_4/                       # Phần 4: Ba bài toán ứng dụng
    ├── doi_tien.py               # Bài 4.1: Đổi tiền (Tham lam vs Quy hoạch động)
    ├── doi_tien.cpp
    ├── doi_tien.jl
    ├── chon_hoat_dong.py         # Bài 4.2: Chọn hoạt động (4 tiêu chí tham lam & kiểm chứng)
    ├── chon_hoat_dong.cpp
    ├── chon_hoat_dong.jl
    ├── giai_ma_lm.py             # Bài 4.3: Mô hình ngôn ngữ & Thuật toán Viterbi
    ├── giai_ma_lm.cpp
    └── giai_ma_lm.jl
```

---

## 🛠️ YÊU CẦU MÔI TRƯỜNG VÀ TRÌNH BIÊN DỊCH

- **Python:** Phiên bản Python 3.8 trở lên (sử dụng thư viện chuẩn tích hợp `sys`, `itertools`, không cần cài thêm gói ngoài).
- **C++:** Trình biên dịch C++ (g++, clang++, hoặc MSVC). Mã nguồn đã được chuẩn hóa để tương thích 100% với tất cả các chuẩn C++ (từ C++98 đến C++20), không gặp lỗi cú pháp hay thiếu cờ biên dịch.
- **Julia:** Phiên bản Julia 1.6 trở lên (sử dụng thư viện chuẩn `Printf`).

---

## 🚀 HƯỚNG DẪN BIÊN DỊCH VÀ CHẠY TỪNG BÀI TOÁN

---

### 1. Phần 2 — Bài toán cái túi 0/1 (`Phan_2`)
**Bộ dữ liệu chuẩn mục A:** $n = 5$ đồ vật, sức chứa $W = 11$.  
**Kết quả tối ưu:** Giá trị lớn nhất $f[5][11] = 25$, tập đồ vật được chọn là **{C, E}** (tổng trọng lượng: $4 + 7 = 11$).

#### Chạy bằng Python:
```bash
cd Phan_2
python cai_tui.py
```

#### Biên dịch và chạy bằng C++:
```bash
cd Phan_2
g++ -O2 cai_tui.cpp -o cai_tui
# Trên Windows:
cai_tui.exe
# Trên Linux/macOS:
./cai_tui
```

#### Chạy bằng Julia:
*(Ghi chú: Bảng f trong toán học đánh chỉ số từ 0, trong Julia mảng đánh chỉ số từ 1 nên ô f[i][j] tương ứng với `f[i+1, j+1]`)*
```bash
cd Phan_2
julia cai_tui.jl
```

---

### 2. Bài 4.1 — Đổi tiền: Tham lam so với Quy hoạch động (`Phan_4`)
**Nhiệm vụ:** So sánh thuật toán tham lam và quy hoạch động trên 6 bộ mệnh giá chuẩn ở mục B. Phát hiện các bộ mệnh giá mà tham lam cho kết quả không tối ưu (Bộ 1, Bộ 5, Bộ 6).

#### Chạy bằng Python:
```bash
cd Phan_4
python doi_tien.py
```

#### Biên dịch và chạy bằng C++:
```bash
cd Phan_4
g++ -O2 doi_tien.cpp -o doi_tien
# Trên Windows:
doi_tien.exe
# Trên Linux/macOS:
./doi_tien
```

#### Chạy bằng Julia:
```bash
cd Phan_4
julia doi_tien.jl
```

---

### 3. Bài 4.2 — Chọn hoạt động với 4 tiêu chí tham lam (`Phan_4`)
**Nhiệm vụ:** Chạy 4 tiêu chí tham lam (kết thúc sớm nhất, bắt đầu sớm nhất, ngắn nhất, ít chồng lấn nhất) kèm chương trình kiểm chứng độc lập vét cạn tập con trên bộ 10 hoạt động mục C.  
**Kết quả:** Chỉ có tiêu chí **Kết thúc sớm nhất** đạt tối ưu (4 hoạt động: `{H4, H5, H7, H9}`).

#### Chạy bằng Python:
```bash
cd Phan_4
python chon_hoat_dong.py
```

#### Biên dịch và chạy bằng C++:
```bash
cd Phan_4
g++ -O2 chon_hoat_dong.cpp -o chon_hoat_dong
# Trên Windows:
chon_hoat_dong.exe
# Trên Linux/macOS:
./chon_hoat_dong
```

#### Chạy bằng Julia:
```bash
cd Phan_4
julia chon_hoat_dong.jl
```

---

### 4. Bài 4.3 — Ba thuật toán giải mã của mô hình ngôn ngữ & Viterbi (`Phan_4`)
**Nhiệm vụ:** Cài đặt 4 thuật toán: Liệt kê toàn bộ câu dài 3, Giải mã tham lam, Giải mã theo chùm (k = 1, 2, 3) và thuật toán Viterbi gán nhãn cho câu “em học bài toán” kèm kiểm chứng vét cạn 2^4 = 16 dãy nhãn.  
**Kết quả:** Dãy nhãn tối ưu là **N V N N** với xác suất lớn nhất p = 0,001806.

#### Chạy bằng Python:
```bash
cd Phan_4
python giai_ma_lm.py
```

#### Biên dịch và chạy bằng C++:
```bash
cd Phan_4
g++ -O2 giai_ma_lm.cpp -o giai_ma_lm
# Trên Windows:
giai_ma_lm.exe
# Trên Linux/macOS:
./giai_ma_lm
```

#### Chạy bằng Julia:
```bash
cd Phan_4
julia giai_ma_lm.jl
```

---

## 📊 BẢNG ĐỐI CHIẾU VÀ KIỂM CHỨNG KẾT QUẢ GIỮA 3 NGÔN NGỮ

| Bài toán | Python | C++ | Julia | Kết quả đối chiếu & Kiểm chứng độc lập |
| :--- | :---: | :---: | :---: | :--- |
| **Phần 2: Cái túi 0/1** | `25` | `25` | `25` | Trùng khớp 100% với bảng 72 ô tính bằng tay, chọn {C, E} |
| **Bài 4.1: Đổi tiền** | Khớp | Khớp | Khớp | Tham lam sai ở Bộ 1, 5, 6; đúng ở Bộ 2, 3, 4 |
| **Bài 4.2: Chọn hoạt động** | `4` | `4` | `4` | Khớp 100% với kết quả vét cạn tối ưu ({H4, H5, H7, H9}) |
| **Bài 4.3: Giải mã & Viterbi** | Khớp | Khớp | Khớp | Trùng khớp 100% với vét cạn 16 dãy nhãn: `N V N N` (0,001806) |

---
*Báo cáo bài tập hoàn thành phục vụ học phần Cấu trúc Dữ liệu và Giải thuật (INT1306) — Học kỳ 1, Năm học 2026–2027.*