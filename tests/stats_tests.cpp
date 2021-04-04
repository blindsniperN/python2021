#include "gtest.h"
#include "../person/person.h"
#include "../person/factories.h"
using namespace stats_library;
TEST(Stats_Tests, Parameter_Test)
{
    try {
        short params[4];
        params[0] = 0; params[1] = 1; params[2] = 2; params[3] = 3;
        ParameterList parameterList(params);
        ASSERT_EQ(0, parameterList.charm_);
        ASSERT_EQ(1, parameterList.cunning_);
        ASSERT_EQ(2, parameterList.intelligence_);
        ASSERT_EQ(3, parameterList.will_);
    } catch {
        FAIL();
    }
}

TEST(Stats_Tests, Skill_Test)
{
    try {
        short params[4];
        params[0] = 0; params[1] = 1; params[2] = 2; params[3] = 3;
        ParameterList parameterList(params);
        short skills[10];
        for (short i = 0; i < 10; ++i) {
            skills[i] = i;
        }
        SkillList skillList(parameterList, skills);
        ASSERT_EQ(0, skillList.etiquette_.value_);
        ASSERT_EQ(1, skillList.people_understand_.value_);
        ASSERT_EQ(2, skillList.deception_.value_);
        ASSERT_EQ(3, skillList.gambling_.value_);
        ASSERT_EQ(4, skillList.leadership_.value_);
        ASSERT_EQ(5, skillList.charisma_.value_);
        ASSERT_EQ(6, skillList.persuasion_.value_);
        ASSERT_EQ(7, skillList.seduction_.value_);
        ASSERT_EQ(8, skillList.intimidation_.value_);
        ASSERT_EQ(9, skillList.persuasion_resist_.value_);

        ASSERT_EQ(parameterList.intelligence_.value_, skillList.etiquette_.parameter_.value_);
        ASSERT_EQ(parameterList.intelligence_.value_, skillList.people_understand_.parameter_.value_);
        ASSERT_EQ(parameterList.cunning_.value_, skillList.deception_.parameter_.value_);
        ASSERT_EQ(parameterList.cunning_.value_, skillList.gambling_.parameter_.value_);
        ASSERT_EQ(parameterList.cunning_.value_, skillList.leadership_.parameter_.value_);
        ASSERT_EQ(parameterList.charm_.value_, skillList.charisma_.parameter_.value_);
        ASSERT_EQ(parameterList.charm_.value_, skillList.persuasion_.parameter_.value_);
        ASSERT_EQ(parameterList.charm_.value_, skillList.seduction_.parameter_.value_);
        ASSERT_EQ(parameterList.will_.value_, skillList.intimidation_.parameter_.value_);
        ASSERT_EQ(parameterList.will_.value_, skillList.persuasion_resist_.parameter_.value_);
    } catch {
        FAIL();
    }
}

TEST(Stats_Tests, Formula_Test) {
    short params[4];
    params[0] = 0; params[1] = 1; params[2] = 2; params[3] = 3;
    ParameterList parameterList(params);
    parameterList.UpdateMaxDetermination();
    ASSERT_EQ(parameterList.max_determination_, 15);
}

