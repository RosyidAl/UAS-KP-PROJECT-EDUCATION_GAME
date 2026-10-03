#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

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

    int fatigue = 0;        // kelelahan jangka panjang 0–100
    int highStressDays = 0; // berapa hari stress tinggi
    int noStudyDays = 0;    // berapa hari tanpa belajar
};

// ===== UTIL =====
void clamp(int &x, int minVal = 0, int maxVal = 100) {
    if (x < minVal) x = minVal;
    if (x > maxVal) x = maxVal;
}

int getIntInRange(int min, int max) {
    int value;
    while (true) {
        cout << ">> ";
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= min && value <= max) return value;
            cout << "Input di luar range.\n";
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan angka yang valid.\n";
        }
    }
}

#ifdef _WIN32
void clearScreen() {
    system("cls");
}
#else
void clearScreen() {
    system("clear");
}
#endif

// ===== DISPLAY =====
void showTitle() {
    cout << "=========================================\n";
    cout << "        SEVEN DAYS BEFORE FINAL EXAM     \n";
    cout << "=========================================\n";
}

void showStats(const PlayerStats& p) {
    cout << "\n================== STATUS ==================\n";
    cout << "Hari        : " << p.day << " / 7\n";
    cout << "Energi      : " << p.energy << " / " << p.maxEnergy << "\n";
    cout << "Kesehatan   : " << p.health << "\n";
    cout << "Stress      : " << p.stress << "\n";
    cout << "Mood belajar: " << p.studyMood << "\n";
    cout << "Bahagia     : " << p.happiness << "\n";
    cout << "Pemahaman   : " << p.understanding << "\n";
    cout << "Fatigue     : " << p.fatigue << " (kelelahan jangka panjang)\n";
    cout << "===========================================\n";
}

void showNarrationMorning(const PlayerStats& p) {
    cout << "\nPagi hari...\n";
    if (p.health < 30)
        cout << "Tubuhmu lemas dan kepalamu pusing.\n";
    else if (p.stress > 80)
        cout << "Kamu bangun dengan perasaan cemas dan gelisah.\n";
    else if (p.health > 80 && p.stress < 40)
        cout << "Kamu bangun dengan tubuh segar dan pikiran jernih.\n";
    else
        cout << "Hari baru dimulai seperti biasa.\n";
}

// ===== FORGETTING =====
void applyForgettingAtMorning(PlayerStats& p) {
    int before = p.understanding;

    if (!p.studiedYesterday) {
        int loss;
        if (p.understanding >= 80) loss = 8;
        else if (p.understanding >= 50) loss = 6;
        else loss = 4;

        p.understanding -= loss;
        if (p.understanding < 0) p.understanding = 0;

        if (p.understanding < before) {
            cout << "\nKarena tidak menyentuh materi kemarin, sebagian hafalanmu mulai memudar.\n";
        }
    } else {
        p.understanding -= 1;
        if (p.understanding < 0) p.understanding = 0;
    }
}

// ===== RANDOM EVENT =====
void triggerRandomEvent(PlayerStats& p) {
    int roll = rand() % 100;
    if (roll >= 40) return; // 40% chance ada event, 60% tidak ada apa-apa

    cout << "\n--- Kejadian tak terduga hari ini ---\n";

    int type = rand() % 3;
    if (type == 0) {
        cout << "Dosen mengumumkan kuis mendadak di akhir kelas.\n";
        if (p.understanding >= 60) {
            cout << "Untungnya kamu cukup paham materi. Sedikit tegang, tapi bisa diatasi.\n";
            p.stress += 5;
            p.happiness += 2;
        } else {
            cout << "Kamu panik karena merasa belum siap.\n";
            p.stress += 15;
            p.happiness -= 8;
        }
    } else if (type == 1) {
        cout << "Semalam listrik sempat padam, tidurmu agak terganggu.\n";
        p.health -= 8;
        p.energy -= 20;
        if (p.energy < 0) p.energy = 0;
        p.stress += 5;
    } else {
        cout << "Temanmu mengajak nongkrong sebentar untuk melepas penat.\n";
        cout << "Kamu ikut, tapi mengorbankan sedikit waktu belajar.\n";
        p.happiness += 10;
        p.stress -= 5;
        p.studyMood += 3;
        p.understanding -= 3;
    }

    clamp(p.health);
    clamp(p.stress);
    clamp(p.happiness);
    clamp(p.studyMood);
    clamp(p.understanding);
}

// ===== AKSI =====
int getEnergyCost(int choice) {
    switch (choice) {
        case 1: return 40; // belajar
        case 2: return 25; // hiburan
        case 3: return 30; // olahraga
        case 4: return 20; // scroll medsos
        default: return 0;
    }
}

void applyChoice(PlayerStats& p, int choice) {
    bool kondisiBuruk = (p.health < 50 || p.stress > 70);

    switch (choice) {
        case 1: { // Belajar keras
            cout << "Kamu belajar serius.\n";

            int gain;
            if (p.understanding < 40) gain = 12;
            else if (p.understanding < 70) gain = 9;
            else if (p.understanding < 90) gain = 5;
            else gain = 3;

            // efek fatigue: semakin tinggi, belajar makin tidak efektif
            int penalty = p.fatigue / 15; // fatigue 30 -> -2, 60 -> -4
            gain -= penalty;
            if (gain < 1) gain = 1;

            // kondisi tubuh buruk → tambah fatigue
            if (kondisiBuruk) p.fatigue += 8;
            else p.fatigue += 3;

            p.understanding += gain;

            p.studyMood -= 6;
            p.stress += 12;
            p.happiness -= 6;
            p.health -= 8;
            break;
        }

        case 2: // Hiburan
            cout << "Kamu bersantai dan mencari hiburan.\n";
            p.happiness += 15;
            p.stress -= 10;
            p.studyMood += 5;
            p.fatigue -= 3; // hiburan mengurangi fatigue sedikit
            break;

        case 3: // Olahraga
            cout << "Kamu berolahraga ringan.\n";
            p.health += 10;
            p.stress -= 5;
            p.happiness += 5;
            p.fatigue -= 4;
            break;

        case 4: // Scroll medsos
            cout << "Kamu tenggelam dalam scrolling tanpa sadar waktu lewat.\n";
            p.happiness += 5;
            p.stress += 5;
            p.studyMood -= 10;
            // scrolling tidak mengurangi fatigue
            break;
    }

    clamp(p.happiness);
    clamp(p.studyMood);
    clamp(p.stress);
    clamp(p.understanding);
    clamp(p.health);
    clamp(p.fatigue, 0, 100);
}

// ===== TIDUR & BEGADANG =====
void applySleep(PlayerStats& p, bool earlySleep) {
    if (earlySleep) {
        cout << "Kamu tidur lebih awal dan beristirahat dengan cukup.\n";
    } else {
        cout << "Kamu tertidur karena kelelahan.\n";
    }

    // efek tidur dipengaruhi fatigue
    int baseHealthGain = earlySleep ? 12 : 8;
    int baseStressDrop = earlySleep ? 12 : 7;

    int fatiguePenalty = p.fatigue / 20; // fatigue 40 -> -2, 80 -> -4

    baseHealthGain -= fatiguePenalty;
    baseStressDrop -= fatiguePenalty;

    if (baseHealthGain < 3) baseHealthGain = 3;
    if (baseStressDrop < 3) baseStressDrop = 3;

    p.health += baseHealthGain;
    p.stress -= baseStressDrop;
    p.happiness += earlySleep ? 4 : 1;

    // tidur juga mengurangi fatigue pelan-pelan
    p.fatigue -= earlySleep ? 6 : 4;

    p.energy = p.maxEnergy;

    clamp(p.health);
    clamp(p.stress);
    clamp(p.happiness);
    clamp(p.fatigue, 0, 100);
}

void applyBegadangPenalty(PlayerStats& p) {
    cout << "Kamu memaksakan diri untuk begadang...\n";
    p.health -= 15;
    p.stress += 15;
    p.happiness -= 5;
    p.maxEnergy -= 10;
    p.fatigue += 12;

    if (p.maxEnergy < 60) p.maxEnergy = 60;
    if (p.energy > p.maxEnergy) p.energy = p.maxEnergy;

    clamp(p.health);
    clamp(p.stress);
    clamp(p.happiness);
    clamp(p.fatigue, 0, 100);
}

// ===== MENU =====
void showChoices() {
    cout << "\nPilih aktivitas:\n";
    cout << "1. Belajar keras (40 energi)\n";
    cout << "2. Hiburan (25 energi)\n";
    cout << "3. Olahraga (30 energi)\n";
    cout << "4. Scroll media sosial (20 energi)\n";
    cout << "5. Tidur sekarang\n";
}

// ===== ENDING =====
void showEnding(const PlayerStats& p) {
    cout << "\n===== HARI UJIAN =====\n";

    if (p.health <= 0) {
        cout << "Kamu sakit parah dan tidak bisa mengikuti ujian.\n";
        cout << "Tubuhmu benar-benar kehabisan tenaga sebelum hari H.\n";
        return;
    }

    cout << "Selama seminggu terakhir, hidupmu naik-turun menjelang ujian.\n";

    if (p.understanding >= 80 &&
        p.stress <= 50 &&
        p.health >= 60 &&
        p.collapseCount <= 1 &&
        p.fatigue <= 40 &&
        p.highStressDays <= 2 &&
        p.noStudyDays <= 2) {

        cout << "\nKamu masuk ruang ujian dengan kepala cukup tenang.\n";
        cout << "Kamu memang lelah, tapi tidak sampai hancur.\n";
        cout << "HASIL: NILAI SANGAT BAIK.\n";
        cout << "Kamu berhasil menyeimbangkan belajar dan istirahat.\n";
    }
    else if (p.understanding >= 60) {
        cout << "\nKamu paham sebagian besar materi, tapi perjalananmu berantakan.\n";
        if (p.collapseCount > 1 || p.highStressDays > 3 || p.fatigue > 60) {
            cout << "Selama seminggu kamu berkali-kali hampir tumbang.\n";
            cout << "HASIL: NILAI CUKUP, tapi dengan harga mental dan fisik yang mahal.\n";
        } else {
            cout << "Persiapanmu lumayan, walau masih banyak yang bisa diperbaiki.\n";
            cout << "HASIL: NILAI CUKUP.\n";
        }
    }
    else {
        cout << "\nSaat soal-soal muncul, kamu merasa banyak bagian yang asing.\n";
        cout << "HASIL: NILAI BURUK.\n";
        cout << "Kurangnya konsistensi belajar selama seminggu terakhir mulai terasa.\n";
    }

    cout << "\nRekap Akhir:\n";
    cout << "Pemahaman       : " << p.understanding << "\n";
    cout << "Kesehatan       : " << p.health << "\n";
    cout << "Stress          : " << p.stress << "\n";
    cout << "Fatigue         : " << p.fatigue << "\n";
    cout << "Runtuh          : " << p.collapseCount << " kali\n";
    cout << "Hari stress tinggi: " << p.highStressDays << " hari\n";
    cout << "Hari tanpa belajar: " << p.noStudyDays << " hari\n";
}

// ===== MAIN LOOP =====
int main() {
    srand((unsigned)time(nullptr));

    PlayerStats p;

    clearScreen();
    showTitle();
    cout << "Kelola waktumu selama 7 hari sebelum ujian.\n\n";

    while (p.day <= 7) {
        cout << "\n-------------------------------------------\n";
        cout << "HARI " << p.day << " DIMULAI\n";
        cout << "-------------------------------------------\n";

        if (p.day > 1) {
            applyForgettingAtMorning(p);
        }

        p.energy = p.maxEnergy;

        showNarrationMorning(p);

        // event tak terduga di awal hari
        triggerRandomEvent(p);

        bool endDay = false;
        bool studiedToday = false;

        while (!endDay) {
            showStats(p);
            showChoices();

            int choice = getIntInRange(1, 5);

            if (choice == 5) {
                applySleep(p, true);
                endDay = true;
            } else {
                int cost = getEnergyCost(choice);

                if (p.energy >= cost) {
                    p.energy -= cost;
                    applyChoice(p, choice);
                    if (choice == 1) studiedToday = true;
                } else {
                    cout << "Energi kamu tidak cukup.\n";
                    cout << "1. Tidur sekarang\n";
                    cout << "2. Begadang untuk tetap melakukan aksi\n";
                    int sub = getIntInRange(1, 2);

                    if (sub == 1) {
                        applySleep(p, false);
                        endDay = true;
                    } else {
                        applyChoice(p, choice);
                        if (choice == 1) studiedToday = true;
                        applyBegadangPenalty(p);
                        endDay = true;
                    }
                }
            }

            if (p.health <= 0 || p.stress >= 100) {
                cout << "\nKondisi tubuh atau mentalmu runtuh.\n";
                p.collapseCount++;

                p.health -= 5;
                p.understanding -= 8;
                p.maxEnergy -= 5;
                p.fatigue += 15;

                if (p.maxEnergy < 60) p.maxEnergy = 60;
                if (p.health < 0) p.health = 0;
                if (p.understanding < 0) p.understanding = 0;
                if (p.energy > p.maxEnergy) p.energy = p.maxEnergy;
                clamp(p.fatigue, 0, 100);

                endDay = true;
            }
        }

        // efek jangka panjang di akhir hari
        if (p.stress > 75) {
            p.highStressDays++;
            p.understanding -= 3;
            if (p.understanding < 0) p.understanding = 0;
        }

        if (!studiedToday) {
            p.noStudyDays++;
        }

        p.studiedYesterday = studiedToday;

        cout << "\nHari " << p.day << " berakhir.\n";
        cout << "-------------------------------------------\n";

        p.day++;
    }

    showEnding(p);
    return 0;
}
