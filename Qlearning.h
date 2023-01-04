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
        int makeDecision(std::vector<double> *newState2);
        void Reward(bool alive, std::vector<double> *previousStates);
        void saveQtable();
        void SetEpsilon(float newepsilon);
        void UpdateQtable(std::vector<float> *state);
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

void Qlearning::UpdateQtable(std::vector<float>* state) {
    for (int i=0; i < 4; i++) {
        // std::cout << std::to_string(state->at(0)) << "  " << state->at(0) << std::endl;
        Qtable[std::to_string(state->at(0))][std::to_string(state->at(1))][std::to_string(state->at(2))][std::to_string(state->at(3))][std::to_string(state->at(4))][std::to_string(state->at(5))][std::to_string(state->at(6))][std::to_string(state->at(7))][std::to_string(i)] = 0;
    }
    // delete state;
}

int Qlearning::makeDecision(std::vector<double> *newState2) {
    std::vector<float> state;
    // std::vector<double> newState = *newState2;
    // delete [] newState2;
    for (int i=0; i < newState2->size(); i++) {
        float rounded = round(newState2->at(i) * 10)/10;
        // double x = std::setprecision(2) << rounded;
        state.push_back(rounded);
        // std::cout << std::to_string(rounded) << std::endl;
    }
    std::vector<int> actions;
    int val = 0;
    std::vector<float>* stateP = new std::vector<float>(state);
    if (!Qtable.contains(std::to_string(state.at(0)))) {
        // nlohmann::json q = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        // [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))];
        // q["0"] = val;
        // q["1"] = val;
        // q["2"] = val;
        // q["3"] = val;
        UpdateQtable(stateP);
    } else if (!Qtable[std::to_string(state.at(0))].contains(std::to_string(state.at(1)))) {
        UpdateQtable(stateP);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))].contains(std::to_string(state.at(2)))) {
        UpdateQtable(stateP);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))].contains(std::to_string(state.at(3)))) {
        UpdateQtable(stateP);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))].contains(std::to_string(state.at(4)))) {
        UpdateQtable(stateP);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))].contains(std::to_string(state.at(5)))) {
        UpdateQtable(stateP);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))][std::to_string(state.at(5))].contains(std::to_string(state.at(6)))) {
        UpdateQtable(stateP);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))].contains(std::to_string(state.at(7)))) {
        UpdateQtable(stateP);
    }
    // std::cout << sizeof(stateP) <<"ja"<< std::endl;
    delete stateP;
    // std::cout << sizeof(stateP) << "nee" << std::endl;
    // stateP = NULL;
    // std::cout << stateP->size() << "nee2" << std::endl;
    // std::cout << stateP->size() << std::endl;
    
    // if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
    //     [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]) {


    // } else {
    //     Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
    //     [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"] = 0;
    //     Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
    //     [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["1"] = 0;
    //     Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
    //     [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["2"] = 0;
    //     Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
    //     [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["3"] = 0;
    // }
    
    double randval = rand() % 100;
    double randomdouble = randval/100;
    // saveQtable();
    // std::cout << " ja nee kaas" << std::endl;
    // float test = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"].get<float>();
    // std::cout << test <<  "avs ????????? "<< std::endl;
    // std::cout << " ja nee kaas" << std::endl;

    action4 = action3;
    action3 = action2;
    action2 = action1;
    action1 = action;

    if (randomdouble <= epsilon) {
        action = rand() % 4;
    } else {
        float value = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
            [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(0)].get<float>();
        for (int i=0; i < 4; i++) {
            if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
            [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(i)].get<float>() >= value) {
                value = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(i)].get<float>();
                // std::cout << value << "ja" << std::endl;
                action = i;
            } else {
                // std::cout << Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                // [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(i)].get<float>() << "nee" << std::endl; 
            }
        }
        // actions.push_back(Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        //     [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"]);
        // actions.push_back(Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        //     [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["1"]);
        // actions.push_back(Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        //     [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["2"]);
        // actions.push_back(Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        //     [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["3"]);
    }

    previousActions.clear();
    previousActions.push_back(action);
    previousActions.push_back(action1);
    previousActions.push_back(action2);
    previousActions.push_back(action3);
    previousActions.push_back(action4);

    // delete newState2;
    // newState2 = NULL;
    return action;
}

void Qlearning::Reward(bool alive, std::vector<double> *previousStates) {
    float alpha = 0.1;
    float gamma = 0.001;

    if (alive) {
        std::vector<double> nextstate;
        std::vector<double> previousMove = *previousStates;
        reward = 100;

        std::vector<double> state;
        for (int i=0; i < previousMove.size(); i++) {
            double rounded = round(previousMove.at(i) * 10)/10;
            state.push_back(rounded);
        } 
        for (int i=0; i < previousStates->size(); i++) {
            double rounded5 = round(previousStates->at(i) * 10)/10;
            nextstate.push_back(rounded5);
        }
        // double value = 0;
        double value = Qtable[std::to_string(nextstate.at(0))][std::to_string(nextstate.at(1))][std::to_string(nextstate.at(2))][std::to_string(nextstate.at(3))]
        [std::to_string(nextstate.at(4))][std::to_string(nextstate.at(5))][std::to_string(nextstate.at(6))][std::to_string(nextstate.at(7))][std::to_string(0)].get<float>();
        int bestaction = 0;
        for (int i=0; i < 4; i++) {
            // std::cout << nextstate.at(0) << " " << nextstate.at(1) << " " << nextstate.at(2) << " " << nextstate.at(3) << " " << nextstate.at(4) << " " << nextstate.at(5) << " " << nextstate.at(6) << " " << nextstate.at(7) << std::endl;
            if (Qtable[std::to_string(nextstate.at(0))][std::to_string(nextstate.at(1))][std::to_string(nextstate.at(2))][std::to_string(nextstate.at(3))]
            [std::to_string(nextstate.at(4))][std::to_string(nextstate.at(5))][std::to_string(nextstate.at(6))][std::to_string(nextstate.at(7))][std::to_string(i)].get<float>() >= value) {
                value = Qtable[std::to_string(nextstate.at(0))][std::to_string(nextstate.at(1))][std::to_string(nextstate.at(2))][std::to_string(nextstate.at(3))]
                [std::to_string(nextstate.at(4))][std::to_string(nextstate.at(5))][std::to_string(nextstate.at(6))][std::to_string(nextstate.at(7))][std::to_string(i)].get<float>();
                bestaction = i;
            }
        }

        float uncalc = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))]
        [std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(previousActions.at(0))].get<float>() + alpha 
        * (reward - gamma * 100 + Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))]
        [std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(previousActions.at(0))].get<float>());
        float calc = round(uncalc * 1000)/1000;
        Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(previousActions.at(0))] 
        = calc;
    } 
    else if (!alive) {
        std::vector<double> previousMove = *previousStates;
        reward = -100;

        std::vector<double> state;
        for (int i=0; i < previousMove.size(); i++) {
            double rounded = round(previousMove.at(i) * 10)/10;
            state.push_back(rounded);
        }

        std::vector<double> nextstate;
        
        for (int i=0; i < previousStates->size(); i++) {
            double rounded5 = round(previousStates->at(i) * 10)/10;
            nextstate.push_back(rounded5);
        }

        // Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        // [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(action)] = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        // [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(action)].get<float>() + 0.5 
        // * (reward + 0.5 * (reward + 0.5 * 25 - Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        // [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(action)].get<float>()));
        double valx;
        // if ((reward + gamma * Qtable[std::to_string(nextstate.at(0))][std::to_string(nextstate.at(1))][std::to_string(nextstate.at(2))][std::to_string(nextstate.at(3))]
        // [std::to_string(nextstate.at(4))][std::to_string(nextstate.at(5))][std::to_string(nextstate.at(6))][std::to_string(nextstate.at(7))][std::to_string(previousActions.at(0))].get<float>()
        // -Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))]
        // [std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(previousActions.at(0))].get<float>()) >= 0) {
        valx = (reward + gamma * 100 - Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))]
        [std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(previousActions.at(0))].get<float>());
        // } else {
        //     valx = -(reward + gamma * Qtable[std::to_string(nextstate.at(0))][std::to_string(nextstate.at(1))][std::to_string(nextstate.at(2))][std::to_string(nextstate.at(3))]
        //     [std::to_string(nextstate.at(4))][std::to_string(nextstate.at(5))][std::to_string(nextstate.at(6))][std::to_string(nextstate.at(7))][std::to_string(previousActions.at(0))].get<float>()
        //     -Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))]
        //     [std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(previousActions.at(0))].get<float>());    
        // }
        float uncalc = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))]
        [std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(previousActions.at(0))].get<float>() + alpha 
        * valx;
        float calc = round(uncalc * 1000)/1000;
        Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(previousActions.at(0))] 
        = calc;
    }
    // delete previousStates;
    // previousStates = NULL;
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
