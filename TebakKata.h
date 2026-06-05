#ifndef TEBAKKATA_H
#define TEBAKKATA_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

struct KataGame {
    string kataAsli;
    string statusTebakan;
    int nyawa;
};

struct ScoreBoard {
    string nama;
    int skor;
};

const int JUMLAH_KATA = 15;

string bankKata[JUMLAH_KATA] = {
    "komputer",
    "algoritma",
    "program",
    "pointer",
    "struktur",
    "variabel",
    "operator",
    "database",
    "jaringan",
    "internet",
    "keyboard",
    "monitor",
    "compiler",
    "aplikasi",
    "terminal"
};

ScoreBoard leaderboard[5];
int jumlahLeaderboard = 0;

void pilihKesulitan(int *nyawa, int *bonus);
void inisialisasiGame(KataGame *game, int nyawa);
void tampilkanGame(KataGame game, char tebakanSalah[], int jumlahSalah);
bool cekHurufSudah(char huruf, char tebakanSalah[], int jumlahSalah, string status);
bool prosesTebakan(KataGame *game, char huruf);
bool cekMenang(KataGame game);
void tambahLeaderboard(string nama, int skor);
void tampilkanLeaderboard();
void gunakanHint(KataGame *game);

#endif
