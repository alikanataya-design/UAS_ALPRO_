{* Humairo Hendrifa
    251401088
    AP UAS - NOMOR 4 *}

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Minesweeper {
private:
    int size;               // ukuran papan
    int bombCount;          // jumlah bom
    int board[10][10];      // isi kotak: -1 = bom, >=0 = jumlah bom sekitar
    bool revealed[10][10];  // status buka
    bool flagged[10][10];   // status tanda
    time_t startTime;       // waktu mulai

    bool inBounds(int x, int y) {
        return x >= 0 && x < size && y >= 0 && y < size;
    }

    void placeBombs() {
        int placed = 0;
        while (placed < bombCount) {
            int x = rand() % size;
            int y = rand() % size;
            if (board[x][y] != -1) {
                board[x][y] = -1;
                placed++;
            }
        }
    }

    void calculateNumbers() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == -1) continue;
                int count = 0;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int nx = i + dx, ny = j + dy;
                        if (inBounds(nx, ny) && board[nx][ny] == -1) count++;
                    }
                }
                board[i][j] = count;
            }
        }
    }

    void floodFill(int x, int y) {
        if (!inBounds(x, y) || revealed[x][y]) return;
        revealed[x][y] = true;
        if (board[x][y] == 0) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx != 0 || dy != 0) floodFill(x + dx, y + dy);
                }
            }
        }
    }

public:
    Minesweeper(int n, int bombs) {
        size = n;
        bombCount = bombs;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++) {
                board[i][j] = 0;
                revealed[i][j] = false;
                flagged[i][j] = false;
            }
        placeBombs();
        calculateNumbers();
        startTime = time(0);
    }

    void showBoard(bool revealAll = false) {
        cout << "   ";
        for (int j = 0; j < size; j++) cout << j+1 << " ";
        cout << "\n";
        for (int i = 0; i < size; i++) {
            cout << i+1 << " ";
            if (i+1 < 10) cout << " ";
            for (int j = 0; j < size; j++) {
                if (revealAll) {
                    if (board[i][j] == -1) cout << "* ";
                    else cout << board[i][j] << " ";
                } else if (flagged[i][j]) cout << "F ";
                else if (!revealed[i][j]) cout << "# ";
                else if (board[i][j] == -1) cout << "* ";
                else cout << board[i][j] << " ";
            }
            cout << "\n";
        }
    }

    bool openCell(int x, int y) {
        if (!inBounds(x, y) || revealed[x][y]) return true;
        if (board[x][y] == -1) {
            cout << "Game Over! Kamu kena bom!\n";
            showBoard(true);
            return false;
        }
        floodFill(x, y);
        return true;
    }

    void flagCell(int x, int y) {
        if (inBounds(x, y) && !revealed[x][y]) flagged[x][y] = !flagged[x][y];
    }

    bool checkWin() {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++) {
                if (board[i][j] == -1 && !flagged[i][j]) return false;
                if (board[i][j] != -1 && !revealed[i][j]) return false;
            }
        return true;
    }

    void play() {
        while (true) {
            showBoard();
            cout << "Aksi: (1) Buka (2) Tandai (3) Keluar\n";
            int action; cin >> action;
            if (action == 3) break;
            int x, y;
            cout << "Masukkan koordinat (baris kolom): ";
            cin >> x >> y;
            x--; y--;
            if (action == 1) {
                if (!openCell(x, y)) break;
            } else if (action == 2) {
                flagCell(x, y);
            }
            if (checkWin()) {
                cout << "Selamat! Kamu menang!\n";
                time_t endTime = time(0);
                cout << "Waktu bermain: " << difftime(endTime, startTime) << " detik\n";
                showBoard(true);
                break;
            }
        }
    }
};

int main() {
    srand(time(0));
    int n, bombs;
    cout << "=== Minesweeper++ ===\n";
    cout << "Masukkan ukuran papan (max 10): ";
    cin >> n;
    cout << "Masukkan jumlah bom: ";
    cin >> bombs;
    Minesweeper game(n, bombs);
    game.play();
    return 0;
}