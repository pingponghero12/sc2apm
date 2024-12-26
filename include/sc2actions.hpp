#ifndef __SC2ACTIONS__
#define __SC2ACTIONS__

#include <vector>
#include <string>

struct sc2action {
    std::string desc;
    int key;
    char display_key;
};

std::vector<sc2action> init_actions();
sc2action get_random_action(const std::vector<sc2action> &actions);

#endif // __SC2ACTIONS__
