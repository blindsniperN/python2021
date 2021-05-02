#include "../person/person.cpp"
#include <windows.h>
#include <iostream>

/*
int main() {
  stats_library::ParameterList x;
  x.charm_.value_ = 10;
  x.intelligence_.value_ = 5;
  x.will_.value_ = 10;
  x.UpdateMaxDetermination();
  stats_library::SkillList sk (x);
  pers_class::Person pear ("Chanel", x, sk);
  for (int i = 0; i < 10; ++i)
    std::cout << pear.Seduce().to_hit << '\n';
  system("Color 07");

  std::cout << "Where are my cornnuts?!";
  system("Color 0C");
  return 0;
} */

void Dots(int n){
  for (int i = 0; i < n; ++i) {
    Sleep(500);
    std::cout << ".";
  }
}

int main(){
  // считываем всё из базы данных
  system("Color 0C");
  std::cout << "Oh hi! What r u doing? Actually, nevermind, you HAVE to help me!\n";

  system("Color 07");
  std::cout << "Do you want to start the game, or do you need some help?\n";
  Sleep(1000);
  system("Color 0C");
  std::cout << "Oh";
  Dots(3);
  std::cout << '\n';
  Sleep(1000);
  std::cout << "So I cannot hear you...\n";
  Sleep(1000);
  std::cout << "Then";
  for (int i = 0; i < 3; ++i) {
    Sleep(500);
    std::cout << ".";
  }
  std::cout << '\n';
  Sleep(1000);
  std::string s = "";
  while ((s != "START") and (s != "HELP")) {
    system("Color 07");
    std::cout << "Type START to start game and type HELP to get help!\n";
    system("Color 0C");
    std::cin >> s;

    if (s == "START") {
      std::cout << "So, dean Munch";
      Dots(3);
      std::cout << " You know her, right?\n";
      Sleep(1500);
      std::cout << "Yeah, she is THE dean of our faculty and THE bitch, who"
      << "wants to allow everyone into Kappa Kappa Tau!\n";
      Sleep(1500);
      std::cout << "THIS sorority is for pretty girls. ";
      Sleep(1000);
      std::cout << "Pretty girls, like you and me. \n";
      Sleep (1500);
      std::cout << "Now I have a plan to keep it that way, and YOU are a part"
      << " of that plan!\n";
      Sleep(2000);
      std::cout << "If dean Munch gets her way, Kappa's gonna be filled with"
      << " fatties and ethnics.\n";
      Sleep(1500);
      std::cout << "The fatties will bring their BIG old appetites, ";
      Sleep(1000);
      std::cout << "and you know what ethnics will bring with them?\n";
      Sleep(2000);
      std::cout << "Weird spices from their home countries.\n";
      Sleep(2000);
      std::cout << "That is a nuclear combination!\n";
      Sleep(1500);
      std::cout << "Weird ethnic spices will send the fatties "
      << "racing to the bathroom to blow liquid fire out of their huge swollen "
      << "bowels.\n";
      Sleep(1000);
      std::cout << "Think of the splash back.\n";
      Sleep(1000);
      std::cout << "Think of the undersides of all the toilets YOU'll have to"
      << " sanitize";
      Sleep(1000);
      std::cout << "I don't want that. ";
      Sleep(500);
      std::cout << "I don't want that for YOU.\n";
      // начало игры
    }
    else if (s == "HELP") { }
    else std::cout << "Are you stupid or something? Let's try one more fucking time!\n";
  }
}