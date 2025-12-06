#include <iostream>

using namespace std;

int main() {
    system("chcp 65001 >nul"); 
    cout << "\033[1;33m";
    cout << R"====ASCII====(
                                             _______________________
   _______________________-------------------                       `\
 /:--__                                                              |
||< > |                                   ___________________________/
| \__/_________________-------------------                         |
|                                                                  |
 |                 )====ASCII====";
    cout << "\033[1;37m";
    cout << R"====ASCII====(______       _          _)====ASCII====";
    cout << "\033[1;33m";
    cout << R"====ASCII====(                        |
 |                 )====ASCII====";
    cout << "\033[1;37m";
    cout << R"====ASCII====(| ___ \     | |        | |)====ASCII====";
    cout << "\033[1;33m";
    cout << R"====ASCII====(                       |
  |                )====ASCII====";
    cout << "\033[1;37m";
    cout << R"====ASCII====(| |_/ /_   _| | ___   _| | ___   _)====ASCII====";
    cout << "\033[1;33m";
    cout << R"====ASCII====(                |
  |                )====ASCII====";
    cout << "\033[1;37m";
    cout << R"====ASCII====(| ___ \ | | | |/ / | | | |/ / | | |)====ASCII====";
    cout << "\033[1;33m";
    cout << R"====ASCII====(               |
  |                )====ASCII====";
    cout << "\033[1;37m";
    cout << R"====ASCII====(| |_/ / |_| |   <| |_| |   <| |_| |)====ASCII====";
    cout << "\033[1;33m";
    cout << R"====ASCII====(               |
  |                )====ASCII====";
    cout << "\033[1;37m";
    cout << R"====ASCII====(\____/ \__,_|_|\_\\__,_|_|\_\\__,_|)====ASCII====";
    cout << "\033[1;33m";
    cout << R"====ASCII====(                |
   |                                                                  |
   |          )====ASCII====";
    cout << "\033[1;37m";
    cout << R"====ASCII====(Nikmati akses cepat ke koleksi buku digital kami)====ASCII====";
    cout << "\033[1;33m";
    cout << R"====ASCII====(        |
   |                )====ASCII====";
    cout << "\033[1;37m";
    cout << R"====ASCII====( baca kapan saja, di mana saja.)====ASCII====";
    cout << "\033[1;33m";
    cout << R"====ASCII====(                  |
  |                                              _________________  _|_
  |  ___________________-------------------------                      `\
  |/`--_                                                                 |
  ||[ ]||                                            ___________________/
   \===/___________________--------------------------

               )====ASCII====";

    cout << "\033[0m\n"; //reset warna   
    int menu;
    do{
      cout << "\033[1;36m"
           << R"====ASCII====(──★ ˙ ̟⪩⪨ Menu Bukuku !!)====ASCII====" 
           << "\033[0m"
           << "\n1. Sign Up\n2. Login\n3. Forgot Password\n0. Exit\nMenu: ";
      cin  >> menu;
      switch (menu){
        case 1:
        break;
        case 2:
        break;
        case 3:
        break;
        case 0:
        break;
        default:
        cout << "Pilihan tidak valid!";
      }
    } while (menu!=0);
    return 0;                           
}