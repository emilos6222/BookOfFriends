#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <cstdio>

using namespace std;

struct userData
{
    int userID;
    string userLogin;
    string userPassword;
};

struct Friend
{
    int id;
    string name;
    string lastName;
    string phoneNum;
    string email;
    string adress;
};

int chooseLoggingMenu(void)
{
    int choice;
    system("cls");

    cout << "1. Registration" << endl;
    cout << "2. Logging in" << endl;
    cout << "3. Exit" << endl << endl;
    cout << "Your choice: ";
    cin >> choice;
    return choice;
}

void insertUserData(string &login, string &password)
{

    cout << "Insert login: ";
    cin >> login;
    cout << "Insert password: ";
    cin >> password;
}

void showMainMenu(void)
{
    system("cls");
    cout << "1. Insert new friend."<<endl;
    cout << "2. Search a friend."<<endl;
    cout << "3. Show all friends."<<endl;
    cout << "4. Delete a friend."<<endl;
    cout << "5. Edit a friend."<<endl;
    cout << "----------------------"<< endl;
    cout << "6. Change password."<<endl;
    cout << "7. Logout."<<endl;
    cout << "----------------------"<<endl;
    cout << endl << "Choose an option: ";
}

void changePassword(vector<userData> &userList, fstream &bookOfUsers, int userID)
{
    string newPassword;
    fstream tempBookOfUser;

    system("cls");
    cout << "Insert new password: ";
    cin >> newPassword;

    tempBookOfUser.open("TemporaryUser.txt", ios::out |ios::app |ios::in);

    for(vector<userData>::iterator i = userList.begin(); i < userList.end(); i++)
    {
        if(userID == i->userID)
            i->userPassword = newPassword;

        tempBookOfUser<< i->userID <<"|"<< i->userLogin <<"|"<< i->userPassword <<"|"<<endl;
    }

    tempBookOfUser.close();
    remove("Users.txt");
    rename( "TemporaryUser.txt", "Users.txt" );

    system("cls");
    cout << "You have changed your password.";
    Sleep(2000);
}

bool isAnyFriendInBook(int numberofFriends)
{
    if(numberofFriends == 0)
    {
        system("cls");
        cout << "Your friends book is empty. Please insert some data first."<<endl;
        Sleep(5000);
        return true;
    }
    return false;
}

void showFriendsData(vector<Friend> friendsList, int numberofFriends)
{
    cout << friendsList[numberofFriends].id<<endl;
    cout << friendsList[numberofFriends].name<<" "<<friendsList[numberofFriends].lastName<<endl;
    cout << friendsList[numberofFriends].adress<<endl;
    cout << friendsList[numberofFriends].phoneNum<<endl;
    cout << friendsList[numberofFriends].email<<endl;
}

void showFriends(vector<Friend> friendsList, int numberofFriends)
{

    if(isAnyFriendInBook(numberofFriends) == true)
        return;

    system("cls");
    cout << "Your friends in your address book:"<<endl;

    for(int i = 0; i<numberofFriends;i++)
    {   cout << endl;
        showFriendsData(friendsList, i);
    }

    cout <<endl <<"Press a button to back to main menu";
    getchar();
    getchar();
}

void searchFriends(vector<Friend> friendsList, int numberofFriends)
{
    if(isAnyFriendInBook(numberofFriends) == true)
        return;

    int numberToChooseFromNameorLastName = 0;
    int numberToCheckIsFriendExist = 0;
    string wordToFindFromNameOrLastName;

    system("cls");
    cout << "1. Searching friends by name."<<endl;
    cout << "2. Searching friends by last name."<<endl;
    cout << "Choose an option: ";
    cin >> numberToChooseFromNameorLastName;
    system("cls");

    if(numberToChooseFromNameorLastName == 1)
    {
        cout<<"Please insert a name: ";
        cin >> wordToFindFromNameOrLastName;

        for(int i = 0; i < numberofFriends; i++)
        {
            if(wordToFindFromNameOrLastName == friendsList[i].name)
            {
                numberToCheckIsFriendExist = friendsList[i].id;
                showFriendsData(friendsList, i);
            }
        }

        if(numberToCheckIsFriendExist == 0)
        {
            cout << "Friend does not exist in your book"<<endl;
            Sleep(3000);
        }
    }
    else if(numberToChooseFromNameorLastName == 2)
    {
        cout<<"Please insert a last name: ";
        cin >> wordToFindFromNameOrLastName;

        for(int i = 0; i < numberofFriends; i++)
        {
            if(wordToFindFromNameOrLastName == friendsList[i].lastName)
            {
                numberToCheckIsFriendExist = friendsList[i].id;
                showFriendsData(friendsList, i);
            }
        }

        if(numberToCheckIsFriendExist == 0)
        {
            cout << "Friend does not exist in your book"<<endl;
            Sleep(3000);
        }
    }

    else
        cout << "You gave a wrong data"<<endl;

    cout <<endl <<"Press a button to back to main menu";
    getchar();getchar();

}

int writeFriendsData(vector<Friend> &friendsList, int userID, fstream &friendsBook, int &lastFriendID)
{
    int numberOfFriendsData = 0;
    int numberofFriends = 0;
    string lineFromTextFile;
    string tempPartOfDatas;
    string userIdToCompare;
    string dataToCheckLastID;

    while(getline(friendsBook, lineFromTextFile))
    {
        int charNumberOfSeparator = 0;

        charNumberOfSeparator = lineFromTextFile.find("|");
        dataToCheckLastID.assign(lineFromTextFile, 0, charNumberOfSeparator);
        lastFriendID = stoi(dataToCheckLastID);
        tempPartOfDatas.assign(lineFromTextFile, charNumberOfSeparator+1, lineFromTextFile.size()-1);
        charNumberOfSeparator = lineFromTextFile.find("|");
        tempPartOfDatas.assign(tempPartOfDatas, 0, charNumberOfSeparator);
        userIdToCompare = tempPartOfDatas;

        if(stoi(userIdToCompare) == userID)
        {
            charNumberOfSeparator = 0;

            charNumberOfSeparator = lineFromTextFile.find("|");
            tempPartOfDatas.assign(lineFromTextFile, 0, charNumberOfSeparator);
            friendsList[numberOfFriendsData].id = stoi(tempPartOfDatas);
            numberofFriends++;

            lineFromTextFile.assign(lineFromTextFile, charNumberOfSeparator+1, lineFromTextFile.size()-1);
            charNumberOfSeparator = lineFromTextFile.find("|");

            lineFromTextFile.assign(lineFromTextFile, charNumberOfSeparator+1, lineFromTextFile.size()-1);
            charNumberOfSeparator = lineFromTextFile.find("|");
            tempPartOfDatas.assign(lineFromTextFile, 0, charNumberOfSeparator);
            friendsList[numberOfFriendsData].name = tempPartOfDatas;

            lineFromTextFile.assign(lineFromTextFile, charNumberOfSeparator+1, lineFromTextFile.size()-1);
            charNumberOfSeparator = lineFromTextFile.find("|");
            tempPartOfDatas.assign(lineFromTextFile, 0, charNumberOfSeparator);
            friendsList[numberOfFriendsData].lastName = tempPartOfDatas;

            lineFromTextFile.assign(lineFromTextFile, charNumberOfSeparator+1, lineFromTextFile.size()-1);
            charNumberOfSeparator = lineFromTextFile.find("|");
            tempPartOfDatas.assign(lineFromTextFile, 0, charNumberOfSeparator);
            friendsList[numberOfFriendsData].phoneNum = tempPartOfDatas;

            lineFromTextFile.assign(lineFromTextFile, charNumberOfSeparator+1, lineFromTextFile.size()-1);
            charNumberOfSeparator = lineFromTextFile.find("|");
            tempPartOfDatas.assign(lineFromTextFile, 0, charNumberOfSeparator);
            friendsList[numberOfFriendsData].email = tempPartOfDatas;

            lineFromTextFile.assign(lineFromTextFile, charNumberOfSeparator+1, lineFromTextFile.size()-1);
            charNumberOfSeparator = lineFromTextFile.find("|");
            tempPartOfDatas.assign(lineFromTextFile, 0, charNumberOfSeparator);
            friendsList[numberOfFriendsData].adress = tempPartOfDatas;

            numberOfFriendsData++;
        }
    }
    return numberofFriends;
}

void saveData(fstream &friendsBook, vector<Friend> friendsList, int *numOfFriendsAndLastIDAndUserID)
{
    friendsBook << friendsList[numOfFriendsAndLastIDAndUserID[0]].id<<"|";
    friendsBook << numOfFriendsAndLastIDAndUserID[2]<<"|";
    friendsBook << friendsList[numOfFriendsAndLastIDAndUserID[0]].name<<"|";
    friendsBook << friendsList[numOfFriendsAndLastIDAndUserID[0]].lastName<<"|";
    friendsBook << friendsList[numOfFriendsAndLastIDAndUserID[0]].phoneNum<<"|";
    friendsBook << friendsList[numOfFriendsAndLastIDAndUserID[0]].email<<"|";
    friendsBook << friendsList[numOfFriendsAndLastIDAndUserID[0]].adress<<"|"<<endl;
}

void addNewFriend(vector<Friend> &friendsList, int *numOfFriendsAndLastIDAndUserID, fstream &friendsBook)
{
    string temporaryName;
    string temporaryLastName;


    system("cls");
    cout << "Insert friend's data."<<endl;
    cout << "NAME: ";
    cin >> temporaryName;
    cout << "LAST NAME: ";
    cin >> temporaryLastName;
    cout << "ADRESS: ";
    getchar();
    getline(cin, friendsList[numOfFriendsAndLastIDAndUserID[0]].adress);
    cout << "E-MAIL: ";
    cin >> friendsList[numOfFriendsAndLastIDAndUserID[0]].email;
    cout << "PHONE NUMBER: ";
    cin >> friendsList[numOfFriendsAndLastIDAndUserID[0]].phoneNum;


    friendsList[numOfFriendsAndLastIDAndUserID[0]].name = temporaryName;
    friendsList[numOfFriendsAndLastIDAndUserID[0]].lastName = temporaryLastName;

        friendsList[numOfFriendsAndLastIDAndUserID[0]].id = ++numOfFriendsAndLastIDAndUserID[1];

    cout << "You added new friend.";

    saveData(friendsBook, friendsList, numOfFriendsAndLastIDAndUserID);

    Sleep(2000);
    numOfFriendsAndLastIDAndUserID[0]++;
}

int changeDataInBookFile(int numberIDToDelete, int *numOfFriendsAndLastIDAndUserID, fstream &friendsBook)
{
    string lineOfText;
    string IdInFile;
    int lastIdInFile = 0;
    int separatorPosition = 0;

    fstream tempTextFile;
    friendsBook.close();
    friendsBook.open("Friends.txt",ios::out | ios::app | ios::in);
    tempTextFile.open("temporaryBook.txt",ios::out | ios::app | ios::in);

    while(getline(friendsBook, lineOfText))
    {
        separatorPosition = lineOfText.find("|");
        IdInFile.assign(lineOfText, 0, separatorPosition);

        if(numberIDToDelete != stoi(IdInFile))
        {
            tempTextFile<<lineOfText<<endl;
            lastIdInFile = stoi(IdInFile);
        }
    }

    friendsBook.close();
    tempTextFile.close();

    remove("Friends.txt");
    rename("temporaryBook.txt", "Friends.txt");

    friendsBook.open("Friends.txt",ios::out |ios::app |ios::in);

    return lastIdInFile;
}

void deleteFriend(vector<Friend> &friendsList, int *numOfFriendsAndLastIDAndUserID, fstream &friendsBook)
{
    int numberIDToDelete;

    system("cls");
    cout << "Insert friend's ID to delete him from the data base: ";
    cin >> numberIDToDelete;

    system("cls");
    for(int i = 0; i < numOfFriendsAndLastIDAndUserID[0]; i++)
    {
        if(friendsList[i].id == numberIDToDelete)
        {
            string decisionToDeleteOrNot;
            cout <<"Are you sure you want delete friend ?"<<endl;
            cout <<"Press 't' to delete. Press any other key to go to main menu: "<<endl;
            cin >> decisionToDeleteOrNot;

            if(decisionToDeleteOrNot == "t")
            {
                numOfFriendsAndLastIDAndUserID[1] = changeDataInBookFile(numberIDToDelete, numOfFriendsAndLastIDAndUserID, friendsBook);
                friendsList.erase(friendsList.begin()+i);
                numOfFriendsAndLastIDAndUserID[0]--;

                cout << "Friend has been deleted.";
                Sleep(3000);
                return;
            }
            return;
        }
    }

    cout << "Friend with data you gave does not exist in your book.";
    Sleep(3000);
}

void chooseDataToEdit(vector<Friend> &friendsList,int numberOfFriendInBook)
{
    int chooseKindOfData;
    string changedData;

    system("cls");
    cout << "Choose number."<<endl;
    cout << "1 - change first name"<<endl;
    cout << "2 - change last name"<<endl;
    cout << "3 - change phone number"<<endl;
    cout << "4 - change email"<<endl;
    cout << "5 - change adress"<<endl;
    cout << "6 - back to main menu"<<endl;
    cout << endl << "Your choice: ";

    cin >> chooseKindOfData;

    system("cls");
    cout << "Insert data to change: ";
    getchar();
    getline(cin, changedData);

    switch(chooseKindOfData)
    {
    case 1:
        friendsList[numberOfFriendInBook].name = changedData;
        break;
    case 2:
        friendsList[numberOfFriendInBook].lastName = changedData;
        break;
    case 3:
        friendsList[numberOfFriendInBook].phoneNum = changedData;
        break;
    case 4:
        friendsList[numberOfFriendInBook].email = changedData;
        break;
    case 5:
        friendsList[numberOfFriendInBook].adress = changedData;
        break;
    case 6:
        return;
        break;
    default:
        cout << "You put wrong data or something went wrong"<<endl;
        Sleep(3000);
        return;
    }

}

void editOneDataInBookFile(vector<Friend> &friendsList, int *numOfFriendsAndLastIDAndUserID, fstream &friendsBook, int numberIDToEdit)
{
    string lineOfText;
    string IdInFile;
    int separatorPosition = 0;
    int lineNumToEditInVector = 0;

    fstream tempTextFile;
    friendsBook.close();
    friendsBook.open("Friends.txt",ios::out | ios::app | ios::in);
    tempTextFile.open("temporaryBook.txt",ios::out | ios::app | ios::in);

    while(getline(friendsBook, lineOfText))
    {
        separatorPosition = lineOfText.find("|");
        IdInFile.assign(lineOfText, 0, separatorPosition);

        if(numberIDToEdit != stoi(IdInFile))
        {
            tempTextFile<<lineOfText<<endl;
        }
        else
        {
            for(vector<Friend>::iterator i = friendsList.begin(); i < friendsList.end(); i++)
            {
                if(numberIDToEdit != (i -> id))
                {
                    lineNumToEditInVector++;
                }
                else
                    break;
            }

            tempTextFile << friendsList[lineNumToEditInVector].id<<"|";
            tempTextFile << numOfFriendsAndLastIDAndUserID[2]<<"|";
            tempTextFile << friendsList[lineNumToEditInVector].name<<"|";
            tempTextFile << friendsList[lineNumToEditInVector].lastName<<"|";
            tempTextFile << friendsList[lineNumToEditInVector].phoneNum<<"|";
            tempTextFile << friendsList[lineNumToEditInVector].email<<"|";
            tempTextFile << friendsList[lineNumToEditInVector].adress<<"|"<<endl;
        }
    }

    friendsBook.close();
    tempTextFile.close();

    remove("Friends.txt");
    rename("temporaryBook.txt", "Friends.txt");

    friendsBook.open("Friends.txt",ios::out |ios::app |ios::in);

}

void editFriend(vector<Friend> &friendsList, int *numOfFriendsAndLastIDAndUserID, fstream &friendsBook)
{
    int numberIDToEdit;

    system("cls");
    cout << "Insert friend's ID to edit his data: ";
    cin >> numberIDToEdit;

    for(int numberOfFriendInBook = 0; numberOfFriendInBook < numOfFriendsAndLastIDAndUserID[0]; numberOfFriendInBook++)
    {
        if(friendsList[numberOfFriendInBook].id == numberIDToEdit)
        {
            chooseDataToEdit(friendsList, numberOfFriendInBook);
            editOneDataInBookFile(friendsList, numOfFriendsAndLastIDAndUserID, friendsBook, numberIDToEdit);

            system("cls");
            cout << "Everything went good.";
            Sleep(3000);
            return;
        }
    }
    cout << "Friend with ID you gave does not exist in your book.";
    Sleep(3000);
}

void operateOnFriendsData(vector<userData> &userList, fstream &bookOfUsers, int userID)
{
    int numberTochooseFromMenu = 0;
    int numberofFriends = 0;
    int lastFriendID = 0;
    int numOfFriendsAndLastIDAndUserID[3];
    vector<Friend> friendsList(100);

    fstream friendsBook;
    friendsBook.open("Friends.txt",ios::out |ios::app |ios::in);
    if(!friendsBook.good())
    {
        cout << "The file is not exist or something went wrong during opening file";
        exit(0);
    }

    numberofFriends = writeFriendsData(friendsList, userID, friendsBook, lastFriendID);
    numOfFriendsAndLastIDAndUserID[0] = numberofFriends;
    numOfFriendsAndLastIDAndUserID[1] = lastFriendID;
    numOfFriendsAndLastIDAndUserID[2] = userID;
    friendsBook.close();
    friendsBook.open("Friends.txt",ios::out |ios::app |ios::in);

    showMainMenu();
    while(cin >> numberTochooseFromMenu)
    {
        switch(numberTochooseFromMenu)
        {
        case 1:
            addNewFriend(friendsList, numOfFriendsAndLastIDAndUserID, friendsBook);
            break;
        case 2:
            searchFriends(friendsList, numOfFriendsAndLastIDAndUserID[0]);
            break;
        case 3:
            showFriends(friendsList, numOfFriendsAndLastIDAndUserID[0]);
            break;
        case 4:
            deleteFriend(friendsList, numOfFriendsAndLastIDAndUserID, friendsBook);
            break;
        case 5:
            editFriend(friendsList, numOfFriendsAndLastIDAndUserID, friendsBook);
            break;
        case 6:
            changePassword(userList, bookOfUsers, userID);
            break;
        case 7:
            friendsBook.close();
            system("cls");
            cout << "You have been logged out.";
            Sleep(2000);
            return;
        default:
            cout << "You insert wrong data. Please do it again."<<endl;
            Sleep(2000);
        }
        showMainMenu();
    }

    friendsBook.close();
    return;
}

void logInUser(vector<userData> &userList, fstream &bookOfUsers)
{
    string login, password;

    system("cls");
    insertUserData(login, password);
    for(vector<userData>::iterator i = userList.begin(); i < userList.end(); i++)
    {
        if(login == (i -> userLogin) && password == (i -> userPassword))
        {
            operateOnFriendsData(userList, bookOfUsers, i->userID);
            return;
        }
    }

    system("cls");
    cout << "Invalid login or password." << endl;
    Sleep(2000);
    return;
}

int registerUser(vector <userData> &userList ,fstream &bookOfUsers, int numberOfUsers)
{
    string login, password;
    string sign;
    userData lastUserInList;

    system("cls");
    insertUserData(login, password);

    for(vector<userData>::iterator i = userList.begin(); i < userList.end(); i++)
    {
        if(login == (i -> userLogin))
        {
            cout << "This user already exist." << endl;
            Sleep(2000);
            return numberOfUsers;
        }
    }

    bookOfUsers.open("Users.txt",ios::out | ios::app | ios::in);
    if(!bookOfUsers.good())
    {
        cout << "Something went wrong during opening file!!!";
        exit(0);
    }

    if(userList.size() == 0)
    {
        lastUserInList.userID = 1;
    }

    else{
        lastUserInList = userList.back();
        lastUserInList.userID++;
    }

    lastUserInList.userLogin = login;
    lastUserInList.userPassword = password;
    userList.push_back(lastUserInList);

    bookOfUsers<<lastUserInList.userID<<"|"<<lastUserInList.userLogin<<"|"<<lastUserInList.userPassword<<"|"<<endl;

    bookOfUsers.close();
    system("cls");
    cout << "You have been registered.";
    Sleep(2000);
    return ++numberOfUsers;
}

int loadUserData(vector <userData> &userList ,fstream &bookOfUsers)
{
    int numberOfUsers = 0;
    string lineOfText;
    string tempPartOfDatas;
    userData tempUser;

    while(getline(bookOfUsers, lineOfText))
    {

        int positionOfSeparator = 0;

        positionOfSeparator = lineOfText.find("|");
        tempPartOfDatas.assign(lineOfText, 0, positionOfSeparator);
        tempUser.userID = stoi(tempPartOfDatas);
        numberOfUsers++;

        lineOfText.assign(lineOfText, positionOfSeparator+1, lineOfText.size()-1);
        positionOfSeparator = lineOfText.find("|");
        tempPartOfDatas.assign(lineOfText, 0, positionOfSeparator);
        tempUser.userLogin = tempPartOfDatas;

        lineOfText.assign(lineOfText, positionOfSeparator+1, lineOfText.size()-1);
        positionOfSeparator = lineOfText.find("|");
        tempPartOfDatas.assign(lineOfText, 0, positionOfSeparator);
        tempUser.userPassword = tempPartOfDatas;

        userList.push_back(tempUser);
    }
    return numberOfUsers;
}

int main()
{

    int choiceOfLogging;
    int numberOfUsers;
    vector<userData> userList;

    fstream bookOfUsers;
    bookOfUsers.open("Users.txt",ios::out |ios::app |ios::in);
    if(!bookOfUsers.good())
    {
        cout << "Something went wrong during opening file";
        exit(0);
    }

    numberOfUsers = loadUserData(userList, bookOfUsers);
    bookOfUsers.close();

    while((choiceOfLogging = chooseLoggingMenu()))
    {
        switch(choiceOfLogging)
        {
        case 1:
            numberOfUsers = registerUser(userList, bookOfUsers, numberOfUsers);
            break;
        case 2:
            logInUser(userList, bookOfUsers);
            break;
        case 3:
            system("cls");
            cout << "Goodbye !!!";
            Sleep(2000);
            return 0;
        default:
            cout << "You insert wrong data. Please do it again."<<endl;
            Sleep(2000);
        }
    }

    return 0;
}
