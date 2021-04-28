#pragma once
#include "settings.h"
#include "person/game_mechanics.h"
#include <vector>
#include <iostream>
#include "person/person.h"
#include "exceptions/exceptions.h"
using namespace stats_library;
void print(const std::vector<PersonContainer>& v) {
    for (int i = 0; i < v.size(); ++i) std::cout << v[i].getName() << '\n';
}

void Settings::Start() {
    bool ok = true;
    while (ok) {
        std::cout << "Welcome to settings! Select what you would like to change:\n";
        std::cout << "1. Create a new protagonist\n";
        std::cout << "2. Create a new antagonist\n";
        std::cout << "3. Edit an existing protagonist\n";
        std::cout << "4. Edit an existing antagonist\n";
        std::cout << "5. Exit settings\n";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:
                CreatePerson<true>();
                break;
            case 2:
                CreatePerson<false>();
                break;
            case 3: {
                std::string name;
                std::cout << "Who would you like to edit?\n";
                print(protagonists_->listAll());
                std::cin >> name;
                UpdatePerson<true>(name);
                break;
            }
            case 4: {
                std::string name;
                std::cout << "Who would you like to edit?\n";
                print(antagonists_->listAll());
                std::cin >> name;
                UpdatePerson<false>(name);
                break;
            }
            case 5:
                ok = false;
                break;
        }
    }

}


std::vector<short> readVector(int count) {
    std::vector<short> ans(count);
    for (int i = 0; i < count; ++i)
        std::cin >> ans[i];
    return ans;
}

int sum(const std::vector<short>& v) {
    int s = 0;
    for (auto i: v) s += i;
    return s;
}

std::vector<short> readVectorWithBoundary(int count, int boundary) {
    std::vector<short> data(count, 0);

    while (sum(data) == 0 || sum(data) > boundary) {
        for (int i = 0; i < count; ++i)
            std::cin >> data[i];

        if (sum(data) > boundary)
            std::cout << "You have exceeded the maximum amount possible (" + std::to_string(sum(data)) + ">" + std::to_string(boundary) + "). Reduce it.\n";
        else if (sum(data) < boundary) {
            std::cout << "You have unused points left over (" + std::to_string(boundary - sum(data)) + "). Are you sure you don't want to use them?\n";
            std::cout << "1. Change my choice\n";
            std::cout << "2. Leave it as it is\n";
            int choice;
            std::cin >> choice;
            if (choice == 1)
                data[0] = boundary + 1; // превышаем количество, чтобы пошло на еще одну итерацию
        }
    }
    return data;
}
template <bool IsProtagonist>
void Settings::CreatePerson() {
    int parameter_boundary, skill_boundary;
    std::string db_name;
    if (IsProtagonist) {
        parameter_boundary = kProtagonistParameters;
        skill_boundary = kProtagonistSkills;
        db_name = kProtagonistsTableName;
    } else {
        parameter_boundary = kAntagonistParameters;
        skill_boundary = kAntagonistSkills;
        db_name = kAntagonistsTableName;
    }

    std::string name;
    std::cout << "Enter the character's name (only one word names are allowed)\n";
    std::cin >> name;
    std::cout << "Enter the parameters separated by a space in the following order: Charm, Cunning, Intelligence, Will. Their sum must not exceed " + std::to_string(parameter_boundary) << '\n';
    std::vector<short> params = readVectorWithBoundary(kParameterCount, parameter_boundary);
    std::cout << "Enter the skills with a space in the following order: Etiquette, People Understanding, Deception, Gambling, Leadership, Charisma, Persuasion, Seduction, Intimidation, Resistance to Persuasion. Their sum must not exceed " + std::to_string(skill_boundary) << '\n';
    std::vector<short> skills = readVectorWithBoundary(kSkillCount, skill_boundary);
    std::cout << "Move on to setting up random attacks. ";
    int choice = 2;
    if (IsProtagonist) {
        std::cout << "Do you want to set them up? They can only be useful if you select the 'Random Attack' option during combat.\n";
        std::cout << "1. No, I don't want to set it up now\n";
        std::cout << "2. Yes, I do.\n";
        std::cin >> choice;
    } else std::cout << '\n';
    std::vector<short> att(kAttackAmount, 0);
    std::vector<short> def(kDefenseAmount, 0);
    std::vector<short> tools(kToolAmount, 0);
    if (choice == 2) {
        std::cout << "You need to enter integers, separated by a space. Their ratio will be the ratio of the probabilities of the actions.\n";
        std::cout << "Enter the attack probabilities in the following order: Seduce, Make An Argument, Convince, Deceive, Mock\n";
        att = readVector(kAttackAmount);
        std::cout << "Enter the defence probabilities in the following order: Ignore, Change Theme, Counterargument\n";
        def = readVector(kDefenseAmount);
        std::cout << "Enter the attack probabilities in the following order: Love, Research, Hint, Bribe\n";
        tools = readVector(kToolAmount);
    }
    ParameterList parameterList(params);
    SkillList skillList(parameterList, skills);
    PersonContainer new_person(name, parameterList, skillList, att, def, tools);
    bool ok = false;
    while (!ok)
        try {
            if (IsProtagonist) protagonists_->add(new_person);
            else antagonists_->add(new_person);
            std::cout << "The character has been successfully added to the database!\n";
            ok = true;
        } catch (AlreadyExists) {
            std::cout << "Oops... Turns out a character with that name already exists. Please enter another name.\n";
            std::cin >> name;
            new_person.setName(name);
        }
}

template <bool IsProtagonist>
void Settings::UpdatePerson(const std::string& name) {}