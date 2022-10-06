#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <string>
#include <cstdlib>
#include <iomanip>

class Qlearning {
    public:
        Qlearning();
        int makeDecision(std::vector<double> *newState2);
        void Reward(bool alive, std::vector<std::vector<double>> *previousStates);
        void saveQtable();
        void SetEpsilon(float newepsilon);
        void UpdateQtable(std::vector<float> *state);
        nlohmann::json Qtable;
    private:
        double epsilon = 0.9;
        float reward;
        int action = 0;
        int action1, action2, action3, action4;
        std::vector<int> previousActions;
};

Qlearning::Qlearning() {
    std::ifstream f("Qtable.json");
    nlohmann::json data = nlohmann::json::parse(f);
    Qtable = data;
}

void Qlearning::UpdateQtable(std::vector<float> *state) {
    Qtable[std::to_string(state->at(0))][std::to_string(state->at(1))][std::to_string(state->at(2))][std::to_string(state->at(3))]
    [std::to_string(state->at(4))][std::to_string(state->at(5))][std::to_string(state->at(6))][std::to_string(state->at(7))]["0"] = 0;
    Qtable[std::to_string(state->at(0))][std::to_string(state->at(1))][std::to_string(state->at(2))][std::to_string(state->at(3))]
    [std::to_string(state->at(4))][std::to_string(state->at(5))][std::to_string(state->at(6))][std::to_string(state->at(7))]["1"] = 0;
    Qtable[std::to_string(state->at(0))][std::to_string(state->at(1))][std::to_string(state->at(2))][std::to_string(state->at(3))]
    [std::to_string(state->at(4))][std::to_string(state->at(5))][std::to_string(state->at(6))][std::to_string(state->at(7))]["2"] = 0;
    Qtable[std::to_string(state->at(0))][std::to_string(state->at(1))][std::to_string(state->at(2))][std::to_string(state->at(3))]
    [std::to_string(state->at(4))][std::to_string(state->at(5))][std::to_string(state->at(6))][std::to_string(state->at(7))]["3"] = 0;
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
    if (!Qtable.contains(std::to_string(state.at(0)))) {
        // nlohmann::json q = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        // [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))];
        // q["0"] = val;
        // q["1"] = val;
        // q["2"] = val;
        // q["3"] = val;
        UpdateQtable(&state);
    } else if (!Qtable[std::to_string(state.at(0))].contains(std::to_string(state.at(1)))) {
        UpdateQtable(&state);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))].contains(std::to_string(state.at(2)))) {
        UpdateQtable(&state);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))].contains(std::to_string(state.at(3)))) {
        UpdateQtable(&state);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))].contains(std::to_string(state.at(4)))) {
        UpdateQtable(&state);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))].contains(std::to_string(state.at(5)))) {
        UpdateQtable(&state);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))][std::to_string(state.at(5))].contains(std::to_string(state.at(6)))) {
        UpdateQtable(&state);
    } else if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))].contains(std::to_string(state.at(7)))) {
        UpdateQtable(&state);
    }
    
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
    float test = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"].get<float>();
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


    return action;
}

void Qlearning::Reward(bool alive, std::vector<std::vector<double>> *previousStates) {
    float alpha = 0.1;
    float gamma = 0.001;

    if (alive) {
        std::vector<double> nextstate;
        for (int j=0; j < previousStates->size()-1; j++) {
            std::vector<double> previousMove = previousStates->at(j);
            if (previousMove.size() == 8 && j == 0) {
                // std::cout << " dood ";
                reward = -100;

                std::vector<double> state;
                for (int i=0; i < previousMove.size(); i++) {
                    double rounded = round(previousMove.at(i) * 10)/10;
                    state.push_back(rounded);
                } 
                if (j==0) {
                    for (int i=0; i < previousStates->at(5).size(); i++) {
                        double rounded5 = round(previousStates->at(5).at(i) * 10)/10;
                        nextstate.push_back(rounded5);
                    }
                } else {
                    for (int i=0; i < previousStates->at(j-1).size(); i++) {
                        double rounded5 = round(previousStates->at(5).at(i) * 10)/10;
                        nextstate.push_back(rounded5);
                    }
                }
                double value = Qtable[std::to_string(nextstate.at(0))][std::to_string(nextstate.at(1))][std::to_string(nextstate.at(2))][std::to_string(nextstate.at(3))]
                [std::to_string(nextstate.at(4))][std::to_string(nextstate.at(5))][std::to_string(nextstate.at(6))][std::to_string(nextstate.at(7))][std::to_string(0)].get<float>();
                int bestaction;
                for (int i=0; i < 4; i++) {
                    if (Qtable[std::to_string(nextstate.at(0))][std::to_string(nextstate.at(1))][std::to_string(nextstate.at(2))][std::to_string(nextstate.at(3))]
                    [std::to_string(nextstate.at(4))][std::to_string(nextstate.at(5))][std::to_string(nextstate.at(6))][std::to_string(nextstate.at(7))][std::to_string(i)].get<float>() >= value) {
                        value = Qtable[std::to_string(nextstate.at(0))][std::to_string(nextstate.at(1))][std::to_string(nextstate.at(2))][std::to_string(nextstate.at(3))]
                        [std::to_string(nextstate.at(4))][std::to_string(nextstate.at(5))][std::to_string(nextstate.at(6))][std::to_string(nextstate.at(7))][std::to_string(i)].get<float>();
                        // std::cout << value << "ja" << std::endl;
                        bestaction = i;
                    } else {
                        // std::cout << Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                        // [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(i)].get<float>() << "nee" << std::endl; 
                    }
                }

                // std::cout << Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                // [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(action)].get<float>() + 0.5 
                // * (reward + 0.5 * (reward + 0.5 * 25 - Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                // [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(action)].get<float>())) << std::endl;
                // std::cout << action << std::endl;
                Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(previousActions.at(0))] 
                = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))]
                [std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(previousActions.at(0))].get<float>() + alpha 
                * (reward -5);
                // std::cout << "ja";
            } else {
                // std::cout << "nijoda";
            }
        }
    } 
    else if (!alive) {
        std::vector<double> previousMove = previousStates->at(0);
        if (previousMove.size() == 8) {
            // std::cout << " alive ";

            reward = 5;

            std::vector<double> state;
            for (int i=0; i < previousMove.size(); i++) {
                double rounded = round(previousMove.at(i) * 10)/10;
                state.push_back(rounded);
            }

            std::vector<double> nextstate;
            
            for (int i=0; i < previousStates->at(5).size(); i++) {
                double rounded5 = round(previousStates->at(5).at(i) * 10)/10;
                nextstate.push_back(rounded5);
            }

            // std::cout << Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
            // [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(action)].get<float>() + 0.5 
            // * (reward + 0.5 * (reward + 0.5 * 25 - Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
            // [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(action)].get<float>())) << std::endl;

            // Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
            // [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(action)] = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
            // [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(action)].get<float>() + 0.5 
            // * (reward + 0.5 * (reward + 0.5 * 25 - Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
            // [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(action)].get<float>()));
            Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
            [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(previousActions.at(0))] 
            = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))]
            [std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(previousActions.at(0))].get<float>() + alpha 
            * (reward + gamma * Qtable[std::to_string(nextstate.at(0))][std::to_string(nextstate.at(1))][std::to_string(nextstate.at(2))][std::to_string(nextstate.at(3))]
            [std::to_string(nextstate.at(4))][std::to_string(nextstate.at(5))][std::to_string(nextstate.at(6))][std::to_string(nextstate.at(7))][std::to_string(previousActions.at(0))].get<float>()
            -Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))]
            [std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))][std::to_string(previousActions.at(0))].get<float>());
        } else {
            // std::cout << "nijoda";
        }
    }
}

void Qlearning::saveQtable() {
    std::ofstream testfile;
    testfile.open ("Qtable.json");
    testfile << Qtable;
    testfile.close();
}   

void Qlearning::SetEpsilon(float newepsilon) {
    epsilon = newepsilon;
    std::cout << epsilon;
}
