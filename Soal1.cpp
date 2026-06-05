#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

// Data tiap mobil yang masuk parkir
struct DataMobil {
    string nomorPlat;
    string namaMerk;
    string warnaBody;
    time_t jamMasuk;
};

// Semua logika parkir ada di sini
class LokasiParkir {
private:
    const int BATAS_SLOT = 20;
    vector<DataMobil*> slotParkir;

public:
    ~LokasiParkir() {
        for (auto* mobil : slotParkir)
            delete mobil;
    }

    bool slotHabis() {
        return (int)slotParkir.size() >= BATAS_SLOT;
    }

    void masukkanMobil(int total) {
        if ((int)slotParkir.size() + total > BATAS_SLOT) {
            cout << "Maaf, parkiran hanya dapat memuat " << BATAS_SLOT << " mobil." << endl;
            return;
        }

        for (int urutan = 0; urutan < total; urutan++) {
            DataMobil* baru = new DataMobil();

            cout << "\nMobil ke " << (slotParkir.size() + 1) << endl;
            cout << "Masukkan plat mobil  : ";
            cin.ignore();
            getline(cin, baru->nomorPlat);
            cout << "Masukkan merk mobil  : ";
            getline(cin, baru->namaMerk);
            cout << "Masukkan warna mobil : ";
            getline(cin, baru->warnaBody);
            baru->jamMasuk = time(nullptr);

            slotParkir.push_back(baru);
        }
    }

    void lihatDaftarParkir() {
        if (slotParkir.empty()) {
            cout << "Belum ada mobil yang terparkir saat ini.\n";
            return;
        }

        cout << "\nDAFTAR MOBIL YANG SUDAH TERPARKIR :" << endl;
        cout << string(65, '=') << endl;

        for (int no = 0; no < (int)slotParkir.size(); no++) {
            DataMobil* mobil = slotParkir[no];

            time_t saat_ini = time(nullptr);
            int totalDetik = (int)difftime(saat_ini, mobil->jamMasuk);

            int j = totalDetik / 3600;
            int m = (totalDetik % 3600) / 60;
            int d = totalDetik % 60;

            cout << "Mobil ke-" << (no + 1) << endl;
            cout << "Plat mobil   : " << mobil->nomorPlat << endl;
            cout << "Merk mobil   : " << mobil->namaMerk << endl;
            cout << "Warna mobil  : " << mobil->warnaBody << endl;
            cout << "Waktu parkir : " << j << " jam " << m << " menit " << d << " detik" << endl;
            cout << string(65, '=') << endl;
        }
    }

    void prosesBayar() {
        if (slotParkir.empty()) {
            cout << "Tidak ada mobil yang sedang parkir.\n";
            return;
        }

        lihatDaftarParkir();

        string inputPlat;
        cout << "\nMasukkan plat mobil yang ingin dibayar : ";
        cin.ignore();
        getline(cin, inputPlat);

        // Samakan ke huruf kapital biar pencarian tidak case-sensitive
        string platKapital = inputPlat;
        transform(platKapital.begin(), platKapital.end(), platKapital.begin(), ::toupper);

        int posisi = -1;
        for (int i = 0; i < (int)slotParkir.size(); i++) {
            string cek = slotParkir[i]->nomorPlat;
            transform(cek.begin(), cek.end(), cek.begin(), ::toupper);
            if (cek == platKapital) {
                posisi = i;
                break;
            }
        }

        if (posisi == -1) {
            cout << "PLAT TIDAK DITEMUKAN !" << endl;
            return;
        }

        DataMobil* targetMobil = slotParkir[posisi];
        int totalDetik = (int)difftime(time(nullptr), targetMobil->jamMasuk);

        int j = totalDetik / 3600;
        int m = (totalDetik % 3600) / 60;
        int d = totalDetik % 60;

        // Tarif: Rp2000/jam + Rp500/menit, minimum Rp2000
        long long tagihan = 0;
        if (totalDetik <= 60) {
            tagihan = 2000;
        } else {
            tagihan = (j * 2000LL) + (m * 500LL) + (d > 0 ? 500LL : 0LL);
            if (tagihan < 2000) tagihan = 2000;
        }

        cout << string(65, '=') << endl;
        cout << "B I A Y A   P A R K I R : Rp" << tagihan << endl;
        cout << string(65, '=') << endl;

        delete slotParkir[posisi];
        slotParkir.erase(slotParkir.begin() + posisi);

        cout << "Mobil " << inputPlat << " berhasil keluar. Terima kasih!\n";
    }
};

// Tampilan menu setiap putaran
void cetakMenu(const string& petugas, const string& idnya) {
    cout << "\nNama Petugas : " << petugas << endl;
    cout << "ID Petugas   : " << idnya << endl;
    cout << "\n              TERIMA KASIH ATAS KERJASAMANYA !" << endl;
    cout << string(28, '-') << " S E L A M A T   B E R T U G A S " << string(9, '-') << endl;
    cout << string(70, '=') << endl;
    cout << "\nSilahkan input opsi berikut dalam bentuk angka." << endl;
    cout << "1. Tambahkan Daftar Kendaraan" << endl;
    cout << "2. Tampilkan Daftar Kendaraan" << endl;
    cout << "3. Pembayaran" << endl;
    cout << "4. Keluar Program" << endl;
    cout << "Masukkan opsi : ";
}

int main() {
    string namaPetugas, idPetugas;
    LokasiParkir parkir;

    cout << string(70, '=') << endl;
    cout << string(28, '-') << " S E L A M A T   D A T A N G " << string(12, '-') << endl;
    cout << "                  DI PORTAL PARKIR KHUSUS MOBIL" << endl;
    cout << "                          MALL PRIENAL" << endl;
    cout << string(70, '=') << endl;
    cout << "\nKami senang Anda telah hadir." << endl;
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini.\n" << endl;

    cout << "Masukkan nama : ";
    getline(cin, namaPetugas);
    cout << "Masukkan ID   : ";
    getline(cin, idPetugas);

    int pilihan;
    do {
        cetakMenu(namaPetugas, idPetugas);
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                if (parkir.slotHabis()) {
                    cout << "Maaf, parkiran hanya dapat memuat 20 mobil." << endl;
                    break;
                }
                int jml;
                cout << "Masukan jumlah mobil yang akan di parkirkan : ";
                cin >> jml;
                parkir.masukkanMobil(jml);
                break;
            }
            case 2:
                parkir.lihatDaftarParkir();
                break;
            case 3:
                parkir.prosesBayar();
                break;
            case 4:
                cout << "\nTerima kasih " << namaPetugas << "! Sampai jumpa.\n";
                break;
            default:
                cout << "Pilihan tidak tersedia. Coba lagi.\n";
        }

    } while (pilihan != 4);

    return 0;
}