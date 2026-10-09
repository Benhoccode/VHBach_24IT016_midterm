# BÁO CÁO LẬP TRÌNH HỆ THỐNG GIỮA KỲ

## Cài đặt và thực thi lệnh `ls(1)` đơn giản hóa

**Họ và tên:** Võ Hoàng Bách

**MSSV:** 24IT016

**Môn học:** Lập trình hệ thống (Midterm Project)

**Môi trường phát triển:** NetBSD 10.1 (x86_64)

**Repository:** [GitHub Link](https://github.com/Benhoccode/VHBach_24IT016_midterm.git)

---

## 1. Yêu cầu, Cấu trúc chương trình & Cách thực thi

### 1.1 Yêu cầu hệ thống

* **Hệ điều hành:** NetBSD 10.1 (tương thích môi trường UNIX / Linux)
* **Trình biên dịch C:** `cc` / `gcc`
* **Công cụ build:** `make` (BSD Make / GNU Make)
* **Quản lý mã nguồn:** `git`

---

### 1.2 Cấu trúc chương trình

```text
VHBach_24IT016_midterm/
├── include/
│   ├── defs.h         # Cấu trúc dữ liệu dùng chung (Flags, FileEntry) và headers hệ thống
│   ├── parse.h        # Khai báo hàm xử lý tham số dòng lệnh (getopt)
│   ├── print.h        # Khai báo các hàm in (-l, -n, -i, -s, -F)
│   ├── sort.h         # Khai báo thuật toán sắp xếp (tên, kích thước, thời gian, đảo ngược)
│   ├── traverse.h     # Khai báo hàm duyệt thư mục và đệ quy (-R)
│   └── util.h         # Hàm tiện ích chuyển đổi dung lượng human-readable (-h)
├── src/
│   ├── main.c         # Điểm vào chương trình, phân tách toán hạng file và thư mục
│   ├── parse.c        # Phân tích cờ lệnh và xử lý quy tắc ghi đè của các cờ đối lập
│   ├── print.c        # Định dạng in chi tiết, strmode, UID/GID, inode, block
│   ├── sort.c         # Sắp xếp qsort theo tên, mtime/atime/ctime, size
│   ├── traverse.c     # Duyệt thư mục bằng opendir/readdir, lstat và đệ quy
│   └── util.c         # Định dạng dung lượng dễ đọc và trích xuất timestamp
├── .gitignore
├── Makefile
└── README.md
```

---

### 1.3 Cách thực thi chương trình

**Bước 1: Clone repository**

```bash
git clone https://github.com/Benhoccode/VHBach_24IT016_midterm.git
cd VHBach_24IT016_midterm
```

**Bước 2: Biên dịch chương trình**

```bash
make          # Biên dịch và tạo file thực thi ./my_ls
make clean    # Dọn dẹp các file .o và file thực thi
```

**Bước 3: Cú pháp chạy lệnh**

```bash
./my_ls [flags] [file/directory ...]
```

* **Chú thích:**

  * `./my_ls`: File thực thi được sinh ra sau lệnh `make` (bắt buộc).
  * `[flags]`: Các cờ lệnh tùy chọn (ví dụ: `-a`, `-l`, `-R`,...).
  * `[file/directory]`: Đường dẫn file hoặc thư mục cần xem (mặc định liệt kê thư mục hiện tại nếu để trống).

* **Ví dụ mẫu:**

  * `./my_ls`: In danh sách file/thư mục hiện tại.
  * `./my_ls -a`: Hiển thị tất cả file/thư mục, bao gồm cả file ẩn (`.` và `..`).
  * `./my_ls -la ./include`: Hiển thị thông tin chi tiết tất cả file trong thư mục `./include`.

---

### 1.4 Chức năng các cờ lệnh

| Cờ lệnh | Chức năng                                                                                                       |
| :-----: | :-------------------------------------------------------------------------------------------------------------- |
|   `-A`  | Liệt kê tất cả thư mục và file, ngoại trừ `.` và `..`                                                           |
|   `-a`  | In tất cả thư mục và file, bao gồm cả `.` và `..`                                                               |
|   `-c`  | Sử dụng thời điểm thay đổi trạng thái file (`ctime`) khi sắp xếp hoặc hiển thị (dùng với `-t` hoặc `-l`)        |
|   `-d`  | Xem thư mục như một file thông thường (không liệt kê nội dung bên trong)                                        |
|   `-F`  | Hiển thị ký tự đánh dấu loại file (`/` thư mục, `*` file thực thi, `@` symlink, `=` socket, `\|` FIFO)          |
|   `-f`  | Không sắp xếp, in theo thứ tự đọc trong thư mục (tự động bật `-a`)                                              |
|   `-h`  | In kích thước file theo dạng human-readable (B, K, M, G)                                                        |
|   `-i`  | In số inode (serial number) của mỗi file/thư mục                                                                |
|   `-k`  | In kích thước file/thư mục theo đơn vị kilobyte (KB)                                                            |
|   `-l`  | Hiển thị danh sách dạng chi tiết (long format: quyền hạn, số liên kết, user, group, kích thước, thời gian, tên) |
|   `-n`  | Tương tự `-l` nhưng hiển thị UID và GID thay vì tên user/group                                                  |
|   `-q`  | Chuyển các ký tự không in được thành dấu `?` (mặc định khi xuất ra terminal)                                    |
|   `-R`  | Liệt kê đệ quy tất cả các thư mục con                                                                           |
|   `-r`  | Đảo ngược thứ tự sắp xếp                                                                                        |
|   `-S`  | Sắp xếp danh sách theo kích thước file giảm dần                                                                 |
|   `-s`  | Hiển thị số block hệ thống tập tin thực tế được cấp phát cho mỗi file                                           |
|   `-t`  | Sắp xếp theo thời gian sửa đổi (`mtime`) mới nhất                                                               |
|   `-u`  | Sử dụng thời gian truy cập gần nhất (`atime`) thay vì `mtime`                                                   |
|   `-w`  | Bắt buộc in nguyên bản các ký tự thô (raw characters)                                                           |

**Lưu ý về các cặp cờ lệnh đối lập:**

Các cặp cờ đối lập bao gồm: `-c`/`-u`, `-R`/`-d`, `-k`/`-h`, `-l`/`-n`, `-w`/`-q`. Cờ nằm ở vị trí bên phải nhất trong câu lệnh sẽ ghi đè tác động của cờ trước đó.

Ví dụ: `./my_ls -ln` sẽ hiển thị ID số (UID/GID) thay vì tên user/group.

---

## 2. Thực hiện demo và kết quả thực nghiệm

Phần này trình bày quá trình biên dịch, thực thi và kiểm tra các chức năng chính của chương trình `my_ls` trên môi trường NetBSD 10.1 (x86_64).

### 2.1. Biên dịch chương trình

**Lệnh thực hiện:**

```bash
make clean && make
```

**Kết quả thực nghiệm:**

```text
rm -f src/*.o my_ls
cc -Wall -Wextra -Iinclude -c src/main.c -o src/main.o
cc -Wall -Wextra -Iinclude -c src/parse.c -o src/parse.o
cc -Wall -Wextra -Iinclude -c src/print.c -o src/print.o
cc -Wall -Wextra -Iinclude -c src/sort.c -o src/sort.o
cc -Wall -Wextra -Iinclude -c src/traverse.c -o src/traverse.o
cc -Wall -Wextra -Iinclude -c src/util.c -o src/util.o
cc -Wall -Wextra -Iinclude -o my_ls src/main.o src/parse.o src/print.o src/sort.o src/traverse.o src/util.o
```

### 2.2. Kiểm tra lệnh mặc định và định dạng chi tiết (`-l`)

**Trường hợp 1: Liệt kê nội dung thư mục hiện tại**

```bash
./my_ls
```

Kết quả:

```text
Makefile
README.md
include
my_ls
src
```

**Trường hợp 2: Hiển thị thông tin chi tiết**

```bash
./my_ls -l
```

Kết quả:

```text
total 128
-rw-r--r--  1 Ben  users    340 Oct  9 21:15 Makefile
-rw-r--r--  1 Ben  users   4210 Oct  9 22:30 README.md
drwxr-xr-x  2 Ben  users    512 Oct  9 20:40 include
-rwxr-xr-x  1 Ben  users  31248 Oct  9 22:15 my_ls
drwxr-xr-x  2 Ben  users    512 Oct  9 21:50 src
```

### 2.3. Kiểm tra khả năng liệt kê thư mục được chỉ định

**Lệnh thực hiện:**

```bash
./my_ls -l ./include
```

Kết quả:

```text
total 24
-rw-r--r--  1 Ben  users   1024 Oct  9 20:30 defs.h
-rw-r--r--  1 Ben  users    180 Oct  9 20:31 parse.h
-rw-r--r--  1 Ben  users    310 Oct  9 20:32 print.h
-rw-r--r--  1 Ben  users    195 Oct  9 20:33 sort.h
-rw-r--r--  1 Ben  users    215 Oct  9 20:33 traverse.h
-rw-r--r--  1 Ben  users    280 Oct  9 20:34 util.h
```

### 2.4. Kiểm tra chức năng hiển thị file ẩn (`-a`, `-A`)

**Trường hợp 1: Sử dụng cờ `-a`**

```bash
./my_ls -a
```

Kết quả:

```text
.
..
.git
.gitignore
Makefile
README.md
include
my_ls
src
```

**Trường hợp 2: Sử dụng cờ `-A`**

```bash
./my_ls -A
```

Kết quả:

```text
.git
.gitignore
Makefile
README.md
include
my_ls
src
```

### 2.5. Kiểm tra định dạng dung lượng dễ đọc (`-h`)

**Lệnh thực hiện:**

```bash
./my_ls -lh
```

Kết quả:

```text
total 128
-rw-r--r--  1 Ben  users   340B Oct  9 21:15 Makefile
-rw-r--r--  1 Ben  users   4.1K Oct  9 22:30 README.md
drwxr-xr-x  2 Ben  users   512B Oct  9 20:40 include
-rwxr-xr-x  1 Ben  users    31K Oct  9 22:15 my_ls
drwxr-xr-x  2 Ben  users   512B Oct  9 21:50 src
```

### 2.6. Kiểm tra chức năng hiển thị số inode (`-i`)

**Lệnh thực hiện:**

```bash
./my_ls -li
```

Kết quả:

```text
total 128
 81234 -rw-r--r--  1 Ben  users    340 Oct  9 21:15 Makefile
 81240 -rw-r--r--  1 Ben  users   4210 Oct  9 22:30 README.md
 80911 drwxr-xr-x  2 Ben  users    512 Oct  9 20:40 include
 81255 -rwxr-xr-x  1 Ben  users  31248 Oct  9 22:15 my_ls
 80920 drwxr-xr-x  2 Ben  users    512 Oct  9 21:50 src
```

### 2.7. Kiểm tra khả năng duyệt thư mục đệ quy (`-R`)

**Lệnh thực hiện:**

```bash
./my_ls -R
```

Kết quả:

```text
Makefile
README.md
include
my_ls
src

./include:
defs.h
parse.h
print.h
sort.h
traverse.h
util.h

./src:
main.c
main.o
parse.c
parse.o
print.c
print.o
sort.c
sort.o
traverse.c
traverse.o
util.c
util.o
```

