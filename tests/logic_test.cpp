//
// Created by Joaquina Daeron on 11/10/23.
//

#include <gtest/gtest.h>
#include "game.h"

using namespace joaquind;

class Testcase {
    std::vector<std::pair<const char *, Field>> v{{"Base field",       Field{}},
                                                  {"Field 20x20",      Field{20, 20}},
                                                  {"Incorrect field",  Field{0, 5}},
                                                  {"Non square field", Field{5, 10}}
    };

    std::string standard_field_in_string{"##############################\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "#                            #\n"
                                         "##############################"};

    std::string small_field_in_string{"#####\n"
                                      "#   #\n"
                                      "#   #\n"
                                      "#   #\n"
                                      "#####\n"};
};

TEST(Field, FieldBaseTest) {

}