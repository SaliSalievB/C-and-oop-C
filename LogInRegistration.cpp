// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
#include <vector>
#include <termios.h>
#include <unistd.h>

// Function to disable echoing characters to the console
void disableEcho() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

// Function to enable echoing characters to the console
void enableEcho() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

int main() {
    std::vector<std::pair<std::string, std::string>> users; // Store usernames and passwords

    int choice;
    bool loggedIn = false;

    do {
        std::cout << "1. Sign in\n";
        std::cout << "2. Log In\n";
        std::cout << "3. Quit\n";
        std::cout << "Enter your choice: ";

        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Register now\n";
                std::cout << "What's your name? ";
                std::string Username;
                std::cin >> Username;

                // Disable echoing characters for password input
                disableEcho();
                std::cout << "Create a password: ";
                std::string Password;
                std::cin >> Password;
                enableEcho(); // Enable echoing characters after password input

                users.push_back(std::make_pair(Username, Password));
                std::cout << "Registration succsessful\n";
                loggedIn = false; // Reset login status after registration
                break;
            }
            case 2: {
                std::cout << "Log In\n";
                std::cout << "What's your name? ";
                std::string Username;
                std::cin >> Username;
                std::cout << "What's your password: ";
                std::string Password;
                std::cin >> Password;
                for (const auto &user : users) {
                    if (user.first == Username && user.second == Password) {
                        std::cout << "Hello, " << Username << "!" << std::endl;
                        loggedIn = true;
                        break;
                    }
                }
                if (!loggedIn) {
                    std::cout << "Invalid username or password.\n";
                }
                break;
            }
            case 3:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }

        // Transition to login window after registration
        if (choice == 1 && !loggedIn) {
            choice = 2;
        }

    } while (choice != 3 && !loggedIn);

    return 0;
}
