#include <limits>
namespace Menu
{
    static int pilihan;
    int padding = 10;

    void exitIfNeeded()
    {
        if (pilihan == 99)
        {
            clear();
            kotakPrinting("SELAMAT TINGGAL");
            exit(1);
        }
    }

    void print(vector<string> data)
    {
        int i = 1;
        enter(2);

        for (auto menu : data)
        {
            if (menu == "")
            {
                cout << endl;
                continue;
            }

            if (menu == "0")
            {
                cout << printWidth(padding) << "[" << 0 << "] Kembali" << endl;
                continue;
            }
            if (menu == "99")
            {
                cout << printWidth(padding) << "[" << 99 << "] Keluar" << endl;
                continue;
            }

            cout << printWidth(padding) << "[" << i << "]"
                 << " " << menu << endl;
            i++;
        }
        enter(2);
    }

    void pilih(string text)
    {
    pilih:
        cout << text;

        if (!(cin >> pilihan))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again \n";
            goto pilih;
        }
    }

    void display()
    {
    daftar_menu:
        kotakPrinting(printWidth(4) + "Daftar Menu" + printWidth(4));
        print({"Manajemen Mahasiswa", "Manajemen Mata Kuliah", "Hitung IPK", "Kosongkan rekapan IPK", "", "", "99"});

        pilih("[Menu] pilih: ");

        switch (pilihan)
        {
        case 1:
        menu_mahasiswa:
            kotakPrinting("Manajemen Data Mahasiswa");
            print({"List Mahasiswa", "Tambah Mahasiswa", "Hapus Mahasiswa", "", "", "0", "99"});

            pilih("[Mahasiswa] pilih: ");

            switch (pilihan)
            {
            case 1:
                clear();
                MahasiswaService::Find();
                break;
            case 2:
                kotakPrinting("Tambah Mahasiswa");
                MahasiswaService::Create();
                break;
            case 3:
                kotakPrinting("Hapus Mahasiswa");
                MahasiswaService::Delete();
                break;
            case 0:
                goto daftar_menu;
                break;

            default:
                exitIfNeeded();
                break;
            }
            enter(2);
            goto menu_mahasiswa;

            break;
        case 2:
        menu_matkul:
            kotakPrinting("Manajemen Data Mata Kuliah");
            print({"List Mata Kuliah", "Tambah Mata Kuliah", "Hapus Mata Kuliah", "", "", "0", "99"});

            pilih("[MataKuliah] pilih: ");

            switch (pilihan)
            {
            case 1:
                clear();
                MataKuliahService::Find();
                break;
            case 2:
                kotakPrinting("Tambah Mata Kuliah");
                MataKuliahService::Create();
                break;
            case 3:
                kotakPrinting("Hapus Mata Kuliah");
                MataKuliahService::Delete();
                break;
            case 0:
                goto daftar_menu;
                break;

            default:
                exitIfNeeded();
                break;
            }
            enter(2);
            goto menu_matkul;

            break;
        case 3:
            clear();

            HitungIPK::display();
            enter(2);
            break;
        case 4:
            enter(2);
            pressEnter2Continue();
            HitungIPKRepository::DeleteAll();
            break;

        default:
            exitIfNeeded();
            break;
        }
        goto daftar_menu;
    }

}