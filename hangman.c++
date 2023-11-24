#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <unistd.h>

bool title_screen() {
    system("cls");
    int choice;
    std::string title_banner =
        "===================================================================\n"
        "                                                                ###\n"    
        "##   ##  #######  ###  ##  #######  ##   ##  #######  ###  ##   ###\n"    
        "##   ##       ##  #### ##           ### ###       ##  #### ##   ###\n"    
        "#######  #######  ## ####  ##   ##  #######  #######  ## ####   ###\n"    
        "##   ##  ##   ##  ##  ###  ##    #  ## # ##  ##   ##  ##  ###\n"          
        "##   ##  ##   ##  ##   ##  #######  ##   ##  ##   ##  ##   ##   ###\n\n"
        "===================================================================\n";
    int len = title_banner.length();
    for(int i = 0; i < len; i++) {
        std::cout << title_banner[i];
        usleep(1000);
    }
    std::cout << "\n                        BY: Darkuz_69\n";
    std::cout << "         [1] Play                           [0] Quit\n";
    do{
        std::cout << "                          INPUT: ";
        std::cin >> choice;
    } while(choice != 1 && choice != 0); //Handles non 1/0 numbers
    if(choice == 1) {
        return true;
    } else {
        return false;
    }
}

void hangman_phase(int mistakes) {
    std::string hangman[] = {
"            +---+\n"
"            |   |\n"
"                |\n"
"                |\n"
"                |\n"
"                |\n"
"            =========\n",

"            +---+\n"
"            |   |\n"
"            O   |\n"
"                |\n"
"                |\n"
"                |\n"
"            =========\n",
"            +---+\n"
"            |   |\n"
"            O   |\n"
"            |   |\n"
"                |\n"
"                |\n"
"            =========\n",
"            +---+\n"
"            |   |\n"
"            O   |\n"
"           /|   |\n"
"                |\n"
"                |\n"
"            =========\n",
"            +---+\n"
"            |   |\n"
"            O   |\n"
"           /|\\  |\n"
"                |\n"
"                |\n"
"            =========\n",
"            +---+\n"
"            |   |\n"
"            O   |\n"
"           /|\\  |\n"
"           /    |\n"
"                |\n"
"            =========\n",
"            +---+\n"
"            |   |\n"
"            O   |\n"
"           /|\\  |\n"
"           / \\  |\n"
"                |\n"
"            =========\n"
    };
    std::cout << hangman[mistakes] << "\n"; //Prints what hangman phase based on how many mistakes taken
}

std::string mystery_word() {
    int word_index = rand() % 58109; // Determines what word will be guessed
    std::string mystery_word; // Where the mystery word will be saved
    std::ifstream infile;
    infile.open("wordlist.txt");
    std::cout << infile.is_open();
    if(infile.is_open()) {
        int i = 0;
        while(true) {
            infile >> mystery_word;
            if(i == word_index) {
                break;
            }
            i++;
        }
    }
    return mystery_word;
}

void main_game() {
    std::string the_word = mystery_word();
    int mistakes = 0; // Limit of mistakes: 7
    int the_length = the_word.length();
    std::string temp_word = "";
    for(int i = 0; i < the_length; i++) {
        temp_word += "-";
    }
    bool game_status = true;
    while(game_status) {
        system("cls");
        char letter;
        if(mistakes == 6) {
            game_status = false;
            break;
        }
        std::cout << "The mystery word has " << the_length << " letters.\n";
        std::cout << "Mystery word: " << temp_word << "\n";
        hangman_phase(mistakes);
        std::cout << "Guess a letter: ";
        std::cin >> letter;
        int flag = 0;
        for(int i = 0; i < the_length; i++) {
            if(letter == the_word[i]) {
                temp_word[i] = letter;
                flag++;
            }
        }
        if(flag == 0) {
            mistakes++;
        }
        if(the_word == temp_word) {
            game_status = false;
        }
    }
    if(the_word == temp_word) {
        std::cout << "Great Work!! The mystery word was " << the_word << "\n";
    } else {
        std::cout << "Try again!! The mystery word was " << the_word << "\n";
    }
}

int main() {

    srand(time(NULL));
    bool run_status;

    if((run_status = title_screen()) == true) {
        while(true) {
            main_game();
            char choice;
            do {
                std::cout << "Continue(Y/N): ";
                std::cin >> choice;
            } while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
            if(choice == 'N' || choice == 'n') {
                system("cls");
                break;
            }
        }           
    }

}