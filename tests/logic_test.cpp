//
// Created by Joaquina Daeron on 11/10/23.
//

#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>

#include "game.h"

using namespace joaquind;

class TestcaseField {
public:
    std::vector<std::pair<const char *, Field>> fields{
            {"Base field",       Field{}},
            {"Field 20x20",      Field{20, 20}},
            {"Incorrect field",  Field{0, 5}},
            {"Non square field", Field{5, 10}},
            {"Small 3x3 field",  Field{3, 3}},
            {"Max size field",   Field{100, 100}},
            {"Oversize field",   Field{150, 120}}
    };

    std::unordered_map<const char *, Field> transform_fields{
            {"3x3 field", Field(3, 3)},
            {"5x5 field", Field(5, 5)},
            {"3x4 field", Field(3, 4)},
            {"5x7 field", Field(5, 7)}

    };
    std::unordered_map<const char *, std::string> string_view_field{
            {"3x3 field", {
                                  "###\n"
                                  "# #\n"
                                  "###\n"
                          }},

            {"3x4 field", {       "####\n"
                                  "#  #\n"
                                  "####\n"}},

            {"5x5 field", {
                                  "#####\n"
                                  "#   #\n"
                                  "#   #\n"
                                  "#   #\n"
                                  "#####\n"
                          }},

            {"5x7 field", {       "#######\n"
                                  "#     #\n"
                                  "#     #\n"
                                  "#     #\n"
                                  "#######\n"}}
    };
};

/* ----------- FIELD_TESTS ----------- */

//TEST(Field, FieldConstructorTest) {
//    TestcaseField t;
//    std::vector<size_t> sizes{30, 30, 20, 20, 30, 30, 5, 10, 3, 3, 100, 100, 30, 30};
//    auto it{sizes.begin()};
//    for (auto &[name, field]: t.fields) {
//        EXPECT_EQ(*(it++), field.GetSize().first);
//        EXPECT_EQ(*(it++), field.GetSize().second);
//        for (auto i{0}; i < field.GetSize().first; ++i) {
//            for (auto j{0}; j < field.GetSize().second; ++j) {
//                if (i == 0 || j == 0 || i == field.GetSize().first - 1 || j == field.GetSize().second - 1)
//                    EXPECT_EQ(field.GetCell({i, j}), Field::kFieldType::BORDER);
//                else
//                    EXPECT_EQ(field.GetCell({i, j}), Field::kFieldType::FIELD);
//            }
//        }
//    }
//}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}