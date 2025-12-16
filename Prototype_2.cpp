#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream> 
#include <vector> 
#include <conio.h> 

// ==========================================
// LIBRARY UNTUK DELAY WAKTU
// ==========================================
#ifdef _WIN32
#include <windows.h>
void sleepMs(int ms) { Sleep(ms); } 
#else
#include <unistd.h>
void sleepMs(int ms) { usleep(ms * 1000); } 
#endif

// ==========================================
// KEY CODE CONSTANTS (Navigasi Menu)
// ==========================================
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_w 119
#define KEY_W 87
#define KEY_s 115
#define KEY_S 83
#define KEY_ENTER 13

using namespace std;

// ==========================================
// 1. KONFIGURASI WARNA & VISUAL
// ==========================================
const string RESET  = "\033[0m";
const string RED    = "\033[31m";
const string GREEN  = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE   = "\033[34m";
const string MAGENTA= "\033[35m";
const string CYAN   = "\033[36m";
const string WHITE  = "\033[37m";
const string BLINK  = "\033[5m"; 
const string BOLD   = "\033[1m";

struct PlayerStats {
    string playerName = "Mahasiswa";
    int day = 1;
    int happiness = 60;
    int studyMood = 50;
    int stress = 40;
    int understanding = 20;
    int health = 70;
    int maxEnergy = 100;
    int energy = 100;
    bool studiedYesterday = false;
    int collapseCount = 0;
    int fatigue = 0;        
    int highStressDays = 0; 
    int noStudyDays = 0;    
};

struct Question {
    string text;
    string a, b, c, d;
    char answerKey; 
};

// ==========================================
// 2. HELPER VISUAL DASAR
// ==========================================

void clearScreen() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) { system("cls"); return; }
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) { system("cls"); return; }
    DWORD cells = (DWORD)(csbi.dwSize.X * csbi.dwSize.Y);
    COORD home = {0, 0};
    DWORD written = 0;
    FillConsoleOutputCharacterA(hConsole, ' ', cells, home, &written);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cells, home, &written);
    SetConsoleCursorPosition(hConsole, home);
    cout.flush();
#else
    cout << "\033[2J\033[1;1H";
    cout.flush();
#endif
}

void typewriterPrint(string text, int delayMs = 30) {
    for (char c : text) {
        cout << c;
        cout.flush(); 
        if (c != '\033' && c != '[') sleepMs(delayMs);
    }
    cout << "\n";
}

void printCentered(string text) {
    int consoleWidth = 80; 
    int actualLength = 0;
    bool inColorCode = false;
    for(char c : text) {
        if(c == '\033') inColorCode = true;
        if(!inColorCode) actualLength++;
        if(inColorCode && c == 'm') inColorCode = false;
    }
    int padding = (consoleWidth - actualLength) / 2;
    if (padding > 0) cout << string(padding, ' ');
    cout << text << "\n";
}

// FUNGSI BARU: Mencetak paragraf rata kiri (dengan opsi animasi on/off)
void printParagraph(string text, bool animate) {
    cout << "\n";
    if (animate) {
        for (char c : text) {
            cout << c;
            cout.flush();
            if (c == '\n') sleepMs(100); // Jeda agak lama saat ganti baris
            else if (c != '\033') sleepMs(20); // Kecepatan mengetik standar
        }
        cout << "\n";
    } else {
        cout << text << "\n"; // Langsung cetak instan
    }
}

string numToStr(int num) {
    stringstream ss; ss << num; return ss.str();
}

void clamp(int &x, int minVal = 0, int maxVal = 100) {
    if (x < minVal) x = minVal;
    if (x > maxVal) x = maxVal;
}

// ==========================================
// 3. LOGIKA TEXT, NARASI & STATUS
// ==========================================

string getConditionText(const PlayerStats& p) {
    if (p.health < 20) return RED + BLINK + "KRITIS" + RESET; 
    if (p.stress > 80) return RED + "STRESS BERAT" + RESET; 
    if (p.fatigue > 80) return YELLOW + "SANGAT LELAH" + RESET; 
    return GREEN + "PRIMA" + RESET;
}

string getMoodText(int mood) {
    if (mood > 70) return GREEN + "Semangat!" + RESET; 
    if (mood > 40) return YELLOW + "Biasa Saja" + RESET; 
    return RED + "Malas..." + RESET; 
}

string getEventNarrative(int day, int eventID) {
    if (day == 7) {
        return "HARI PENGHAKIMAN SUDAH DEKAT.\nKalender di dinding seolah menatapmu tajam. Suasana kosan hening mencekam.\nBukan hening yang damai, tapi hening sebelum badai. Jantungmu berpacu lebih cepat.";
    }

    switch(eventID) {
        case 0: 
            return "TING! Sebuah notifikasi masuk ke HP-mu pagi-pagi buta.\nTernyata email dari Dosen Killer? Jantungmu mau copot membukanya.\nTapi tunggu... isinya pujian? \"Tugasmu saya jadikan contoh untuk angkatan lain.\"\nRasanya seperti menang lotre! Semangatmu membara seketika.";
        case 1: 
            return "Ugh... Perutmu melilit hebat saat bangun tidur.\nKeringat dingin mengucur di pelipis. Sepertinya sambal ayam geprek semalam adalah kesalahan fatal.\nAlih-alih bersiap belajar, kamu malah menghabiskan pagi ini bolak-balik ke kamar mandi. Tenagamu terkuras habis.";
        case 2: 
            return "BARU SAJA KAMU MEMBUKA MATA, Group Chat angkatan sudah meledak.\n\"REVISI TOTAL! DEADLINE MAJU JADI BESOK!\" teriak ketua tingkat di chat.\nKepalamu langsung pening. Rencana belajarmu hari ini hancur berantakan karena panik serangan fajar ini.";
        case 3: 
            return "Dinding kosan ini sepertinya terbuat dari kertas.\nSejak subuh, tetangga sebelah memutar lagu galau dengan volume speaker hajatan.\nMatamu merah, kepala berat, dan emosi sudah di ubun-ubun. Tidurmu hancur total malam ini.";
        case 4: 
            return "Saat sedang melamun di kantin sarapan, seorang kakak tingkat menghampirimu.\nTanpa banyak bicara, dia memberimu Flashdisk. \"Isinya kisi-kisi soal tahun lalu yang nggak pernah meleset.\"\nIni dia! Harta karun yang dicari semua mahasiswa! Kamu merasa tercerahkan.";
        default: 
            return "Matahari pagi menembus celah gorden kamar kosmu yang berdebu.\nTumpukan buku dan kertas coretan berserakan di lantai, saksi bisu perjuanganmu.\nHari ini sepi. Tidak ada drama, tidak ada gangguan. Hanya ada kamu dan ambisimu untuk lulus.";
    }
}

string getAdvice(const PlayerStats& p) {
    if (p.health < 30) return "TUBUHMU SEKARAT! Jangan memaksakan diri atau kamu akan DO.";
    if (p.stress > 80) return "JIWAMU TERGUNCANG. Kamu butuh hiburan atau tidur segera.";
    if (p.energy < 20) return "Tenaga habis. Produktivitasmu akan hancur jika tidak istirahat.";
    if (p.fatigue > 70) return "Matamu sangat berat. Tidurlah lebih awal malam ini.";
    if (p.understanding < 30) return "Materi tertinggal jauh. Coba curi-curi waktu belajar saat mood bagus.";
    if (p.studyMood > 80) return "Mood sedang sangat bagus! Ini saat emas untuk Belajar Keras.";
    return "Kondisi stabil. Jaga ritme antara belajar dan istirahat.";
}

// ==========================================
// 4. VISUAL MENU & STATS
// ==========================================

void drawTitle() {
    clearScreen();
    cout << "\n\n";
    cout << RED << BOLD << BLINK;
    
    printCentered("##############################################################################");
    printCentered("                                                                              ");
    printCentered("       #######    ######      #    #       #   #####       ");
    printCentered("            #     #     #    # #     #   #    #     #      ");
    printCentered("           #      #     #   #   #     # #     #            ");
    printCentered("          #       #     #  #     #     #       #####       ");
    printCentered("         #        #     #  #######     #            #      ");
    printCentered("        #         #     #  #     #     #      #     #      ");
    printCentered("        #         ######   #     #     #       #####       ");
    printCentered("                                                                             ");
    printCentered("                               BEFORE THE FINAL TEST                                ");
    printCentered("                                                                             ");
    printCentered("##############################################################################");
    
    cout << RESET << "";
}

string drawBar(int current, int max, bool isBadStat) {
    int width = 20; 
    float percent = (float)current / max; 
    int fill = (int)(percent * width);
    if (fill > width) fill = width; 
    if (fill < 0) fill = 0;
    
    string color = RESET; 
    if (!isBadStat) { 
        if (percent >= 0.7) color = GREEN; 
        else if (percent >= 0.4) color = YELLOW; 
        else color = RED + BLINK; 
    } else { 
        if (percent >= 0.7) color = RED + BLINK; 
        else if (percent >= 0.4) color = YELLOW; 
        else color = GREEN; 
    }
    
    string bar = "["; bar += color; 
    for (int i = 0; i < fill; i++) bar += "|"; 
    bar += RESET; 
    for (int i = fill; i < width; i++) bar += "."; 
    bar += "]";
    return bar;
}

void showStats(const PlayerStats& p, string eventText, string actionLog) {
    string border = "=================================================================";
    
    cout << "\n";
    cout << border << "\n";
        // HEADER (HARI + JUDUL INDIKATOR DI SAMPING KANAN)
        cout << "| HARI: " << p.day << "/7"
             << "      " << CYAN << BOLD << "[INDIKATOR KONDISI HARI INI]" << RESET << "\n";
    cout << border << "\n";
    
    // BAGIAN 1: STATISTIK VERTIKAL (Dengan HP Bar)
        // STATUS: representasikan kondisi fisik sebagai sebuah bar di kolom
        int statusScore = (p.health + (100 - p.stress) + (100 - p.fatigue)) / 3;
        if (statusScore < 0) statusScore = 0; if (statusScore > 100) statusScore = 100;
        cout << "| STATUS    : " << drawBar(statusScore, 100, false) << " " << getConditionText(p) << "\n";
    cout << "| KESEHATAN : " << drawBar(p.health, 100, false) << " " << p.health << "% \n";
    cout << "| ENERGI    : " << drawBar(p.energy, p.maxEnergy, false) << " " << p.energy << "/" << p.maxEnergy << "\n";
    cout << "| STRESS    : " << drawBar(p.stress, 100, true) << " " << p.stress << "% \n";
    cout << "| PEMAHAMAN : " << drawBar(p.understanding, 100, false) << " " << p.understanding << "% \n";
    cout << "| FATIGUE   : " << drawBar(p.fatigue, 100, true) << " " << p.fatigue << "% \n";
    cout << "| MOOD      : " << getMoodText(p.studyMood) << "\n";
    cout << border << "\n";

    // BAGIAN 2: INFO EVENT (Pengganti Rekomendasi)
    cout << "| " << MAGENTA << BOLD << "EVENT / SITUASI SAAT INI:" << RESET << "\n";
    if (eventText.empty()) {
        cout << "| " << "Tidak ada kejadian khusus." << "\n";
    } else {
        if (eventText[0] == '\n') eventText.erase(0, 1);
        cout << "| " << eventText << "\n";
    }
    cout << border << "\n";

    // BAGIAN 3: SARAN SINGKAT
    cout << "| " << CYAN << "SARAN SISTEM:" << RESET << "\n";
    cout << "| " << getAdvice(p) << "\n";
    cout << border << "\n";

    // BAGIAN 4: LOG AKTIVITAS
    cout << "| " << YELLOW << "LOG AKTIVITAS:" << RESET << "\n";
    stringstream ss(actionLog); 
    string line;
    while(getline(ss, line)) {
        if(!line.empty()) {
            if (line.length() > 60) line = line.substr(0, 57) + "..."; 
            cout << "| > " << line << "\n";
        }
    }
    cout << border << "\n";
}

int showMainMenu() {
    int selection = 1; int maxChoice = 3; bool selected = false; char key;
    while(!selected) {
        drawTitle(); 
        cout << "\n\n"; 
        if(selection == 1) printCentered(CYAN + BOLD + ">> [1] MULAI BARU <<" + RESET); else printCentered("   [1] MULAI BARU   ");
        if(selection == 2) printCentered(CYAN + BOLD + ">> [2] MUAT GAME (LOAD SAVE) <<" + RESET); else printCentered("   [2] MUAT GAME (LOAD SAVE)   ");
        if(selection == 3) printCentered(RED + BOLD + ">> [3] KELUAR APLIKASI (QUIT) <<" + RESET); else printCentered("   [3] KELUAR APLIKASI (QUIT)   ");
        cout << "\n\n\n"; 
        printCentered(YELLOW + "Gunakan W/S atau PANAH untuk memilih, ENTER untuk oke" + RESET);
        key = _getch(); 
        if (key == -32 || key == 224) { key = _getch(); switch(key) { case KEY_UP: if(selection > 1) selection--; break; case KEY_DOWN: if(selection < maxChoice) selection++; break; } } 
        else { switch(key) { case KEY_w: case KEY_W: if(selection > 1) selection--; break; case KEY_s: case KEY_S: if(selection < maxChoice) selection++; break; case KEY_ENTER: selected = true; break; } }
    }
    return selection;
}

// ==========================================
// 5. FITUR NARASI & GAMEPLAY
// ==========================================

void showPrologue() {
    clearScreen();
    sleepMs(1000);
    cout << "\n\n\n";
    printCentered("7 HARI LAGI..."); sleepMs(2000);
    clearScreen(); cout << "\n\n"; 
    
    typewriterPrint("  Hah... (Menghela napas panjang).", 60);
    typewriterPrint("  Kalender di dinding seolah mengejekku.", 60);
    sleepMs(1000);
    typewriterPrint("\n  Ujian Akhir Semester tinggal menghitung hari.", 40);
    typewriterPrint("  Dosen killer, materi menumpuk setinggi gunung, HAHAHAHA SEPERTINYA AKU BISA GILA SETELAH INI", 40);
    sleepMs(1500);
    typewriterPrint("\n  BENAR-BENAR MEMUAKKAN SEKALI...", 70);
    sleepMs(1000);
    typewriterPrint("\n  ...ERGHH.. SIALAN, AKU TIDAK MAU MATI KONYOL KARENA STRESS DI KOSTAN INI.", 80);
    sleepMs(1000);
    
    // Loading Screen
    cout << "\n\n\n"; 
    string loadingText = "[ MEMULAI HARI PERTAMA ]";
    int padding = (80 - loadingText.length()) / 2;
    cout << "\r"; if (padding > 0) cout << string(padding, ' ');
    for(char c : loadingText) { cout << c; cout.flush(); sleepMs(100); }
    cout << "\n";
    sleepMs(2500);
    
    clearScreen(); 
}

// UPDATE: Sekarang menerima parameter 'animate'
void showCharacterDialogue(const PlayerStats& p, int eventID, bool animate) {
    cout << "\n";
    cout << CYAN << BOLD << "  [" << p.playerName << " bergumam]:" << RESET << "\n";
    string dialogue = "";

    if (eventID != -1) {
        switch(eventID) {
            case 0: dialogue = "  \"Tumben dosen muji. Apa dia salah orang? Ah, bodo amat, ambil aja positifnya.\""; break;
            case 1: dialogue = "  \"Aduh... perutku melilit. SIALAN, SALAH MAKAN APA AKU SEMALAM?\""; break;
            case 2: dialogue = "  \"Revisi lagi?! DOSEN ITU BENAR-BENAR INGIN MEMBUNUHKU PELAN-PELAN.\""; break;
            case 3: dialogue = "  \"TETANGGA SEBELAH WOI! BERISIK BANGET HAJATAN PAGI BUTA.\""; break;
            case 4: dialogue = "  \"Materi rahasia! Hahaha, dewi fortuna sedang tersenyum padaku.\""; break;
        }
    } 
    else if (p.health < 30) dialogue = "  \"KEPALAKU MAU PECAH... badanku panas dingin. Apa aku skip aja hari ini?\"";
    else if (p.stress > 80) dialogue = "  \"AKU NGGAK KUAT... RASANYA PENGEN TERIAK. APA GUNANYA KULIAH?\"";
    else if (p.fatigue > 80) dialogue = "  \"Mata ini... berat banget. Kopi mana kopi...\"";
    else if (p.day == 7) dialogue = "  \"Oke. Hari terakhir. Habis-habisan atau pulang nama.\"";
    else {
        int r = rand() % 3;
        if (r == 0) dialogue = "  \"Satu hari lagi, satu perjuangan lagi. Ayo bangun.\"";
        else if (r == 1) dialogue = "  \"Kosan sepi banget yakk..\"";
        else dialogue = "  \"Semoga hari ini dosen nggak aneh-aneh.\"";
    }

    // Logic Animasi
    if (animate) {
        cout << CYAN; typewriterPrint(dialogue, 30); cout << RESET;
    } else {
        cout << CYAN << dialogue << RESET << "\n";
    }
}

void showActionReaction(int choice, bool isSuccess) {
    cout << "\n" << CYAN << "  [Reaksi]: ";
    string txt = "";
    switch(choice) {
        case 1: 
            if (isSuccess) txt = "\"Yes! Masuk akal! Ternyata nggak sesulit itu kalau fokus.\"";
            else txt = "\"ARGH! APAAN SIH INI?! HURUF-HURUFNYA KAYAK NARI-NARI DI DEPANKU!\""; break;
        case 2: txt = "\"Hah... lega rasanya. Lupakan kuliah sejenak.\""; break;
        case 3: txt = "\"Huh.. hah.. Keringat ini setidaknya nyata, nggak kayak janji dosen.\""; break;
        case 4: txt = "\"Scroll dikit... eh kok udah sejam? SIALAN ALGORITMA TIKTOK.\""; break;
        case 5: txt = "\"Akhirnya... Kasurku sayang, aku pulang kepadamu...\""; break;
        case 99: txt = "\"MATAKU PERIH... JANTUNGMU BERDEBAR... TAPI MATERI INI BELUM SELESAI!\""; break;
    }
    typewriterPrint(txt, 30); cout << RESET << "\n"; sleepMs(1000); 
}

void showChoices() {
    cout << "\n[ PILIH AKTIVITAS ]\n";
    cout << " [1] Belajar Keras  (40 Energi & QUIZ)\n";
    cout << " [2] Hiburan        (25 Energi)\n";
    cout << " [3] Olahraga       (30 Energi)\n";
    cout << " [4] Scroll Medsos  (20 Energi)\n";
    cout << " [5] Tidur (Akhiri Hari & Save)\n"; 
    cout << "\n --------------------------------------\n";
    cout << "  " << RED << "[ Q ] KELUAR / MENU UTAMA" << RESET << "\n";
    cout << " --------------------------------------\n";
}

// ==========================================
// 6. SISTEM SAVE/LOAD & FILE
// ==========================================

vector<Question> loadQuestions() {
    vector<Question> questions;
    ifstream file("latihan_soal.txt");
    if (!file.is_open()) return questions;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        Question q; q.text = line;
        if (!getline(file, q.a)) break; if (!getline(file, q.b)) break;
        if (!getline(file, q.c)) break; if (!getline(file, q.d)) break;
        string keyLine; if (!getline(file, keyLine)) break;
        if (!keyLine.empty()) q.answerKey = keyLine[0];
        questions.push_back(q);
    }
    file.close();
    return questions;
}

const string SAVE_FILE = "savegame.txt";
void saveGame(const PlayerStats& p) {
    ofstream file(SAVE_FILE);
    if (file.is_open()) {
        file << p.playerName << "\n" << p.day << "\n" << p.happiness << "\n" << p.studyMood << "\n" << p.stress << "\n";
        file << p.understanding << "\n" << p.health << "\n" << p.maxEnergy << "\n" << p.energy << "\n";
        file << p.studiedYesterday << "\n" << p.collapseCount << "\n" << p.fatigue << "\n";
        file << p.highStressDays << "\n" << p.noStudyDays << "\n";
        file.close();
    }
}
bool loadGame(PlayerStats& p) {
    ifstream file(SAVE_FILE);
    if (file.is_open()) {
        file >> p.playerName >> p.day >> p.happiness >> p.studyMood >> p.stress;
        file >> p.understanding >> p.health >> p.maxEnergy >> p.energy;
        file >> p.studiedYesterday >> p.collapseCount >> p.fatigue;
        file >> p.highStressDays >> p.noStudyDays;
        file.close(); return true; 
    } return false; 
}

// ==========================================
// 7. INPUT & LOGIC HELPERS
// ==========================================

int getChoiceOrQuit() {
    string input;
    while (true) {
        cout << ">> Pilihan Anda (1-5) atau [Q]: "; cin >> input;
        if (input == "q" || input == "Q") return -1;
        try { int val = stoi(input); if (val >= 1 && val <= 5) return val; else cout << RED << "Masukkan angka 1-5.\n" << RESET; } 
        catch (...) { cout << RED << "Input tidak valid.\n" << RESET; }
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int getIntInRange(int min, int max) {
    int value;
    while (true) {
        cout << ">> Pilih [" << min << "-" << max << "]: ";
        if (cin >> value) { cin.ignore(numeric_limits<streamsize>::max(), '\n'); if (value >= min && value <= max) return value; } 
        else { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
        cout << RED << "Input tidak valid.\n" << RESET;
    }
}

// ==========================================
// 8. ANIMASI LOADING LAINNYA
// ==========================================
void printCenteredLoadingBar() {
    string padding(22, ' '); cout << padding << "Loading: [";
    for (int i = 0; i < 20; i++) { cout << "="; cout.flush(); sleepMs(50); }
    cout << "] 100%\n";
}
void showLoadingDayChange() {
    clearScreen(); cout << "\n\n\n";
    printCentered(GREEN + "Kamu beristirahat dengan tenang..." + RESET);
    printCentered(YELLOW + "Mengakhiri hari dan memulihkan energi..." + RESET);
    cout << "\n"; printCenteredLoadingBar(); sleepMs(1500); 
}
void showForcedCollapseLoading(string actionName) {
    clearScreen(); cout << "\n\n\n";
    printCentered(RED + "Kamu memaksakan " + actionName + "..." + RESET);
    printCentered(RED + "...lalu AMBRUK PINGSAN." + RESET);
    cout << "\n"; printCentered(YELLOW + "Mengakhiri hari dan memulihkan energi..." + RESET);
    cout << "\n"; printCenteredLoadingBar(); sleepMs(2500); 
}
void showLoadingReturnMenu() {
    clearScreen(); cout << "\n\n\n";
    printCentered("Menutup permainan..."); cout << "\n";
    string padding(23, ' '); cout << padding << "System: [";
    for (int i = 0; i < 20; i++) { cout << "#"; cout.flush(); sleepMs(40); }
    cout << "] OK\n"; sleepMs(800); 
}

// ==========================================
// 9. GAME LOGIC (QUIZ & EVENTS)
// ==========================================

bool runMiniQuiz(const vector<Question>& questions) {
    if (questions.empty()) return true; 
    int idx = rand() % questions.size();
    Question q = questions[idx];
    clearScreen(); cout << "\n\n";
    printCentered("======================================");
    printCentered(CYAN + BOLD + "LATIHAN SOAL HARIAN" + RESET);
    printCentered("======================================"); cout << "\n";
    cout << "  Soal: \n  " << YELLOW << q.text << RESET << "\n\n";
    cout << "  [A] " << q.a << "\n  [B] " << q.b << "\n  [C] " << q.c << "\n  [D] " << q.d << "\n\n";
    char ans; cout << "  >> Jawaban Anda (A/B/C/D): "; cin >> ans; ans = toupper(ans);
    cout << "\n  Mengecek jawaban"; for(int i=0; i<3; i++) { cout << "."; cout.flush(); sleepMs(300); }
    if (ans == q.answerKey) { cout << " " << GREEN << BOLD << "BENAR!" << RESET << "\n"; sleepMs(1000); return true; } 
    else { cout << " " << RED << BOLD << "SALAH!" << RESET << "\n  Jawaban: " << q.answerKey << "\n"; sleepMs(1500); return false; }
}

string applyChoice(PlayerStats& p, int choice, bool quizSuccess) {
    string log = ""; bool kondisiBuruk = (p.health < 50 || p.stress > 70);
    switch (choice) {
        case 1: { 
            int gain = 0;
            if (quizSuccess) { gain = (p.understanding < 40) ? 15 : ((p.understanding < 70) ? 10 : 6); p.studyMood += 10; log = "Belajar Sukses! (Paham +" + numToStr(gain) + ")"; } 
            else { gain = 4; p.stress += 8; log = "Belajar Sulit. (Paham +4)"; }
            int penalty = p.fatigue / 15; gain -= penalty; if (gain < 1) gain = 1;
            if (kondisiBuruk) p.fatigue += 8; else p.fatigue += 3;
            p.understanding += gain; p.stress += 5; p.happiness -= 5; p.health -= 5; break;
        }
        case 2: log = "Hiburan. (Happy +15, Stress -10)"; p.happiness += 15; p.stress -= 10; p.studyMood += 5; p.fatigue -= 3; break;
        case 3: log = "Olahraga. (Health +10)"; p.health += 10; p.stress -= 5; p.happiness += 5; p.fatigue -= 4; break;
        case 4: log = "Scroll medsos. (Happy +5, Mood -10)"; p.happiness += 5; p.stress += 5; p.studyMood -= 10; break;
    }
    clamp(p.happiness); clamp(p.studyMood); clamp(p.stress); clamp(p.understanding); clamp(p.health); clamp(p.fatigue, 0, 100);
    return log;
}

string applyChoiceWithQuiz(PlayerStats& p, int choice, bool quizSuccess) { return applyChoice(p, choice, quizSuccess); }
string applyForgettingAtMorning(PlayerStats& p) {
    int before = p.understanding; string msg = "";
    if (!p.studiedYesterday) {
        int loss = (p.understanding >= 80) ? 8 : ((p.understanding >= 50) ? 6 : 4);
        p.understanding -= loss; if (p.understanding < 0) p.understanding = 0;
        if (p.understanding < before) msg = "[!] Tidak belajar kemarin, hafalan hilang -" + numToStr(loss) + ".\n";
    } else { p.understanding -= 1; if (p.understanding < 0) p.understanding = 0; }
    return msg;
}
int triggerRandomEvent(PlayerStats& p, string& logBuffer) {
    int roll = rand() % 100; if (roll >= 50) return -1; 
    int type = rand() % 5; 
    if (type == 0) { p.happiness += 20; p.stress -= 15; p.studyMood += 10; logBuffer = "\n[EVENT] Dosen memuji tugasmu! (Happy +20, Stress -15)"; return 0; } 
    else if (type == 1) { p.health -= 20; p.energy -= 30; p.stress += 10; if (p.energy < 0) p.energy = 0; logBuffer = "\n[EVENT] Sakit perut parah! (Health -20, Energi -30)"; return 1; } 
    else if (type == 2) { p.stress += 25; p.studyMood -= 15; p.happiness -= 10; logBuffer = "\n[EVENT] Revisi dadakan dosen! (Stress +25)"; return 2; } 
    else if (type == 3) { p.fatigue += 20; p.energy -= 15; if (p.energy < 0) p.energy = 0; logBuffer = "\n[EVENT] Tetangga berisik. (Fatigue +20)"; return 3; } 
    else { p.understanding += 10; p.happiness += 5; logBuffer = "\n[EVENT] Materi rahasia kating. (Paham +10)"; return 4; }
}
int getEnergyCost(int choice) { switch (choice) { case 1: return 40; case 2: return 25; case 3: return 30; case 4: return 20; default: return 0; } }
string applySleep(PlayerStats& p, bool earlySleep) {
    int baseHealthGain = earlySleep ? 12 : 8; int baseStressDrop = earlySleep ? 12 : 7; int fatiguePenalty = p.fatigue / 20;
    baseHealthGain -= fatiguePenalty; baseStressDrop -= fatiguePenalty; if (baseHealthGain < 3) baseHealthGain = 3; if (baseStressDrop < 3) baseStressDrop = 3;
    p.health += baseHealthGain; p.stress -= baseStressDrop; p.happiness += earlySleep ? 4 : 1; p.fatigue -= earlySleep ? 6 : 4; p.energy = p.maxEnergy;
    clamp(p.health); clamp(p.stress); clamp(p.happiness); clamp(p.fatigue, 0, 100);
    return earlySleep ? "Tidur tepat waktu." : "Ketiduran.";
}
string applyBegadangPenalty(PlayerStats& p) {
    p.health -= 15; p.stress += 15; p.happiness -= 5; p.maxEnergy -= 10; p.fatigue += 12;
    if (p.maxEnergy < 60) p.maxEnergy = 60; if (p.energy > p.maxEnergy) p.energy = p.maxEnergy;
    clamp(p.health); clamp(p.stress); clamp(p.happiness); clamp(p.fatigue, 0, 100);
    return " [!] BEGADANG. (Health -15)";
}

void showEnding(const PlayerStats& p) {
    clearScreen(); cout << "\n\n";
    printCentered(BOLD + "HARI UJIAN AKHIR TELAH TIBA" + RESET); cout << "\n";
    typewriterPrint("\tKamu duduk di ruang ujian...", 50); sleepMs(500);
    string progressBar = "\tMengerjakan soal: ["; cout << progressBar;
    for (int i = 0; i < 20; i++) { int delay = (p.health > 50) ? 50 : 150; sleepMs(delay); if (p.understanding > (i * 5)) cout << "="; else cout << "."; cout.flush(); }
    cout << "] Selesai!\n\n"; sleepMs(1000);
    typewriterPrint("\tDosen sedang menilai lembar jawabanmu...", 60); sleepMs(2000); 
    clearScreen();

    string rank, title, color, message;
    if (p.health <= 0) { rank = "F (DROP OUT)"; title = "PASIEN RUMAH SAKIT"; color = RED; message = "Kamu tidak bisa mengikuti ujian karena dirawat intensif.\nKesehatanmu hancur demi ambisi yang salah."; } 
    else if (p.understanding >= 90 && p.stress <= 40) { rank = "S (Perfect)"; title = "DEWA KAMPUS"; color = GREEN + BLINK; message = "Nilaimu Sempurna! Dosen terkejut melihat jawabanmu.\nKamu menjadi legenda di angkatan ini."; } 
    else if (p.understanding >= 75) { rank = "A (Excellent)"; title = "MAHASISWA TELADAN"; color = GREEN; message = "Kamu lulus dengan nilai sangat memuaskan.\nKerja kerasmu terbayar lunas!"; } 
    else if (p.understanding >= 50) { rank = "B (Standard)"; title = "MAHASISWA RATA-RATA"; color = YELLOW; message = "Kamu lulus, meski tidak terlalu istimewa.\nYang penting aman dan bisa lanjut semester depan."; } 
    else { rank = "D (Failed)"; title = "CALON MAHASISWA ABADI"; color = RED; message = "Nilaimu hancur. Sebagian besar jawabanmu salah.\nSiap-siap mengulang mata kuliah ini tahun depan."; }

    cout << "\n\n"; printCentered(BOLD + "TRANSKRIP NILAI AKHIR" + RESET); cout << "\n";
    string padding = "\t   ";
    typewriterPrint(padding + "NAMA  : " + p.playerName); sleepMs(300);
    string rankStr = padding + "RANK  : " + color + rank + RESET; typewriterPrint(rankStr); sleepMs(300);
    string titleStr = padding + "GELAR : " + color + title + RESET; typewriterPrint(titleStr); sleepMs(300);
    cout << "\n"; printCentered("[ STATISTIK PERJUANGAN ]"); sleepMs(500);
    typewriterPrint(padding + "> Pemahaman Akhir : " + numToStr(p.understanding) + "/100", 40);
    cout << "\n"; printCentered("[ KESIMPULAN ]"); sleepMs(500);
    cout << "\n" << CYAN << "  [Kata Terakhir]: " << message << RESET << "\n";
    sleepMs(2000); cout << "\n\n"; printCentered("Tekan Enter untuk kembali ke Menu Utama..."); cin.get(); cin.get();
}

// ==========================================
// 10. MAIN CONTROLLER
// ==========================================
int main() {
    srand((unsigned)time(nullptr));
    vector<Question> questions = loadQuestions();

    while (true) {
        PlayerStats p;
        bool backToMenu = false; 
        int menuChoice = showMainMenu();
        
        clearScreen(); // 1. BERSIHKAN LAYAR SETELAH MENU

        if (menuChoice == 3) { cout << "\n\n"; printCentered("Sampai Jumpa!"); sleepMs(1000); return 0; }
        if (menuChoice == 2) {
            if (loadGame(p)) { 
                cout << "\n\n"; printCentered(GREEN + "SAVE GAME DITEMUKAN!" + RESET);
                printCentered("Selamat datang kembali, " + p.playerName); sleepMs(2000); 
            } else { 
                cout << "\n\n"; printCentered(RED + "Tidak ada Save Game." + RESET); sleepMs(1500); 
                clearScreen(); cout << "\n\n"; printCentered("[ GAME BARU ]");
                cout << "\n            Masukkan Nama Panggilanmu (Tanpa Spasi): "; cin >> p.playerName; cin.ignore(); showPrologue(); 
            } 
        } else if (menuChoice == 1) {
            cout << "\n\n"; printCentered(CYAN + BOLD + "[ MEMULAI PERJALANAN BARU ]" + RESET);
            cout << "\n            Masukkan Nama Panggilanmu (Tanpa Spasi): "; cin >> p.playerName; cin.ignore(); showPrologue(); 
        }

        if(questions.empty()) { cout << RED << "\n[INFO] Mode belajar otomatis aktif.\n" << RESET; sleepMs(2000); }

        while (p.day <= 7 && !backToMenu) {
            saveGame(p); 
            
            string actionLog = ""; 
            string eventLog = "";
            string statusLog = ""; 

            if (p.day > 1) statusLog += applyForgettingAtMorning(p);
            
            // 1. TRIGGER EVENT DULUAN
            int eventID = triggerRandomEvent(p, eventLog); 
            
            // 2. AMBIL NARASI BERDASARKAN EVENT
            string dailyNarrative = getEventNarrative(p.day, eventID);

            bool endDay = false; 
            bool studiedToday = false;
            
            // FLAG UNTUK ANIMASI: Hanya true saat render pertama hari itu
            bool isFirstRender = true;

            while (!endDay && !backToMenu) {
                clearScreen(); 
                
                // BAGIAN 1: NARASI (Rata Kiri, Animasi Conditional)
                // Warna putih redup biar kayak storyteller
                cout << "\n";
                // Garis pembatas atas
                cout << "------------------------------------------------------------------------------" << "";
                printParagraph(dailyNarrative, isFirstRender); 
                // Garis pembatas bawah
                cout << "------------------------------------------------------------------------------" << "\n";
                
                // BAGIAN 2: DIALOG KARAKTER (Reaksi, Animasi Conditional)
                showCharacterDialogue(p, eventID, isFirstRender); 
                
                // BAGIAN 3: STATS (Selalu Instan)
                showStats(p, eventLog, statusLog + actionLog); 
                
                // Matikan animasi untuk render berikutnya dalam hari yang sama
                isFirstRender = false;

                showChoices();
                
                int choice = getChoiceOrQuit(); 
                if (choice == -1) { 
                    char confirm; cout << "\n" << YELLOW << "Simpan & Keluar? (y/n): " << RESET; cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') { saveGame(p); }
                    if (confirm != 'c' && confirm != 'C') { showLoadingReturnMenu(); backToMenu = true; }
                }
                else if (choice == 5) { 
                    showActionReaction(5, true); showLoadingDayChange(); applySleep(p, true); endDay = true; 
                } else {
                    int cost = getEnergyCost(choice);
                    if (p.energy >= cost) {
                        p.energy -= cost;
                        bool quizResult = true;
                        if (choice == 1) quizResult = runMiniQuiz(questions);
                        showActionReaction(choice, quizResult); 
                        actionLog = applyChoiceWithQuiz(p, choice, quizResult); 
                        if (choice == 1) studiedToday = true;
                        eventID = -1; // Reset dialog event setelah aksi pertama
                    } else {
                        clearScreen(); showStats(p, eventLog, actionLog); 
                        cout << "\n\n\t" << RED << BLINK << "!!! PERINGATAN: ENERGI HABIS !!!" << RESET << "\n";
                        cout << "\t[1] Tidur (Pulihkan)   [2] Paksakan (Bahaya)\n";
                        int sub = getIntInRange(1, 2);
                        if (sub == 1) { showActionReaction(5, true); showLoadingDayChange(); applySleep(p, false); endDay = true; } 
                        else {
                            string actName = (choice==1)?"belajar":(choice==2?"hiburan":"aktivitas");
                            p.energy -= cost; if(p.energy < 0) p.energy = 0; 
                            showActionReaction(99, true); 
                            bool quizResult = true; if(choice == 1) quizResult = runMiniQuiz(questions);
                            actionLog = applyChoiceWithQuiz(p, choice, quizResult); 
                            applyBegadangPenalty(p);
                            if (choice == 1) studiedToday = true;
                            showForcedCollapseLoading(actName); endDay = true; 
                        }
                    }
                }
            }
            if (!backToMenu) {
                if (p.stress > 75) { p.highStressDays++; p.understanding -= 3; if (p.understanding < 0) p.understanding = 0; }
                if (!studiedToday) p.noStudyDays++; p.studiedYesterday = studiedToday; p.day++; 
            }
        }
        if (!backToMenu) showEnding(p);
    }
}
