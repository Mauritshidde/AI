#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <string>
#include <cstdlib>
#include <iomanip>

class Qlearning {
    public:
        Qlearning();
        int makeDecision(std::vector<double> state);
        void saveQtable();
        nlohmann::json Qtable;
    private:
        double epsilon = 0.9;
};

Qlearning::Qlearning() {
    std::ifstream f("Qtable.json");
    nlohmann::json data = nlohmann::json::parse(f);
    Qtable = data;
}

int Qlearning::makeDecision(std::vector<double> newState) {
    std::vector<double> state;
    for (int i=0; i < newState.size(); i++) {
        double rounded = round(newState.at(i) * 1000)/1000;
        // double x = std::setprecision(2) << rounded;
        state.push_back(rounded);
        std::cout << std::to_string(rounded) << std::endl;
    }
    std::vector<int> actions;
    int action = 0;
    double val = 0;
    if (!Qtable.contains(std::to_string(state.at(0)))) {
        std::cout << "hbdwkhjbqewfhbo kjwnbkjwef wonnjfw";
        Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"] = val;
        Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["1"] = val;
        Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["2"] = val;
        Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
        [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["3"] = val;
    } else if (Qtable.contains(std::to_string(state.at(0)))) {
        if (!Qtable[std::to_string(state.at(0))].contains(std::to_string(state.at(1)))) {
            std::cout << "hbdwkhjbqewfhbo kjwnbkjwef wonnjfw";
            Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
            [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"] = val;
            Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
            [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["1"] = val;
            Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
            [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["2"] = val;
            Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
            [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["3"] = val;
        }
    } else if (Qtable.contains(std::to_string(state.at(0)))) {
        if (Qtable[std::to_string(state.at(0))].contains(std::to_string(state.at(1)))) {
            if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))].contains(std::to_string(state.at(2)))) {
                std::cout << "hbdwkhjbqewfhbo kjwnbkjwef wonnjfw";
                Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"] = val;
                Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["1"] = val;
                Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["2"] = val;
                Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["3"] = val;
            }
        }
    } else if (Qtable.contains(std::to_string(state.at(0)))) {
        if (Qtable[std::to_string(state.at(0))].contains(std::to_string(state.at(1)))) {
            if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))].contains(std::to_string(state.at(2)))) {
                if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))].contains(std::to_string(state.at(3)))) {
                    std::cout << "hbdwkhjbqewfhbo kjwnbkjwef wonnjfw";
                    Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                    [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"] = val;
                    Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                    [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["1"] = val;
                    Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                    [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["2"] = val;
                    Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                    [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["3"] = val;
                }
            }
        }
    } else if (Qtable.contains(std::to_string(state.at(0)))) {
        if (Qtable[std::to_string(state.at(0))].contains(std::to_string(state.at(1)))) {
            if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))].contains(std::to_string(state.at(2)))) {
                if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))].contains(std::to_string(state.at(3)))) {
                    if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))].contains(std::to_string(state.at(4)))) {
                        std::cout << "hbdwkhjbqewfhbo kjwnbkjwef wonnjfw";
                        Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                        [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"] = val;
                        Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                        [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["1"] = val;
                        Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                        [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["2"] = val;
                        Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                        [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["3"] = val;
                    }
                }
            }
        }
    } else if (Qtable.contains(std::to_string(state.at(0)))) {
        if (Qtable[std::to_string(state.at(0))].contains(std::to_string(state.at(1)))) {
            if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))].contains(std::to_string(state.at(2)))) {
                if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))].contains(std::to_string(state.at(3)))) {
                    if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))].contains(std::to_string(state.at(4)))) {
                        if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))].contains(std::to_string(state.at(5)))) {
                            std::cout << "hbdwkhjbqewfhbo kjwnbkjwef wonnjfw";
                            Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                            [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"] = val;
                            Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                            [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["1"] = val;
                            Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                            [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["2"] = val;
                            Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                            [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["3"] = val;
                        }
                    }
                }
            }
        }
    } else if (Qtable.contains(std::to_string(state.at(0)))) {
        if (Qtable[std::to_string(state.at(0))].contains(std::to_string(state.at(1)))) {
            if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))].contains(std::to_string(state.at(2)))) {
                if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))].contains(std::to_string(state.at(3)))) {
                    if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))].contains(std::to_string(state.at(4)))) {
                        if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))].contains(std::to_string(state.at(5)))) {
                            if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))][std::to_string(state.at(5))].contains(std::to_string(state.at(6)))) {
                                std::cout << "hbdwkhjbqewfhbo kjwnbkjwef wonnjfw";
                                Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                                [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"] = val;
                                Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                                [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["1"] = val;
                                Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                                [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["2"] = val;
                                Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                                [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["3"] = val;
                            }
                        }
                    }
                }
            }
        }
    } else if (Qtable.contains(std::to_string(state.at(0)))) {
        if (Qtable[std::to_string(state.at(0))].contains(std::to_string(state.at(1)))) {
            if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))].contains(std::to_string(state.at(2)))) {
                if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))].contains(std::to_string(state.at(3)))) {
                    if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))].contains(std::to_string(state.at(4)))) {
                        if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))].contains(std::to_string(state.at(5)))) {
                            if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))][std::to_string(state.at(5))].contains(std::to_string(state.at(6)))) {
                                if (!Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))].contains(std::to_string(state.at(7)))) {
                                    std::cout << "hbdwkhjbqewfhbo kjwnbkjwef wonnjfw";
                                    Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                                    [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"] = val;
                                    Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                                    [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["1"] = val;
                                    Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                                    [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["2"] = val;
                                    Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
                                    [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["3"] = val;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    saveQtable();
    
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
    std::cout << " ja nee kaas" << std::endl;
    float test = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))][std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"].get<float>();
    std::cout << test <<  "avs ????????? "<< std::endl;
    std::cout << " ja nee kaas" << std::endl;

    // if (randomdouble <= epsilon) {
    //     action = rand() % 2;
    // } else {
    //     float value = -100;
    //     for (int i=0; i < 2; i++) {
    //         std::cout << "jasda dsad " << std::endl;
    //         if (Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
    //         [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"].get<float>() > value) {

    //             value = Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
    //             [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"].get<float>();

                
    //         std::cout << "jasda dsad " << std::endl;
            
    //         }
    //     }
    //     // actions.push_back(Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
    //     //     [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["0"]);
    //     // actions.push_back(Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
    //     //     [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["1"]);
    //     // actions.push_back(Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
    //     //     [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["2"]);
    //     // actions.push_back(Qtable[std::to_string(state.at(0))][std::to_string(state.at(1))][std::to_string(state.at(2))][std::to_string(state.at(3))]
    //     //     [std::to_string(state.at(4))][std::to_string(state.at(5))][std::to_string(state.at(6))][std::to_string(state.at(7))]["3"]);

    // }


    action = 1;
    return action;
}

void Qlearning::saveQtable() {
    std::ofstream testfile;
    testfile.open ("Qtable.json");
    testfile << Qtable;
    testfile.close();
}   