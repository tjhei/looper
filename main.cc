/**
 * looper
 * (c) timo.heister@gmail.com
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

 /**
   * Zerteilt den String str an den Stellen delim und gibt
   * das Ergebnis in output zurueck.
   *
   */
  inline void split_str(const std::string& str, const std::string& delim,
                        std::vector<std::string>& output)
  {
    unsigned int offset = 0;
    std::string::size_type delimIndex = 0;

    delimIndex = str.find(delim, offset);

    while (delimIndex != std::string::npos)
    {
      output.push_back(str.substr(offset, delimIndex - offset));
      offset += delimIndex - offset + delim.length();
      delimIndex = str.find(delim, offset);
    }

    output.push_back(str.substr(offset));
  }

class schnipsel
{
public:
        schnipsel():index(0){}

        schnipsel(string str, bool split):index(0)
        {
                if (!split)
                {
                        parts.push_back(str);
                        return;
                }
                split_str(str,"|",parts);
                for (int i=0;i<parts.size();++i)
                {
                        parts[i] = parts[i].erase(parts[i].find_last_not_of(' ') + 1);
                        parts[i] = parts[i].erase(0, parts[i].find_first_not_of(' '));
                }
        }

        bool inc()
        {
                index++;
                if (index>=parts.size())
                {
                        index=0;
                        return true;
                }
                else return false;
        }

        string get()
        {
                return parts[index];
        }

        int index;
        vector<string> parts;
};

int main(int argc, char *argv[])
{
    if (argc!=3)
    {
        cout << "usage: looper <programname> <loopfile>" << std::endl;
        return 0;
    }
    string cmd(argv[1]);
    cmd.append(" temp.~");
    std::ifstream in(argv[2]);

    string line, str;

    while (getline (in, line))
    {
        vector<string> parts;
        split_str(line,"#",parts);
            str.append(parts[0]);
        str.append("\n");
        line.erase();
    }

    vector<schnipsel> alles;
    {
            vector<string> p1;
            split_str(str,"{",p1);
            alles.push_back(schnipsel(p1[0],false));
            for (int i=1;i<p1.size();++i)
            {
                    vector<string> p2;
                    split_str(p1[i],"}",p2);
                    alles.push_back(schnipsel(p2[0],true));
                    alles.push_back(schnipsel(p2[1],false));
            }
    }

    int c=1;
    do {
        cout << "Loop " << c << ":" << endl;c++;
        {
            std::ofstream out("temp.~");
            for (int i=0;i<alles.size();++i)
            {
            out << alles[i].get();
            }
        }
        system(cmd.c_str());

            int j=0;
            while (j<alles.size() && alles[j].inc())
            {
                    j=j+1;
            }
            if (j>=alles.size()) break;
    } while (true);


    system("rm temp.~");
    return 0;
}
