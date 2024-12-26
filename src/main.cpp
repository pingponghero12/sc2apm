#include <ncurses.h>
#include <csignal>
#include <ctime>
#include <vector>
#include <string>
#include <chrono>
#include "sc2actions.hpp"
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

std::atomic<bool> exit_signal(false);
std::atomic<int> hits(0);
std::mutex action_mutex;

void signal_handler(int signum) {
    if (signum == SIGINT) {
        exit_signal = true;
    }
}

void animate(const sc2action& action, std::chrono::steady_clock::time_point start_time) {
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);

    const std::vector<std::vector<std::string>> fire_frames = {
        {
            "    #   #   #    #  ## ",
            "   ##  # #  ##  # ### #",
            "   ### # #  ## # ### ##",
            "    #### ## ### ### ####",
            "    ###################",
            "    #                 #",
            "    #     APM: %d     #",
            "    #                 #",
            "    ###################"
        },
        {
            "   #  # #  # # # #  ## ",
            "   ##  ## ## ## ### # #",
            "   # ## #  ## # ### ### ",
            " #  ##### ### # ### ####",
            " ## #################### #",
            "    #                 #",
            "    #     APM: %d     # #",
            "   ##                 #",
            "    ###################"
        },
        {
            " ##  # # #    #   #  # #",
            "   ##  ## ## ## ###  ###",
            "   # ## #  ## # # # ### #",
            " #  ## # #### # ##### ## #",
            " ## #################### #",
            "   ##                 ###",
            "   ##     APM: %d     #",
            "   ##                 ##",
            "    ###################"
        }
    };

    int frame_id = 0;
    int counter = 0;
    while (!exit_signal) {
        int hits_local = hits.load();

        const auto end_time = std::chrono::steady_clock::now();
        const std::chrono::duration<double> total_time = end_time - start_time;
        const double total_time_sec = total_time.count();
        const double total_time_min = total_time_sec / 60;


        const int apm = static_cast<int>(hits_local / total_time_min);

        clear();


        for (int i = 0; i < (int)fire_frames[frame_id].size(); ++i) {
            if (i % 2 == 0) {
                attron(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));
            }
            mvprintw(i + 5, 0, fire_frames[frame_id][i].c_str(), apm);
            if (i % 2 == 0) {
                attroff(COLOR_PAIR(1));
            } else {
                attroff(COLOR_PAIR(2));
            }
        }

        attron(COLOR_PAIR(3));
        mvprintw(0, 0, "WELCOM TO SC2 APM TRAINING BUAHAHAHAHA");
        attroff(COLOR_PAIR(3));

        action_mutex.lock();
        mvprintw((int)fire_frames[frame_id].size() + 10, 0, "ACTION: %s", action.desc.c_str());
        mvprintw((int)fire_frames[frame_id].size() + 11, 0, "HOTKEY: %c", action.display_key);
        action_mutex.unlock();

        refresh();

        if (counter == 10) {
            frame_id = (frame_id + 1) % (int)fire_frames.size();
            counter = 0;
        }
        else counter++;

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
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

    sc2action action = get_random_action(actions);

    const auto start_time = std::chrono::steady_clock::now();
    std::thread animation_thread(animate, std::ref(action), start_time);
    // Thanks god we have auto

    while (!exit_signal) {
        int input = getch();

        if (input == ':') {
            int look_exit = getch();
            if (look_exit == 'q') {
                exit_signal = true;
                break;
            }
        }

        // read-read is no problemo
        if (input == action.key) {
            hits++;

            action_mutex.lock();
            action = get_random_action(actions);
            action_mutex.unlock();
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

