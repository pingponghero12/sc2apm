#include "sc2actions.hpp"
#include <cstdlib>
#include <ctime>

std::vector<sc2action> init_actions() {
    std::vector<sc2action> actions = {
        {"Build SCV",         's', 'S'},
        {"Build Marine",      'a', 'A'},
        {"Build SupplyDepot", 'd', 'D'},
        {"Set Rally",         'r', 'R'},
        {"Select All Army",   'f', 'F'},
        {"Build Overlord",    'o', 'O'},
        {"Spawn Larva",       'q', 'Q'},
        {"Research Upgrade",  'u', 'U'},
    };

    return actions;
}

sc2action get_random_action(const std::vector<sc2action> &actions) {
    int index = rand() % actions.size();
    return actions[index];
}
