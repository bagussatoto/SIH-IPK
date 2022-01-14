namespace HitungIPK
{
    HitungIPKEntity rekapipk;
    string kdmatkul;
    float sks;
    char ket;
    int banyakMatakuliah;

    bool validRange(char ket)
    {
        // 65 => A
        // 69 => E
        // 97 => a
        // 101 => e
        int cekKet = (int)char(ket);

        bool rangeLowerChar = (cekKet >= 97 and cekKet <= 101);
        bool rangeUpperChar = (cekKet >= 65 and cekKet <= 69);
        return (rangeLowerChar or rangeUpperChar);
    }

    int Nilai()
    {
        int n = 0;
        switch (ket)
        {
        case 'A':
        case 'a':
            n = 4;
            break;
        case 'B':
        case 'b':
            n = 3;
            break;
        case 'C':
        case 'c':
            n = 2;
            break;
        case 'D':
        case 'd':
            n = 1;
            break;
        case 'E':
        case 'e':
            n = 0;
            break;
        }
        return (n * sks);
    }

    void PrintHasil()
    {

        cout << "\nNilai total = " << rekapipk.nilai;
        cout << "\nTotal SKS   = " << rekapipk.totalSks;
        cout << "\nIPK         = " << setiosflags(ios::fixed)
             << setprecision(2)
             << rekapipk.ipk;
    }

    void
    display()
    {
        kotakPrinting("List Mahasiswa");
        MahasiswaService::Find();

        cout << "Masukkan npm mahasiswa yang ingin dihitung ipknya" << endl;

        cin.ignore();
    mahasiswa_404:
        input("NPM\t\t: ", rekapipk.npm);

        MahasiswaEntity mhs = MahasiswaRepository::FindOneByNpm(rekapipk.npm);
        if (mhs.npm.empty())
        {
            cerr << "Mahasiswa tidak ditemukan,coba lagi" << endl;
            goto mahasiswa_404;
        }

        cout << "\nInputkan banyaknya mata kuliah: ";
        cin >> banyakMatakuliah;
        rekapipk.namaMahasiswa = mhs.nama;
        rekapipk.kelas = mhs.kelas;
        rekapipk.nilai = 0;
        rekapipk.totalSks = 0;
        rekapipk.ipk = 0;
        for (int i = 1; i <= banyakMatakuliah; i++)
        {
            enter(2);
            cin.ignore(256, '\n');

            kotakPrinting("Data ke-" + to_string(i));

            MataKuliahService::Find();
        matkul_404:
            cout << "NPM\t\t: " << rekapipk.npm << endl;
            input("Kode Matkul\t: ", kdmatkul);
            MataKuliahEntity matkul = MataKuliahRepository::FindOneByKodeMatkul(kdmatkul);
            if (matkul.kodeMatkul.empty())
            {
                cerr << "Kode Matkul tidak ditemukan,coba lagi" << endl;
                enter(2);
                goto matkul_404;
            }

            cout << "Mata kuliah\t: " << matkul.mataKuliah << endl;
            cout << "Dosen Pengampu\t: " << matkul.dosenPengampu << endl;
            cout << "Jumlah SKS\t: ";
            cin >> sks;
        input_nilai:
            cout << "Nilai huruf\t: ";
            cin >> ket;

            if (!validRange(ket))
            {
                cout << "Range nilai hanya dari A-E";
                enter(2);
                cin.ignore();
                goto input_nilai;
            }

            rekapipk.nilai += Nilai();
            rekapipk.totalSks += sks;
        }
        rekapipk.ipk = rekapipk.nilai / rekapipk.totalSks;
        PrintHasil();
        HitungIPKRepository::Create(rekapipk);
        pressEnter2Continue();
    }
}