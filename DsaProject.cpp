1#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

struct Song {
    string title;
    string artist;
    Song* next;
};

// para sa end ig add sa song
void addSong(Song*& head, string title, string artist) {
    Song* newSong = new Song{title, artist, nullptr};

    if (!head) {
        head = newSong;
        return;
    }

    Song* temp = head;
    while (temp->next != nullptr) temp = temp->next;
    temp->next = newSong;
}

// para na display 
void displayPlaylist(Song* head) {
    if (!head) {
        cout << "Playlist is empty.\n";
        return;
    }

    cout << "\n--- PLAYLIST ---\n";
    Song* temp = head;
    int num = 1;
    while (temp != nullptr) {
        cout << num++ << ". " << temp->title << " - " << temp->artist << endl;
        temp = temp->next;
    }
    cout << "-----------------\n";
}

// this part is where to find song in playlist
Song* findSong(Song* head, string title) {
    Song* temp = head;
    while (temp != nullptr) {
        if (temp->title == title) return temp;
        temp = temp->next;
    }
    return nullptr;
}


int main() {
    Song* playlist = nullptr;
    queue<Song*> playQueue;
    stack<Song*> history;

    Song* currentSong = nullptr;
    int choice;
    string title, artist;

 do {

    cout << "                                                                    \n";
    cout << "                                                                    \n";
    cout << "██▄  ▄██ ▄▄ ▄▄  ▄▄▄▄ ▄▄  ▄▄▄▄   ▄▄▄▄  ▄▄     ▄▄▄  ▄▄ ▄▄ ▄▄▄▄▄ ▄▄▄▄  \n";
    cout << "██ ▀▀ ██ ██ ██ ███▄▄ ██ ██▀▀▀   ██▄█▀ ██    ██▀██ ▀███▀ ██▄▄  ██▄█▄ \n";
    cout << "██    ██ ▀███▀ ▄▄██▀ ██ ▀████   ██    ██▄▄▄ ██▀██   █   ██▄▄▄ ██ ██ \n";
    cout << "                                                                    \n";
    cout << "                                                                    \n";

    cout << "♪ =================== ♪  PLAYLIST MANAGER MENU ♪ ==================== ♪ \n";

    cout << "[1.] Add Song to Playlist\n";
    cout << "[2.] Display Playlist\n";
    cout << "[3.] Add Song to Queue\n";
    cout << "[4.] Play Next Song\n";
    cout << "[5.] Previous Song\n";
    cout << "[6.] Show Current Song\n";
    cout << "[7.] Exit\n";
    cout << "Select an option: ";

    // FIXED INPUT HANDLING
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\n[Choose from choices only!]\n\n";
        continue;   // go back to menu
    }
    cin.ignore(1000, '\n');

    switch (choice) {
        case 1: {
            cout << "Enter song title ♬ : ";
            getline(cin, title);
            cout << "Enter artist ♬ : ";
            getline(cin, artist);
            addSong(playlist, title, artist);
            cout << "♪ SONG SUCCESSFULLY ADDED! ♪\n";
            break;
        }
        case 2:
            displayPlaylist(playlist);
            break;
        case 3: {
            cout << "♬ Enter song title to queue: ";
            getline(cin, title);

            Song* s = findSong(playlist, title);
            if (s) {
                playQueue.push(s);
                cout << s->title << " added to queue.\n";
            } else {
                cout << "[Song not found!]\n";
            }
            break;
        }
        case 4: {
            if (playQueue.empty()) {
                cout << "[Queue is empty]\n";
            } else {
                if (currentSong) history.push(currentSong);
                currentSong = playQueue.front();
                playQueue.pop();
                cout << "Now playing: " << currentSong->title << " ♬\n";
            }
            break;
        }
        case 5: {
            if (history.empty()) {
                cout << "[No previous song]\n";
            } else {
                playQueue.push(currentSong);
                currentSong = history.top();
                history.pop();
                cout << "Previous: " << currentSong->title << " ♬\n";
            }
            break;
        }
        case 6:
            if (currentSong)
                cout << "Current: " << currentSong->title << " - " << currentSong->artist << endl;
            else
                cout << "[No song playing]\n";
            break;

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "[Invalid choice!]\n";
    }

} while (choice != 7);
}
