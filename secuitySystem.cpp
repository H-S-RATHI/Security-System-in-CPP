#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    int choice;
    string username, password, age;
    
    cout << "\t\t\t---------------Security System--------------" << endl;
    
    while (true) {
        cout << "\t\t\t___________________________________________" << endl;
        cout << "\t\t\t|___________|1. Register        |_________|" << endl;
        cout << "\t\t\t|___________|2. Login           |_________|" << endl;
        cout << "\t\t\t|___________|3. Change Password |_________|" << endl;
        cout << "\t\t\t|___________|4. End Program     |_________|" << endl;
        cout << "\t\t\t-------------------------------------------" << endl << endl;
        
        cout << "\t\t\tEnter your Choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                cout << "\t\t\t___________________________________________" << endl;
                cout << "\t\t\t___________________Register________________" << endl;
                cout << "\t\t\t-------------------------------------------" << endl << endl;
                
                cout << "\t\t\tPlease Enter Your Username: ";
                cin >> username;
                
                cout << "\t\t\tPlease Enter the Password: ";
                cin >> password;
                
                cout << "\t\t\tPlease Enter your Age: ";
                cin >> age;
                
                ofstream file("users.txt", ios::app);
                
                if (file.is_open()) {
                    file << username << "\n";
                    file << password << "\n";
                    file << age << "\n";
                    file.close();
                    
                    cout << "\t\t\tRegistration Successful" << endl << endl;
                } else {
                    cout << "\t\t\tError: Unable to open the file." << endl;
                }
                
                break;
            }
            case 2: {
                cout << "\t\t\t___________________________________________" << endl;
                cout << "\t\t\t____________________Login__________________" << endl;
                cout << "\t\t\t___________________________________________" << endl << endl;
                
                cout << "\t\t\tPlease Enter Your Username: ";
                cin >> username;
                
                cout << "\t\t\tPlease Enter the Password: ";
                cin >> password;
                
                ifstream file("users.txt");
                string line;
                bool loggedIn = false;
                
                if (file.is_open()) {
                    while (getline(file, line)) {
                        if (line == username) {
                            getline(file, line);
                            if (line == password) {
                                loggedIn = true;
                                cout << "\t\t\t---Login Successful---" << endl << endl;
                                cout << "\t\t\tDetails: " << endl;
                                cout << "\t\t\tUsername: " << username << endl;
                                cout << "\t\t\tPassword: " << password << endl;
                                getline(file, line);
                                cout << "\t\t\tAge: " << line << endl;
                                break;
                            }
                        }
                    }
                    
                    file.close();
                    
                    if (!loggedIn) {
                        cout << endl << endl;
                        cout << "\t\t\tIncorrect Credentials" << endl;
                        cout << "\t\t\t-----1. Press 2 to Login-----" << endl;
                        cout << "\t\t\t-----2. Press 3 to change password-----" << endl;
                    }
                } else {
                    cout << "\t\t\tError: Unable to open the file." << endl;
                }
                
                break;
            }
            case 3: {
                cout << "\t\t\t-----------Change Password-----------" << endl;
                cout << "\t\t\tEnter the Username: ";
                cin >> username;
                
                cout << "\t\t\tEnter the old Password: ";
                cin >> password;
                
                cout << "\t\t\tEnter the new Password: ";
                string newPassword;
                cin >> newPassword;
                
                ifstream file("users.txt");
                string line;
               
                if (file.is_open()) {
                    string tempFile = "temp.txt";
                    ofstream temp(tempFile);
                    
                    bool passwordChanged = false;
                    
                    while (getline(file, line)) {
                        if (line == username) {
                            getline(file, line);
                            
                            if (line == password) {
                                temp << username << "\n";
                                temp << newPassword << "\n";
                                getline(file, line); // Skip the old age
                                temp << line << "\n";
                                
                                passwordChanged = true;
                                cout << "\t\t\tPassword Changed Successfully" << endl << endl;
                            } else {
                                temp << username << "\n";
                                temp << line << "\n";
                                getline(file, line); // Skip the old age
                                temp << line << "\n";
                            }
                        } else {
                            temp << line << "\n";
                        }
                    }
                    
                    file.close();
                    temp.close();
                    
                    // Remove the original file and rename the temporary file
                    remove("users.txt");
                    rename(tempFile.c_str(), "users.txt");
                    
                    if (!passwordChanged) {
                        cout << "\t\t\tIncorrect Credentials" << endl;
                    }
                } else {
                    cout << "\t\t\tError: Unable to open the file." << endl;
                }
                
                break;
            }
            case 4: {
                cout << "\t\t\tProgram Ended" << endl;
                return 0;
            }
            default: {
                cout << "\t\t\tInvalid Choice. Please enter a valid option." << endl;
                break;
            }
        }
    }

    return 0;
}