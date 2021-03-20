#include "gtest.h"
#include "../person/person.h"
#include "../person/factories.h"
#include <vector>
using namespace pers_class;
using namespace stats_library;
TEST(Person_Tests, Factory_Test)
{
    try {
        Factory personFactory;
        short params[4];
        params[0] = 0; params[1] = 1; params[2] = 2; params[3] = 3;
        ParameterList parameterList(params);
        short skills[10];
        for (short i = 0; i < 10; ++i) {
            skills[i] = i;
        }
        SkillList skillList(parameterList, skills);
        std::vector<int> attack(6, 1);
        std::vector<int> defense(2, 1);
        std::vector<int> tools(4, 1);
        Person person = personFactory.createPerson("Test", parameterList, skillList, attack, defense, tools);
        // what do i do to check????????
    } catch {
        FAIL()
    }
}

TEST(Person_Tests, Roll_Tests) {
    try {
        Factory personFactory;
        short params[4];
        params[0] = 0; params[1] = 1; params[2] = 2; params[3] = 3;
        ParameterList parameterList(params);
        short skills[10];
        for (short i = 0; i < 10; ++i) {
            skills[i] = i;
        }
        SkillList skillList(parameterList, skills);
        std::vector<int> attack(6, 1);
        std::vector<int> defense(2, 1);
        std::vector<int> tools(4, 1);
        Person person = personFactory.createPerson("Test", parameterList, skillList, attack, defense, tools);
        // random checcks
        ASSERT_LE(person.RandomAttack(), 5);
        ASSERT_GE(person.RandomAttack(), 0);
        ASSERT_LE(person.RandomDefense(), 1);
        ASSERT_GE(person.RandomDefense(), 0);
        ASSERT_LE(person.RandomTool(), 3);
        ASSERT_GE(person.RandomTool(), 0);

        // roll checks

        // to_hit
        ASSERT_LE(person.Seduce().to_hit, 30);
        ASSERT_GE(person.Seduce().to_hit, 0);
        ASSERT_LE(person.MakeAnArgument().to_hit, 30);
        ASSERT_GE(person.MakeAnArgument().to_hit, 0);
        ASSERT_LE(person.Intimidate().to_hit, 30);
        ASSERT_GE(person.Intimidate().to_hit, 0);
        ASSERT_LE(person.Deceive().to_hit, 30);
        ASSERT_GE(person.Deceive().to_hit, 0);
        ASSERT_LE(person.Mock().to_hit, 30);
        ASSERT_GE(person.Mock().to_hit, 0);
        ASSERT_LE(person.Ignore().to_hit, 30);
        ASSERT_GE(person.Ignore().to_hit, 0);
        ASSERT_LE(person.ChangeTheme().to_hit, 30);
        ASSERT_GE(person.ChangeTheme().to_hit, 0);

        // dmg
        ASSERT_LE(person.Seduce().dmg, 30);
        ASSERT_GE(person.Seduce().dmg, 0);
        ASSERT_LE(person.MakeAnArgument().dmg, 30);
        ASSERT_GE(person.MakeAnArgument().dmg, 0);
        ASSERT_LE(person.Intimidate().dmg, 30);
        ASSERT_GE(person.Intimidate().dmg, 0);
        ASSERT_LE(person.Deceive().dmg, 30);
        ASSERT_GE(person.Deceive().dmg, 0);
        ASSERT_LE(person.Mock().dmg, 30);
        ASSERT_GE(person.Mock().dmg, 0);
        ASSERT_LE(person.Ignore().dmg, 30);
        ASSERT_GE(person.Ignore().dmg, 0);
        ASSERT_LE(person.ChangeTheme().dmg, 30);
        ASSERT_GE(person.ChangeTheme().dmg, 0);

        // tools check
        ASSERT_LE(person.Love(), 30);
        ASSERT_GE(person.Love(), 0);
        ASSERT_LE(person.Research(), 30);
        ASSERT_GE(person.Research(), 0);
        ASSERT_LE(person.Hint(), 30);
        ASSERT_GE(person.Hint(), 0);
        ASSERT_LE(person.Bribe(), 30);
        ASSERT_GE(person.Bribe(), 0);

    } catch {
        FAIL();
    }
}
TEST(Person_Tests, PrefixVector_Tests) {
    try {
        std::vector<int> attack(6, 1);
        PrefixVector prefixVector = attack;
        ASSERT_EQ(prefixVector.Sum(), 6);
        ASSERT_EQ(prefixVector.Index(2), 3);
    } catch {
        FAIL();
    }
}

