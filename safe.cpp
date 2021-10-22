#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class LFSR {
    private:
        int tap; // indexing from 1
        vector<uint8_t> current_bits;

        uint8_t step() {
            uint8_t new_bit = (uint8_t) ((int) current_bits[tap - 1] ^ (int) current_bits.back());
            current_bits.insert(current_bits.begin(), new_bit);
            current_bits.pop_back();
            //to_string(); // for debugging
            return new_bit;
        }
        
    public:
        LFSR(int seed, int size, int tap) {
            // lsb at position 0
            for (int i = 0; i < size; i++) {
                current_bits.push_back((uint8_t)((seed >> i) & 0x1));
            }
            this->tap = tap;
        }

        void to_string() {
            cout << "[";
            int i;
            for (i = 0; i < current_bits.size() - 1; i++) {
                cout << (int) current_bits[i] << ", ";
            }
            cout << (int) current_bits[i] << "]" << endl;
        }

        uint8_t next() {
            uint8_t next_byte;
            for (int i = 0; i < sizeof(uint8_t) * 8; i++) {
               next_byte = next_byte << 1;
               next_byte = (uint8_t) ((int) next_byte | (int) step());
            }
            return next_byte;
        }

};

int main(int argc, char **args) {
    if (argc != 2 && argc != 3) {
        cout << "usage: " << args[0] << " [file] [secret (optional)]" << endl;
        exit(EXIT_FAILURE);
    }
    string filename(args[1]);
    string key;
    if (argc == 3) {
        key = args[2];
    } else {
        cout << "enter encrypt/decrypt key: ";
        cin >> key;
    }

    hash<string> h;
    LFSR lfsr((int) h(key), 11, 9);

    ifstream infile(filename);

    infile.seekg(0, ios::end);
    size_t length = infile.tellg();
    infile.seekg(0, ios::beg);

    char buf[length];

    infile.read(buf, length);
    infile.close();

    // XOR loop
    for (int i = 0; i < length; i++) {
        buf[i] = buf[i] ^ (int) lfsr.next();
    }

    string outname(filename);
    size_t slash = outname.find_last_of("/");
    if (slash != string::npos) {
        outname = outname.substr(slash + 1);
    }
    size_t pos = outname.find_last_of(".");
    if (pos == string::npos) {
        outname += ".enc";
    } else {
        outname = outname.substr(0, pos) + ".enc" + outname.substr(pos);
    }

    ofstream fout;
    fout.open(outname, ios::binary | ios::out);
    fout.write(buf, length);
    fout.close();
    cout << "wrote to file named '" << outname << "'" << endl;
}
