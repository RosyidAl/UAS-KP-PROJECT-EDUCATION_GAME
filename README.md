# 7 DAYS BEFORE THE FINAL EXAMS

## Deskripsi Program
**7 DAYS BEFORE THE FINAL EXAMS** merupakan permainan simulasi berbasis terminal yang menggambarkan perjuangan seorang mahasiswa dalam mempersiapkan diri menghadapi ujian akhir selama tujuh hari. Program ini mengombinasikan mekanisme manajemen waktu, pengambilan keputusan, serta kuis singkat untuk melatih pemahaman materi. Setiap keputusan yang diambil pemain akan memengaruhi kondisi karakter, seperti kesehatan, stres, energi, suasana belajar, dan tingkat pemahaman hingga hari ujian tiba.

---

## Fitur Utama
1. **Simulasi 7 Hari Menjelang Ujian**  
   - Permainan berlangsung selama tujuh hari, di mana setiap hari pemain memilih aktivitas seperti belajar, hiburan, olahraga, atau aktivitas lain yang memengaruhi statistik pemain.
2. **Sistem Statistik Pemain**  
   - Program menggunakan berbagai parameter seperti Health, Energy, Stress, Happiness, Fatigue, Study Mood, dan Understanding untuk merepresentasikan kondisi pemain secara realistis.
3. **Mini Quiz Harian**  
   - Terdapat latihan soal pilihan ganda yang muncul secara acak untuk menguji pemahaman pemain. Hasil kuis memengaruhi peningkatan atau penurunan statistik.
4. **Random Event**  
   - Setiap hari berpotensi memunculkan kejadian acak (event) yang dapat memberikan dampak positif maupun negatif terhadap kondisi pemain.
5. **Sistem Save dan Load**  
   - Program menyediakan fitur penyimpanan dan pemuatan data permainan sehingga pemain dapat melanjutkan progres yang telah dicapai.
6. **Multiple Ending**  
   - Hasil akhir permainan ditentukan oleh kondisi pemain saat hari ujian, seperti tingkat pemahaman dan kesehatan, yang menghasilkan peringkat dan gelar berbeda.
7. **Tampilan Terminal Interaktif**  
   - Menggunakan animasi loading, teks typewriter, warna, dan paragraf terpusat untuk meningkatkan pengalaman pengguna di terminal.

---

## Struktur File (Terbaru)
```text
├── src/
│   └── main.cpp           # Kode sumber utama program (sebelumnya UAS_7DaysBeforeTheFinalExams.cpp)
├── data/
│   ├── latihan_soal.txt   # File teks data bank soal (dibutuhkan saat kuis)
│   └── savegame.txt       # File yang akan otomatis dibuat saat Anda melakukan Save
├── prototypes/
│   └── (file prototype lama untuk referensi)
├── bin/                   # Folder hasil compile (otomatis dibuat untuk file executable)
├── README.md
└── .gitignore
```

---

## Persyaratan Sistem (Dependencies)
- **Bahasa Pemrograman**: C++ (C++11 atau versi lebih baru)
- **Compiler**: 
  - Windows: GCC / G++ (MinGW)
  - Linux / macOS: GCC / G++ / Clang
- **Sistem Operasi**: Cross-platform (Dapat berjalan mulus di Windows, Linux, maupun macOS tanpa isu tombol/keyboard khusus).

---

## Cara Instalasi & Menjalankan Program

### 1. Unduh / Clone Repositori
Jalankan perintah berikut pada terminal Anda:
```bash
git clone https://github.com/RosyidAl/UAS-KP-PROJECT-EDUCATION_GAME.git
cd UAS-KP-PROJECT-EDUCATION_GAME
```

### 2. Kompilasi (Compile) Kode
Gunakan `g++` untuk membangun ulang executable dari *source code*. Hasil kompilasi akan disimpan di folder `bin/`.

**Di Linux / macOS:**
```bash
mkdir -p bin
g++ src/main.cpp -o bin/game
```

**Di Windows (MinGW / CMD / PowerShell):**
```cmd
mkdir bin
g++ src/main.cpp -o bin\game.exe
```

### 3. Jalankan Program (Run)

**Di Linux / macOS:**
```bash
./bin/game
```

**Di Windows:**
```cmd
.\bin\game.exe
```

> **Catatan:** Pastikan Anda menjalankan executable dari dalam **root direktori** proyek (`UAS-KP-PROJECT-EDUCATION_GAME`) dan BUKAN dari dalam folder `bin/` ataupun `src/`. Hal ini agar program dapat membaca file `data/latihan_soal.txt` dengan benar.

---

## Kontributor 
- Rosyid Al Ansori (L0125065)
- Rafi Alfarisy N. P. (L0125061)
- Daffabian Farel R. P. (L0125134)
