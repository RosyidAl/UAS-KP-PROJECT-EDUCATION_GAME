#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream> 
#include <vector> 

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
// 2. HELPER VISUAL
// ==========================================

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
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

// FUNGSI CENTER YANG PRESISI
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

void typewriterCenteredMultiline(string text, int delayMs = 40) {
    stringstream ss(text);
    string line;
    while(getline(ss, line)) {
        int len = line.length();
        int padding = (80 - len) / 2;
        if (padding > 0) cout << string(padding, ' ');
        for (char c : line) {
            cout << c; cout.flush(); sleepMs(delayMs);
        }
        cout << "\n";
    }
}

// ==========================================
// 3. TITLE SCREEN
// ==========================================
void drawTitle() {
    clearScreen();
    cout << "\n\n";
    cout << RED << BOLD << BLINK;
    
    printCentered("##############################################################################");
    printCentered("#                                                                            #");
    printCentered("       #######    ######      #     #     #    #####       ");
    printCentered("            #     #     #    # #     #   #    #     #      ");
    printCentered("           #      #     #   #   #     # #     #            ");
    printCentered("          #       #     #  #     #     #       #####       ");
    printCentered("         #        #     #  #######     #            #      ");
    printCentered("        #         #     #  #     #     #      #     #      ");
    printCentered("        #         ######   #     #     #       #####       ");
    printCentered("#                                                                            #");
    printCentered("#                       BEFORE THE FINAL TEST                                #");
    printCentered("#                                                                            #");
    printCentered("##############################################################################");
    
    cout << RESET << "\n";
}

// ==========================================
// 4. FITUR NARASI & DIALOG (PERBAIKAN TOTAL)
// ==========================================

void showPrologue() {
    clearScreen();
    sleepMs(1000);
    cout << "\n\n\n";
    
    // REVISI: HITAM PUTIH (TANPA WARNA MERAH)
    printCentered("7 HARI LAGI..."); 
    sleepMs(2000);
    
    clearScreen();
    cout << "\n\n"; 
    
    // NARASI HITAM PUTIH
    typewriterPrint("  Hah... (Menghela napas panjang).", 60);
    typewriterPrint("  Kalender di dinding seolah mengejekku.", 60);
    sleepMs(1000);
    
    typewriterPrint("\n  Ujian Akhir Semester tinggal menghitung hari.", 40);
    typewriterPrint("  Dosen killer, materi menumpuk setinggi gunung,", 40);
    typewriterPrint("  dan ekspektasi orang tua yang membebani bahu.", 40);
    sleepMs(1500);
    
    // CAPSLOCK HITAM PUTIH (TANPA KUNING)
    typewriterPrint("\n  BENAR-BENAR MEMUAKKAN SEKALI...", 70);
    sleepMs(1000);
    
    typewriterPrint("\n  Tapi mau bagaimana lagi? Aku harus bertahan.", 40);
    typewriterPrint("  Aku harus lulus. Atau setidaknya...", 40);
    sleepMs(1000);
    
    // CAPSLOCK HITAM PUTIH (TANPA MERAH)
    typewriterPrint("\n  ...TIDAK MATI KONYOL KARENA STRESS DI KOSAN INI.", 80);
    sleepMs(1000);
    
    // --- REVISI: LOADING CENTER TEPAT DI BAWAH TEXT ---
    // Tidak ada clearScreen di sini, agar teks di atas tetap terlihat
    cout << "\n\n\n"; 
    
    string loadingText = "[ MEMULAI HARI PERTAMA ]";
    // Hitung center manual
    int padding = (80 - loadingText.length()) / 2;
    if (padding > 0) cout << string(padding, ' ');
    
    // Efek ketik untuk loadingnya
    for(char c : loadingText) {
        cout << c; cout.flush(); sleepMs(100);
    }
    cout << "\n";
    sleepMs(2500);
}

void showCharacterDialogue(const PlayerStats& p, int eventID) {
    cout << "\n";
    cout << CYAN << BOLD << "  [" << p.playerName << " bergumam]:" << RESET << "\n";
    
    string dialogue = "";

    if (eventID != -1) {
        switch(eventID) {
            case 0: dialogue = "  \"Tumben dosen muji. Apa dia salah orang? Ah, bodo amat, ambil aja positifnya.\""; break;
            case 1: dialogue = "  \"Aduh... perutku melilit. SIALAN, SALAH MAKAN APA AKU SEMALAM? RASANYA MAU PINGSAN.\""; break;
            case 2: dialogue = "  \"Revisi lagi?! DOSEN ITU BENAR-BENAR INGIN MEMBUNUHKU PELAN-PELAN. STRESS BANGET!\""; break;
            case 3: dialogue = "  \"TETANGGA SEBELAH WOI! BERISIK BANGET HAJATAN PAGI BUTA. KEPALAKU PUSING KURANG TIDUR...\""; break;
            case 4: dialogue = "  \"Materi rahasia! Hahaha, dewi fortuna sedang tersenyum padaku.\""; break;
        }
    } 
    else if (p.health < 30) {
        dialogue = "  \"KEPALAKU MAU PECAH... badanku panas dingin. Apa aku skip aja hari ini?\"";
    }
    else if (p.stress > 80) {
        dialogue = "  \"AKU NGGAK KUAT... RASANYA PENGEN TERIAK. APA GUNANYA KULIAH KALAU GILA DULUAN?\"";
    }
    else if (p.fatigue > 80) {
        dialogue = "  \"Mata ini... berat banget. Kopi mana kopi...\"";
    }
    else if (p.day == 7) {
        dialogue = "  \"Oke. Hari terakhir. Habis-habisan atau pulang nama.\"";
    }
    else if (p.studyMood > 80) {
        dialogue = "  \"Aneh, hari ini rasanya aku bisa menghafal satu kamus.\"";
    }
    else {
        int r = rand() % 3;
        if (r == 0) dialogue = "  \"Satu hari lagi, satu perjuangan lagi. Ayo bangun.\"";
        else if (r == 1) dialogue = "  \"Kosan sepi banget. Fokus, [Nama], fokus.\"";
        else dialogue = "  \"Semoga hari ini dosen nggak aneh-aneh.\"";
    }

    cout << CYAN;
    typewriterPrint(dialogue, 30);
    cout << RESET;
}

void showActionReaction(int choice, bool isSuccess) {
    cout << "\n" << CYAN << "  [Reaksi]: ";
    string txt = "";
    
    switch(choice) {
        case 1: 
            if (isSuccess) txt = "\"Yes! Masuk akal! Ternyata nggak sesulit itu kalau fokus.\"";
            else txt = "\"ARGH! APAAN SIH INI?! HURUF-HURUFNYA KAYAK NARI-NARI DI DEPANKU!\"";
            break;
        case 2: txt = "\"Hah... lega rasanya. Lupakan kuliah sejenak.\""; break;
        case 3: txt = "\"Huh.. hah.. Keringat ini setidaknya nyata, nggak kayak janji dosen.\""; break;
        case 4: txt = "\"Scroll dikit... eh kok udah sejam? SIALAN ALGORITMA TIKTOK.\""; break;
        case 5: txt = "\"Akhirnya... Kasurku sayang, aku pulang kepadamu...\""; break;
        case 99: txt = "\"MATAKU PERIH... JANTUNGMU BERDEBAR... TAPI MATERI INI BELUM SELESAI!\""; break;
    }
    
    typewriterPrint(txt, 30);
    cout << RESET << "\n";
    sleepMs(1000); 
}

void showEndingReaction(string rank) {
    cout << "\n" << CYAN << "  [Kata Terakhir]: ";
    string txt = "";
    
    if (rank == "F (DROP OUT)") txt = "\"IBU... MAAFKAN AKU... SEMUANYA GELAP...\"";
    else if (rank == "S (Perfect)") txt = "\"Hahaha! Lihat siapa rajanya sekarang! IPK 4.0 bukan mimpi!\"";
    else if (rank == "A (Excellent)") txt = "\"Alhamdulillah... Usaha emang nggak mengkhianati hasil. Aku bisa tidur nyenyak malam ini.\"";
    else if (rank == "B (Standard)") txt = "\"Hufft... Nyaris. Yang penting lulus lah ya. Waktunya main game sepuasnya.\"";
    else txt = "\"SIALAN... KENAPA SOALNYA BEDA SAMA KISI-KISI?! DOSEN PENIPU!\"";
    
    typewriterPrint(txt, 50);
    cout << RESET << "\n";
    sleepMs(2000);
}

// ==========================================
// 5. SISTEM & HELPER
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
        file.close();
        return true; 
    }
    return false; 
}

void clamp(int &x, int minVal = 0, int maxVal = 100) {
    if (x < minVal) x = minVal;
    if (x > maxVal) x = maxVal;
}

string numToStr(int num) {
    stringstream ss; ss << num; return ss.str();
}

int getChoiceOrQuit() {
    string input;
    while (true) {
        cout << ">> Pilihan Anda (1-5) atau [Q]: ";
        cin >> input;
        if (input == "q" || input == "Q") return -1;
        try {
            int val = stoi(input);
            if (val >= 1 && val <= 5) return val;
            else cout << RED << "Masukkan angka 1-5 atau Q.\n" << RESET;
        } catch (...) { cout << RED << "Input tidak valid.\n" << RESET; }
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int getIntInRange(int min, int max) {
    int value;
    while (true) {
        cout << ">> Pilih [" << min << "-" << max << "]: ";
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= min && value <= max) return value;
            cout << RED << "Input tidak valid.\n" << RESET;
        } else {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Harap masukkan angka.\n" << RESET;
        }
    }
}

// ==========================================
// 6. ANIMASI LOADING
// ==========================================

void printCenteredLoadingBar() {
    string padding(22, ' '); 
    cout << padding << "Loading: [";
    for (int i = 0; i < 20; i++) {
        cout << "="; cout.flush(); sleepMs(50);     
    }
    cout << "] 100%\n";
}

void showLoadingDayChange() {
    clearScreen(); 
    cout << "\n\n\n";
    printCentered(GREEN + "Kamu beristirahat dengan tenang..." + RESET);
    printCentered(YELLOW + "Mengakhiri hari dan memulihkan energi..." + RESET);
    cout << "\n";
    printCenteredLoadingBar();
    sleepMs(1500); 
}

void showForcedCollapseLoading(string actionName) {
    clearScreen(); 
    cout << "\n\n\n";
    printCentered(RED + "Kamu memutuskan untuk memaksakan " + actionName + "..." + RESET);
    printCentered(RED + "...lalu AMBRUK PINGSAN." + RESET);
    cout << "\n";
    printCentered(YELLOW + "Mengakhiri hari dan memulihkan energi..." + RESET);
    cout << "\n";
    printCenteredLoadingBar();
    sleepMs(2500); 
}

void showLoadingReturnMenu() {
    clearScreen(); 
    cout << "\n\n\n";
    printCentered("Menutup permainan...");
    cout << "\n";
    string padding(23, ' ');
    cout << padding << "System: [";
    for (int i = 0; i < 20; i++) {
        cout << "#"; cout.flush(); sleepMs(40);     
    }
    cout << "] OK\n";
    sleepMs(800); 
}

// ==========================================
// 7. GAMEPLAY LOGIC
// ==========================================

string drawBar(int current, int max, bool isBadStat) {
    int width = 15; float percent = (float)current / max; int fill = (int)(percent * width);
    if (fill > width) fill = width; if (fill < 0) fill = 0;
    string color = RESET; 
    if (!isBadStat) { if (percent >= 0.7) color = GREEN; else if (percent >= 0.4) color = YELLOW; else color = RED + BLINK; } 
    else { if (percent >= 0.7) color = RED + BLINK; else if (percent >= 0.4) color = YELLOW; else color = GREEN; }
    string bar = "["; bar += color; for (int i = 0; i < fill; i++) bar += "|"; bar += RESET; for (int i = fill; i < width; i++) bar += "."; bar += "]";
    return bar;
}

string getConditionText(const PlayerStats& p) {
    if (p.health < 20) return "KRITIS (BAHAYA)"; if (p.stress > 80) return "STRESS BERAT"; if (p.fatigue > 80) return "SANGAT LELAH"; return "PRIMA";
}

string getMoodText(int mood) {
    if (mood > 70) return "Semangat!"; if (mood > 40) return "Biasa Saja"; return "Malas..."; 
}

int showMainMenu() {
    drawTitle();
    cout << "\t[1] MULAI BARU\n";
    cout << "\t[2] MUAT GAME (LOAD SAVE)\n";
    cout << "\t[3] KELUAR APLIKASI (QUIT)\n\n";
    return getIntInRange(1, 3);
}

void showStats(const PlayerStats& p, string log) {
    cout << "\n";
    cout << "========================================================================\n";
    cout << "|  HARI " << p.day << " / 7\t\t|  STATUS: " << getConditionText(p) << "\t|  TARGET: UJIAN AKHIR |\n";
    cout << "========================================================================\n";
    cout << "|  VITALITAS            |  MENTAL               |  AKADEMIK            |\n";
    cout << "|  HP : " << p.health << "%             |  STRESS : " << p.stress << "%         |  PEMAHAMAN: " << p.understanding << "%      |\n";
    cout << "|  " << drawBar(p.health, 100, false)    <<"    |  " << drawBar(p.stress, 100, true) << "    |  " << drawBar(p.understanding, 100, false) << "   |\n";
    
    string moodTxt = getMoodText(p.studyMood);
    string spaceAlign = (moodTxt == "Biasa Saja") ? "   " : ((moodTxt == "Malas...") ? "     " : "    ");

    cout << "|  ENERGI : " << p.energy << "         |  FATIGUE : " << p.fatigue << "%         |  MOOD: " << moodTxt << spaceAlign << " |\n";
    cout << "|  " << drawBar(p.energy, p.maxEnergy, false) << "    |  " << drawBar(p.fatigue, 100, true) << "    |  (Niat Belajar)      |\n";

    cout << "========================================================================\n";
    cout << "|  LOG SISTEM:                                                         |\n";
    stringstream ss(log); string line;
    while(getline(ss, line)) {
        if(!line.empty()) {
            if (line.length() > 64) line = line.substr(0, 61) + "..."; 
            cout << "|  > " << line << string(64 - line.length(), ' ') << "|\n";
        }
    }
    cout << "========================================================================\n";
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

bool runMiniQuiz(const vector<Question>& questions) {
    if (questions.empty()) return true; 
    int idx = rand() % questions.size();
    Question q = questions[idx];

    clearScreen(); cout << "\n\n";
    printCentered("======================================");
    printCentered(CYAN + BOLD + "LATIHAN SOAL HARIAN" + RESET);
    printCentered("======================================"); cout << "\n";
    
    // REVISI: LANGSUNG MUNCUL
    cout << "  Soal: \n";
    cout << "  " << YELLOW << q.text << RESET << "\n\n";
    
    cout << "  [A] " << q.a << "\n";
    cout << "  [B] " << q.b << "\n";
    cout << "  [C] " << q.c << "\n";
    cout << "  [D] " << q.d << "\n\n";
    
    char ans; cout << "  >> Jawaban Anda (A/B/C/D): "; cin >> ans; ans = toupper(ans);
    cout << "\n  Mengecek jawaban"; for(int i=0; i<3; i++) { cout << "."; cout.flush(); sleepMs(300); }
    
    if (ans == q.answerKey) { cout << " " << GREEN << BOLD << "BENAR!" << RESET << "\n"; sleepMs(1000); return true; } 
    else { cout << " " << RED << BOLD << "SALAH!" << RESET << "\n  Jawaban: " << q.answerKey << "\n"; sleepMs(1500); return false; }
}

string applyChoice(PlayerStats& p, int choice, bool quizSuccess) {
    string log = "";
    bool kondisiBuruk = (p.health < 50 || p.stress > 70);

    switch (choice) {
        case 1: { 
            int gain = 0;
            if (quizSuccess) { gain = (p.understanding < 40) ? 15 : ((p.understanding < 70) ? 10 : 6); p.studyMood += 10; log = "Belajar Sukses! Jawaban Benar. "; } 
            else { gain = 4; p.stress += 8; log = "Belajar Sulit. Jawaban Salah. "; }
            int penalty = p.fatigue / 15; gain -= penalty; if (gain < 1) gain = 1;
            if (kondisiBuruk) p.fatigue += 8; else p.fatigue += 3;
            p.understanding += gain; p.stress += 5; p.happiness -= 5; p.health -= 5;
            log += "(Pemahaman +" + numToStr(gain) + ")";
            break;
        }
        case 2: log = "Hiburan. (Stress -10, Bahagia +15)"; p.happiness += 15; p.stress -= 10; p.studyMood += 5; p.fatigue -= 3; break;
        case 3: log = "Olahraga. (Health +10, Fatigue -4)"; p.health += 10; p.stress -= 5; p.happiness += 5; p.fatigue -= 4; break;
        case 4: log = "Scroll medsos. (Mood -10, Bahagia +5)"; p.happiness += 5; p.stress += 5; p.studyMood -= 10; break;
    }
    clamp(p.happiness); clamp(p.studyMood); clamp(p.stress); clamp(p.understanding); clamp(p.health); clamp(p.fatigue, 0, 100);
    return log;
}

string applyChoiceWithQuiz(PlayerStats& p, int choice, bool quizSuccess) {
    return applyChoice(p, choice, quizSuccess);
}

string getMorningNarration(const PlayerStats& p) {
    if (p.health < 30) return "Fisik: Tubuhmu lemas."; if (p.stress > 80) return "Mental: Sangat cemas."; if (p.health > 80 && p.stress < 40) return "Kondisi: Segar bugar."; return "Kondisi: Normal.";
}

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
    int roll = rand() % 100;
    if (roll >= 50) return -1; 

    int type = rand() % 5; 
    if (type == 0) { p.happiness += 20; p.stress -= 15; p.studyMood += 10; logBuffer = "\n[EVENT] Dosen memuji tugasmu! (Happy +20, Stress -15)"; return 0; } 
    else if (type == 1) { p.health -= 20; p.energy -= 30; p.stress += 10; if (p.energy < 0) p.energy = 0; logBuffer = "\n[EVENT] Sakit perut parah semalam! (Health -20, Energi -30)"; return 1; } 
    else if (type == 2) { p.stress += 25; p.studyMood -= 15; p.happiness -= 10; logBuffer = "\n[EVENT] Revisi dadakan dosen killer! (Stress +25, Mood -15)"; return 2; } 
    else if (type == 3) { p.fatigue += 20; p.energy -= 15; if (p.energy < 0) p.energy = 0; logBuffer = "\n[EVENT] Tetangga hajatan berisik. (Fatigue +20, Energi -15)"; return 3; } 
    else { p.understanding += 10; p.happiness += 5; logBuffer = "\n[EVENT] Menemukan materi rahasia kating. (Paham +10, Happy +5)"; return 4; }
}

int getEnergyCost(int choice) {
    switch (choice) { case 1: return 40; case 2: return 25; case 3: return 30; case 4: return 20; default: return 0; }
}

string applySleep(PlayerStats& p, bool earlySleep) {
    int baseHealthGain = earlySleep ? 12 : 8; int baseStressDrop = earlySleep ? 12 : 7; int fatiguePenalty = p.fatigue / 20;
    baseHealthGain -= fatiguePenalty; baseStressDrop -= fatiguePenalty;
    if (baseHealthGain < 3) baseHealthGain = 3; if (baseStressDrop < 3) baseStressDrop = 3;
    p.health += baseHealthGain; p.stress -= baseStressDrop; p.happiness += earlySleep ? 4 : 1; p.fatigue -= earlySleep ? 6 : 4; p.energy = p.maxEnergy;
    clamp(p.health); clamp(p.stress); clamp(p.happiness); clamp(p.fatigue, 0, 100);
    return earlySleep ? "Tidur tepat waktu. (Health +" + numToStr(baseHealthGain) + ")" : "Ketiduran. (Health +" + numToStr(baseHealthGain) + ")";
}

string applyBegadangPenalty(PlayerStats& p) {
    p.health -= 15; p.stress += 15; p.happiness -= 5; p.maxEnergy -= 10; p.fatigue += 12;
    if (p.maxEnergy < 60) p.maxEnergy = 60; if (p.energy > p.maxEnergy) p.energy = p.maxEnergy;
    clamp(p.health); clamp(p.stress); clamp(p.happiness); clamp(p.fatigue, 0, 100);
    return " [!] BEGADANG. (Health -15, Max NRG Turun)";
}

void showEnding(const PlayerStats& p) {
    clearScreen(); cout << "\n\n";
    printCentered("======================================================");
    printCentered(BOLD + "HARI UJIAN AKHIR TELAH TIBA" + RESET);
    printCentered("======================================================");
    cout << "\n";
    typewriterPrint("\tKamu duduk di ruang ujian. Kertas soal dibagikan...", 50);
    sleepMs(500);

    string progressBar = "\tMengerjakan soal: ["; cout << progressBar;
    for (int i = 0; i < 20; i++) {
        int delay = (p.health > 50) ? 50 : 150; sleepMs(delay);
        if (p.understanding > (i * 5)) cout << "="; else cout << "."; cout.flush();
    }
    cout << "] Selesai!\n\n"; sleepMs(1000);
    typewriterPrint("\tDosen sedang menilai lembar jawabanmu...", 60); sleepMs(2000); 
    clearScreen();

    string rank, title, color, message;
    if (p.health <= 0) { rank = "F (DROP OUT)"; title = "PASIEN RUMAH SAKIT"; color = RED; message = "Kamu tidak bisa mengikuti ujian karena dirawat intensif.\nKesehatanmu hancur demi ambisi yang salah."; } 
    else if (p.understanding >= 90 && p.stress <= 40) { rank = "S (Perfect)"; title = "DEWA KAMPUS"; color = GREEN + BLINK; message = "Nilaimu Sempurna! Dosen terkejut melihat jawabanmu.\nKamu menjadi legenda di angkatan ini."; } 
    else if (p.understanding >= 75) { rank = "A (Excellent)"; title = "MAHASISWA TELADAN"; color = GREEN; message = "Kamu lulus dengan nilai sangat memuaskan.\nKerja kerasmu terbayar lunas!"; } 
    else if (p.understanding >= 50) { rank = "B (Standard)"; title = "MAHASISWA RATA-RATA"; color = YELLOW; message = "Kamu lulus, meski tidak terlalu istimewa.\nYang penting aman dan bisa lanjut semester depan."; } 
    else { rank = "D (Failed)"; title = "CALON MAHASISWA ABADI"; color = RED; message = "Nilaimu hancur. Sebagian besar jawabanmu salah.\nSiap-siap mengulang mata kuliah ini tahun depan."; }

    cout << "\n\n";
    printCentered("======================================================");
    printCentered(BOLD + "TRANSKRIP NILAI AKHIR" + RESET);
    printCentered("======================================================");
    cout << "\n";
    string padding = "\t   ";
    typewriterPrint(padding + "NAMA  : " + p.playerName); sleepMs(300);
    string rankStr = padding + "RANK  : " + color + rank + RESET; typewriterPrint(rankStr); sleepMs(300);
    string titleStr = padding + "GELAR : " + color + title + RESET; typewriterPrint(titleStr); sleepMs(300);
    cout << "\n"; printCentered("======================================================");
    printCentered("[ STATISTIK PERJUANGAN ]"); sleepMs(500);
    typewriterPrint(padding + "> Pemahaman Akhir : " + numToStr(p.understanding) + "/100", 40);
    typewriterPrint(padding + "> Sisa Mental     : " + numToStr(100 - p.stress) + "%", 40);
    typewriterPrint(padding + "> Total Ambruk    : " + numToStr(p.collapseCount) + " kali", 40);
    typewriterPrint(padding + "> Hari Bolos      : " + numToStr(p.noStudyDays) + " hari", 40);
    cout << "\n"; printCentered("[ KESIMPULAN ]"); sleepMs(500);
    typewriterCenteredMultiline(message, 50); 
    
    showEndingReaction(rank);

    cout << "\n"; printCentered("======================================================");
    cout << "\n\n"; printCentered("Tekan Enter untuk kembali ke Menu Utama..."); cin.get(); cin.get();
}

// ==========================================
// 8. MAIN CONTROLLER
// ==========================================
int main() {
    srand((unsigned)time(nullptr));
    vector<Question> questions = loadQuestions();

    while (true) {
        PlayerStats p;
        string currentLog = ""; 
        bool backToMenu = false; 

        int menuChoice = showMainMenu();
        if (menuChoice == 3) { clearScreen(); cout << "\n\n"; printCentered("Sampai Jumpa! Terima kasih sudah bermain."); sleepMs(1000); return 0; }
        if (menuChoice == 2) {
            if (loadGame(p)) { cout << GREEN << "\nSave Game Ditemukan! Memuat data " << p.playerName << " (Hari " << p.day << ")...\n" << RESET; sleepMs(2000); } 
            else { cout << RED << "\nTidak ada Save Game! Memulai Game Baru...\n" << RESET; sleepMs(1500); cout << "\nMasukkan Nama Panggilanmu (Tanpa Spasi): "; cin >> p.playerName; cin.ignore(); showPrologue(); } 
        } else if (menuChoice == 1) {
            cout << "\nMasukkan Nama Panggilanmu (Tanpa Spasi): "; cin >> p.playerName; cin.ignore();
            showPrologue(); 
        }

        if(questions.empty()) { cout << RED << "\n[INFO] File latihan_soal.txt tidak ditemukan. Mode belajar otomatis aktif.\n" << RESET; sleepMs(2000); }

        while (p.day <= 7 && !backToMenu) {
            saveGame(p); 
            currentLog = ""; 
            if (p.day > 1) currentLog += applyForgettingAtMorning(p);
            currentLog += getMorningNarration(p);
            
            string eventLog = "";
            int eventID = triggerRandomEvent(p, eventLog);
            currentLog += eventLog;

            bool endDay = false;
            bool studiedToday = false;

            while (!endDay && !backToMenu) {
                clearScreen();
                
                showCharacterDialogue(p, eventID); 
                
                showStats(p, currentLog); 
                showChoices();          
                
                int choice = getChoiceOrQuit(); 
                if (choice == -1) { 
                    char confirm; cout << "\n" << YELLOW << "Apakah kamu ingin menyimpan game sebelum keluar? (y/n/c untuk cancel): " << RESET; cin >> confirm;
                    if (confirm == 'c' || confirm == 'C') continue; 
                    if (confirm == 'y' || confirm == 'Y') { saveGame(p); cout << GREEN << "Game berhasil disimpan!\n" << RESET; sleepMs(1000); }
                    showLoadingReturnMenu(); backToMenu = true; 
                }
                else if (choice == 5) { 
                    showActionReaction(5, true); 
                    showLoadingDayChange(); 
                    applySleep(p, true); 
                    endDay = true; 
                } 
                else {
                    int cost = getEnergyCost(choice);
                    if (p.energy >= cost) {
                        p.energy -= cost;
                        
                        bool quizResult = true;
                        if (choice == 1) {
                            quizResult = runMiniQuiz(questions);
                        }
                        
                        showActionReaction(choice, quizResult); 

                        currentLog = applyChoiceWithQuiz(p, choice, quizResult); 
                        if (choice == 1) studiedToday = true;
                    } else {
                        clearScreen(); showStats(p, ""); 
                        cout << "\n\n\t" << RED << BLINK << "############################################" << RESET << "\n";
                        cout << "\t" << RED <<        "      !!! PERINGATAN: ENERGI HABIS !!!      " << RESET << "\n";
                        cout << "\t" << RED << BLINK << "############################################" << RESET << "\n\n";
                        cout << "\t" << YELLOW << "  Tubuhmu gemetar. Kamu tidak kuat lagi..." << RESET << "\n";
                        cout << "\t  Apa yang akan kamu lakukan?\n\n";
                        cout << "\t" << GREEN << "[1] Tidur & Pulihkan Diri" << RESET << " (Sangat Disarankan)\n";
                        cout << "\t" << RED   << "[2] Paksakan Diri" << RESET << "         (Resiko Tinggi!)\n\n";
                        
                        int sub = getIntInRange(1, 2);
                        if (sub == 1) { 
                            showActionReaction(5, true); 
                            showLoadingDayChange(); 
                            applySleep(p, false); 
                            endDay = true; 
                        } 
                        else {
                            string actName = "";
                            switch(choice) { case 1: actName = "belajar keras"; break; case 2: actName = "mencari hiburan"; break; case 3: actName = "berolahraga"; break; case 4: actName = "scroll medsos"; break; }
                            p.energy -= cost; if(p.energy < 0) p.energy = 0; 
                            
                            showActionReaction(99, true); 

                            bool quizResult = true;
                            if (choice == 1) quizResult = runMiniQuiz(questions);

                            applyChoiceWithQuiz(p, choice, quizResult); 
                            applyBegadangPenalty(p);
                            if (choice == 1) studiedToday = true;
                            
                            showForcedCollapseLoading(actName); endDay = true; 
                        }
                    }
                }

                if (!endDay && !backToMenu && (p.health <= 0 || p.stress >= 100)) {
                    p.collapseCount++; p.health -= 5; p.understanding -= 8; p.maxEnergy -= 5; p.fatigue += 20;
                    if(p.health < 0) p.health = 0; p.energy += 30; if (p.energy > p.maxEnergy) p.energy = p.maxEnergy;
                    showForcedCollapseLoading("kesehatan/stress yang buruk"); endDay = true;
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
