#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <string>
#include <cstdlib>
#include <iomanip>

#include <malloc.h>

class Qlearning {
    public:
        Qlearning();
        int makeDecision(std::vector<int> *newState2, std::vector<bool>* board);
        void Reward(bool alive, std::vector<int> *nextstate);
        void saveQtable();
        void SetEpsilon(float newepsilon);
        void UpdateQtable(std::vector<int> *state, std::vector<bool>* board);
        nlohmann::json Qtable;
    private:
        double epsilon = 1;
        float reward;
        int action = 0;
        int action1, action2, action3, action4;
        std::vector<int> previousActions;
};

Qlearning::Qlearning() {
    std::ifstream f("Qtable.json");
    nlohmann::json data = nlohmann::json::parse(f);
    f.close();
    Qtable = data;
    // malloc_trim(0);
    // delete data;
    // data = NULL;
    
}

void Qlearning::UpdateQtable(std::vector<int>* state, std::vector<bool>* board) {

    // std::cout << std::to_string(state->at(0)) << "  " << state->at(0) << std::endl;
    for (int i=0; i < 9; i++) {
        if (!board->at(i)) {
            Qtable[std::to_string(state->at(0))][std::to_string(state->at(1))][std::to_string(state->at(2))][std::to_string(state->at(3))][std::to_string(state->at(4))][std::to_string(state->at(5))][std::to_string(state->at(6))][std::to_string(state->at(7))][std::to_string(state->at(8))][std::to_string(i)] = 0;
        } else {
            Qtable[std::to_string(state->at(0))][std::to_string(state->at(1))][std::to_string(state->at(2))][std::to_string(state->at(3))][std::to_string(state->at(4))][std::to_string(state->at(5))][std::to_string(state->at(6))][std::to_string(state->at(7))][std::to_string(state->at(8))][std::to_string(i)] = -100000000000;
        }
        // std::cout << Qtable[std::to_string(state->at(0))][std::to_string(state->at(1))][std::to_string(state->at(2))][std::to_string(state->at(3))][std::to_string(state->at(4))][std::to_string(state->at(5))][std::to_string(state->at(6))][std::to_string(state->at(7))][std::to_string(state->at(8))][std::to_string(i)] << "njweknjfwnjlf" << std::endl;
    }

    // delete state;
}

int Qlearning::makeDecision(std::vector<int>* newState2, std::vector<bool>* board) {
    // std::cout << "ja" << std::endl;
    std::vector<int> state = *newState2;
    // // std::vector<double> newState = *newState2;
    // // delete [] newState2;
    // for (int i=0; i < newState2->size(); i++) {
    //     float rounded = round(newState2->at(i) * 10)/10;
    //     // double x = std::setprecision(2) << rounded;
    //     state.push_back(rounded);
    //     // std::cout << std::to_string(rounded) << std::endl;
    // }
    // std::cout << "ja2" << std::endl;

    std::vector<int> actions;
    int val = 0;
    // std::vector<float>* stateP = new std::vector<float>(state);
    // std::cout << "ja3" << std::endl;

    if (!Qtable.contains(std::to_string(state.at(0)))) {
        UpdateQtable(newState2, board);
    } else if (!Qtable[std::to_string(state.at(0))].contains(std::to_string(state.at(1)))) {
        UpdateQtable(newState2, board);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))].contains(std::to_string(state.at(2)))) {
        UpdateQtable(newState2, board);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))].contains(std::to_string(state.at(3)))) {
        UpdateQtable(newState2, board);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))].contains(std::to_string(state.at(4)))) {
        UpdateQtable(newState2, board);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))].contains(std::to_string(state.at(5)))) {
        UpdateQtable(newState2, board);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))][std::to_string(state.at(5))].contains(std::to_string(state.at(6)))) {
        UpdateQtable(newState2, board);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))].contains(std::to_string(state.at(7)))) {
        UpdateQtable(newState2, board);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))].contains(std::to_string(state.at(8)))) {
        UpdateQtable(newState2, board);
    }
    // std::cout << Qtable[std::to_string(newState2->at(0))][std::to_string(newState2->at(1))][std::to_string(newState2->at(2))][std::to_string(newState2->at(3))][std::to_string(newState2->at(4))][std::to_string(newState2->at(5))][std::to_string(newState2->at(6))][std::to_string(newState2->at(7))][std::to_string(newState2->at(8))][std::to_string(0)].get<float>() << "nee" << std::endl;

    // delete stateP;
    
    double randval = rand() % 100;
    double randomdouble = randval/100;

    action4 = action3;
    action3 = action2;
    action2 = action1;
    action1 = action;
    action = 0;

    if (randomdouble <= epsilon) {
        bool actionloop = true;
        while (actionloop) {
            action = rand() % 9;
            if (!board->at(action)) {
                actionloop = false;
            }
        }
    } else {
        // std::cout << "ja4" << std::endl;

        // float value = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        //     [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(8)][std::to_string(0)].get<float>();
        float value = 0;
        // std::cout << "ja3" << std::endl;
        
        for (int i=0; i < board->size(); i++) {
            // std::cout << "ja5" << std::endl;

            if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))]
            [std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(state.at(8))][std::to_string(i)].get<float>() >= value && !board->at(i)) {
                // std::cout << "ja99" << std::endl;
                
                value = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(state.at(8))][std::to_string(i)].get<float>();
                action = i;
            } else {
                // std::cout << "ja66" << std::endl;
            }
        }
    }

    previousActions.clear();
    previousActions.push_back(action);
    previousActions.push_back(action1);
    previousActions.push_back(action2);
    previousActions.push_back(action3);
    previousActions.push_back(action4);

    // delete newState2;
    // newState2 = NULL;
    // std::cout << action << " ja 31" << std::endl;
    return action;
}

void Qlearning::Reward(bool alive, std::vector<int> *nextstate) {
    float alpha = 0.1;
    float gamma = 0.001;

    if (alive) {
        reward = -1;

        // std::vector<double> state;
        // for (int i=0; i < previousMove.size(); i++) {
        //     double rounded = round(previousMove.at(i) * 10)/10;
        //     state.push_back(rounded);
        // } 

        std::vector<int> state;
        for (int i=0; i < nextstate->size(); i++) {
            double rounded = nextstate->at(i);
            state.push_back(rounded);
        } 

        double value = Qtable[std::to_string(nextstate->at(0))][std::to_string(nextstate->at(1))][std::to_string(nextstate->at(2))][std::to_string(nextstate->at(3))]
        [std::to_string(nextstate->at(4))][std::to_string(nextstate->at(5))][std::to_string(nextstate->at(6))][std::to_string(nextstate->at(7))][std::to_string(nextstate->at(8))][std::to_string(0)].get<float>();
        int bestaction;
        for (int i=0; i < 4; i++) {
            if (Qtable[std::to_string(nextstate->at(0))][std::to_string(nextstate->at(1))][std::to_string(nextstate->at(2))][std::to_string(nextstate->at(3))]
            [std::to_string(nextstate->at(4))][std::to_string(nextstate->at(5))][std::to_string(nextstate->at(6))][std::to_string(nextstate->at(7))][std::to_string(nextstate->at(8))][std::to_string(i)].get<float>() >= value) {
                value = Qtable[std::to_string(nextstate->at(0))][std::to_string(nextstate->at(1))][std::to_string(nextstate->at(2))][std::to_string(nextstate->at(3))]
                [std::to_string(nextstate->at(4))][std::to_string(nextstate->at(5))][std::to_string(nextstate->at(6))][std::to_string(nextstate->at(7))][std::to_string(nextstate->at(8))][std::to_string(i)].get<float>();
                bestaction = i;
            } else {
            }
        }

        float uncalc = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))]
        [std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(state.at(8))][std::to_string(previousActions.at(0))].get<float>() + alpha 
        * (reward -5);
        float calc = round(uncalc * 1000)/1000;
        Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(state.at(8))][std::to_string(previousActions.at(0))] 
        = calc;

    } else if (!alive) {
        // std::vector<double> previousMove = previousStates->at(0);
        if (nextstate->size() == 9) {

            std::vector<int> state;
            for (int i=0; i < nextstate->size(); i++) {
                // double rounded = nextstate->at(i);
                state.push_back(nextstate->at(i));
            } 
            reward = 0.05;
            std::cout << previousActions.at(0) << std::endl;
            float uncalc = Qtable[std::to_string(nextstate->at(0))][std::to_string(nextstate->at(1))][std::to_string(nextstate->at(2))][std::to_string(nextstate->at(3))][std::to_string(nextstate->at(4))]
            [std::to_string(nextstate->at(5))][std::to_string(nextstate->at(6))][std::to_string(nextstate->at(7))][std::to_string(nextstate->at(8))][std::to_string(previousActions.at(0))].get<float>() + alpha 
            * (reward + gamma * Qtable[std::to_string(nextstate->at(0))][std::to_string(nextstate->at(1))][std::to_string(nextstate->at(2))][std::to_string(nextstate->at(3))]
            [std::to_string(nextstate->at(4))][std::to_string(nextstate->at(5))][std::to_string(nextstate->at(6))][std::to_string(nextstate->at(7))][std::to_string(nextstate->at(8))][std::to_string(previousActions.at(0))].get<float>()
            -Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))]
            [std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(state.at(8))][std::to_string(previousActions.at(0))].get<float>());
            // std::cout << "bhjklghcvbhj" << std::endl;
            float calc = round(uncalc * 1000)/1000;
            Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
            [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(state.at(8))][std::to_string(previousActions.at(0))] 
            = calc;
        } else {
        }
    }
}

void Qlearning::saveQtable() {
    std::ofstream testfile;
    testfile.open("Qtable.json");
    testfile << Qtable;
    testfile.close();
}   

void Qlearning::SetEpsilon(float newepsilon) {
    epsilon = newepsilon;
}
