#include <fstream>
#include <algorithm>
namespace MahasiswaRepository
{
    const string SEPARATOR = "\t";

    string filename = "database/mahasiswa.tsv";
    bool compareByNpm(const MahasiswaEntity &a, const MahasiswaEntity &b)
    {
        return a.npm < b.npm;
    }
    vector<MahasiswaEntity> sortMahasiswaEntity(vector<MahasiswaEntity> mhs)
    {
        std::sort(mhs.begin(), mhs.end(), compareByNpm);
        return mhs;
    }

    vector<MahasiswaEntity> Find(string kelas = "")
    {
        vector<MahasiswaEntity> mhsAll;
        fstream fin(filename, ios::in);
        string line;
        getline(fin, line); // skip firstline
        while (getline(fin, line))
        {
            MahasiswaEntity mhs;
            vector<string> items = split(line, SEPARATOR);
            mhs.npm = items.at(0);
            mhs.nama = items.at(1);
            mhs.kelas = items.at(2);
            if (kelas != "" && kelas != mhs.kelas)
            {
                continue;
            }
            mhsAll.push_back(mhs);
        }
        fin.close();
        mhsAll = sortMahasiswaEntity(mhsAll);
        return mhsAll;
    }

    MahasiswaEntity FindOneByNpm(string npm)
    {
        MahasiswaEntity mhs;
        fstream fin(filename, ios::in);
        string line;
        while (getline(fin, line))
        {

            vector<string> items = split(line, SEPARATOR);

            if (items.at(0) == npm)
            {
                mhs.npm = items.at(0);
                mhs.nama = items.at(1);
                mhs.kelas = items.at(2);
                fin.close();
                break;
            }
        }
        if (fin.is_open())
        {
            fin.close();
        }

        return mhs;
    }

    bool Create(MahasiswaEntity mahasiswa)
    {
        fstream fin(filename, ios::in);
        string firstLine;
        getline(fin, firstLine);

        fstream fout(filename, ios::out | ios::app);
        if (firstLine == "")
        {
            fout << "NPM" << SEPARATOR << "Nama" << SEPARATOR << "Kelas"
                 << "\n";
        }
        if (FindOneByNpm(mahasiswa.npm).npm != "")
        {
            return false;
        }
        fout << mahasiswa.npm << SEPARATOR << mahasiswa.nama << SEPARATOR << capitalizeString(mahasiswa.kelas) << "\n";
        fout.close();
        return true;
    }

    void CreateMany(vector<MahasiswaEntity> mahasiswa)
    {
        for (auto mhs : mahasiswa)
        {
            Create(mhs);
        }
    }

    void Delete(string npm)
    {
        ifstream fin;
        std::string line;
        fin.open(filename);

        int i = 0;
        while (getline(fin, line))
        {
            ++i;
            if (i == 1)
                continue;

            if (line.find(npm + SEPARATOR) != string::npos)
            {
                delete_line(filename.c_str(), i);
            }
        }
        if (fin.is_open())
        {
            fin.close();
        }
    }
};
