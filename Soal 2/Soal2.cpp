#include <iostream>
#include "TebakKata.h"

void pilihKesulitan(int *nyawa, int *bonus) {
    int pilihan;

    cout << "===== PILIH KESULITAN =====\n";
    cout << "1. Easy   (8 nyawa)\n";
    cout << "2. Medium (6 nyawa)\n";
    cout << "3. Hard   (4 nyawa)\n";
    cout << "Pilih : ";
    cin >> pilihan;

    switch(pilihan) {
        case 1:
            *nyawa = 8;
            *bonus = 10;
            break;
        case 2:
            *nyawa = 6;
            *bonus = 20;
            break;
        case 3:
            *nyawa = 4;
            *bonus = 30;
            break;
        default:
            *nyawa = 8;
            *bonus = 10;
    }
}

void inisialisasiGame(KataGame *game, int nyawa) {
    int index = rand() % JUMLAH_KATA;

    game->kataAsli = bankKata[index];
    game->statusTebakan = "";

    for(int i = 0; i < game->kataAsli.length(); i++) {
        game->statusTebakan += "_";
    }

    game->nyawa = nyawa;
}

void tampilkanGame(KataGame game, char tebakanSalah[], int jumlahSalah) {

    cout << "\n===== GAME TEBAK KATA =====\n";

    cout << "Kata : ";
    for(int i = 0; i < game.statusTebakan.length(); i++) {
        cout << game.statusTebakan[i] << " ";
    }

    cout << "\nNyawa : " << game.nyawa;

    cout << "\nHuruf Salah : ";
    for(int i = 0; i < jumlahSalah; i++) {
        cout << tebakanSalah[i] << " ";
    }

    cout << endl;
}

bool cekHurufSudah(char huruf, char tebakanSalah[], int jumlahSalah, string status) {

    for(int i = 0; i < jumlahSalah; i++) {
        if(huruf == tebakanSalah[i]) {
            return true;
        }
    }

    for(int i = 0; i < status.length(); i++) {
        if(huruf == status[i]) {
            return true;
        }
    }

    return false;
}

bool prosesTebakan(KataGame *game, char huruf) {

    bool benar = false;

    for(int i = 0; i < game->kataAsli.length(); i++) {

        if(huruf == game->kataAsli[i]) {
            game->statusTebakan[i] = huruf;
            benar = true;
        }
    }

    return benar;
}

bool cekMenang(KataGame game) {

    if(game.kataAsli == game.statusTebakan) {
        return true;
    }

    return false;
}

void tambahLeaderboard(string nama, int skor) {

    if(jumlahLeaderboard < 5) {

        leaderboard[jumlahLeaderboard].nama = nama;
        leaderboard[jumlahLeaderboard].skor = skor;
        jumlahLeaderboard++;

    } else {

        int indeksTerkecil = 0;

        for(int i = 1; i < 5; i++) {
            if(leaderboard[i].skor < leaderboard[indeksTerkecil].skor) {
                indeksTerkecil = i;
            }
        }

        if(skor > leaderboard[indeksTerkecil].skor) {
            leaderboard[indeksTerkecil].nama = nama;
            leaderboard[indeksTerkecil].skor = skor;
        }
    }
}

void tampilkanLeaderboard() {

    cout << "\n===== LEADERBOARD =====\n";

    for(int i = 0; i < jumlahLeaderboard; i++) {
        cout << i + 1 << ". "
             << leaderboard[i].nama
             << " - "
             << leaderboard[i].skor
             << endl;
    }
}

void gunakanHint(KataGame *game) {

    if(game->nyawa <= 1) {
        cout << "Nyawa tidak cukup untuk hint!\n";
        return;
    }

    char huruf = game->kataAsli[0];

    for(int i = 0; i < game->kataAsli.length(); i++) {
        if(game->kataAsli[i] == huruf) {
            game->statusTebakan[i] = huruf;
        }
    }

    game->nyawa--;

    cout << "Hint digunakan! Huruf pertama dibuka.\n";
}

int main() {

    srand(time(0));

    char mainLagi;

    do {

        KataGame game;

        int nyawa;
        int bonus;

        pilihKesulitan(&nyawa, &bonus);

        inisialisasiGame(&game, nyawa);

        char tebakanSalah[26];
        int jumlahSalah = 0;

        bool selesai = false;

        while(!selesai) {

            system("cls");

            tampilkanGame(game, tebakanSalah, jumlahSalah);

            char huruf;

            cout << "\nMasukkan huruf : ";
            cin >> huruf;

            if(huruf == '?') {
                gunakanHint(&game);
                continue;
            }

            if(cekHurufSudah(huruf, tebakanSalah,
                             jumlahSalah,
                             game.statusTebakan)) {

                cout << "Huruf sudah pernah ditebak!\n";
                system("pause");
                continue;
            }

            bool benar = prosesTebakan(&game, huruf);

            if(!benar) {

                tebakanSalah[jumlahSalah] = huruf;
                jumlahSalah++;

                game.nyawa--;

                cout << "Tebakan salah!\n";
            }
            else {
                cout << "Tebakan benar!\n";
            }

            if(cekMenang(game)) {

                system("cls");

                tampilkanGame(game, tebakanSalah, jumlahSalah);

                cout << "\nANDA MENANG!\n";

                int skor = (game.nyawa * 10) + bonus;

                cout << "Skor Anda : " << skor << endl;

                string nama;

                cout << "Masukkan nama : ";
                cin >> nama;

                tambahLeaderboard(nama, skor);

                selesai = true;
            }

            if(game.nyawa <= 0) {

                system("cls");

                cout << "\nANDA KALAH!\n";
                cout << "Kata rahasia : "
                     << game.kataAsli << endl;

                selesai = true;
            }

            system("pause");
        }

        tampilkanLeaderboard();

        cout << "\nMain lagi? (Y/N) : ";
        cin >> mainLagi;

    } while(mainLagi == 'Y' || mainLagi == 'y');

    cout << "\nTerima kasih telah bermain!\n";

    return 0;
}