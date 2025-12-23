#ifndef data_berobat_h
#define data_berobat_h

#include <iostream>
#include <string>
using namespace std;

struct elmDokter;
struct elmRelasi;
struct elmPasien;

typedef elmDokter* adrDokter;
typedef elmRelasi* adrRelasi;
typedef elmPasien* adrPasien;


// Data Dokter (Parent) - Double Linked List
struct Dokter {
    string nama_dokter;
    string id;
    string spesialisasi;
    int jumlah_pasien;
};
struct elmDokter {
    Dokter info;
    adrDokter next;
    adrDokter prev;
    adrRelasi firstRelasi; // head dari list relasi
};

struct ListDokter {
    adrDokter first;
    adrDokter last;
};

// Data Relasi - Single Linked List
struct elmRelasi {
    adrRelasi next;
    adrPasien child; // pointer ke data pasien (child)
};

// Data Pasien (Child) - Single Linked List
struct infotypePasien {
    string nama_pasien;   
    int id;
    int umur;
    string keluhan;       
    int jumlah_dokter;    
};

struct elmPasien {
    infotypePasien info;
    adrPasien next;
};

struct ListPasien {
    adrPasien first;
};

// Manajemen Dokter
void createListDokter(ListDokter &L);
adrDokter alokasiDokter(string nama, string id, string spesialisasi);
void insertLastDokter(ListDokter &L, adrDokter P);
void deleteDokter(ListDokter &L, string id); // menghapus dokter beserta semua relasinya
adrDokter findDokter(ListDokter L, string id); 
void showAllDokter(ListDokter L); // menampilkan semua data dokter tanpa pasien

// Manajemen Relasi
void connect(ListDokter &LD, ListPasien &LP, string idDokter, int idPasien); // c. connect parent dengan child (dan sebaliknya)
void showPasienByDokter (ListDokter LD, string idDokter); // g. Menampilkan data pasien yang ditangani dokter tertentu
void showDokterByPasien(ListDokter LD, ListPasien LP, int idPasien); // h. Menampilkan data dokter yang menangani pasien tertentu
void showDokterSibuk (ListDokter LD); // i. Menampilkan data dokter yang tidak sibuk dan yang paling sibuk

// Manajemen Pasien
void createListPasien(ListPasien &L);
adrPasien alokasiPasien(string nama, int id, int umur, string keluhan);
void insertPasien(ListPasien &L, adrPasien P);
adrPasien findPasien(ListPasien L, int id);
void deletePasien(ListPasien &LP, ListDokter &LD, int id);
void showAllPasienWithDokter(ListPasien LP, ListDokter LD);

#endif