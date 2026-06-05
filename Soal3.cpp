#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    char mainLagi;

    do {
        string kataRahasia = "SHOFY";
        string kataTebakan(kataRahasia.length(), '_');

        vector<char> tebakanSalah;
        vector<char> semuaTebakan;

        int nyawa = 6;
        char huruf;

        while (nyawa > 0 && kataTebakan != kataRahasia) {

            system("cls");

            cout << " PERMAINAN HANGMAN \n\n";

            cout << "Kata : ";
            for (char c : kataTebakan) {
                cout << c << " ";
            }

            cout << "\n\nSisa Nyawa : " << nyawa;

            cout << "\nTebakan Salah : ";
            for (char c : tebakanSalah) {
                cout << c << " ";
            }

            cout << "\n\nMasukkan huruf: ";
            cin >> huruf;

            huruf = toupper(huruf);

            if (find(semuaTebakan.begin(), semuaTebakan.end(), huruf) != semuaTebakan.end()) {
                cout << "\nHuruf sudah pernah ditebak!";
                cout << "\nTekan Enter untuk lanjut...";
                cin.ignore();
                cin.get();
                continue;
            }

            semuaTebakan.push_back(huruf);

            bool benar = false;

            for (int i = 0; i < kataRahasia.length(); i++) {
                if (kataRahasia[i] == huruf) {
                    kataTebakan[i] = huruf;
                    benar = true;
                }
            }

            if (!benar) {
                tebakanSalah.push_back(huruf);
                nyawa--;
            }
        }

        system("cls");

        if (kataTebakan == kataRahasia) {
            cout << "SELAMAT! ANDA MENANG!\n";
            cout << "Kata Rahasia: " << kataRahasia << endl;
        } else {
            cout << "ANDA KALAH!\n";
            cout << "Kata Rahasia sebenarnya: " << kataRahasia << endl;
        }

        cout << "\nApakah Anda ingin bermain lagi? (Y/N): ";
        cin >> mainLagi;
        mainLagi = toupper(mainLagi);

    } while (mainLagi == 'Y');
    cout << "\nTerima kasih telah bermain!\n";

    return 0;
}