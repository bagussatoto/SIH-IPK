#include <fstream>
#include <algorithm>

namespace MataKuliahRepository
{
    const string SEPARATOR = "\t";
    string filename = "database/mataKuliah.tsv";
    bool compareByKodeMatkul(const MataKuliahEntity &a, const MataKuliahEntity &b)
    {
        return a.kodeMatkul < b.kodeMatkul;
    }
    vector<MataKuliahEntity> sortMataKuliahEntity(vector<MataKuliahEntity> matkul)
    {
        std::sort(matkul.begin(), matkul.end(), compareByKodeMatkul);
        return matkul;
    }

    vector<MataKuliahEntity> Find()
    {
        vector<MataKuliahEntity> matkulAll;
        fstream fin(filename, ios::in);
        string line;
        getline(fin, line); // skip firstline

        while (getline(fin, line))
        {
            MataKuliahEntity matkul;
            vector<string> items = split(line, SEPARATOR);
            matkul.kodeMatkul = items.at(0);
            matkul.mataKuliah = items.at(1);
            matkul.dosenPengampu = items.at(2);

            matkulAll.push_back(matkul);
        }
        fin.close();
        matkulAll = sortMataKuliahEntity(matkulAll);
        return matkulAll;
    }

    MataKuliahEntity FindOneByKodeMatkul(string kodeMatkul)
    {
        MataKuliahEntity matkul;
        fstream fin(filename, ios::in);
        string line;
        while (getline(fin, line))
        {

            vector<string> items = split(line, SEPARATOR);

            if (items.at(0) == kodeMatkul)
            {
                matkul.kodeMatkul = items.at(0);
                matkul.mataKuliah = items.at(1);
                matkul.dosenPengampu = items.at(2);
                fin.close();
            }
        }
        if (fin.is_open())
        {
            fin.close();
        }

        return matkul;
    }

    bool Create(MataKuliahEntity mahasiswa)
    {
        fstream fin(filename, ios::in);
        string firstLine;
        getline(fin, firstLine);

        fstream fout(filename, ios::out | ios::app);
        if (firstLine == "")
        {
            fout << "Kode Matkul" << SEPARATOR << "Mata Kuliah" << SEPARATOR << "Dosen Pengampu"
                 << "\n";
        }
        if (FindOneByKodeMatkul(mahasiswa.kodeMatkul).kodeMatkul != "")
        {
            return false;
        }
        fout << mahasiswa.kodeMatkul << SEPARATOR << mahasiswa.mataKuliah << SEPARATOR << mahasiswa.dosenPengampu << "\n";
        fout.close();
        return true;
    }

    void CreateMany(vector<MataKuliahEntity> mahasiswa)
    {
        for (auto matkul : mahasiswa)
        {
            Create(matkul);
        }
    }

    void Delete(string kodeMatkul)
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

            if (line.find(kodeMatkul + SEPARATOR) != string::npos)
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
