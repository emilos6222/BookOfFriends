#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

struct Friend
{
    int id;
    string name;
    string lastName;
    string phoneNum;
    string email;
    string adress;
};

void saveData(fstream &friendsBook, vector<Friend> friendsList, int numberofFriends)
{
    friendsBook << friendsList[numberofFriends].id<<"|";
    friendsBook << friendsList[numberofFriends].name<<"|";
    friendsBook << friendsList[numberofFriends].lastName<<"|";
    friendsBook << friendsList[numberofFriends].phoneNum<<"|";
    friendsBook << friendsList[numberofFriends].email<<"|";
    friendsBook << friendsList[numberofFriends].adress<<"|"<<endl;
}

int addNewFriend(vector<Friend> &friendsList, int numberofFriends, fstream &friendsBook)
{
    string temporaryName;
    string temporaryLastName;

    system("cls");
    cout << "Insert friend's data."<<endl;
    cout << "NAME: ";
    cin >> temporaryName;
    cout << "LAST NAME: ";
    cin >> temporaryLastName;

    for(int i = 0; i < numberofFriends; i++)
    {
        if(friendsList[i].name == temporaryName)
        {
            if(friendsList[i].lastName == temporaryLastName)
            {
                cout << "This friend already exist in your address book.";
                Sleep(2000);
                return numberofFriends;
            }
        }
    }

    cout << "ADRESS: ";
    getchar();
    getline(cin, friendsList[numberofFriends].adress);
    cout << "E-MAIL: ";
    cin >> friendsList[numberofFriends].email;
    cout << "PHONE NUMBER: ";
    cin >> friendsList[numberofFriends].phoneNum;

    friendsList[numberofFriends].name = temporaryName;
    friendsList[numberofFriends].lastName = temporaryLastName;

    if(numberofFriends > 0)
        friendsList[numberofFriends].id = friendsList[numberofFriends-1].id + 1;
    else
        friendsList[numberofFriends].id = numberofFriends + 1;

    cout << "You added new friend.";

    saveData(friendsBook, friendsList, numberofFriends);

    Sleep(2000);
    return friendsList[numberofFriends].id;
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

void changeDataInBookFile(vector<Friend> friendsList, int numberofFriends, fstream &friendsBook)
{
    friendsBook.close();
    remove("ksiazka4.txt");

    friendsBook.open("ksiazka4.txt",ios::out |ios::app |ios::in);

    for(int i = 0; i < numberofFriends; i++)
        saveData(friendsBook, friendsList, i);
}

int deleteFriend(vector<Friend> &friendsList, int numberofFriends, fstream &friendsBook)
{
    int numberIDToEdit;

    system("cls");
    cout << "Insert friend's ID to delete him from the data base: ";
    cin >> numberIDToEdit;

    system("cls");
    for(int i = 0; i < numberofFriends; i++)
    {
        if(friendsList[i].id == numberIDToEdit)
        {
            string decisionToDeleteOrNot;
            cout <<"Are you sure you want delete friend ?"<<endl;
            cout <<"Press 't' to delete. Press any other key to go to main menu: "<<endl;
            cin >> decisionToDeleteOrNot;

            if(decisionToDeleteOrNot == "t")
            {
                friendsList.erase(friendsList.begin()+i);
                numberofFriends--;
                changeDataInBookFile(friendsList, numberofFriends, friendsBook);

                cout << "Friend has been deleted.";
                Sleep(3000);
                return numberofFriends;
            }
            return numberofFriends;
        }
    }
    cout << "Friend with data you gave does not exist in your book.";
    Sleep(3000);

    return numberofFriends;
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

void editFriend(vector<Friend> &friendsList, int numberofFriends, fstream &friendsBook)
{
    int numberIDToEdit;

    system("cls");
    cout << "Insert friend's ID to edit his data: ";
    cin >> numberIDToEdit;

    for(int numberOfFriendInBook = 0; numberOfFriendInBook < numberofFriends; numberOfFriendInBook++)
    {
        if(friendsList[numberOfFriendInBook].id == numberIDToEdit)
        {
            chooseDataToEdit(friendsList, numberOfFriendInBook);
            changeDataInBookFile(friendsList, numberofFriends, friendsBook);

            system("cls");
            cout << "Everything went good.";
            Sleep(3000);
            return;
        }
    }
    cout << "Friend with ID you gave does not exist in your book.";
    Sleep(3000);
}

int writeFriendsData(vector<Friend> &friendsList, int numberofFriends, fstream &friendsBook)
{
    int numberOfFriendsData = 0;
    string lineFromTextFile;
    int numberOfLineFromTextFile = 1;
    string tempPartOfDatas;

    while(getline(friendsBook, lineFromTextFile))
    {
        int charNumberOfSeparator = 0;

        charNumberOfSeparator = lineFromTextFile.find("|");
        tempPartOfDatas.assign(lineFromTextFile, 0, charNumberOfSeparator);
        friendsList[numberOfFriendsData].id = stoi(tempPartOfDatas);
        numberofFriends++;

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
        numberOfLineFromTextFile++;
    }
    return numberofFriends;
}

void showMainMenu(void)
{
    system("cls");
    cout << "1. Insert new friend."<<endl;
    cout << "2. Search a friend."<<endl;
    cout << "3. Show all friends."<<endl;
    cout << "4. Delete a friend."<<endl;
    cout << "5. Edit a friend."<<endl;
    cout << "9. Exit program."<<endl;
    cout << "Choose an option: "<<endl;
}

int main()
{
    int numberTochooseFromMenu = 0;
    int numberofFriends = 0;
    vector<Friend> friendsList(100);

    fstream friendsBook;
    friendsBook.open("ksiazka4.txt",ios::out |ios::app |ios::in);
    if(!friendsBook.good())
    {
        cout << "The file is not exist or something went wrong during opening file";
        exit(0);
    }

    numberofFriends = writeFriendsData(friendsList, numberofFriends, friendsBook);
    friendsBook.close();
    friendsBook.open("ksiazka4.txt",ios::out |ios::app |ios::in);

    showMainMenu();
    while(cin >> numberTochooseFromMenu)
    {
        switch(numberTochooseFromMenu)
        {
        case 1:
            numberofFriends = addNewFriend(friendsList, numberofFriends, friendsBook);
            break;
        case 2:
            searchFriends(friendsList, numberofFriends);
            break;
        case 3:
            showFriends(friendsList, numberofFriends);
            break;
        case 4:
            numberofFriends = deleteFriend(friendsList, numberofFriends, friendsBook);
            break;
        case 5:
            editFriend(friendsList, numberofFriends, friendsBook);
            break;
        case 9:
            system("cls");
            cout << "Goodbye !!!";
            Sleep(2000);
            friendsBook.close();
            return 0;
        default:
            cout << "You insert wrong data. Please do it again."<<endl;
            Sleep(2000);
        }
        showMainMenu();
    }

    friendsBook.close();
    return 0;
}
