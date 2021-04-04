#pragma once
#include <string>
#include <iostream>
#include "phrases.h"

class SuccessPhrases: public Phrases {
 public:
  SuccessPhrases() {
    add("It’s not my fault you’re, like, in love with me or something!"); // mean girls
    add("That's why her hair is so big. It's full of secrets.");
    add("Raise your hand if you have ever been personally victimized by Regina George.");
    add("Dear Diary: My teen angst bullshit now has a body count."); // heathers
    add("Did you have a brain tumor for breakfast?");
    add("I just killed my best friend.");
    add("If you think I’m doing another suicide note you’re wrong!");
    add("You're a virgin who can't drive."); // clueless
    add("You're a full-on Monet. It’s like a painting, see? From far away, it’s okay, but up close it’s a big old mess.");
    add("Haven’t you heard? I’m the crazy bitch around here."); // gossip girl
    add("Whoever said money doesn't buy happiness didn't know where to shop.");
    add("Some people are simply better than others.");
    add("Do you have any idea the psychological torture that I have endured being nice to you?");
    add("Your methods of inquiry must be as tired as your hair.");
    add("How’s John, by the way? Were they able to sew his fingers back on?"); // vampire diaries
    add("The cute one's here.");
    add("I want to be a role model for all people. Even the ones who need makeup really badly."); // riverdale
    add("If you breathe, it's because I give you air.");
  }
};

class FailurePhrases: public Phrases {
 public:
  FailurePhrases() {
    add("I can't go out tonight. *fake coughs* I'm sick."); // mean girls
    add("Fuck me gently with a chainsaw!"); // heathers
    add("God, Veronica. My afterlife is so boring. If I have to sing Kumbaya one more time…");
    add("Grow up, Heather. Bulimia’s so ’87.");
    add("I shop, therefore I am.");
    add("Ugh, As if!"); // clueless
    add("Oh my God, I'm totally buggin!");
    add("It does not say R.S.V.P on the Statue of Liberty.");
    add("If you're going to be sad, you might as well be sad in Paris."); // gossip girl
    add("Now if you'll excuse me, I've got to go kill myself. Or max out my credit card, whichever comes first.");
    add("You honestly believe I don't have a Plan B?"); // vampire diaries
    add("Oh, I've missed it ... said no one ever.");
    add("You may think you're winning the battle, but I'll win the war."); // pretty little liars
    add("Who sharpened your tongue, little girl?");
    add("I think you're crazier than a serial killer on bath salts."); // riverdale
    add("You're welcome to challenge me. But you'll lose.");
  }
};
