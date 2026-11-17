/*
 * Nama : [Isi Nama Lengkap Anda]
 * NIM  : [Isi NIM Anda]
 * Kelas: IF-D
 */

#include <iostream>
#include <string>

using namespace std;

struct nodeQueue {
    int kode;
    string nama;
    nodeQueue* next;
};

struct nodeStack {
    int kode;
    string nama;
    nodeStack* next;
};

struct nodeTree {
    int kode;
    string nama;
    nodeTree* kiri;
    nodeTree* kanan;
};

nodeQueue* front = nullptr;
nodeQueue* last = nullptr;
nodeStack* top = nullptr;
nodeTree* akar = nullptr;

nodeTree* tambah_tree(nodeTree* akar, int kode, string nama) {
    if (akar == nullptr) {
        return new nodeTree{kode, nama, nullptr, nullptr};
    }
    if (kode < akar->kode) {
        akar->kiri = tambah_tree(akar->kiri, kode, nama);
    } else if (kode > akar->kode) {
        akar->kanan = tambah_tree(akar->kanan, kode, nama);
    }
    return akar;
}

nodeTree* cari_tree(nodeTree* akar, int kode) {
    if (akar == nullptr || akar->kode == kode) {
        return akar;
    }
    if (kode < akar->kode) {
        return cari_tree(akar->kiri, kode);
    }
    return cari_tree(akar->kanan, kode);
}

nodeTree* hapus_tree(nodeTree* akar, int kode) {
    if (akar == nullptr) {
        return nullptr;
    }

    if (kode < akar->kode) {
        akar->kiri = hapus_tree(akar->kiri, kode);
    } else if (kode > akar->kode) {
        akar->kanan = hapus_tree(akar->kanan, kode);
    } else {
        // Kasus 1 & 2: 0 anak atau 1 anak
        if (akar->kiri == nullptr) {
            nodeTree* sisa = akar->kanan;
            delete akar;
            return sisa;
        } else if (akar->kanan == nullptr) {
            nodeTree* sisa = akar->kiri;
            delete akar;
            return sisa;
        }
        // Kasus 3: 2 anak (ambil inorder successor dari sub-pohon kanan)
        else {
            nodeTree* pengganti = akar->kanan;
            while (pengganti->kiri != nullptr) {
                pengganti = pengganti->kiri;
            }
            akar->kode = pengganti->kode;
            akar->nama = pengganti->nama;
            akar->kanan = hapus_tree(akar->kanan, pengganti->kode);
        }
    }
    return akar;
}

void preOrder(nodeTree* akar, int& no) {
    if (akar == nullptr) {
        return;
    }
    cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
    no++;
    preOrder(akar->kiri, no);
    preOrder(akar->kanan, no);
}

void inOrder(nodeTree* akar, int& no) {
    if (akar == nullptr) {
        return;
    }
    inOrder(akar->kiri, no);
    cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
    no++;
    inOrder(akar->kanan, no);
}

void postOrder(nodeTree* akar, int& no) {
    if (akar == nullptr) {
        return;
    }
    postOrder(akar->kiri, no);
    postOrder(akar->kanan, no);
    cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
    no++;
}

void tambah_energi() {
    int kode;
    string nama;

    cout << "Masukkan kode energi: ";
    cin >> kode;
    if (cin.fail() || kode <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Kode energi harus berupa angka lebih dari 0!" << endl << endl;
        return;
    }

    nodeQueue* q = front;
    while (q != nullptr) {
        if (q->kode == kode) {
            cout << "Nomor kode sudah digunakan!" << endl << endl;
            return;
        }
        q = q->next;
    }

    nodeStack* s = top;
    while (s != nullptr) {
        if (s->kode == kode) {
            cout << "Nomor kode sudah digunakan!" << endl << endl;
            return;
        }
        s = s->next;
    }

    if (cari_tree(akar, kode) != nullptr) {
        cout << "Nomor kode sudah digunakan!" << endl << endl;
        return;
    }

    cout << "Masukkan nama energi: ";
    cin.ignore(10000, '\n');
    getline(cin, nama);
    if (nama.empty()) {
        cout << "Nama energi tidak boleh kosong!" << endl << endl;
        return;
    }

    nodeQueue* nb = new nodeQueue{kode, nama, nullptr};
    if (front == nullptr) {
        front = last = nb;
    } else {
        last->next = nb;
        last = nb;
    }
    cout << "Berhasil memasukkan energi!" << endl << endl;
}

void lihat_antrean() {
    if (front == nullptr) {
        cout << "Antrean energi kosong!" << endl << endl;
        return;
    }
    cout << "=== Energi Dalam Antrean ===" << endl << endl;
    nodeQueue* nb = front;
    int no = 1;
    while (nb != nullptr) {
        cout << no << ". [" << nb->kode << "] " << nb->nama << endl;
        nb = nb->next;
        no++;
    }
    cout << endl;
}

void proses_energi() {
    if (front == nullptr) {
        cout << "Antrean energi kosong!" << endl << endl;
        return;
    }

    nodeQueue* hapus = front;
    nodeStack* nb = new nodeStack{hapus->kode, hapus->nama, top};
    top = nb;
    akar = tambah_tree(akar, hapus->kode, hapus->nama);

    cout << "Berhasil memproses energi " << hapus->nama << "!" << endl << endl;

    front = hapus->next;
    if (front == nullptr) {
        last = nullptr;
    }
    delete hapus;
}

void lihat_riwayat() {
    if (top == nullptr) {
        cout << "Riwayat energi yang sudah terserap kosong!" << endl << endl;
        return;
    }
    cout << "=== Energi Yang Sudah Terserap ===" << endl << endl;
    nodeStack* nb = top;
    int no = 1;
    while (nb != nullptr) {
        cout << no << ". [" << nb->kode << "] " << nb->nama << endl;
        nb = nb->next;
        no++;
    }
    cout << endl;
}

void hapus_riwayat() {
    if (top == nullptr) {
        cout << "Riwayat energi yang sudah terserap kosong!" << endl << endl;
        return;
    }

    nodeStack* hapus = top;
    top = top->next;
    cout << "Riwayat energi " << hapus->nama << " teratas telah dihapus!" << endl << endl;
    delete hapus;
}

void cari_energi() {
    if (akar == nullptr) {
        cout << "Energi dalam organ kosong!" << endl << endl;
        return;
    }

    int kode;
    cout << "Masukkan kode energi: ";
    cin >> kode;
    if (cin.fail() || kode <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Nomor kode harus lebih dari 0!" << endl << endl;
        return;
    }

    nodeTree* hasil = cari_tree(akar, kode);
    if (hasil == nullptr) {
        cout << "Energi dengan kode " << kode << " tidak ada di organ!" << endl << endl;
        return;
    }
    cout << "Ditemukan: [" << hasil->kode << "] " << hasil->nama << endl << endl;
}

void lihat_organ() {
    if (akar == nullptr) {
        cout << "Energi organ masih kosong!" << endl << endl;
        return;
    }

    char pil;
    int no = 1;
    cout << "=== Isi Kristal Organ ===" << endl << endl;
    cout << "1. Pre-order" << endl;
    cout << "2. In-order" << endl;
    cout << "3. Post-order" << endl;
    cout << "Masukkan pilihan anda: ";
    cin >> pil;
    cout << endl;

    switch (pil) {
        case '1':
            preOrder(akar, no);
            break;
        case '2':
            inOrder(akar, no);
            break;
        case '3':
            postOrder(akar, no);
            break;
        default:
            cout << "Pilihan anda salah!" << endl;
            break;
    }
    cout << endl;
}

void gunakan_energi() {
    if (akar == nullptr) {
        cout << "Energi organ masih kosong!" << endl << endl;
        return;
    }

    int kode;
    cout << "Masukkan kode energi: ";
    cin >> kode;
    if (cin.fail() || kode <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Nomor kode harus lebih dari 0!" << endl << endl;
        return;
    }

    nodeTree* hasil = cari_tree(akar, kode);
    if (hasil == nullptr) {
        cout << "Energi dengan kode " << kode << " tidak ada di organ!" << endl << endl;
        return;
    }

    cout << "Energi " << hasil->nama << " telah digunakan!" << endl << endl;
    akar = hapus_tree(akar, kode);
}

int main() {
    char pil = '0';
    while (pil != '9') {
        cout << "=== Sistem Organ Inti Nirwana ===" << endl << endl;
        cout << "1. Tambah Energi" << endl;
        cout << "2. Lihat Energi Dalam Antrean" << endl;
        cout << "3. Proses Energi" << endl;
        cout << "4. Lihat Energi Yang Sudah Terserap" << endl;
        cout << "5. Hapus Riwayat Energi Teratas" << endl;
        cout << "6. Cari Energi Di Organ" << endl;
        cout << "7. Lihat Isi Organ" << endl;
        cout << "8. Gunakan Energi" << endl;
        cout << "9. Keluar" << endl;
        cout << "Masukkan pilihan anda: ";
        cin >> pil;
        cout << endl;

        switch (pil) {
            case '1': {
                char pil_tambah = 'y';
                while (pil_tambah == 'y' || pil_tambah == 'Y') {
                    tambah_energi();
                    cout << "Apakah anda ingin menambahkan energi lagi? (y/n): ";
                    cin >> pil_tambah;
                    cout << endl;
                }
                break;
            }
            case '2':
                lihat_antrean();
                break;
            case '3':
                proses_energi();
                break;
            case '4':
                lihat_riwayat();
                break;
            case '5':
                hapus_riwayat();
                break;
            case '6':
                cari_energi();
                break;
            case '7':
                lihat_organ();
                break;
            case '8':
                gunakan_energi();
                break;
            case '9':
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan anda salah!" << endl << endl;
                break;
        }
    }
    return 0;
}
