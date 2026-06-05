#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

struct Negara {
    string nama;
    string hint;
};

int main() {
    srand(time(0));

    Negara daftar[] = {
        {"malaysia", "_al_ys_a"},
        {"peru", "_er_"},
        {"vatikan", "va_ika_"},
        {"brazil", "br_zi_"},
        {"kamboja", "_am_o_a"},
        {"swedia", "sw_d__"},
        {"uzbekistan", "u_b_k_st_n"}
    };
    int jumlah = sizeof(daftar)/sizeof(daftar[0]);

    int skor = 0;
    char lagi = 'y';

    cout << "=== Game Tebak Negara ===\n";

    while (lagi == 'y' || lagi == 'Y') {
        int idx = rand() % jumlah;
        cout << "Tebak negara: " << daftar[idx].hint << endl;
        cout << "Negara apakah yang dimaksud? ";
        string jawaban;
        cin >> jawaban;

        if (jawaban == daftar[idx].nama) {
            cout << "Selamat! Anda benar.\n";
            skor++;
        } else {
            cout << "Maaf, jawaban Anda salah. Coba lagi.\n";
        }

        cout << "Skor Anda: " << skor << endl;
        cout << "Ingin bermain lagi? (y/n): ";
        cin >> lagi;
    }

    cout << "Game Selesai :D\n";
    cout << "Skor akhir Anda: " << skor << endl;
    return 0;
}
