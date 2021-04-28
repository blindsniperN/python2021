#pragma once
#include <string>
// В этом файле лежат все константы, важные для внутренних механик
// Как раз удовлетворяет отсутствию рандомных констант в коде
// Кроме того, если предполагать, что это реальный проект, то
// Можно будет очень легко модифицировать внутриигровую механику

// количество параметров и навыков
const int kParameterCount = 4;
const int kSkillCount = 10;

// максимальная сумма параметров
const int kProtagonistParameters = 20;
const int kAntagonistParameters = 25;

// максимальная сумма навыков
const int kProtagonistSkills = 40;
const int kAntagonistSkills = 45;

// кубик на попадание
const int kHitDice = 10;

// атаки
// соблазн
const int kSeduceDmgDice = 6;
const int kSeduceModifier = 2; // модификатор кумулятивного эффекта соблазнения

// привести довод
const int kArgumentDmgDice = 8;
const int kArgumentModifier = 1; // кумулятивный эффект довода

// убедить
const int kConvinceDmgDice = 6;

// обмануть
const int kDeceiveDmgDice = 12;
const int kDeceiveModifier = 2; // кумулятивный эффект обмана

// насмехнуться
const int kMockDmgDice = 6;
const int kMockModifier = 1; // кумулятивный эффект насмешки

// защиты
// игнорировать
const int kIgnoreDmgDice = 10;

// смены темы
const int kChangeThemeDmgDice = 6;

// рычаги
// любовь
const int kLoveModifier = 3;

// изучить

// намёк

// подкуп


//  количество атак
const int kAttackAmount = 5;
const int kDefenseAmount = 3;
const int kToolAmount = 4;

// названия таблиц
const std::string kProtagonistsTableName = "lol";
const std::string kAntagonistsTableName = "antagonists";