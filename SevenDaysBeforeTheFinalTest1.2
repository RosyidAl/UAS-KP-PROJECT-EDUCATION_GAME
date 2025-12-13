#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

// ==========================================
// 1. KONFIGURASI WARNA & VISUAL
// ==========================================
const string RESET  = "\033[0m";
const string RED    = "\033[31m";
const string GREEN  = "\033[32m";
const string YELLOW = "\033[33m";
const string CYAN   = "\033[36m";
const string GREY   = "\033[90m"; 
const string BOLD   = "\033[1m";
// --- TAMBAHAN BARU: KODE KEDIP ---
const string BLINK  = "\033[5m"; 

struct PlayerStats {
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

// ==========================================
// 2. HELPER FUNGSI (LOGIKA & DISPLAY)
// ==========================================

void clamp(int &x, int minVal = 0, int maxVal = 100) {
    if (x < minVal) x = minVal;
    if (x > maxVal) x = maxVal;
}

string numToStr(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

int getIntInRange(int min, int max) {
    int value;
    while (true) {
        cout << ">> Pilih [1-" << max << "]: ";
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= min && value <= max) return value;
            cout << RED << "Input tidak valid. Coba lagi.\n" << RESET;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Masukkan angka.\n" << RESET;
        }
    }
}

#ifdef _WIN32
void clearScreen() { system("cls"); }
#else
void clearScreen() { system("clear"); }
#endif

// --- FUNGSI BAR (DENGAN EFEK KEDIP JIKA MERAH) ---
string drawBar(int current, int max, bool isBadStat) {
    int width = 15; 
    float percent = (float)current / max;
    int fill = (int)(percent * width);
    if (fill > width) fill = width;
    if (fill < 0) fill = 0;

    string color;
    if (!isBadStat) {
        // Stat Bagus (HP/Energy)
        if (percent >= 0.7) color = GREEN;
        else if (percent >= 0.4) color = YELLOW;
        else color = RED + BLINK; // <--- TAMBAH BLINK DISINI (HP Rendah)
    } else {
        // Stat Buruk (Stress/Fatigue)
        if (percent >= 0.7) color = RED + BLINK; // <--- TAMBAH BLINK DISINI (Stress Tinggi)
        else if (percent >= 0.4) color = YELLOW;
        else color = GREEN;
    }

    string bar = color; 
    for (int i = 0; i < fill; i++) bar += "|"; 
    bar += GREY;
    for (int i = fill; i < width; i++) bar += "."; 
    bar += RESET;

    return bar;
}

string getConditionText(const PlayerStats& p) {
    // Kita buat gaya khusus untuk kondisi kritis: Merah + Tebal + Kedip
    string criticalStyle = RED + BOLD + BLINK;
    
    if (p.health < 20) return criticalStyle + "KRITIS" + RESET;
    if (p.stress > 80) return criticalStyle + "STRESS BERAT" + RESET;
    
    if (p.fatigue > 80) return YELLOW + "SANGAT LELAH" + RESET;
    return GREEN + "PRIMA" + RESET;
}

string getMoodText(int mood) {
    if (mood > 70) return GREEN + "Semangat!   " + RESET;
    if (mood > 40) return YELLOW + "Biasa Saja  " + RESET;
    return RED + "Malas...    " + RESET; // Mood malas tidak perlu kedip, cukup merah
}

// ==========================================
// 3. TAMPILAN UTAMA (DASHBOARD)
// ==========================================

void showStats(const PlayerStats& p, string log) {
    cout << "\n";
    cout << "========================================================================\n";
    cout << "|  HARI " << p.day << " / 7  |  STATUS: " << getConditionText(p) << "\t\t       |  TARGET: UJIAN AKHIR     |\n";
    cout << "========================================================================\n";
    cout << "|  " << CYAN << "VITALITAS" << RESET << "             |  " << CYAN << "MENTAL" << RESET << "                |  " << CYAN << "AKADEMIK" << RESET << "            |\n";
    cout << "|                        |                        |                      |\n";

    // BARIS 1
    cout << "|  HP  : " << p.health << "%            |  STRESS  : " << p.stress << "%           |  PEMAHAMAN: " << p.understanding << "%        |\n";
    cout << "|  [" << drawBar(p.health, 100, false) << "]  |  [" << drawBar(p.stress, 100, true) << "]  |  [" << drawBar(p.understanding, 100, false) << "] |\n";
    cout << "|                        |                        |                      |\n";

    // BARIS 2
    string moodTxt = getMoodText(p.studyMood);
    cout << "|  NRG : " << p.energy << "             |  FATIGUE : " << p.fatigue << "%           |  MOOD: " << moodTxt << "   |\n";
    cout << "|  [" << drawBar(p.energy, p.maxEnergy, false) << "]  |  [" << drawBar(p.fatigue, 100, true) << "]  |  (Niat Belajar)      |\n";

    cout << "========================================================================\n";
    cout << "|  LOG TERAKHIR:                                                       |\n";
    
    stringstream ss(log);
    string line;
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
    cout << "1. Belajar Keras  (40 Energi)\n";
    cout << "2. Hiburan        (25 Energi)\n";
    cout << "3. Olahraga       (30 Energi)\n";
    cout << "4. Scroll Medsos  (20 Energi)\n";
    cout << "5. Tidur (Akhiri Hari)\n";
}

// ==========================================
// 4. LOGIKA GAME (GAMEPLAY)
// ==========================================

string getMorningNarration(const PlayerStats& p) {
    string log = "Pagi hari: ";
    if (p.health < 30) return log + "Tubuhmu lemas dan kepalamu pusing.";
    if (p.stress > 80) return log + "Kamu bangun dengan perasaan cemas.";
    if (p.health > 80 && p.stress < 40) return log + "Tubuh segar, pikiran jernih.";
    return log + "Hari dimulai seperti biasa.";
}

string applyForgettingAtMorning(PlayerStats& p) {
    int before = p.understanding;
    string msg = "";
    if (!p.studiedYesterday) {
        int loss = (p.understanding >= 80) ? 8 : ((p.understanding >= 50) ? 6 : 4);
        p.understanding -= loss;
        if (p.understanding < 0) p.understanding = 0;
        if (p.understanding < before) {
            msg = "[!] Tidak belajar kemarin, hafalan hilang -" + numToStr(loss) + ".\n";
        }
    } else {
        p.understanding -= 1;
        if (p.understanding < 0) p.understanding = 0;
    }
    return msg;
}

string triggerRandomEvent(PlayerStats& p) {
    int roll = rand() % 100;
    if (roll >= 40) return ""; 

    string log = "\n";
    int type = rand() % 3;
    if (type == 0) {
        log += "[EVENT] Kuis dadakan! ";
        if (p.understanding >= 60) {
            log += "Kamu bisa mengerjakannya. (Stress +5)";
            p.stress += 5; p.happiness += 2;
        } else {
            log += "Kamu panik! (Stress +15)";
            p.stress += 15; p.happiness -= 8;
        }
    } else if (type == 1) {
        log += "[EVENT] Listrik padam. (Health -8, Energi -20)";
        p.health -= 8; p.energy -= 20; p.stress += 5;
        if (p.energy < 0) p.energy = 0;
    } else {
        log += "[EVENT] Diajak teman nongkrong. (Happy +10, Paham -3)";
        p.happiness += 10; p.stress -= 5; p.studyMood += 3; p.understanding -= 3;
    }
    clamp(p.health); clamp(p.stress); clamp(p.happiness);
    clamp(p.studyMood); clamp(p.understanding);
    return log;
}

int getEnergyCost(int choice) {
    switch (choice) {
        case 1: return 40; 
        case 2: return 25; 
        case 3: return 30; 
        case 4: return 20; 
        default: return 0;
    }
}

string applyChoice(PlayerStats& p, int choice) {
    string log = "";
    bool kondisiBuruk = (p.health < 50 || p.stress > 70);

    switch (choice) {
        case 1: { 
            log = "Belajar keras. ";
            int gain = (p.understanding < 40) ? 12 : ((p.understanding < 70) ? 9 : ((p.understanding < 90) ? 5 : 3));
            int penalty = p.fatigue / 15;
            gain -= penalty;
            if (gain < 1) gain = 1;

            if (kondisiBuruk) p.fatigue += 8; else p.fatigue += 3;

            p.understanding += gain;
            p.studyMood -= 6; p.stress += 12; p.happiness -= 6; p.health -= 8;
            log += "(Pemahaman +" + numToStr(gain) + ", Stress +12)";
            break;
        }
        case 2:
            log = "Hiburan. (Stress -10, Bahagia +15)";
            p.happiness += 15; p.stress -= 10; p.studyMood += 5; p.fatigue -= 3;
            break;
        case 3:
            log = "Olahraga. (Health +10, Fatigue -4)";
            p.health += 10; p.stress -= 5; p.happiness += 5; p.fatigue -= 4;
            break;
        case 4:
            log = "Scroll medsos. (Mood -10, Bahagia +5)";
            p.happiness += 5; p.stress += 5; p.studyMood -= 10;
            break;
    }
    clamp(p.happiness); clamp(p.studyMood); clamp(p.stress);
    clamp(p.understanding); clamp(p.health); clamp(p.fatigue, 0, 100);
    return log;
}

string applySleep(PlayerStats& p, bool earlySleep) {
    string log;
    if (earlySleep) log = "Tidur tepat waktu. ";
    else log = "Ketiduran karena kelelahan. ";

    int baseHealthGain = earlySleep ? 12 : 8;
    int baseStressDrop = earlySleep ? 12 : 7;
    int fatiguePenalty = p.fatigue / 20;

    baseHealthGain -= fatiguePenalty; 
    baseStressDrop -= fatiguePenalty;
    if (baseHealthGain < 3) baseHealthGain = 3;
    if (baseStressDrop < 3) baseStressDrop = 3;

    p.health += baseHealthGain;
    p.stress -= baseStressDrop;
    p.happiness += earlySleep ? 4 : 1;
    p.fatigue -= earlySleep ? 6 : 4;
    p.energy = p.maxEnergy;

    clamp(p.health); clamp(p.stress); clamp(p.happiness); clamp(p.fatigue, 0, 100);
    return log + "(Health +" + numToStr(baseHealthGain) + ")";
}

string applyBegadangPenalty(PlayerStats& p) {
    p.health -= 15; p.stress += 15; p.happiness -= 5;
    p.maxEnergy -= 10; p.fatigue += 12;

    if (p.maxEnergy < 60) p.maxEnergy = 60;
    if (p.energy > p.maxEnergy) p.energy = p.maxEnergy;
    
    clamp(p.health); clamp(p.stress); clamp(p.happiness); clamp(p.fatigue, 0, 100);
    // Di sini juga kita tambahkan BLINK agar peringatannya dramatis
    return " " + RED + BLINK + "[!] BEGADANG. (Health -15, Max NRG Turun)" + RESET;
}

void showEnding(const PlayerStats& p) {
    clearScreen();
    cout << BOLD << "\n===== HARI UJIAN TIBA =====\n" << RESET;
    cout << "Statistik Akhir:\n";
    cout << "Pemahaman : " << p.understanding << "\n";
    cout << "Kesehatan : " << p.health << "\n";
    cout << "Stress    : " << p.stress << "\n\n";

    if (p.health <= 0) cout << RED << BOLD << BLINK << "BAD ENDING: Kamu sakit parah saat ujian.\n" << RESET;
    else if (p.understanding >= 80 && p.stress <= 50) cout << GREEN << BOLD << "BEST ENDING: Nilai A! Persiapan sempurna.\n" << RESET;
    else if (p.understanding >= 60) cout << YELLOW << BOLD << "NORMAL ENDING: Nilai Cukup. Kamu lulus.\n" << RESET;
    else cout << RED << BOLD << "BAD ENDING: Nilai Buruk. Persiapan kurang matang.\n" << RESET;
}

// ==========================================
// 5. MAIN LOOP
// ==========================================
int main() {
    srand((unsigned)time(nullptr));
    PlayerStats p;
    string currentLog = ""; 

    while (p.day <= 7) {
        currentLog = ""; 
        if (p.day > 1) currentLog += applyForgettingAtMorning(p);
        
        p.energy = p.maxEnergy;
        currentLog += getMorningNarration(p);
        currentLog += triggerRandomEvent(p);

        bool endDay = false;
        bool studiedToday = false;

        while (!endDay) {
            clearScreen();          
            showStats(p, currentLog); 
            showChoices();          
            int choice = getIntInRange(1, 5);

            if (choice == 5) {
                string sleepLog = applySleep(p, true);
                clearScreen();
                showStats(p, sleepLog);
                cout << "\nTekan Enter untuk lanjut...";
                cin.get(); 
                endDay = true;
            } else {
                int cost = getEnergyCost(choice);
                if (p.energy >= cost) {
                    p.energy -= cost;
                    currentLog = applyChoice(p, choice); 
                    if (choice == 1) studiedToday = true;
                } else {
                    currentLog = "Energi tidak cukup! Pilih: 1.Tidur, 2.Begadang";
                    clearScreen();
                    showStats(p, currentLog);
                    
                    int sub = getIntInRange(1, 2);
                    if (sub == 1) {
                        string sleepLog = applySleep(p, false);
                        clearScreen();
                        showStats(p, sleepLog);
                        cout << "\nTekan Enter...";
                        cin.get();
                        endDay = true;
                    } else {
                        p.energy -= cost; 
                        if(p.energy < 0) p.energy = 0;
                        string actionLog = applyChoice(p, choice);
                        string penaltyLog = applyBegadangPenalty(p);
                        currentLog = actionLog + penaltyLog; 
                        if (choice == 1) studiedToday = true;
                        endDay = true; 
                        
                        clearScreen();
                        showStats(p, currentLog);
                        cout << "\nEfek begadang terasa... Tekan Enter...";
                        cin.get();
                    }
                }
            }

            if (!endDay && (p.health <= 0 || p.stress >= 100)) {
                p.collapseCount++;
                p.health -= 5; p.understanding -= 8; p.maxEnergy -= 5; p.fatigue += 15;
                if(p.health < 0) p.health = 0;
                
                // Pesan Ambruk juga dikasih kedip
                currentLog = RED + BLINK + "!!! AMBRUK KARENA SAKIT/STRESS !!!" + RESET;
                endDay = true;
                
                clearScreen();
                showStats(p, currentLog);
                cout << "\nTekan Enter...";
                cin.get();
            }
        }

        if (p.stress > 75) {
            p.highStressDays++;
            p.understanding -= 3;
            if (p.understanding < 0) p.understanding = 0;
        }
        if (!studiedToday) p.noStudyDays++;
        p.studiedYesterday = studiedToday;
        p.day++;
    }

    showEnding(p);
    return 0;
}
