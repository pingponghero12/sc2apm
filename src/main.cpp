#include <ncurses.h>
#include <csignal>
#include <ctime>
#include <vector>
#include <string>
#include <chrono>
#include "sc2actions.hpp"
#include <iostream>

bool exit_signal = false;

void signal_handler(int signum) {
    if (signum == SIGINT) {
        exit_signal = true;
    }
}

int main() {
    signal(SIGINT, signal_handler);
    srand(static_cast<unsigned>(time(nullptr)));

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, false);
    curs_set(0);

    std::vector<sc2action> actions = init_actions();

    int hits = 0;

    // Thanks god we have auto
    const auto start_time = std::chrono::steady_clock::now();

    while (!exit_signal) {
        clear();
        mvprintw(0, 0, "WELCOM TO SC2 APM TRAINING BUAHAHAHAHA");
        mvprintw(1, 0, "HITS: %d", hits);

        sc2action action = get_random_action(actions);
        mvprintw(3, 0, "ACTION: %s", action.desc.c_str());
        mvprintw(4, 0, "HOTKEY: %c", action.display_key);

        refresh();
        int input = getch();

        if (input == ':') {
            int look_exit = getch();
            if (look_exit == 'q') {
                exit_signal = true;
                break;
            }
        }

        if (input == action.key) {
            hits++;
        }
    }

    const auto end_time = std::chrono::steady_clock::now();
    const std::chrono::duration<double> total_time = end_time - start_time;
    const double total_time_sec = total_time.count();
    const double total_time_min = total_time_sec / 60;


    const int apm = static_cast<int>(hits / total_time_min);

    endwin();

    std::cout << "SC2 APM Training Summary" << std::endl;
    std::cout << "APM: " << apm << std::endl;
    std::cout << "Time: " << total_time_sec << " sec" << std::endl;
    std::cout << std::endl;

    return 0;
}

