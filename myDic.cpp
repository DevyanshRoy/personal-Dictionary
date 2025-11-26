#include <bits/stdc++.h>
using namespace std;

struct WordNode 
{
    string word;
    string meaning;
    WordNode* next;
};

struct FileNode
{
    string filename;
    WordNode* words;  
    FileNode* next;
};

FileNode* fileHead = nullptr;

string getFile(char ch) 
{
    ch = tolower(ch);
    string file = "";
    file += ch;     
    file += ".txt"; 
    return file;
}

void createFileList()
{
    FileNode* prev = nullptr;
    for(char c = 'a'; c <= 'z'; c++)
    {
        FileNode* newFile = new FileNode();
        newFile->filename = getFile(c);
        newFile->words = nullptr;
        newFile->next = nullptr;

        if(fileHead == nullptr) fileHead = newFile;
        else prev->next = newFile;

        prev = newFile;
    }
}

void loadFiles() 
{
    FileNode* f = fileHead;
    while(f != nullptr)
    {
        ifstream in(f->filename);
        if(!in) { f = f->next; continue; }

        string line;
        WordNode* headWords = nullptr;
        while(getline(in, line))
        {
            int pos = line.find(" - ");
            if(pos == -1) continue;
            string w = line.substr(0, pos);
            string m = line.substr(pos + 3); 
            WordNode* newNode = new WordNode();
            newNode->word = w;
            newNode->meaning = m;
            newNode->next = headWords;
            headWords = newNode;
        }
        f->words = headWords;
        in.close();
        f = f->next;
    }
}

void addWord() 
{
    string w, m;
    cout << "Enter word: ";
    cin >> w;
    cout << "Enter meaning: ";
    cin.ignore();
    getline(cin, m);
    string file = getFile(w[0]);
    FileNode* f = fileHead;
    while(f != nullptr)
    {
        if(f->filename == file)
            break;
        f = f->next;
    }
    WordNode* newNode = new WordNode();
    newNode->word = w;
    newNode->meaning = m;
    newNode->next = f->words;
    f->words = newNode;
    ofstream out(file, ios::app);
    out << w << " - " << m << endl;
    out.close();
    cout << "Word added successfully!" << endl;
}

void searchWord() 
{
    string w;
    cout << "Enter word to search: ";
    cin >> w;
    FileNode* f = fileHead;
    while(f != nullptr)
    {
        WordNode* temp = f->words;
        while(temp != nullptr)
        {
            if(temp->word == w)
            {
                cout << "Meaning: " << temp->meaning << endl;
                return;
            }
            temp = temp->next;
        }
        f = f->next;
    }

    cout << "Word not found!" << endl;
}

// Delete a word
void deleteWord() 
{
    string w;
    cout << "Enter word to delete: ";
    cin >> w;
    string file = getFile(w[0]);
    FileNode* f = fileHead;
    while(f != nullptr)
    {
        if(f->filename == file) break;
        f = f->next;
    }
    if(!f) return;
    WordNode* temp = f->words;
    WordNode* prev = nullptr;
    bool found = false;
    while(temp != nullptr)
    {
        if(temp->word == w)
        {
            found = true;
            if(prev == nullptr) f->words = temp->next;
            else prev->next = temp->next;
            delete temp;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    if(!found)
    {
        cout << "Word not found!" << endl;
        return;
    }
    ifstream in(file);
    ofstream tempFile("temp.txt");
    string line;
    while(getline(in, line))
    {
        int pos = line.find(" - ");
        string wordInFile = line.substr(0, pos);
        if(wordInFile != w) tempFile << line << endl;
    }
    in.close();
    tempFile.close();
    remove(file.c_str());
    rename("temp.txt", file.c_str());

    cout << "Word deleted!" << endl;
}

void showWordsByLetter()
{
    char c;
    cout << "Enter starting letter: ";
    cin >> c;
    string file = getFile(c);
    FileNode* f = fileHead;
    while(f != nullptr)
    {
        if(f->filename == file) break;
        f = f->next;
    }
    if(!f || !f->words) { cout << "No words found." << endl; return; }
    WordNode* temp = f->words;
    while(temp != nullptr)
    {
        cout << temp->word << " - " << temp->meaning << endl;
        temp = temp->next;
    }
}

void showAllWords() 
{
    FileNode* f = fileHead;
    bool any = false;
    while(f != nullptr)
    {
        WordNode* temp = f->words;
        while(temp != nullptr)
        {
            cout << temp->word << " - " << temp->meaning << endl;
            temp = temp->next;
            any = true;
        }
        f = f->next;
    }
    if(!any) cout << "No words found." << endl;
}

int main() 
{
    createFileList();
    loadFiles();
    int choice;
    while(true)
    {
        cout << "+-+-+-+-+DICTIONARY MENU+-+-+-+-+" << endl;
        cout << "1. Add a word" << endl;
        cout << "2. Search a word" << endl;
        cout << "3. Delete a word" << endl;
        cout << "4. Show words starting from a letter" << endl;
        cout << "5. Show all words" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice)
        {
            case 1: addWord(); 
            break;
            case 2: searchWord(); 
            break;
            case 3: deleteWord(); 
            break;
            case 4: showWordsByLetter(); 
            break;
            case 5: showAllWords(); 
            break;
            case 6: cout << "Exiting program..." << endl; 
            return 0;
            default: cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
