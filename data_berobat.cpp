#include "data_berobat.h"

void createListDokter(ListDokter &L) {
    L.first = nullptr;
    L.last = nullptr;
}

// createListPasien
void createListPasien(ListPasien &L) {
    L.first = nullptr;
    L.last = nullptr;
}

adrDokter alokasiDokter(string nama, string spesialisasi) {
    adrDokter P = new elmDokter;
    P->info.nama_dokter = nama;
    P->info.spesialisasi = spesialisasi;
    P->info.jumlah_pasien = 0;
    P->next = nullptr;
    P->prev = nullptr;
    P->firstRelasi = nullptr; // inisialisasi head relasi
    return P;
}

// alokasiPasien
adrPasien alokasiPasien(string nama, int umur, string keluhan) {
    adrPasien P = new elmPasien;
    P->info.nama_pasien = nama;
    P->info.umur = umur;
    P->info.keluhan = keluhan;
    P->info.jumlah_dokter = 0;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}

// a. Penambahan Dokter (Instert Last)
void insertLastDokter(ListDokter &L, adrDokter P) {
    if (L.first == nullptr) {
        L.first = P;
        L.last = P;
    } else {
        L.last->next = P;
        P->prev = L.last;
        L.last = P;
    }
}

// b. Penambahan Pasien (Insert First)
void insertFirstPasien(ListPasien &L, adrPasien P) {
    if (L.first == nullptr) {
        L.first = P;
        L.last = P;
    } else {
        P->next = L.first;
        L.first->prev = P;
        L.first = P;
    }
}

adrDokter findDokter(ListDokter L, string nama) {
    adrDokter P = L.first;
    while (P != nullptr) {
        if (P->info.nama_dokter == nama) {
            return P;
        }
        P = P->next;
    }
    return nullptr; // jika tidak ditemukan
}

// find pasien
adrPasien findPasien(ListPasien L, string nama) {
    adrPasien P = L.first;
    while (P != nullptr) {
        if (P->info.nama_pasien == nama) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

// c. connect parent dengan child (dan sebaliknya)
void connect(ListDokter &LD, ListPasien &LP, string namaDokter, string namaPasien) {
    adrDokter D = findDokter(LD, namaDokter);
    adrPasien P = findPasien(LP, namaPasien);
    if (D == nullptr && P == nullptr) {
        cout << "Dokter atau Pasien tidak ditemukan\n";
        return;
    }
    // validasi jumlah dokter pada pasien maksimal 5
    if (P->info.jumlah_dokter > 5) {
        cout << "Pasien " << P->info.nama_pasien << " sudah memiliki 5 dokter (Max).\n";
        return;
    }
    // cek apakah relasi sudah ada
    adrRelasi cek = D->firstRelasi;
    while (cek != nullptr) {
        if (cek->child == P) {
            cout << "Relasi sudah ada sebelumnya.\n";
            return;
        }
        cek = cek->next;
    }
    // membuat relasi baru (insert first ke list relasi dokter)
    adrRelasi R = new elmRelasi;
    R->child = P;
    R->next = D->firstRelasi;
    D->firstRelasi = R;
    // update jumlah pasien pada dokter dan jumlah dokter pada pasien
    D->info.jumlah_pasien += 1;
    P->info.jumlah_dokter += 1;
    cout << "Berhasil menghubungkan Dr. " << D->info.nama_dokter << " dengan Pasien " << P->info.nama_pasien << ".\n";
}

// d. Menghapus data dokter tertentu beserta semua relasinya
void deleteDokter(ListDokter &L, string nama) {
    adrDokter D = findDokter(L, nama);
    if (D == nullptr) {
        cout << "Dokter tidak ditemukan.\n";
        return;
    }
    // menghapus semua relasi pada dokter tersebut dan update counter pasien
    adrRelasi R = D->firstRelasi;
    while (R != nullptr) {
        R->child->info.jumlah_dokter -= 1; // update jumlah dokter pada pasien
        adrRelasi temp = R;
        R = R->next;
        delete temp;
    }
    // menghapus node dokter dari list dokter
    if (D == L.first && D == L.last) {
        L.first = nullptr;
        L.last = nullptr;
    } else if (D == L.first) {
        L.first = D->next;
        L.first->prev = nullptr;
    } else if (D == L.last) {
        L.last = D->prev;
        L.last->next = nullptr;
    } else {
        D->prev->next = D->next;
        D->next->prev = D->prev;
    }
    delete D;
    cout << "Dokter " << nama << " beserta semua relasinya telah dihapus.\n";
}

// e. Menghapus data pasien tertentu beserta semua relasinya
void deletePasien(ListPasien &LP, ListDokter &LD, string nama) {
    adrPasien target = findPasien(LP, nama);
    if (target == nullptr) {
        cout << "Pasien tidak ditemukan.\n";
        return;
    }


 // hapus relasi pasien dari semua dokter
    adrDokter D = LD.first;
    while (D != nullptr) {
        adrRelasi R = D->firstRelasi;
        adrRelasi prevR = nullptr;
        while (R != nullptr) {
            if (R->child == target) {
                if (prevR == nullptr) {
                    D->firstRelasi = R->next;
                } else {
                    prevR->next = R->next;
                }
                D->info.jumlah_pasien--;
                adrRelasi temp = R;
                R = R->next;
                delete temp;
                continue;
            }
            prevR = R;
            R = R->next;
        }
        D = D->next;
    }

       // hapus node pasien dari list pasien
    if (target == LP.first && target == LP.last) {
        LP.first = nullptr;
        LP.last = nullptr;
    } else if (target == LP.first) {
        LP.first = target->next;
        if (LP.first != nullptr) LP.first->prev = nullptr;
    } else if (target == LP.last) {
        LP.last = target->prev;
        if (LP.last != nullptr) LP.last->next = nullptr;
    } else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }
    delete target;
    cout << "Pasien " << nama << " beserta semua relasinya telah dihapus.\n";
}


// f. Menampilkan semua pasien beserta dokternya
void showAllPasienWithDokter(ListPasien LP, ListDokter LD) {
    cout << "\n=== DAFTAR PASIEN ===\n";
    adrPasien P = LP.first;
    while (P != nullptr) {
        cout << "\nPasien: " << P->info.nama_pasien
             << " (Umur: " << P->info.umur
             << ", Keluhan: " << P->info.keluhan << ")\n";
        cout << "Jumlah Dokter: " << P->info.jumlah_dokter << "\n";
        cout << "Daftar Dokter:\n";

        bool adaDokter = false;
        adrDokter D = LD.first;
        while (D != nullptr) {
            adrRelasi R = D->firstRelasi;
            while (R != nullptr) {
                if (R->child == P) {
                    cout << "- Dr. " << D->info.nama_dokter
                         << " (" << D->info.spesialisasi << ")\n";
                    adaDokter = true;
                }
                R = R->next;
            }
            D = D->next;
        }
        if (!adaDokter) {
            cout << "- Tidak ada dokter.\n";
        }
        P = P->next;
    }
}

// g. Menampilkan data pasien yang ditangani dokter tertentu
void showPasienByDokter(ListDokter LD, string namaDokter) {
    adrDokter D = findDokter(LD, namaDokter);
    if (!D) {
        cout << "Dokter dengan nama " << namaDokter << " tidak ditemukan.\n";
        return;
    }

    cout << "\n=== Pasien yang ditangani Dr. " << D->info.nama_dokter << " ===\n";
    if (D->firstRelasi == nullptr) {
        cout << "- Belum ada pasien.\n";
        return;
    }

    // beda gaya: pakai for loop pointer
    for (adrRelasi R = D->firstRelasi; R != nullptr; R = R->next) {
        adrPasien P = R->child;
        cout << "- " << P->info.nama_pasien
             << " | Umur: " << P->info.umur
             << " | Keluhan: " << P->info.keluhan << "\n";
    }
}

// h. Menampilkan data dokter yang menangani pasien tertentu
void showDokterByPasien (ListDokter LD, ListPasien LP, string namaPasien) {
    adrPasien P = findPasien(LP, namaPasien);
    if (P == nullptr) {
        cout << "Pasien tidak ditemukan.\n";
        return;
    }
    cout << "\nDokter yang menangani Pasien " << P->info.nama_pasien << ":\n";
    adrDokter D = LD.first;
    bool found = false;
    while (D != nullptr) {
        adrRelasi R = D->firstRelasi;
        while (R != nullptr) {
            if (R->child == P) {
                cout << "- Dr. " << D->info.nama_dokter << " (" << D->info.spesialisasi << ")\n";
                found = true;
            }
            R = R->next;
        }
        D = D->next;
    }
    if (!found) {
        cout << "Tidak ada dokter yang menangani pasien ini.\n";
    }
}

// i. Menampilkan data dokter yang tidak sibuk dan yang paling sibuk
void showDokterSibuk (ListDokter LD) {
    if (LD.first == nullptr) {
        cout << "Tidak ada data dokter.\n";
        return;
    }
    adrDokter D = LD.first;
    int maxPasien = -1;
    int minPasien = 9999; // asumsi tidak ada dokter dengan pasien sebanyak ini
    while (D != nullptr) {
        if (D->info.jumlah_pasien > maxPasien) {
            maxPasien = D->info.jumlah_pasien;
        }
        if (D->info.jumlah_pasien < minPasien) {
            minPasien = D->info.jumlah_pasien;
        }
        D = D->next;
    }
    cout << "\n=== KESIBUKAN DOKTER ===\n";
    cout << "Dokter Paling Sibuk (" << maxPasien << " pasien):\n";
    D = LD.first;
    while (D != nullptr) {
        if (D->info.jumlah_pasien == maxPasien) {
            cout << "- Dr. " << D->info.nama_dokter << " (" << D->info.spesialisasi << ")\n";
        }
        D = D->next;
    }
    cout << "\nDokter Paling Luang/Tidak Sibuk (" << minPasien << " pasien):\n";
    D = LD.first;
    while (D != nullptr) {
        if (D->info.jumlah_pasien == minPasien) {
            cout << "- Dr. " << D->info.nama_dokter << " (" << D->info.spesialisasi << ")\n";
        }
        D = D->next;
    }
}

// menampilkan dokter tanpa pasien
void showAllDokter (ListDokter L) {
    cout << "\n=== DAFTAR DOKTER ===\n";
    adrDokter D = L.first;
    while (D != nullptr) {
        cout << "Nama Dokter: " << D->info.nama_dokter << endl;
        cout << "Spesialisasi: " << D->info.spesialisasi << endl;
        cout << "Jumlah pasien: " << D->info.jumlah_pasien << endl;
        cout << "-----------------------------" << endl;
        D = D->next;
    }
}

